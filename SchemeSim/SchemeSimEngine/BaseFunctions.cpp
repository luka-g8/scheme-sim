#include "BaseFunctions.h"

using namespace std;


GenSeq plus_op(const vector<GenSeq>& param) {
    double lhv = stod(param[0].getVal());
    for (vector<GenSeq>::const_iterator param_itr = param.begin() + 1; 
         param_itr != param.end(); param_itr++) {
        
        double rhv = stod(param_itr->getVal());
        lhv += rhv;
    }

    return GenSeq(lhv);
}

GenSeq minus_op(const vector<GenSeq>& param) {
    double lhv = stod(param[0].getVal());
    for (vector<GenSeq>::const_iterator param_itr = param.begin() + 1; 
         param_itr != param.end(); param_itr++) {

        double rhv = stod(param_itr->getVal());
        lhv -= rhv;
    }

    return GenSeq(lhv);
}

GenSeq multp_op(const vector<GenSeq>& param) {
    double lhv = stod(param[0].getVal());
    for (vector<GenSeq>::const_iterator param_itr = param.begin() + 1; 
         param_itr != param.end(); param_itr++) {

        double rhv = stod(param_itr->getVal());
        lhv *= rhv;
    }

    return GenSeq(lhv);
}

GenSeq div_op(const vector<GenSeq>& param) {
    double lhv = stod(param[0].getVal());
    for (vector<GenSeq>::const_iterator param_itr = param.begin() + 1; 
         param_itr != param.end(); param_itr++) {

        double divBy = stod(param_itr->getVal());
        if (divBy == 0) throw "Error_BaseFunctions: Dividing by ZERO";
        lhv /= divBy;
    }

    return GenSeq(lhv);
}

GenSeq less_cmp(const vector<GenSeq>& param) {
    for (vector<GenSeq>::const_iterator param_itr = param.begin(); 
         param_itr != param.end() - 1; param_itr++) {

        double lhv = stod(param_itr->getVal());
        double rhv = stod((param_itr + 1)->getVal());

        if (lhv >= rhv) return GenSeq("#f");
    }

    return GenSeq("#t");
}

GenSeq more_cmp(const vector<GenSeq>& param) {
    for (vector<GenSeq>::const_iterator param_itr = param.begin(); 
         param_itr != param.end() - 1; param_itr++) {

        double lhv = stod(param_itr->getVal());
        double rhv = stod((param_itr + 1)->getVal());

        if (lhv <= rhv) return GenSeq("#f");
    }

    return GenSeq("#t");
}

GenSeq less_or_equal(const vector<GenSeq>& param) {
    for (vector<GenSeq>::const_iterator param_itr = param.begin(); 
         param_itr != param.end() - 1; param_itr++) {

        double lhv = stod(param_itr->getVal());
        double rhv = stod((param_itr + 1)->getVal());

        if (lhv > rhv) return GenSeq("#f");
    }

    return GenSeq("#t");
}

GenSeq more_or_equal(const vector<GenSeq>& param) {
    for (vector<GenSeq>::const_iterator param_itr = param.begin(); 
         param_itr != param.end() - 1; param_itr++) {

        double lhv = stod(param_itr->getVal());
        double rhv = stod((param_itr + 1)->getVal());

        if (lhv < rhv) return GenSeq("#f");
    }

    return GenSeq("#t");
}


GenSeq abs(const vector<GenSeq>& param) {
    double val = stod(param[0].getVal());
    if (val < 0) val *= (-1);

    return GenSeq(val);
}

GenSeq mod(const vector<GenSeq>& param) {
    int lhv = stoi(param[0].getVal());
    int rhv = stoi(param[1].getVal());
    lhv %= rhv;

    return GenSeq(lhv);
}

GenSeq min(const vector<GenSeq>& param) {
    double curMin = stod(param[0].getVal());
    for (vector<GenSeq>::const_iterator param_itr = param.begin(); 
         param_itr != param.end() - 1; param_itr++) {

        double candMin = stod(param_itr->getVal());

        if (candMin < curMin) curMin = candMin;
    }

    return curMin;
}

