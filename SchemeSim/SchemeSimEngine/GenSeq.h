#ifndef GenSeq_h
#define GenSeq_h

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>


using namespace std;


class GenSeq {
    public:
        enum value_T {VOID, NUMBER, STRING, SYMBOL, FUNC, LAMBDA, LIST};
        //             0      1       2       3      4      5      6

        GenSeq();
        GenSeq(double num_param);
        GenSeq(string str_param, bool _isRealString);
        GenSeq(string sym_param);
        typedef GenSeq (*Func)(const vector<GenSeq>&);
        GenSeq(Func fn);
        GenSeq(value_T valType);
        GenSeq(vector<GenSeq> list_param);
        
        value_T getValType() const;
        string getVal() const;
        Func getFuncPtr() const;
        vector<GenSeq> getList() const;

        void setValType(value_T t);
        void pushSeqFront(GenSeq s);
        void pushSeq(GenSeq s);
        void pushSeqList(vector<GenSeq> s);
        
        string printEvaluated();

    private:
        value_T valType;
        string val;

        Func fn;
        vector<GenSeq> list;

        string evalNumber();
        string evalList();
};

#endif
