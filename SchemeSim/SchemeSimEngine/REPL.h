#ifndef REPL_h
#define REPL_h

#include <stdlib.h>
#include <unordered_map>
#include "ProcessInput.h"
#include "ProcessLang.h"
#include "GenSeq.h"
#include "BaseFunctions.h"
#include "SymbolFunction.h"

using namespace std;


class REPL {
    public:
        static GenSeq evalLines(GenSeq seq, SymbolFunction* symFn);
        static void populate_s_fn(SymbolFunction* symFn);

        static void defineBaseFuncs(SymbolFunction* symFn);
        static void evalFromFile(SymbolFunction* symFn, bool defaultFile);
        static void evalFromTerminal(SymbolFunction& symFn);

    private:
        static GenSeq evalSymbol(GenSeq& seq, SymbolFunction* symFn);
        static GenSeq evalEval(GenSeq& seq, SymbolFunction* symFn);
        static GenSeq evalDefineNoLambda(GenSeq& seq, SymbolFunction* symFn);
        static GenSeq evalLambda(GenSeq& seq, SymbolFunction* symFn);
        static GenSeq evalQuote(GenSeq& seq, SymbolFunction* symFn);
        static GenSeq evalDefine(GenSeq& seq, SymbolFunction* symFn);
        static GenSeq evalListFn(GenSeq& seq, SymbolFunction* symFn);
};

#endif
