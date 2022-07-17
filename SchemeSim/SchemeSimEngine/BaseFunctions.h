#ifndef BaseFunctions_h
#define BaseFunctions_h

#include <string>
#include <stdlib.h>
#include <cmath>
#include "GenSeq.h"

GenSeq plus_op(const vector<GenSeq>& param);
GenSeq minus_op(const vector<GenSeq>& param);
GenSeq multp_op(const vector<GenSeq>& param);
GenSeq div_op(const vector<GenSeq>& param);
GenSeq less_cmp(const vector<GenSeq>& param);
GenSeq more_cmp(const vector<GenSeq>& param);
GenSeq less_or_equal(const vector<GenSeq>& param);
GenSeq more_or_equal(const vector<GenSeq>& param);

GenSeq abs(const vector<GenSeq>& param);
GenSeq mod(const vector<GenSeq>& param);
GenSeq min(const vector<GenSeq>& param);
GenSeq max(const vector<GenSeq>& param);
GenSeq sqrt(const vector<GenSeq>& param);

GenSeq isEqual(const vector<GenSeq>& param);
GenSeq isNumber(const vector<GenSeq>& param);
GenSeq isSymbol(const vector<GenSeq>& param);
GenSeq isFunc(const vector<GenSeq>& param);
GenSeq isList(const vector<GenSeq>& param);
GenSeq isNull(const vector<GenSeq>& param);

GenSeq length(const vector<GenSeq>& param);
GenSeq list(const vector<GenSeq>& param);
GenSeq car(const vector<GenSeq>& param);
GenSeq cdr(const vector<GenSeq>& param);
GenSeq cons(const vector<GenSeq>& param);
GenSeq append(const vector<GenSeq>& param);
GenSeq predApply(const vector<GenSeq>& param);
GenSeq predMap(const vector<GenSeq>& param);

// 2
GenSeq caar(const vector<GenSeq>& param);
GenSeq cdar(const vector<GenSeq>& param);

GenSeq cadr(const vector<GenSeq>& param);
GenSeq cddr(const vector<GenSeq>& param);
// \2

// 3
GenSeq caaar(const vector<GenSeq>& param);
GenSeq cadar(const vector<GenSeq>& param);
GenSeq cdaar(const vector<GenSeq>& param);
GenSeq cddar(const vector<GenSeq>& param);

GenSeq caadr(const vector<GenSeq>& param);
GenSeq caddr(const vector<GenSeq>& param);
GenSeq cdadr(const vector<GenSeq>& param);
GenSeq cdddr(const vector<GenSeq>& param);
// \3

// 4
GenSeq caaaar(const vector<GenSeq>& param);
GenSeq cadaar(const vector<GenSeq>& param);
GenSeq cdaaar(const vector<GenSeq>& param);
GenSeq cddaar(const vector<GenSeq>& param);
GenSeq caadar(const vector<GenSeq>& param);
GenSeq caddar(const vector<GenSeq>& param);
GenSeq cdadar(const vector<GenSeq>& param);
GenSeq cdddar(const vector<GenSeq>& param);

GenSeq caaadr(const vector<GenSeq>& param);
GenSeq cadadr(const vector<GenSeq>& param);
GenSeq cdaadr(const vector<GenSeq>& param);
GenSeq cddadr(const vector<GenSeq>& param);
GenSeq caaddr(const vector<GenSeq>& param);
GenSeq cadddr(const vector<GenSeq>& param);
GenSeq cdaddr(const vector<GenSeq>& param);
GenSeq cddddr(const vector<GenSeq>& param);
// \4

// 5
GenSeq caaaaar(const vector<GenSeq>& param);
GenSeq cadaaar(const vector<GenSeq>& param);
GenSeq cdaaaar(const vector<GenSeq>& param);
GenSeq cddaaar(const vector<GenSeq>& param);
GenSeq caadaar(const vector<GenSeq>& param);
GenSeq caddaar(const vector<GenSeq>& param);
GenSeq cdadaar(const vector<GenSeq>& param);
GenSeq cdddaar(const vector<GenSeq>& param);
GenSeq caaadar(const vector<GenSeq>& param);
GenSeq cadadar(const vector<GenSeq>& param);
GenSeq cdaadar(const vector<GenSeq>& param);
GenSeq cddadar(const vector<GenSeq>& param);
GenSeq caaddar(const vector<GenSeq>& param);
GenSeq cadddar(const vector<GenSeq>& param);
GenSeq cdaddar(const vector<GenSeq>& param);
GenSeq cddddar(const vector<GenSeq>& param);

