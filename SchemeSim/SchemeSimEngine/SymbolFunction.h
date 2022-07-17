#ifndef SymbolFunction_h
#define SymbolFunction_h  

#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include "GenSeq.h"

using namespace std;

class SymbolFunction {
    public:
        SymbolFunction();
        SymbolFunction(vector<GenSeq> lambdaArgs, 
                       vector<GenSeq> lambdaArgVals, 
                       SymbolFunction* parent_symFn);

        void defineSymFn(string sym, GenSeq fn);
        unordered_map<string, GenSeq>* findReplace(string);
        
    private:
        unordered_map<string, GenSeq> symFn_data;
        SymbolFunction* parent_symFn;

        bool symbolIsDefined(const unordered_map<string, GenSeq>& symFn_data, const string& sym);
        unordered_map<string, GenSeq>* findInParent(const string& sym);
};

#endif
