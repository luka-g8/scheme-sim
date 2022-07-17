#include "REPL.h"

using namespace std;


//A: private //**********************************************************************************//
GenSeq REPL::evalSymbol(GenSeq& seq, SymbolFunction* symFn) {
    string symVal = seq.getVal();
    if (symVal[0] == '\'') {
        string deQuoteSym = symVal.substr(1, symVal.length() - 1);
        return GenSeq(deQuoteSym);
    }

    unordered_map<string, GenSeq>* symFnTable_ptr = symFn->findReplace(symVal);
    return (*symFnTable_ptr)[symVal];
}

GenSeq REPL::evalEval(GenSeq& seq, SymbolFunction* symFn) {
    GenSeq res_step1 = evalLines(seq.getList()[1], symFn);
    GenSeq res_step2 = evalLines(res_step1, symFn);
    return res_step2;
}

GenSeq REPL::evalDefineNoLambda(GenSeq& seq, SymbolFunction* symFn) {
    GenSeq curSym = seq.getList()[1].getList()[0];
    GenSeq curFnLambda(GenSeq::LIST);

    GenSeq lambda("lambda");
    GenSeq args(GenSeq::LIST);
    for (int i = 1; i < seq.getList()[1].getList().size(); i++) {
        GenSeq curArg = seq.getList()[1].getList()[i];
        args.pushSeq(curArg);
    }
    GenSeq fn = seq.getList()[2];

    curFnLambda.pushSeq(lambda);
    curFnLambda.pushSeq(args);
    curFnLambda.pushSeq(fn);

    GenSeq curFn = evalLines(curFnLambda, symFn);
    symFn->defineSymFn(curSym.getVal(), curFn);
    return curFn;
}

GenSeq REPL::evalLambda(GenSeq& seq, SymbolFunction* symFn) {
    seq.setValType(GenSeq::LAMBDA);
    return seq;
}

GenSeq REPL::evalQuote(GenSeq& seq, SymbolFunction* symFn) {
    return seq.getList()[1];
}

GenSeq REPL::evalDefine(GenSeq& seq, SymbolFunction* symFn) {
    GenSeq curSym = seq.getList()[1];
    GenSeq curFnLambda = seq.getList()[2];

    GenSeq curFn = evalLines(curFnLambda, symFn);
    symFn->defineSymFn(curSym.getVal(), curFn);
    return curFn;
}

GenSeq REPL::evalListFn(GenSeq& seq, SymbolFunction* symFn) {
    GenSeq fn = evalLines(seq.getList()[0], symFn);

    vector<GenSeq> params;
    vector<GenSeq> paramSeq = seq.getList();
    for (int i = 1; i < paramSeq.size(); i++) {
        params.push_back(paramSeq[i]);
    }


    for (int i = 0; i < params.size(); i++) {
        params[i] = evalLines(params[i], symFn);
    }

    if (fn.getValType() == GenSeq::LAMBDA) {
        SymbolFunction lambda_symFn = SymbolFunction(fn.getList()[1].getList(), params, symFn);
        GenSeq res = evalLines(fn.getList()[2], &lambda_symFn);
        return res;

    } else if (fn.getValType() == GenSeq::FUNC) {
        return (fn.getFuncPtr())(params);
    } else return evalLines(fn, symFn);
}
//\A: private //**********************************************************************************//


