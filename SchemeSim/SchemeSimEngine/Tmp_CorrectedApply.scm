;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;A apply: corrected
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
;\A apply: corrected

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; apply: discarded
"*** apply *** :: "
(define (apply fn seq)
    (if (null? seq) '()
        (eval (cons fn 
                    seq
              )
        )
    )
)
; \apply: discarded

(apply append '((1) (2))) ;(1 2)
(eval (cons append '((1) (2)))) ;Argument #1 '1' to 'apply-to-args' 
                                ;has wrong type (integer) (expected: 
                                ;procedure, sequence, or other operator)
(append (1) (2)) ;Argument #1 '1' to 'apply-to-args' 
                 ;has wrong type (integer) (expected: 
                 ;procedure, sequence, or other operator)
(append '(1) '(2)) ;(1 2)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(apply append '((+ 1 7) (2))) ;(+ 1 7 2)
(eval (cons append '((+ 1 7) (2)))) ;Argument #1 '2' to 'apply-to-args' 
                                    ;has wrong type (integer) (expected: 
                                    ;procedure, sequence, or other operator)
(append (+ 1 7) (2)) ;Argument #1 '2' to 'apply-to-args' 
                     ;has wrong type (integer) (expected: 
                     ;procedure, sequence, or other operator)
(append '(+ 1 7) '(2)) ;(+ 1 7 2)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
