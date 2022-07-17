#include "ProcessLang.h"

using namespace std;


GenSeq ProcessLang::processLang(const string input) {
    // for string
    if (input.length() >= 2 && input[0] == '"' && 
        input[input.length() - 1] == '"') {
        
        string res = input.substr(1, input.length() - 1 - 1);
        return GenSeq(res, true);
    }
    // \for string

    deque<string> listSeq = deListInOrder(input);
    return processLangTree(listSeq);
}

int ProcessLang::upTo_lastIdx(const string input, const int cur_start_idx, 
                              deque<string>& listSeq) {
    int last_idx = cur_start_idx;
    while (last_idx < input.size() && input[last_idx] != ' ' && 
            input[last_idx] != '(' && input[last_idx] != ')') {

        last_idx++;
    }

    listSeq.push_back(input.substr(cur_start_idx, last_idx - cur_start_idx));
    return (last_idx - 1);
}

deque<string> ProcessLang::deListInOrder(const string input) {
    deque<string> listSeq;
    for (int cur_start_idx = 0; cur_start_idx < input.length(); cur_start_idx++) {
        while (input[cur_start_idx] == ' ') cur_start_idx++;

        if (input[cur_start_idx] == '(') {
            listSeq.push_back("(");

        } else if (input[cur_start_idx] == ')') {
            listSeq.push_back(")");

        } else {
            cur_start_idx = upTo_lastIdx(input, cur_start_idx, listSeq);
        }
    }

    return listSeq;
}

GenSeq ProcessLang::inQuote(deque<string>& listSeq) {
    int listBlc = 0;
    for (deque<string>::iterator curQuote = listSeq.begin(); 
            curQuote != listSeq.end(); curQuote++) {

        if (*curQuote == "(") listBlc++;
        if (*curQuote == ")") listBlc--;

        if (listBlc == 0) {
            listSeq.insert(curQuote, ")");
            break;
        }
    }

    listSeq.push_front("quote");
    listSeq.push_front("(");


    return processLangTree(listSeq);
}

GenSeq ProcessLang::toDo_eval(deque<string>& listSeq) {
    vector<GenSeq> listsInside;

    while (listSeq.front() != ")") {
        listsInside.push_back(processLangTree(listSeq));
    }

    listSeq.pop_front(); // "("

    return GenSeq(listsInside);
}

GenSeq ProcessLang::processLangTree(deque<string>& listSeq) {
    if (listSeq.size() == 0) throw "Error_ProcessLang:: Nothing To Evaluate";

    string curList = listSeq.front();
    listSeq.pop_front();

    if (curList == "'") { // quote, '
        return inQuote(listSeq);

    } else if (curList == "(") { // todo: eval
        return toDo_eval(listSeq);

    } else if (curList == ")") {
        throw "Error_ProcessLang: Too Many ')'";

    } else {
        string mask = "0.123456789";
        if (curList.find_first_not_of(mask) == string::npos) {
            return GenSeq(stod(curList));
        } else return GenSeq(curList);
    }
}