GenSeq REPL::evalLines(GenSeq seq, SymbolFunction* symFn) {
    if (seq.getValType() == GenSeq::SYMBOL) {
        return evalSymbol(seq, symFn);

    } else if (seq.getValType() == GenSeq::NUMBER || 
               seq.getValType() == GenSeq::STRING || 
               seq.getList().size() == 0) {

        return seq;

    } else if (seq.getList()[0].getVal() == "eval") { // List
        return evalEval(seq, symFn);

    } else if (seq.getList()[0].getVal() == "define") { // List

        if (seq.getList()[1].getValType() == GenSeq::LIST) { // define without lambda
            return evalDefineNoLambda(seq, symFn);
        } else return evalDefine(seq, symFn); // define with lambda

    } else if (seq.getList()[0].getVal() == "lambda") {
        return evalLambda(seq, symFn);

    } else if (seq.getList()[0].getVal() == "quote") {
        return evalQuote(seq, symFn);

    } else if (seq.getList()[0].getVal() == "if") {
        if (evalLines(seq.getList()[1],symFn).getVal() == "#t") {
            return evalLines(seq.getList()[2],symFn);
        } else if (evalLines(seq.getList()[1],symFn).getVal() == "#f") {
            return evalLines(seq.getList()[3],symFn);
        } else return GenSeq();

    } else if (seq.getList()[0].getVal() == "and") {
        if (seq.getList().size() < 2) {
            throw "Syntax Error: Too Few Arguments";
        }
        for (int i = 1; i < seq.getList().size(); i++) {
            if (evalLines(seq.getList()[i],symFn).getVal() != "#t") {
                return GenSeq("#f");
            }
        }
        return GenSeq("#t");

    } else if (seq.getList()[0].getVal() == "or") {
        if (seq.getList().size() < 2) {
            throw "Syntax Error: Too Few Arguments";
        }
        for (int i = 1; i < seq.getList().size(); i++) {
            if (evalLines(seq.getList()[i],symFn).getVal() == "#t") {
                return GenSeq("#t");
            }
        }
        return GenSeq("#f");

    } else if (seq.getList()[0].getVal() == "not") {
        if (seq.getList().size() > 2) {
            throw "Syntax Error: Too Many Arguments";
        }
        if (evalLines(seq.getList()[1],symFn).getVal() == "#t") {
            return GenSeq("#f");
        }
        return GenSeq("#t");

    } else { // function // list
        return evalListFn(seq, symFn);
    }
}