GenSeq max(const vector<GenSeq>& param) {
    double curMax = stod(param[0].getVal());
    for (vector<GenSeq>::const_iterator param_itr = param.begin(); 
         param_itr != param.end() - 1; param_itr++) {

        double candMax = stod(param_itr->getVal());

        if (curMax < candMax) curMax = candMax;
    }

    return curMax;
}

GenSeq sqrt(const vector<GenSeq>& param) {
    double val = stod(param[0].getVal());

    return GenSeq(sqrt(val));
}


GenSeq isEqual(const vector<GenSeq>& param) {
    for (vector<GenSeq>::const_iterator param_itr = param.begin(); 
         param_itr != param.end() - 1; param_itr++) {

        if (param_itr->getValType() != (param_itr + 1)->getValType()) {
            return GenSeq("#f");

        } else if (param_itr->getValType() == GenSeq::NUMBER) {
            if (stod(param_itr->getVal()) != stod((param_itr + 1)->getVal())) {
                return GenSeq("#f");
            }

        } else if (param_itr->getValType() == GenSeq::SYMBOL) {
            if (param_itr->getVal() != (param_itr + 1)->getVal()) {
                return GenSeq("#f");
            }

        } else if (param_itr->getValType() == GenSeq::FUNC || 
                   param_itr->getValType() == GenSeq::LAMBDA) {
            if (param_itr->getFuncPtr() != (param_itr + 1)->getFuncPtr()) {
                return GenSeq("#f");
            }

        } else {
            return isEqual(param_itr->getList());
        }
    }

    return GenSeq("#t");
}

GenSeq isNumber(const vector<GenSeq>& param) {
    if (param[0].getValType() == GenSeq::NUMBER) {
        return GenSeq("#t");
    } else return GenSeq("#f");
}

GenSeq isSymbol(const vector<GenSeq>& param) {
    if (param[0].getValType() == GenSeq::SYMBOL) {
        return GenSeq("#t");
    } else return GenSeq("#f");
}

GenSeq isFunc(const vector<GenSeq>& param) {
    if (param[0].getValType() == GenSeq::FUNC) {
        return GenSeq("#t");
    } else return GenSeq("#f");
}

GenSeq isList(const vector<GenSeq>& param) {
    if (param[0].getValType() == GenSeq::LIST) {
        return GenSeq("#t");
    } else return GenSeq("#f");
}

GenSeq isNull(const vector<GenSeq>& param) {
    if (param[0].getValType() != GenSeq::LIST) {
        return GenSeq("#f");
    } else if (param[0].getList().size() == 0) {
        return GenSeq("#t");
    } else return GenSeq("#f");
}


GenSeq length(const vector<GenSeq>& param) {
    return param[0].getList().size();
}

GenSeq list(const vector<GenSeq>& param) {
    GenSeq consList(GenSeq::LIST);
    for (vector<GenSeq>::const_iterator param_itr = param.begin(); 
         param_itr != param.end(); param_itr++) {

        consList.pushSeq(*param_itr);
    }

    return consList;
}

GenSeq car(const vector<GenSeq>& param) {
    if (param[0].getValType() != GenSeq::LIST) {
        throw "ERROR_BaseFunctions: parameter isn't a LIST";
    }

    return param[0].getList()[0];
}

GenSeq cdr(const vector<GenSeq>& param) {
    if (param[0].getValType() != GenSeq::LIST) {
        throw "ERROR_BaseFunctions: parameter isn't a LIST";
    }

    GenSeq consList(GenSeq::LIST);
    for (int i = 1; i < param[0].getList().size(); i++) {
        consList.pushSeq(param[0].getList()[i]);
    }

    return consList;
}

