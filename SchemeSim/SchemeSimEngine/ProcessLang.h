#ifndef ProcessLang_h
#define ProcessLang_h

#include <stdlib.h>
#include <deque>
#include <string>
#include "ProcessInput.h"
#include "GenSeq.h"

using namespace std;

class ProcessLang {
    public:
        static GenSeq processLang(const string input);
    private:
        static int upTo_lastIdx(const string input, const int cur_start_idx, deque<string>& listSeq);
        static deque<string> deListInOrder(const string input);
        static GenSeq inQuote(deque<string>& listSeq);
        static GenSeq toDo_eval(deque<string>& listSeq);
        static GenSeq processLangTree(deque<string>& tokens);
};

#endif