GenSeq caaaadr(const vector<GenSeq>& param);
GenSeq cadaadr(const vector<GenSeq>& param);
GenSeq cdaaadr(const vector<GenSeq>& param);
GenSeq cddaadr(const vector<GenSeq>& param);
GenSeq caadadr(const vector<GenSeq>& param);
GenSeq caddadr(const vector<GenSeq>& param);
GenSeq cdadadr(const vector<GenSeq>& param);
GenSeq cdddadr(const vector<GenSeq>& param);
GenSeq caaaddr(const vector<GenSeq>& param);
GenSeq cadaddr(const vector<GenSeq>& param);
GenSeq cdaaddr(const vector<GenSeq>& param);
GenSeq cddaddr(const vector<GenSeq>& param);
GenSeq caadddr(const vector<GenSeq>& param);
GenSeq caddddr(const vector<GenSeq>& param);
GenSeq cdadddr(const vector<GenSeq>& param);
GenSeq cdddddr(const vector<GenSeq>& param);
// \5

// 6
GenSeq caaaaaar(const vector<GenSeq>& param);
GenSeq cadaaaar(const vector<GenSeq>& param);
GenSeq cdaaaaar(const vector<GenSeq>& param);
GenSeq cddaaaar(const vector<GenSeq>& param);
GenSeq caadaaar(const vector<GenSeq>& param);
GenSeq caddaaar(const vector<GenSeq>& param);
GenSeq cdadaaar(const vector<GenSeq>& param);
GenSeq cdddaaar(const vector<GenSeq>& param);
GenSeq caaadaar(const vector<GenSeq>& param);
GenSeq cadadaar(const vector<GenSeq>& param);
GenSeq cdaadaar(const vector<GenSeq>& param);
GenSeq cddadaar(const vector<GenSeq>& param);
GenSeq caaddaar(const vector<GenSeq>& param);
GenSeq cadddaar(const vector<GenSeq>& param);
GenSeq cdaddaar(const vector<GenSeq>& param);
GenSeq cddddaar(const vector<GenSeq>& param);
GenSeq caaaadar(const vector<GenSeq>& param);
GenSeq cadaadar(const vector<GenSeq>& param);
GenSeq cdaaadar(const vector<GenSeq>& param);
GenSeq cddaadar(const vector<GenSeq>& param);
GenSeq caadadar(const vector<GenSeq>& param);
GenSeq caddadar(const vector<GenSeq>& param);
GenSeq cdadadar(const vector<GenSeq>& param);
GenSeq cdddadar(const vector<GenSeq>& param);
GenSeq caaaddar(const vector<GenSeq>& param);
GenSeq cadaddar(const vector<GenSeq>& param);
GenSeq cdaaddar(const vector<GenSeq>& param);
GenSeq cddaddar(const vector<GenSeq>& param);
GenSeq caadddar(const vector<GenSeq>& param);
GenSeq caddddar(const vector<GenSeq>& param);
GenSeq cdadddar(const vector<GenSeq>& param);
GenSeq cdddddar(const vector<GenSeq>& param);

GenSeq caaaaadr(const vector<GenSeq>& param);
GenSeq cadaaadr(const vector<GenSeq>& param);
GenSeq cdaaaadr(const vector<GenSeq>& param);
GenSeq cddaaadr(const vector<GenSeq>& param);
GenSeq caadaadr(const vector<GenSeq>& param);
GenSeq caddaadr(const vector<GenSeq>& param);
GenSeq cdadaadr(const vector<GenSeq>& param);
GenSeq cdddaadr(const vector<GenSeq>& param);
GenSeq caaadadr(const vector<GenSeq>& param);
GenSeq cadadadr(const vector<GenSeq>& param);
GenSeq cdaadadr(const vector<GenSeq>& param);
GenSeq cddadadr(const vector<GenSeq>& param);
GenSeq caaddadr(const vector<GenSeq>& param);
GenSeq cadddadr(const vector<GenSeq>& param);
GenSeq cdaddadr(const vector<GenSeq>& param);
GenSeq cddddadr(const vector<GenSeq>& param);
GenSeq caaaaddr(const vector<GenSeq>& param);
GenSeq cadaaddr(const vector<GenSeq>& param);
GenSeq cdaaaddr(const vector<GenSeq>& param);
GenSeq cddaaddr(const vector<GenSeq>& param);
GenSeq caadaddr(const vector<GenSeq>& param);
GenSeq caddaddr(const vector<GenSeq>& param);
GenSeq cdadaddr(const vector<GenSeq>& param);
GenSeq cdddaddr(const vector<GenSeq>& param);
GenSeq caaadddr(const vector<GenSeq>& param);
GenSeq cadadddr(const vector<GenSeq>& param);
GenSeq cdaadddr(const vector<GenSeq>& param);
GenSeq cddadddr(const vector<GenSeq>& param);
GenSeq caaddddr(const vector<GenSeq>& param);
GenSeq cadddddr(const vector<GenSeq>& param);
GenSeq cdaddddr(const vector<GenSeq>& param);
GenSeq cddddddr(const vector<GenSeq>& param);
// \6