GenSeq cons(const vector<GenSeq>& param) {
    if (param.size() < 2) {
        throw "ERROR_BaseFunctions: 'cons' has too few paramuments";
    }

    if (param.size() > 2) {
        throw "ERROR_BaseFunctions: 'cons' has too many paramuments";
    }

    GenSeq consList = param[1];
    consList.pushSeqFront(param[0]);
    return consList;
}

GenSeq append(const vector<GenSeq>& param) {
    GenSeq consList;
    for (vector<GenSeq>::const_iterator param_itr = param.begin(); 
         param_itr != param.end(); param_itr++) {

        consList.pushSeqList(param_itr->getList());
    }

    return GenSeq(consList);
}

GenSeq predApply(const vector<GenSeq>& param) {
    GenSeq::Func fn = param[0].getFuncPtr();
    vector<GenSeq> param_forFn = param[1].getList();
    return fn(param_forFn);
}

GenSeq predMap(const vector<GenSeq>& param) {
    GenSeq consList(GenSeq::LIST);
    for (int i = 0; i < param[1].getList().size(); i++) {
        
        GenSeq param_forMap(GenSeq::LIST);
        for (int j = 1; j < param.size(); j++) {
            param_forMap.pushSeq(param[j].getList()[i]);
        }

        vector<GenSeq> stepList;
        stepList.push_back(param[0]);
        stepList.push_back(param_forMap);
        consList.pushSeq(predApply(stepList));
    }

    return consList;
}


