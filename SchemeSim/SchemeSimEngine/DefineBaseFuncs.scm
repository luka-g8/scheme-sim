;; !!! READ ONLY !!!
;;
;; User Shall not modify contents 
;; of this or any other file.

; cond
"*** cond *** :: "
(define (cond seqList) 
    (if (eval (caar seqList)) 
        (eval (cadar seqList))
        (cond (cdr seqList))
    )
)
; \cond

; ; apply: discarded
; "*** apply *** :: "
; (define (apply fn seq)
;     (if (null? seq) '()
;         (eval (cons fn 
;                     seq
;               )
;         )
;     )
; )
; ; \apply: discarded

; unary-map
"*** unary-map *** :: "
(define (unary-map fn seq)
    (if (null? seq) '()
        (cons (fn (car seq))
              (unary-map fn (cdr seq))
        )
    )
)
; \unary-map

; inQuote
; EVAL: (quote elem)
; (inQuote elem) == (cons quote (list elem)) 
"*** inQuote *** :: "
(define (inQuote elem)
    (list (car '(quote)) 
          elem
    )
)
; \inQuote

; apply
"*** apply *** :: "
(define (apply fn seq)
    (if (null? seq) '()
        (eval (cons fn 
                    (unary-map inQuote seq)
              )
        )
    )
)
; \apply

; (apply + 1 2 (list 3 4 5)) 
; ERROR_BaseFunctions: parameter isn't a LIST


; multi-map
"*** multi-map *** :: "
(define (multi-map fn seqList)

    ; '("*** multi-map *** :: To Be Implemented")

    (if (null? (car seqList)) '()
	    (cons 
            (apply fn (unary-map car seqList))
		    (apply multi-map (cons fn 
                             	(list (inQuote (unary-map cdr seqList)))
                             )
            )
        )
    )
)
; \multi-map

; (map + '((1 2) (3 4) (5 6)))
; **      ** ERROR_SymbolFunction: Symbol Doesn't Have Matching Function

; map
"*** map *** :: "
(define (map fn seqList)
    (multi-map fn seqList)
)
; \map
