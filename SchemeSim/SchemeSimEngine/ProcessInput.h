#ifndef ProcessInput_h
#define ProcessInput_h

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>

using namespace std;


class ProcessInput {
    public:
        static string readProcTerminal(int& lineNum);
        static void readProcFile(string fileName, vector<string>& lines);
};

#endif