// 2
GenSeq caar(const vector<GenSeq>& param) { GenSeq stepHead = car(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdar(const vector<GenSeq>& param) { GenSeq stepHead = car(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }

GenSeq cadr(const vector<GenSeq>& param) { GenSeq stepHead = cdr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddr(const vector<GenSeq>& param) { GenSeq stepHead = cdr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
// \2

// 3
GenSeq caaar(const vector<GenSeq>& param) { GenSeq stepHead = caar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaar(const vector<GenSeq>& param) { GenSeq stepHead = caar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadar(const vector<GenSeq>& param) { GenSeq stepHead = cdar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddar(const vector<GenSeq>& param) { GenSeq stepHead = cdar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }

GenSeq caadr(const vector<GenSeq>& param) { GenSeq stepHead = cadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadr(const vector<GenSeq>& param) { GenSeq stepHead = cadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddr(const vector<GenSeq>& param) { GenSeq stepHead = cddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddr(const vector<GenSeq>& param) { GenSeq stepHead = cddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
// \3

// 4
GenSeq caaaar(const vector<GenSeq>& param) { GenSeq stepHead = caaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaar(const vector<GenSeq>& param) { GenSeq stepHead = caaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadar(const vector<GenSeq>& param) { GenSeq stepHead = cadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadar(const vector<GenSeq>& param) { GenSeq stepHead = cadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddar(const vector<GenSeq>& param) { GenSeq stepHead = cddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddar(const vector<GenSeq>& param) { GenSeq stepHead = cddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }

GenSeq caaadr(const vector<GenSeq>& param) { GenSeq stepHead = caadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadr(const vector<GenSeq>& param) { GenSeq stepHead = caadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadr(const vector<GenSeq>& param) { GenSeq stepHead = cdadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadr(const vector<GenSeq>& param) { GenSeq stepHead = cdadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddr(const vector<GenSeq>& param) { GenSeq stepHead = caddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddr(const vector<GenSeq>& param) { GenSeq stepHead = caddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddr(const vector<GenSeq>& param) { GenSeq stepHead = cdddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddr(const vector<GenSeq>& param) { GenSeq stepHead = cdddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
// \4

// 5
GenSeq caaaaar(const vector<GenSeq>& param) { GenSeq stepHead = caaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaaar(const vector<GenSeq>& param) { GenSeq stepHead = caaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadaar(const vector<GenSeq>& param) { GenSeq stepHead = cadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadaar(const vector<GenSeq>& param) { GenSeq stepHead = cadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddaar(const vector<GenSeq>& param) { GenSeq stepHead = cddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddaar(const vector<GenSeq>& param) { GenSeq stepHead = cddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaadar(const vector<GenSeq>& param) { GenSeq stepHead = caadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadar(const vector<GenSeq>& param) { GenSeq stepHead = caadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadar(const vector<GenSeq>& param) { GenSeq stepHead = cdadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadar(const vector<GenSeq>& param) { GenSeq stepHead = cdadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddar(const vector<GenSeq>& param) { GenSeq stepHead = caddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddar(const vector<GenSeq>& param) { GenSeq stepHead = caddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddar(const vector<GenSeq>& param) { GenSeq stepHead = cdddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddar(const vector<GenSeq>& param) { GenSeq stepHead = cdddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }

GenSeq caaaadr(const vector<GenSeq>& param) { GenSeq stepHead = caaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaadr(const vector<GenSeq>& param) { GenSeq stepHead = caaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadadr(const vector<GenSeq>& param) { GenSeq stepHead = cadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadadr(const vector<GenSeq>& param) { GenSeq stepHead = cadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddadr(const vector<GenSeq>& param) { GenSeq stepHead = cddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddadr(const vector<GenSeq>& param) { GenSeq stepHead = cddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaddr(const vector<GenSeq>& param) { GenSeq stepHead = caaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaddr(const vector<GenSeq>& param) { GenSeq stepHead = caaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadddr(const vector<GenSeq>& param) { GenSeq stepHead = cadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadddr(const vector<GenSeq>& param) { GenSeq stepHead = cadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddddr(const vector<GenSeq>& param) { GenSeq stepHead = cddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddddr(const vector<GenSeq>& param) { GenSeq stepHead = cddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
// \5

// 6
GenSeq caaaaaar(const vector<GenSeq>& param) { GenSeq stepHead = caaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaaaar(const vector<GenSeq>& param) { GenSeq stepHead = caaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadaaar(const vector<GenSeq>& param) { GenSeq stepHead = cadaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadaaar(const vector<GenSeq>& param) { GenSeq stepHead = cadaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddaaar(const vector<GenSeq>& param) { GenSeq stepHead = cddaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddaaar(const vector<GenSeq>& param) { GenSeq stepHead = cddaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaadaar(const vector<GenSeq>& param) { GenSeq stepHead = caadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadaar(const vector<GenSeq>& param) { GenSeq stepHead = caadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadaar(const vector<GenSeq>& param) { GenSeq stepHead = cdadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadaar(const vector<GenSeq>& param) { GenSeq stepHead = cdadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddaar(const vector<GenSeq>& param) { GenSeq stepHead = caddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddaar(const vector<GenSeq>& param) { GenSeq stepHead = caddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddaar(const vector<GenSeq>& param) { GenSeq stepHead = cdddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddaar(const vector<GenSeq>& param) { GenSeq stepHead = cdddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaadar(const vector<GenSeq>& param) { GenSeq stepHead = caaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaadar(const vector<GenSeq>& param) { GenSeq stepHead = caaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaadar(const vector<GenSeq>& param) { GenSeq stepHead = cdaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaadar(const vector<GenSeq>& param) { GenSeq stepHead = cdaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadadar(const vector<GenSeq>& param) { GenSeq stepHead = cadadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadadar(const vector<GenSeq>& param) { GenSeq stepHead = cadadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddadar(const vector<GenSeq>& param) { GenSeq stepHead = cddadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddadar(const vector<GenSeq>& param) { GenSeq stepHead = cddadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaddar(const vector<GenSeq>& param) { GenSeq stepHead = caaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaddar(const vector<GenSeq>& param) { GenSeq stepHead = caaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaddar(const vector<GenSeq>& param) { GenSeq stepHead = cdaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaddar(const vector<GenSeq>& param) { GenSeq stepHead = cdaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadddar(const vector<GenSeq>& param) { GenSeq stepHead = cadddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadddar(const vector<GenSeq>& param) { GenSeq stepHead = cadddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddddar(const vector<GenSeq>& param) { GenSeq stepHead = cddddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddddar(const vector<GenSeq>& param) { GenSeq stepHead = cddddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }

GenSeq caaaaadr(const vector<GenSeq>& param) { GenSeq stepHead = caaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaaadr(const vector<GenSeq>& param) { GenSeq stepHead = caaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadaadr(const vector<GenSeq>& param) { GenSeq stepHead = cadaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadaadr(const vector<GenSeq>& param) { GenSeq stepHead = cadaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddaadr(const vector<GenSeq>& param) { GenSeq stepHead = cddaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddaadr(const vector<GenSeq>& param) { GenSeq stepHead = cddaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaadadr(const vector<GenSeq>& param) { GenSeq stepHead = caadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadadr(const vector<GenSeq>& param) { GenSeq stepHead = caadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadadr(const vector<GenSeq>& param) { GenSeq stepHead = cdadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadadr(const vector<GenSeq>& param) { GenSeq stepHead = cdadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddadr(const vector<GenSeq>& param) { GenSeq stepHead = caddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddadr(const vector<GenSeq>& param) { GenSeq stepHead = caddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddadr(const vector<GenSeq>& param) { GenSeq stepHead = cdddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddadr(const vector<GenSeq>& param) { GenSeq stepHead = cdddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaaddr(const vector<GenSeq>& param) { GenSeq stepHead = caaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaaddr(const vector<GenSeq>& param) { GenSeq stepHead = caaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadaddr(const vector<GenSeq>& param) { GenSeq stepHead = cadaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadaddr(const vector<GenSeq>& param) { GenSeq stepHead = cadaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddaddr(const vector<GenSeq>& param) { GenSeq stepHead = cddaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddaddr(const vector<GenSeq>& param) { GenSeq stepHead = cddaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaadddr(const vector<GenSeq>& param) { GenSeq stepHead = caadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadddr(const vector<GenSeq>& param) { GenSeq stepHead = caadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadddr(const vector<GenSeq>& param) { GenSeq stepHead = cdadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadddr(const vector<GenSeq>& param) { GenSeq stepHead = cdadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddddr(const vector<GenSeq>& param) { GenSeq stepHead = caddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddddr(const vector<GenSeq>& param) { GenSeq stepHead = caddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddddr(const vector<GenSeq>& param) { GenSeq stepHead = cdddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddddr(const vector<GenSeq>& param) { GenSeq stepHead = cdddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
// \6

// 7
GenSeq caaaaaaar(const vector<GenSeq>& param) { GenSeq stepHead = caaaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaaaaar(const vector<GenSeq>& param) { GenSeq stepHead = caaaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaaaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaaaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadaaaar(const vector<GenSeq>& param) { GenSeq stepHead = cadaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadaaaar(const vector<GenSeq>& param) { GenSeq stepHead = cadaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddaaaar(const vector<GenSeq>& param) { GenSeq stepHead = cddaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddaaaar(const vector<GenSeq>& param) { GenSeq stepHead = cddaaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaadaaar(const vector<GenSeq>& param) { GenSeq stepHead = caadaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadaaar(const vector<GenSeq>& param) { GenSeq stepHead = caadaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdadaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdadaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddaaar(const vector<GenSeq>& param) { GenSeq stepHead = caddaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddaaar(const vector<GenSeq>& param) { GenSeq stepHead = caddaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdddaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddaaar(const vector<GenSeq>& param) { GenSeq stepHead = cdddaaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaadaar(const vector<GenSeq>& param) { GenSeq stepHead = caaadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaadaar(const vector<GenSeq>& param) { GenSeq stepHead = caaadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaadaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaadaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadadaar(const vector<GenSeq>& param) { GenSeq stepHead = cadadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadadaar(const vector<GenSeq>& param) { GenSeq stepHead = cadadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddadaar(const vector<GenSeq>& param) { GenSeq stepHead = cddadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddadaar(const vector<GenSeq>& param) { GenSeq stepHead = cddadaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaddaar(const vector<GenSeq>& param) { GenSeq stepHead = caaddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaddaar(const vector<GenSeq>& param) { GenSeq stepHead = caaddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaddaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaddaar(const vector<GenSeq>& param) { GenSeq stepHead = cdaddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadddaar(const vector<GenSeq>& param) { GenSeq stepHead = cadddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadddaar(const vector<GenSeq>& param) { GenSeq stepHead = cadddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddddaar(const vector<GenSeq>& param) { GenSeq stepHead = cddddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddddaar(const vector<GenSeq>& param) { GenSeq stepHead = cddddaar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaaadar(const vector<GenSeq>& param) { GenSeq stepHead = caaaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaaadar(const vector<GenSeq>& param) { GenSeq stepHead = caaaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaaadar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaaadar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadaadar(const vector<GenSeq>& param) { GenSeq stepHead = cadaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadaadar(const vector<GenSeq>& param) { GenSeq stepHead = cadaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddaadar(const vector<GenSeq>& param) { GenSeq stepHead = cddaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddaadar(const vector<GenSeq>& param) { GenSeq stepHead = cddaadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaadadar(const vector<GenSeq>& param) { GenSeq stepHead = caadadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadadar(const vector<GenSeq>& param) { GenSeq stepHead = caadadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadadar(const vector<GenSeq>& param) { GenSeq stepHead = cdadadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadadar(const vector<GenSeq>& param) { GenSeq stepHead = cdadadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddadar(const vector<GenSeq>& param) { GenSeq stepHead = caddadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddadar(const vector<GenSeq>& param) { GenSeq stepHead = caddadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddadar(const vector<GenSeq>& param) { GenSeq stepHead = cdddadar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddadar(const vector<GenSeq>& param) { GenSeq stepHead = cdddadar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaaddar(const vector<GenSeq>& param) { GenSeq stepHead = caaaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaaddar(const vector<GenSeq>& param) { GenSeq stepHead = caaaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaaddar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaaddar(const vector<GenSeq>& param) { GenSeq stepHead = cdaaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadaddar(const vector<GenSeq>& param) { GenSeq stepHead = cadaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadaddar(const vector<GenSeq>& param) { GenSeq stepHead = cadaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddaddar(const vector<GenSeq>& param) { GenSeq stepHead = cddaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddaddar(const vector<GenSeq>& param) { GenSeq stepHead = cddaddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaadddar(const vector<GenSeq>& param) { GenSeq stepHead = caadddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadddar(const vector<GenSeq>& param) { GenSeq stepHead = caadddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadddar(const vector<GenSeq>& param) { GenSeq stepHead = cdadddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadddar(const vector<GenSeq>& param) { GenSeq stepHead = cdadddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddddar(const vector<GenSeq>& param) { GenSeq stepHead = caddddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddddar(const vector<GenSeq>& param) { GenSeq stepHead = caddddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddddar(const vector<GenSeq>& param) { GenSeq stepHead = cdddddar(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddddar(const vector<GenSeq>& param) { GenSeq stepHead = cdddddar(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }

GenSeq caaaaaadr(const vector<GenSeq>& param) { GenSeq stepHead = caaaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaaaadr(const vector<GenSeq>& param) { GenSeq stepHead = caaaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaaaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaaaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadaaadr(const vector<GenSeq>& param) { GenSeq stepHead = cadaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadaaadr(const vector<GenSeq>& param) { GenSeq stepHead = cadaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddaaadr(const vector<GenSeq>& param) { GenSeq stepHead = cddaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddaaadr(const vector<GenSeq>& param) { GenSeq stepHead = cddaaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaadaadr(const vector<GenSeq>& param) { GenSeq stepHead = caadaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadaadr(const vector<GenSeq>& param) { GenSeq stepHead = caadaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdadaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdadaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddaadr(const vector<GenSeq>& param) { GenSeq stepHead = caddaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddaadr(const vector<GenSeq>& param) { GenSeq stepHead = caddaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdddaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddaadr(const vector<GenSeq>& param) { GenSeq stepHead = cdddaadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaadadr(const vector<GenSeq>& param) { GenSeq stepHead = caaadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaadadr(const vector<GenSeq>& param) { GenSeq stepHead = caaadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaadadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaadadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadadadr(const vector<GenSeq>& param) { GenSeq stepHead = cadadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadadadr(const vector<GenSeq>& param) { GenSeq stepHead = cadadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddadadr(const vector<GenSeq>& param) { GenSeq stepHead = cddadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddadadr(const vector<GenSeq>& param) { GenSeq stepHead = cddadadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaddadr(const vector<GenSeq>& param) { GenSeq stepHead = caaddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaddadr(const vector<GenSeq>& param) { GenSeq stepHead = caaddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaddadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaddadr(const vector<GenSeq>& param) { GenSeq stepHead = cdaddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadddadr(const vector<GenSeq>& param) { GenSeq stepHead = cadddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadddadr(const vector<GenSeq>& param) { GenSeq stepHead = cadddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddddadr(const vector<GenSeq>& param) { GenSeq stepHead = cddddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddddadr(const vector<GenSeq>& param) { GenSeq stepHead = cddddadr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaaaddr(const vector<GenSeq>& param) { GenSeq stepHead = caaaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaaaddr(const vector<GenSeq>& param) { GenSeq stepHead = caaaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaaaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaaaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadaaddr(const vector<GenSeq>& param) { GenSeq stepHead = cadaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadaaddr(const vector<GenSeq>& param) { GenSeq stepHead = cadaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddaaddr(const vector<GenSeq>& param) { GenSeq stepHead = cddaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddaaddr(const vector<GenSeq>& param) { GenSeq stepHead = cddaaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaadaddr(const vector<GenSeq>& param) { GenSeq stepHead = caadaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaadaddr(const vector<GenSeq>& param) { GenSeq stepHead = caadaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadadaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdadaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddadaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdadaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaddaddr(const vector<GenSeq>& param) { GenSeq stepHead = caddaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaddaddr(const vector<GenSeq>& param) { GenSeq stepHead = caddaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadddaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdddaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddddaddr(const vector<GenSeq>& param) { GenSeq stepHead = cdddaddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaadddr(const vector<GenSeq>& param) { GenSeq stepHead = caaadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaadddr(const vector<GenSeq>& param) { GenSeq stepHead = caaadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaadddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaadddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadadddr(const vector<GenSeq>& param) { GenSeq stepHead = cadadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadadddr(const vector<GenSeq>& param) { GenSeq stepHead = cadadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddadddr(const vector<GenSeq>& param) { GenSeq stepHead = cddadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddadddr(const vector<GenSeq>& param) { GenSeq stepHead = cddadddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caaaddddr(const vector<GenSeq>& param) { GenSeq stepHead = caaddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdaaddddr(const vector<GenSeq>& param) { GenSeq stepHead = caaddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq cadaddddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cddaddddr(const vector<GenSeq>& param) { GenSeq stepHead = cdaddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caadddddr(const vector<GenSeq>& param) { GenSeq stepHead = cadddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdadddddr(const vector<GenSeq>& param) { GenSeq stepHead = cadddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
GenSeq caddddddr(const vector<GenSeq>& param) { GenSeq stepHead = cddddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return car(stepTail); }
GenSeq cdddddddr(const vector<GenSeq>& param) { GenSeq stepHead = cddddddr(param); 
    vector<GenSeq> stepTail{stepHead}; return cdr(stepTail); }
// \7