// 7
GenSeq caaaaaaar(const vector<GenSeq>& param);
GenSeq cadaaaaar(const vector<GenSeq>& param);
GenSeq cdaaaaaar(const vector<GenSeq>& param);
GenSeq cddaaaaar(const vector<GenSeq>& param);
GenSeq caadaaaar(const vector<GenSeq>& param);
GenSeq caddaaaar(const vector<GenSeq>& param);
GenSeq cdadaaaar(const vector<GenSeq>& param);
GenSeq cdddaaaar(const vector<GenSeq>& param);
GenSeq caaadaaar(const vector<GenSeq>& param);
GenSeq cadadaaar(const vector<GenSeq>& param);
GenSeq cdaadaaar(const vector<GenSeq>& param);
GenSeq cddadaaar(const vector<GenSeq>& param);
GenSeq caaddaaar(const vector<GenSeq>& param);
GenSeq cadddaaar(const vector<GenSeq>& param);
GenSeq cdaddaaar(const vector<GenSeq>& param);
GenSeq cddddaaar(const vector<GenSeq>& param);
GenSeq caaaadaar(const vector<GenSeq>& param);
GenSeq cadaadaar(const vector<GenSeq>& param);
GenSeq cdaaadaar(const vector<GenSeq>& param);
GenSeq cddaadaar(const vector<GenSeq>& param);
GenSeq caadadaar(const vector<GenSeq>& param);
GenSeq caddadaar(const vector<GenSeq>& param);
GenSeq cdadadaar(const vector<GenSeq>& param);
GenSeq cdddadaar(const vector<GenSeq>& param);
GenSeq caaaddaar(const vector<GenSeq>& param);
GenSeq cadaddaar(const vector<GenSeq>& param);
GenSeq cdaaddaar(const vector<GenSeq>& param);
GenSeq cddaddaar(const vector<GenSeq>& param);
GenSeq caadddaar(const vector<GenSeq>& param);
GenSeq caddddaar(const vector<GenSeq>& param);
GenSeq cdadddaar(const vector<GenSeq>& param);
GenSeq cdddddaar(const vector<GenSeq>& param);
GenSeq caaaaadar(const vector<GenSeq>& param);
GenSeq cadaaadar(const vector<GenSeq>& param);
GenSeq cdaaaadar(const vector<GenSeq>& param);
GenSeq cddaaadar(const vector<GenSeq>& param);
GenSeq caadaadar(const vector<GenSeq>& param);
GenSeq caddaadar(const vector<GenSeq>& param);
GenSeq cdadaadar(const vector<GenSeq>& param);
GenSeq cdddaadar(const vector<GenSeq>& param);
GenSeq caaadadar(const vector<GenSeq>& param);
GenSeq cadadadar(const vector<GenSeq>& param);
GenSeq cdaadadar(const vector<GenSeq>& param);
GenSeq cddadadar(const vector<GenSeq>& param);
GenSeq caaddadar(const vector<GenSeq>& param);
GenSeq cadddadar(const vector<GenSeq>& param);
GenSeq cdaddadar(const vector<GenSeq>& param);
GenSeq cddddadar(const vector<GenSeq>& param);
GenSeq caaaaddar(const vector<GenSeq>& param);
GenSeq cadaaddar(const vector<GenSeq>& param);
GenSeq cdaaaddar(const vector<GenSeq>& param);
GenSeq cddaaddar(const vector<GenSeq>& param);
GenSeq caadaddar(const vector<GenSeq>& param);
GenSeq caddaddar(const vector<GenSeq>& param);
GenSeq cdadaddar(const vector<GenSeq>& param);
GenSeq cdddaddar(const vector<GenSeq>& param);
GenSeq caaadddar(const vector<GenSeq>& param);
GenSeq cadadddar(const vector<GenSeq>& param);
GenSeq cdaadddar(const vector<GenSeq>& param);
GenSeq cddadddar(const vector<GenSeq>& param);
GenSeq caaddddar(const vector<GenSeq>& param);
GenSeq cadddddar(const vector<GenSeq>& param);
GenSeq cdaddddar(const vector<GenSeq>& param);
GenSeq cddddddar(const vector<GenSeq>& param);