void REPL::populate_s_fn(SymbolFunction* symFn) {
    symFn->defineSymFn("#t", GenSeq("#t"));
    symFn->defineSymFn("#f", GenSeq("#f"));
    symFn->defineSymFn("+", GenSeq(&plus_op));
    symFn->defineSymFn("plus", GenSeq(&plus_op));
    symFn->defineSymFn("-", GenSeq(&minus_op));
    symFn->defineSymFn("minus", GenSeq(&minus_op));
    symFn->defineSymFn("*", GenSeq(&multp_op));
    symFn->defineSymFn("multp", GenSeq(&multp_op));
    symFn->defineSymFn("/", GenSeq(&div_op));
    symFn->defineSymFn("div", GenSeq(&div_op));
    symFn->defineSymFn("=", GenSeq(&isEqual));
    symFn->defineSymFn("<", GenSeq(&less_cmp));
    symFn->defineSymFn(">", GenSeq(&more_cmp));
    symFn->defineSymFn("<=", GenSeq(&less_or_equal));
    symFn->defineSymFn(">=", GenSeq(&more_or_equal));

    symFn->defineSymFn("abs", GenSeq(&abs));
    symFn->defineSymFn("mod", GenSeq(&mod));
    symFn->defineSymFn("min", GenSeq(&min));
    symFn->defineSymFn("max", GenSeq(&max));
    symFn->defineSymFn("sqrt", GenSeq(&sqrt));

    symFn->defineSymFn("eqv?", GenSeq(&isEqual));
    symFn->defineSymFn("number?", GenSeq(&isNumber));
    symFn->defineSymFn("symbol?", GenSeq(&isSymbol));
    symFn->defineSymFn("func?", GenSeq(&isFunc));
    symFn->defineSymFn("list?", GenSeq(&isList));
    symFn->defineSymFn("null?", GenSeq(&isNull));

    symFn->defineSymFn("length", GenSeq(&length));
    symFn->defineSymFn("list", GenSeq(&list));
    symFn->defineSymFn("car", GenSeq(&car));
    symFn->defineSymFn("cdr", GenSeq(&cdr));
    symFn->defineSymFn("cons", GenSeq(&cons));
    symFn->defineSymFn("append", GenSeq(&append));
    symFn->defineSymFn("pred-apply", GenSeq(&predApply));
    symFn->defineSymFn("pred-map", GenSeq(&predMap));

    // 2
    symFn->defineSymFn("caar", GenSeq(&caar));
    symFn->defineSymFn("cdar", GenSeq(&cdar));

    symFn->defineSymFn("cadr", GenSeq(&cadr));
    symFn->defineSymFn("cddr", GenSeq(&cddr));
    // \2

    // 3
    symFn->defineSymFn("caaar", GenSeq(&caaar));
    symFn->defineSymFn("cdaar", GenSeq(&cdaar));
    symFn->defineSymFn("cadar", GenSeq(&cadar));
    symFn->defineSymFn("cddar", GenSeq(&cddar));

    symFn->defineSymFn("caadr", GenSeq(&caadr));
    symFn->defineSymFn("cdadr", GenSeq(&cdadr));
    symFn->defineSymFn("caddr", GenSeq(&caddr));
    symFn->defineSymFn("cdddr", GenSeq(&cdddr));
    // \3

    // 4
    symFn->defineSymFn("caaaar", GenSeq(&caaaar));
    symFn->defineSymFn("cdaaar", GenSeq(&cdaaar));
    symFn->defineSymFn("cadaar", GenSeq(&cadaar));
    symFn->defineSymFn("cddaar", GenSeq(&cddaar));
    symFn->defineSymFn("caadar", GenSeq(&caadar));
    symFn->defineSymFn("cdadar", GenSeq(&cdadar));
    symFn->defineSymFn("caddar", GenSeq(&caddar));
    symFn->defineSymFn("cdddar", GenSeq(&cdddar));

    symFn->defineSymFn("caaadr", GenSeq(&caaadr));
    symFn->defineSymFn("cdaadr", GenSeq(&cdaadr));
    symFn->defineSymFn("cadadr", GenSeq(&cadadr));
    symFn->defineSymFn("cddadr", GenSeq(&cddadr));
    symFn->defineSymFn("caaddr", GenSeq(&caaddr));
    symFn->defineSymFn("cdaddr", GenSeq(&cdaddr));
    symFn->defineSymFn("cadddr", GenSeq(&cadddr));
    symFn->defineSymFn("cddddr", GenSeq(&cddddr));
    // \4

    // 5
    symFn->defineSymFn("caaaaar", GenSeq(&caaaaar));
    symFn->defineSymFn("cdaaaar", GenSeq(&cdaaaar));
    symFn->defineSymFn("cadaaar", GenSeq(&cadaaar));
    symFn->defineSymFn("cddaaar", GenSeq(&cddaaar));
    symFn->defineSymFn("caadaar", GenSeq(&caadaar));
    symFn->defineSymFn("cdadaar", GenSeq(&cdadaar));
    symFn->defineSymFn("caddaar", GenSeq(&caddaar));
    symFn->defineSymFn("cdddaar", GenSeq(&cdddaar));
    symFn->defineSymFn("caaadar", GenSeq(&caaadar));
    symFn->defineSymFn("cdaadar", GenSeq(&cdaadar));
    symFn->defineSymFn("cadadar", GenSeq(&cadadar));
    symFn->defineSymFn("cddadar", GenSeq(&cddadar));
    symFn->defineSymFn("caaddar", GenSeq(&caaddar));
    symFn->defineSymFn("cdaddar", GenSeq(&cdaddar));
    symFn->defineSymFn("cadddar", GenSeq(&cadddar));
    symFn->defineSymFn("cddddar", GenSeq(&cddddar));

    symFn->defineSymFn("caaaadr", GenSeq(&caaaadr));
    symFn->defineSymFn("cdaaadr", GenSeq(&cdaaadr));
    symFn->defineSymFn("cadaadr", GenSeq(&cadaadr));
    symFn->defineSymFn("cddaadr", GenSeq(&cddaadr));
    symFn->defineSymFn("caadadr", GenSeq(&caadadr));
    symFn->defineSymFn("cdadadr", GenSeq(&cdadadr));
    symFn->defineSymFn("caddadr", GenSeq(&caddadr));
    symFn->defineSymFn("cdddadr", GenSeq(&cdddadr));
    symFn->defineSymFn("caaaddr", GenSeq(&caaaddr));
    symFn->defineSymFn("cdaaddr", GenSeq(&cdaaddr));
    symFn->defineSymFn("cadaddr", GenSeq(&cadaddr));
    symFn->defineSymFn("cddaddr", GenSeq(&cddaddr));
    symFn->defineSymFn("caadddr", GenSeq(&caadddr));
    symFn->defineSymFn("cdadddr", GenSeq(&cdadddr));
    symFn->defineSymFn("caddddr", GenSeq(&caddddr));
    symFn->defineSymFn("cdddddr", GenSeq(&cdddddr));
    // \5

    // 6
    symFn->defineSymFn("caaaaaar", GenSeq(&caaaaaar));
    symFn->defineSymFn("cdaaaaar", GenSeq(&cdaaaaar));
    symFn->defineSymFn("cadaaaar", GenSeq(&cadaaaar));
    symFn->defineSymFn("cddaaaar", GenSeq(&cddaaaar));
    symFn->defineSymFn("caadaaar", GenSeq(&caadaaar));
    symFn->defineSymFn("cdadaaar", GenSeq(&cdadaaar));
    symFn->defineSymFn("caddaaar", GenSeq(&caddaaar));
    symFn->defineSymFn("cdddaaar", GenSeq(&cdddaaar));
    symFn->defineSymFn("caaadaar", GenSeq(&caaadaar));
    symFn->defineSymFn("cdaadaar", GenSeq(&cdaadaar));
    symFn->defineSymFn("cadadaar", GenSeq(&cadadaar));
    symFn->defineSymFn("cddadaar", GenSeq(&cddadaar));
    symFn->defineSymFn("caaddaar", GenSeq(&caaddaar));
    symFn->defineSymFn("cdaddaar", GenSeq(&cdaddaar));
    symFn->defineSymFn("cadddaar", GenSeq(&cadddaar));
    symFn->defineSymFn("cddddaar", GenSeq(&cddddaar));
    symFn->defineSymFn("caaaadar", GenSeq(&caaaadar));
    symFn->defineSymFn("cdaaadar", GenSeq(&cdaaadar));
    symFn->defineSymFn("cadaadar", GenSeq(&cadaadar));
    symFn->defineSymFn("cddaadar", GenSeq(&cddaadar));
    symFn->defineSymFn("caadadar", GenSeq(&caadadar));
    symFn->defineSymFn("cdadadar", GenSeq(&cdadadar));
    symFn->defineSymFn("caddadar", GenSeq(&caddadar));
    symFn->defineSymFn("cdddadar", GenSeq(&cdddadar));
    symFn->defineSymFn("caaaddar", GenSeq(&caaaddar));
    symFn->defineSymFn("cdaaddar", GenSeq(&cdaaddar));
    symFn->defineSymFn("cadaddar", GenSeq(&cadaddar));
    symFn->defineSymFn("cddaddar", GenSeq(&cddaddar));
    symFn->defineSymFn("caadddar", GenSeq(&caadddar));
    symFn->defineSymFn("cdadddar", GenSeq(&cdadddar));
    symFn->defineSymFn("caddddar", GenSeq(&caddddar));
    symFn->defineSymFn("cdddddar", GenSeq(&cdddddar));

    symFn->defineSymFn("caaaaadr", GenSeq(&caaaaadr));
    symFn->defineSymFn("cdaaaadr", GenSeq(&cdaaaadr));
    symFn->defineSymFn("cadaaadr", GenSeq(&cadaaadr));
    symFn->defineSymFn("cddaaadr", GenSeq(&cddaaadr));
    symFn->defineSymFn("caadaadr", GenSeq(&caadaadr));
    symFn->defineSymFn("cdadaadr", GenSeq(&cdadaadr));
    symFn->defineSymFn("caddaadr", GenSeq(&caddaadr));
    symFn->defineSymFn("cdddaadr", GenSeq(&cdddaadr));
    symFn->defineSymFn("caaadadr", GenSeq(&caaadadr));
    symFn->defineSymFn("cdaadadr", GenSeq(&cdaadadr));
    symFn->defineSymFn("cadadadr", GenSeq(&cadadadr));
    symFn->defineSymFn("cddadadr", GenSeq(&cddadadr));
    symFn->defineSymFn("caaddadr", GenSeq(&caaddadr));
    symFn->defineSymFn("cdaddadr", GenSeq(&cdaddadr));
    symFn->defineSymFn("cadddadr", GenSeq(&cadddadr));
    symFn->defineSymFn("cddddadr", GenSeq(&cddddadr));
    symFn->defineSymFn("caaaaddr", GenSeq(&caaaaddr));
    symFn->defineSymFn("cdaaaddr", GenSeq(&cdaaaddr));
    symFn->defineSymFn("cadaaddr", GenSeq(&cadaaddr));
    symFn->defineSymFn("cddaaddr", GenSeq(&cddaaddr));
    symFn->defineSymFn("caadaddr", GenSeq(&caadaddr));
    symFn->defineSymFn("cdadaddr", GenSeq(&cdadaddr));
    symFn->defineSymFn("caddaddr", GenSeq(&caddaddr));
    symFn->defineSymFn("cdddaddr", GenSeq(&cdddaddr));
    symFn->defineSymFn("caaadddr", GenSeq(&caaadddr));
    symFn->defineSymFn("cdaadddr", GenSeq(&cdaadddr));
    symFn->defineSymFn("cadadddr", GenSeq(&cadadddr));
    symFn->defineSymFn("cddadddr", GenSeq(&cddadddr));
    symFn->defineSymFn("caaddddr", GenSeq(&caaddddr));
    symFn->defineSymFn("cdaddddr", GenSeq(&cdaddddr));
    symFn->defineSymFn("cadddddr", GenSeq(&cadddddr));
    symFn->defineSymFn("cddddddr", GenSeq(&cddddddr));
    // \6

    // 7
    symFn->defineSymFn("caaaaaaar", GenSeq(&caaaaaaar));
    symFn->defineSymFn("cdaaaaaar", GenSeq(&cdaaaaaar));
    symFn->defineSymFn("cadaaaaar", GenSeq(&cadaaaaar));
    symFn->defineSymFn("cddaaaaar", GenSeq(&cddaaaaar));
    symFn->defineSymFn("caadaaaar", GenSeq(&caadaaaar));
    symFn->defineSymFn("cdadaaaar", GenSeq(&cdadaaaar));
    symFn->defineSymFn("caddaaaar", GenSeq(&caddaaaar));
    symFn->defineSymFn("cdddaaaar", GenSeq(&cdddaaaar));
    symFn->defineSymFn("caaadaaar", GenSeq(&caaadaaar));
    symFn->defineSymFn("cdaadaaar", GenSeq(&cdaadaaar));
    symFn->defineSymFn("cadadaaar", GenSeq(&cadadaaar));
    symFn->defineSymFn("cddadaaar", GenSeq(&cddadaaar));
    symFn->defineSymFn("caaddaaar", GenSeq(&caaddaaar));
    symFn->defineSymFn("cdaddaaar", GenSeq(&cdaddaaar));
    symFn->defineSymFn("cadddaaar", GenSeq(&cadddaaar));
    symFn->defineSymFn("cddddaaar", GenSeq(&cddddaaar));
    symFn->defineSymFn("caaaadaar", GenSeq(&caaaadaar));
    symFn->defineSymFn("cdaaadaar", GenSeq(&cdaaadaar));
    symFn->defineSymFn("cadaadaar", GenSeq(&cadaadaar));
    symFn->defineSymFn("cddaadaar", GenSeq(&cddaadaar));
    symFn->defineSymFn("caadadaar", GenSeq(&caadadaar));
    symFn->defineSymFn("cdadadaar", GenSeq(&cdadadaar));
    symFn->defineSymFn("caddadaar", GenSeq(&caddadaar));
    symFn->defineSymFn("cdddadaar", GenSeq(&cdddadaar));
    symFn->defineSymFn("caaaddaar", GenSeq(&caaaddaar));
    symFn->defineSymFn("cdaaddaar", GenSeq(&cdaaddaar));
    symFn->defineSymFn("cadaddaar", GenSeq(&cadaddaar));
    symFn->defineSymFn("cddaddaar", GenSeq(&cddaddaar));
    symFn->defineSymFn("caadddaar", GenSeq(&caadddaar));
    symFn->defineSymFn("cdadddaar", GenSeq(&cdadddaar));
    symFn->defineSymFn("caddddaar", GenSeq(&caddddaar));
    symFn->defineSymFn("cdddddaar", GenSeq(&cdddddaar));
    symFn->defineSymFn("caaaaadar", GenSeq(&caaaaadar));
    symFn->defineSymFn("cdaaaadar", GenSeq(&cdaaaadar));
    symFn->defineSymFn("cadaaadar", GenSeq(&cadaaadar));
    symFn->defineSymFn("cddaaadar", GenSeq(&cddaaadar));
    symFn->defineSymFn("caadaadar", GenSeq(&caadaadar));
    symFn->defineSymFn("cdadaadar", GenSeq(&cdadaadar));
    symFn->defineSymFn("caddaadar", GenSeq(&caddaadar));
    symFn->defineSymFn("cdddaadar", GenSeq(&cdddaadar));
    symFn->defineSymFn("caaadadar", GenSeq(&caaadadar));
    symFn->defineSymFn("cdaadadar", GenSeq(&cdaadadar));
    symFn->defineSymFn("cadadadar", GenSeq(&cadadadar));
    symFn->defineSymFn("cddadadar", GenSeq(&cddadadar));
    symFn->defineSymFn("caaddadar", GenSeq(&caaddadar));
    symFn->defineSymFn("cdaddadar", GenSeq(&cdaddadar));
    symFn->defineSymFn("cadddadar", GenSeq(&cadddadar));
    symFn->defineSymFn("cddddadar", GenSeq(&cddddadar));
    symFn->defineSymFn("caaaaddar", GenSeq(&caaaaddar));
    symFn->defineSymFn("cdaaaddar", GenSeq(&cdaaaddar));
    symFn->defineSymFn("cadaaddar", GenSeq(&cadaaddar));
    symFn->defineSymFn("cddaaddar", GenSeq(&cddaaddar));
    symFn->defineSymFn("caadaddar", GenSeq(&caadaddar));
    symFn->defineSymFn("cdadaddar", GenSeq(&cdadaddar));
    symFn->defineSymFn("caddaddar", GenSeq(&caddaddar));
    symFn->defineSymFn("cdddaddar", GenSeq(&cdddaddar));
    symFn->defineSymFn("caaadddar", GenSeq(&caaadddar));
    symFn->defineSymFn("cdaadddar", GenSeq(&cdaadddar));
    symFn->defineSymFn("cadadddar", GenSeq(&cadadddar));
    symFn->defineSymFn("cddadddar", GenSeq(&cddadddar));
    symFn->defineSymFn("caaddddar", GenSeq(&caaddddar));
    symFn->defineSymFn("cdaddddar", GenSeq(&cdaddddar));
    symFn->defineSymFn("cadddddar", GenSeq(&cadddddar));
    symFn->defineSymFn("cddddddar", GenSeq(&cddddddar));

    symFn->defineSymFn("caaaaaadr", GenSeq(&caaaaaadr));
    symFn->defineSymFn("cdaaaaadr", GenSeq(&cdaaaaadr));
    symFn->defineSymFn("cadaaaadr", GenSeq(&cadaaaadr));
    symFn->defineSymFn("cddaaaadr", GenSeq(&cddaaaadr));
    symFn->defineSymFn("caadaaadr", GenSeq(&caadaaadr));
    symFn->defineSymFn("cdadaaadr", GenSeq(&cdadaaadr));
    symFn->defineSymFn("caddaaadr", GenSeq(&caddaaadr));
    symFn->defineSymFn("cdddaaadr", GenSeq(&cdddaaadr));
    symFn->defineSymFn("caaadaadr", GenSeq(&caaadaadr));
    symFn->defineSymFn("cdaadaadr", GenSeq(&cdaadaadr));
    symFn->defineSymFn("cadadaadr", GenSeq(&cadadaadr));
    symFn->defineSymFn("cddadaadr", GenSeq(&cddadaadr));
    symFn->defineSymFn("caaddaadr", GenSeq(&caaddaadr));
    symFn->defineSymFn("cdaddaadr", GenSeq(&cdaddaadr));
    symFn->defineSymFn("cadddaadr", GenSeq(&cadddaadr));
    symFn->defineSymFn("cddddaadr", GenSeq(&cddddaadr));
    symFn->defineSymFn("caaaadadr", GenSeq(&caaaadadr));
    symFn->defineSymFn("cdaaadadr", GenSeq(&cdaaadadr));
    symFn->defineSymFn("cadaadadr", GenSeq(&cadaadadr));
    symFn->defineSymFn("cddaadadr", GenSeq(&cddaadadr));
    symFn->defineSymFn("caadadadr", GenSeq(&caadadadr));
    symFn->defineSymFn("cdadadadr", GenSeq(&cdadadadr));
    symFn->defineSymFn("caddadadr", GenSeq(&caddadadr));
    symFn->defineSymFn("cdddadadr", GenSeq(&cdddadadr));
    symFn->defineSymFn("caaaddadr", GenSeq(&caaaddadr));
    symFn->defineSymFn("cdaaddadr", GenSeq(&cdaaddadr));
    symFn->defineSymFn("cadaddadr", GenSeq(&cadaddadr));
    symFn->defineSymFn("cddaddadr", GenSeq(&cddaddadr));
    symFn->defineSymFn("caadddadr", GenSeq(&caadddadr));
    symFn->defineSymFn("cdadddadr", GenSeq(&cdadddadr));
    symFn->defineSymFn("caddddadr", GenSeq(&caddddadr));
    symFn->defineSymFn("cdddddadr", GenSeq(&cdddddadr));
    symFn->defineSymFn("caaaaaddr", GenSeq(&caaaaaddr));
    symFn->defineSymFn("cdaaaaddr", GenSeq(&cdaaaaddr));
    symFn->defineSymFn("cadaaaddr", GenSeq(&cadaaaddr));
    symFn->defineSymFn("cddaaaddr", GenSeq(&cddaaaddr));
    symFn->defineSymFn("caadaaddr", GenSeq(&caadaaddr));
    symFn->defineSymFn("cdadaaddr", GenSeq(&cdadaaddr));
    symFn->defineSymFn("caddaaddr", GenSeq(&caddaaddr));
    symFn->defineSymFn("cdddaaddr", GenSeq(&cdddaaddr));
    symFn->defineSymFn("caaadaddr", GenSeq(&caaadaddr));
    symFn->defineSymFn("cdaadaddr", GenSeq(&cdaadaddr));
    symFn->defineSymFn("cadadaddr", GenSeq(&cadadaddr));
    symFn->defineSymFn("cddadaddr", GenSeq(&cddadaddr));
    symFn->defineSymFn("caaddaddr", GenSeq(&caaddaddr));
    symFn->defineSymFn("cdaddaddr", GenSeq(&cdaddaddr));
    symFn->defineSymFn("cadddaddr", GenSeq(&cadddaddr));
    symFn->defineSymFn("cddddaddr", GenSeq(&cddddaddr));
    symFn->defineSymFn("caaaadddr", GenSeq(&caaaadddr));
    symFn->defineSymFn("cdaaadddr", GenSeq(&cdaaadddr));
    symFn->defineSymFn("cadaadddr", GenSeq(&cadaadddr));
    symFn->defineSymFn("cddaadddr", GenSeq(&cddaadddr));
    symFn->defineSymFn("caadadddr", GenSeq(&caadadddr));
    symFn->defineSymFn("cdadadddr", GenSeq(&cdadadddr));
    symFn->defineSymFn("caddadddr", GenSeq(&caddadddr));
    symFn->defineSymFn("cdddadddr", GenSeq(&cdddadddr));
    symFn->defineSymFn("caaaddddr", GenSeq(&caaaddddr));
    symFn->defineSymFn("cdaaddddr", GenSeq(&cdaaddddr));
    symFn->defineSymFn("cadaddddr", GenSeq(&cadaddddr));
    symFn->defineSymFn("cddaddddr", GenSeq(&cddaddddr));
    symFn->defineSymFn("caadddddr", GenSeq(&caadddddr));
    symFn->defineSymFn("cdadddddr", GenSeq(&cdadddddr));
    symFn->defineSymFn("caddddddr", GenSeq(&caddddddr));
    symFn->defineSymFn("cdddddddr", GenSeq(&cdddddddr));
    // \7
}


