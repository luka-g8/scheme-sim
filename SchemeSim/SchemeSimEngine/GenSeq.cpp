#include "GenSeq.h"

using namespace std;


GenSeq::GenSeq() {
    valType = VOID;
    val = "";
    fn = NULL;
};

GenSeq::GenSeq(double num_param) {
    valType = NUMBER;
    val = to_string(num_param);
    fn = NULL;
}

GenSeq::GenSeq(string str_param, bool _isRealString) {
    valType = STRING;
    this->val = str_param;
    fn = NULL;
}

GenSeq::GenSeq(string sym_param) {
    valType = SYMBOL;
    this->val = sym_param;
    fn = NULL;
}

GenSeq::GenSeq(Func fn) {
    valType = FUNC;
    val = "";
    this->fn = fn;   
}

GenSeq::GenSeq(value_T valType) {
    this->valType = valType;
    val = "";
    fn = NULL;
}

GenSeq::GenSeq(vector<GenSeq> list_param) {
    valType = LIST;
    val = "";
    list = list_param;
    fn = NULL;
}


GenSeq::value_T GenSeq::getValType() const {
    return valType;
}

string GenSeq::getVal() const {
    return val;
}

GenSeq::Func GenSeq::getFuncPtr() const {
    return fn;
}

vector<GenSeq> GenSeq::getList() const {
    return list;
}


void GenSeq::setValType(value_T t) {
    valType = t;
}

void GenSeq::pushSeqFront(GenSeq lst) {
    list.insert(list.begin(), lst);
}

void GenSeq::pushSeq(GenSeq lst) {
    list.push_back(lst);
}

void GenSeq::pushSeqList(vector<GenSeq> lst) {
    for (vector<GenSeq>::iterator cur_list_itr = lst.begin(); 
         cur_list_itr != lst.end(); cur_list_itr++) {

        list.push_back(*cur_list_itr);
    }
}

string GenSeq::evalNumber() {
    double valInD = stod(val);
    int valInInt = (int)valInD;

    if (valInD == valInInt) {
        return to_string(valInInt);
    } else return val;
}

string GenSeq::evalList() {
    string str_eval = "(";
    for (vector<GenSeq>::iterator cur_list_itr = list.begin(); 
         cur_list_itr != list.end(); cur_list_itr++) {

        string next_eval = cur_list_itr->printEvaluated();
        str_eval += next_eval;

        if (cur_list_itr != list.end() - 1) {
            str_eval += " ";
        }
    }

    if (str_eval[str_eval.length() - 1] == ' ') {
        str_eval = str_eval.substr(0, str_eval.length() - 1);
    }

    str_eval += ") ";

    return str_eval;
}


string GenSeq::printEvaluated() {
    if (valType == NUMBER) {
       return evalNumber();

    } else if (valType == STRING) {
        return val;

    } else if (valType == SYMBOL) {
        return val;

    } else if (valType == FUNC) {
        return "FUNC";

    } else if (valType == LAMBDA) {
        return "LAMBDA";

    } else { // LIST
        return evalList();
    }
}