GenSeq caaaaaadr(const vector<GenSeq>& param);
GenSeq cadaaaadr(const vector<GenSeq>& param);
GenSeq cdaaaaadr(const vector<GenSeq>& param);
GenSeq cddaaaadr(const vector<GenSeq>& param);
GenSeq caadaaadr(const vector<GenSeq>& param);
GenSeq caddaaadr(const vector<GenSeq>& param);
GenSeq cdadaaadr(const vector<GenSeq>& param);
GenSeq cdddaaadr(const vector<GenSeq>& param);
GenSeq caaadaadr(const vector<GenSeq>& param);
GenSeq cadadaadr(const vector<GenSeq>& param);
GenSeq cdaadaadr(const vector<GenSeq>& param);
GenSeq cddadaadr(const vector<GenSeq>& param);
GenSeq caaddaadr(const vector<GenSeq>& param);
GenSeq cadddaadr(const vector<GenSeq>& param);
GenSeq cdaddaadr(const vector<GenSeq>& param);
GenSeq cddddaadr(const vector<GenSeq>& param);
GenSeq caaaadadr(const vector<GenSeq>& param);
GenSeq cadaadadr(const vector<GenSeq>& param);
GenSeq cdaaadadr(const vector<GenSeq>& param);
GenSeq cddaadadr(const vector<GenSeq>& param);
GenSeq caadadadr(const vector<GenSeq>& param);
GenSeq caddadadr(const vector<GenSeq>& param);
GenSeq cdadadadr(const vector<GenSeq>& param);
GenSeq cdddadadr(const vector<GenSeq>& param);
GenSeq caaaddadr(const vector<GenSeq>& param);
GenSeq cadaddadr(const vector<GenSeq>& param);
GenSeq cdaaddadr(const vector<GenSeq>& param);
GenSeq cddaddadr(const vector<GenSeq>& param);
GenSeq caadddadr(const vector<GenSeq>& param);
GenSeq caddddadr(const vector<GenSeq>& param);
GenSeq cdadddadr(const vector<GenSeq>& param);
GenSeq cdddddadr(const vector<GenSeq>& param);
GenSeq caaaaaddr(const vector<GenSeq>& param);
GenSeq cadaaaddr(const vector<GenSeq>& param);
GenSeq cdaaaaddr(const vector<GenSeq>& param);
GenSeq cddaaaddr(const vector<GenSeq>& param);
GenSeq caadaaddr(const vector<GenSeq>& param);
GenSeq caddaaddr(const vector<GenSeq>& param);
GenSeq cdadaaddr(const vector<GenSeq>& param);
GenSeq cdddaaddr(const vector<GenSeq>& param);
GenSeq caaadaddr(const vector<GenSeq>& param);
GenSeq cadadaddr(const vector<GenSeq>& param);
GenSeq cdaadaddr(const vector<GenSeq>& param);
GenSeq cddadaddr(const vector<GenSeq>& param);
GenSeq caaddaddr(const vector<GenSeq>& param);
GenSeq cadddaddr(const vector<GenSeq>& param);
GenSeq cdaddaddr(const vector<GenSeq>& param);
GenSeq cddddaddr(const vector<GenSeq>& param);
GenSeq caaaadddr(const vector<GenSeq>& param);
GenSeq cadaadddr(const vector<GenSeq>& param);
GenSeq cdaaadddr(const vector<GenSeq>& param);
GenSeq cddaadddr(const vector<GenSeq>& param);
GenSeq caadadddr(const vector<GenSeq>& param);
GenSeq caddadddr(const vector<GenSeq>& param);
GenSeq cdadadddr(const vector<GenSeq>& param);
GenSeq cdddadddr(const vector<GenSeq>& param);
GenSeq caaaddddr(const vector<GenSeq>& param);
GenSeq cadaddddr(const vector<GenSeq>& param);
GenSeq cdaaddddr(const vector<GenSeq>& param);
GenSeq cddaddddr(const vector<GenSeq>& param);
GenSeq caadddddr(const vector<GenSeq>& param);
GenSeq caddddddr(const vector<GenSeq>& param);
GenSeq cdadddddr(const vector<GenSeq>& param);
GenSeq cdddddddr(const vector<GenSeq>& param);
// \7

#endif
