#include "SymbolFunction.h"
 

SymbolFunction::SymbolFunction() {
    parent_symFn = NULL;
}

SymbolFunction::SymbolFunction(vector<GenSeq> lambdaArgs, 
                               vector<GenSeq> lambdaArgVals, 
                               SymbolFunction* parent_symFn) {

    this->parent_symFn = parent_symFn;                
    
    vector<GenSeq>::iterator curVal_itr = lambdaArgVals.begin();
    for (vector<GenSeq>::iterator curArg_itr = lambdaArgs.begin(); 
         curArg_itr != lambdaArgs.end(); curArg_itr++) {

        defineSymFn(curArg_itr->getVal(), *curVal_itr);
        curVal_itr++;
    }
}

bool SymbolFunction::symbolIsDefined(const unordered_map<string, GenSeq>& symFn_data, 
                                     const string& sym) {
    if (symFn_data.find(sym) == symFn_data.end()) {
        return false;
    } else return true;
}

unordered_map<string, GenSeq>* SymbolFunction::findInParent(const string& sym) {
    if (parent_symFn == NULL) {
        cout << "**" << sym << "** ";
        throw "ERROR_SymbolFunction: Symbol Doesn't Have Matching Function";
    } else return parent_symFn->findReplace(sym);
}


unordered_map<string, GenSeq>* SymbolFunction::findReplace(string sym) {
    if (symbolIsDefined(symFn_data, sym)) {
        return &symFn_data;
    }
    
    return findInParent(sym);
}

void SymbolFunction::defineSymFn(string sym, GenSeq fn) {
    if (symFn_data.find(sym) != symFn_data.end()) {
        symFn_data.erase(sym);
    }

    symFn_data.insert({sym, fn});
}