void REPL::defineBaseFuncs(SymbolFunction* symFn) {
    vector<GenSeq> res;
    bool forceEndl = false;
    try {
        string fileName = "DefineBaseFuncs.scm"; // default
        cout << "  &&|Evaluating|&&: \"" << fileName << "\"" << endl; // Hide DBF
        vector<string> fnLines;
        ProcessInput::readProcFile(fileName, fnLines);
        if (fnLines.size() == 0) {
            cout << "  File is empty" << endl; // Hide DBF
            return;
        }

        for (int i = 0; i < fnLines.size(); i++) {
            GenSeq curParsedFnLine = ProcessLang::processLang(fnLines[i]);
            GenSeq curRes = evalLines(curParsedFnLine, symFn);
            res.push_back(curRes);
        }

        GenSeq lastGL = res[res.size() - 1];
        if (lastGL.getValType() == GenSeq::STRING && 
            lastGL.getVal() != "\"\n\"") {
            forceEndl = true;
        }

    } catch (const char* errCode) {
        cerr << errCode << endl;
        return;
    } catch (...) {
        cerr << "  Error_Kawa:: Unknown Error" << endl;
    }

    // A : Hide DBF
    for (int i = 0; i < res.size(); i++) {
        cout << "  " << res[i].printEvaluated();
    
        if (res[i].getValType() != GenSeq::STRING) {
            cout << endl;
        }

        if (i == (res.size() - 1) && forceEndl) {
            cout << endl;
        }
    }

    cout << endl;
    cout << "<<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>>" << endl << endl;
    // \A : Hide DBF
}

