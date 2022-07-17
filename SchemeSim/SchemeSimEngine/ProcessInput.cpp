#include "ProcessInput.h"

using namespace std;


string ProcessInput::readProcTerminal(int& lineNum) {
    cout << "#|kawa:" << lineNum++ << "|# ";

    string fullLine = "";
    int listBlc = 0;
    bool first = true;
    while (true) {
        if (! first) {
            cout << "#|....." << lineNum++ << "|# ";
        }

        string line = "";
        getline(cin, line);


        // for string
        if (listBlc == 0 && line.length() > 0 && line[0] == '\"') {
            if (line.length() == 1) {
                throw "Error_ProcessInput:: String not properly ended";
            }

            if (line[line.length() - 1] == '\"') {
                if (line == "\"\"") return "";
                return line;
            } else {
                throw "Error_ProcessInput:: String not properly ended";
            }
        }
        // \for string

        // for lists
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '(') listBlc++;
            if (line[i] == ')') listBlc--;
        }

        if (! first) fullLine += " ";
        fullLine += line;
        first = false;

        if (listBlc == 0) break;
        // \for lists
    }

    if (fullLine == "(exit)")
        return "(exit)";
    else if (fullLine == "(df)")
        return "(df)";
    else if (fullLine == "(file)")
        return "(file)";
    else if (fullLine.find_first_not_of(" ") == string::npos)
        return "";
    else
        return fullLine;
}

int commentBeginIdx(string& line) {
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ';') {
            return i;
        }
    }

    return -1;
}

void ProcessInput::readProcFile(string fileName, vector<string>& fnLines) {
    // Open fileName
    ifstream inputFile (fileName.c_str());
    if (inputFile.fail()) {
        return;
    }

    // Extract fullLine from inputFile
    string fullLine = "";
    string curLine = "";
    while (!inputFile.eof()) {
        getline(inputFile, curLine);
        if (curLine != "" && curLine[0] == ';') {
            continue;
        }
        int cmtBeginIdx = commentBeginIdx(curLine);
        if (cmtBeginIdx != -1) {
            curLine = curLine.substr(0, cmtBeginIdx);
        }

        fullLine += curLine;
    }
    inputFile.close();

    // Populate fnLines from fullLine
    int lastBeginIdx = 0;
    int listBlc = 0;
    stack<string> endlStrs;
    for (int i = 0; i < fullLine.length(); i++) {
        // for string
        if (listBlc == 0 && lastBeginIdx <= i && fullLine[i] == '\"') {
            int strEndIdx = i + 1;
            while (true) {
                if (fullLine.length() <= strEndIdx) {
                    throw "Error_ProcessInput:: String not properly ended";
                }
                if (fullLine[strEndIdx] == '\\') {
                    if (fullLine.length() <= strEndIdx + 1) {
                        throw "Error_ProcessInput:: String not properly ended";
                    } else if (fullLine[strEndIdx + 1] == 'n') {
                        endlStrs.push("\"\n\"");
                        fullLine[strEndIdx] = '\"';
                        fullLine[strEndIdx + 1] = '\"';
                    }
                }
                if (fullLine[strEndIdx] == '\"') {
                    break;
                }

                strEndIdx++;
            }


            string str = fullLine.substr(i, strEndIdx - i + 1);
            if (str != "\"\"") fnLines.push_back(str);
            if (!endlStrs.empty()) {
                string curEndlStr = endlStrs.top();
                endlStrs.pop();
                fnLines.push_back(curEndlStr);
            }

            lastBeginIdx = strEndIdx + 1;
        }
        // \for string

        // for lists
        if (lastBeginIdx <= i) {
            if (fullLine[i] == '(') listBlc++;
            if (fullLine[i] == ')') listBlc--;

            if (listBlc == 0) {
                string curLine = fullLine.substr(lastBeginIdx, i - lastBeginIdx + 1);

                if (curLine[0] == '(') {
                    // firstQtFromFile
                    string spaceSt = "";
                    for (int qtIdx = lastBeginIdx-1; qtIdx >= 0; qtIdx--) {
                        if (fullLine[qtIdx] != ' ' && fullLine[qtIdx] != '\'') {
                            break;
                        }

                        if (fullLine[qtIdx] == ' ') {
                            spaceSt += " ";
                            continue;
                        }

                        if (fullLine[qtIdx] == '\'') {
                            curLine = "\'" + spaceSt + curLine;
                        }
                    }
                    // \firstQtFromFile

                    fnLines.push_back(curLine);
                }
        
                lastBeginIdx = i + 1;
            }
        }
        // \for lists

    }
}