void REPL::evalFromFile(SymbolFunction* symFn, bool defaultFile) {
    vector<GenSeq> res;
    bool forceEndl = false;
    try {
        string fileName = "input_default.scm"; // default
        if (! defaultFile) {
            cout << "&&|File_Path|&&: ";
            getline(cin, fileName); // "cin >> ..." has duplicate 
                                    // output side effect.

            if (fileName.length() > 2 && fileName[0] == '\"' && 
                fileName[fileName.length()-1] == '\"') {
                
                fileName = fileName.substr(1, fileName.length()-2 -1 +1);
            } else {
                throw "Error_Kawa:: File name String has invalid format";
            }
        }
        cout << "&&|Evaluating|&&: \"" << fileName << "\"" << endl;
        vector<string> fnLines;
        ProcessInput::readProcFile(fileName, fnLines);
        if (fnLines.size() == 0) {
            cout << "File is empty" << endl;
            return;
        }

        for (int i = 0; i < fnLines.size(); i++) {
            GenSeq curParsedFnLine = ProcessLang::processLang(fnLines[i]);
            GenSeq curRes = evalLines(curParsedFnLine, symFn);
            res.push_back(curRes);
        }

        GenSeq lastGL = res[res.size() - 1];
        if (lastGL.getValType() == GenSeq::STRING && 
            lastGL.getVal() != "\"\n\"") {
            forceEndl = true;
        }

    } catch (const char* errCode) {
        cerr << errCode << endl;
        return;
    } catch (...) {
        cerr << "Error_Kawa:: Unknown Error" << endl;
    }

    for (int i = 0; i < res.size(); i++) {
        cout << res[i].printEvaluated();
    
        if (res[i].getValType() != GenSeq::STRING) {
            cout << endl;
        }

        if (i == (res.size() - 1) && forceEndl) {
            cout << endl;
        }
    }
}

void REPL::evalFromTerminal(SymbolFunction& symFn) {
    int lineNum = 1;
    while (true) {
        GenSeq res;
        try {
            string line = ProcessInput::readProcTerminal(lineNum);
            if (line.length() == 0) continue;
            if (line == "(df)") {
                REPL::evalFromFile(&symFn, true);
                continue;
            }
            if (line == "(file)") {
                REPL::evalFromFile(&symFn, false);
                continue;
            }
            if (line == "(exit)") {
                cout << endl;
                cout << "             SEE YOU SOON" << endl;
                cout << "#******************************************#" << endl;
                return;
            }

            GenSeq parsedFnLine = ProcessLang::processLang(line);
            res = REPL::evalLines(parsedFnLine, &symFn);

        } catch (const char* errCode) {
            cerr << errCode << endl;
            continue;
        } catch (...) {
            cerr << "Error_Kawa:: Unknown Error" << endl;
            continue;
        }

        cout << res.printEvaluated() << endl;
    }   
}
