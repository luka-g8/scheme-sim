;; !!! READ-WRITE ENABLED !!!
;;
;; This is default input file for
;; Kawa, you can access it by 
;; typing: (df) into the Kawa terminal.
;; 
;; For accessing user created input 
;; files type: (file) and then path; i.e.
;; #|kawa:1|# (file)
;; &&|File_Path|&&: "file_name.scm"
;; 
;; For exiting from Kawa type: (exit)
;;
;; For executiong program in valgrind
;; type: "valgrind ./a" or "valgrind ./kawa"
;; in the terminal.

;; In this file there are usefull notes, which
;; can help you use Kawa program
;; They can be found by searching for 
;; "NOTE:" keyword.
;; (single line coments only start with "NOTE:",
;; whereas multi line comments start with "NOTE:" 
;; and end with "\NOTE" keywords).

"\n//-----------------------BEGIN-------------------------//\n\n"

; Instead of "display" we can use
; "quote" or "\'" functions.
; (display ( + (* 5 8) 
;     2
; ))

(quote ( + (* 5 8) 
    2
)) ;(+ (* 5 8)  2) 

'( + (* 5 8) 
    2
) ;(+ (* 5 8)  2) 

;; NOTE:
;; Every list outputs evaluation or
;; gives feedback that new list if defined, 
;; so "display" function is't needed.
;; \NOTE

( + (* 5 8) 
    2
)
;42

( + (* 2.2 2) 
    1
)
;5.4

(define square (lambda (x) (+ x x)) ) ;to change L27
(define square (lambda (x) (* x x)) )

( (lambda (z) (- z 2)) 5) ;3
( (lambda (x y) (- x 2 y)) 7 5) ;0
; ( (lambda (x y) (- y 2 x z)) 5 7) ;catch;-5

( (lambda (x y) (- x
                    ( (lambda (y) (- y 2)) 13)
                   y)
        ) 7 5) ;-9

( (lambda (x y) (- x 
                   ( (lambda (w) (- w x)) 5) 
                   y)
        ) 7 5) ;4

(define addme (lambda (x) (+ x x)))

(square 3) ;9
(addme 7) ;14

(quote (append '(0) '(0))) ;(append (quote (0))  (quote (0))) 

"\n//-N1--------------------------------------------------//\n\n"

(car '(1 2 3)) ;1
(cdr '(1 2 3)) ;(2 3)

(and (= 2 2) (= 3 3)) ;#t
(and (= 2 2) (= 3 11)) ;#f
; (and) ;catch

(or (= 2 11) (= 3 3)) ;#t
(or (= 2 11) (= 3 11)) ;#f
; (or) ;catch

(not (= 2 11)) ;#t
(not (= 2 2)) ;#f
; (not (= 2 2) (= 13 11)) ;catch

(quote (cons car  
             (list (cons 1 (cons 2 '()))) )) 
    ;(cons car (list (cons 1 (cons 2 (quote ())))))

(quote (cons car '(1 2))) ;(cons car (quote (1 2))) 

(cons car  
      (list (cons 1 (cons 2 '()))) ) ;(FUNC (1 2)) 

(car '(1 2)) ;1

(eval (cons car  
        (list (quote (cons 1 (cons 2 '())))) )) ;1

(cons 1 '(2 3)) ;(1 2 3)
(list 2 21 1) ;(2 21 1) 

(if #f 10 (+ 3 15)) ;18

"\n//-N2--------------------------------------------------//\n\n"

(define addL (lambda (x y) (+ x y)))
(addL 1 2) ;3
(define (addnL x y) (+ x y))
(addnL 10 20) ;30

(define (kkdl x y) (+ x y
                      ((lambda (x) (+ x x)) 5)
                      ))
(kkdl 2 3) ;15

(define kkll (lambda (x) (* x 
                            ((lambda (x) (+ x x)) 5)
                            )))
(kkll 4) ;40

((lambda (x) (+ x x)) 5) ;10

"\n//-N3--------------------------------------------------//\n\n"

(define (fib n)
  (if (< n 2) n
    (+ (fib (- n 1)) 
       (fib (- n 2))
    )
  )
)
(fib 7) ;13

(define (fibo n)
 (if (or (= n 0) (= n 1)) n
  (+ (fibo (- n 1)) 
     (fibo (- n 2)))))
(fibo 7) ;13

; A
"\n define sorted?_1 \n"
(define (sorted?_1 seq)
 (if (< (length seq) 2) #t
  (and (<= (car seq) (cadr seq))
       (sorted?_1 (cdr seq))) ))
(sorted?_1 '(3 4 5)) ;#t
(sorted?_1 '(3 4 2)) ;#f
; \A

(car '((1) 2)) ;(1)
(car (quote ((1) 2)) ) ;(1) 
(cdr '(1 2)) ;(2)
(cdr '((1) 2)) ;(2)
(cdr (quote ((1) 2)) ) ;(2)

;A
"\n define flatten_1 \n"
(define (flatten_1 seq)
 (if (null? seq) (quote ())
  (append (if (list? (car seq))
              (flatten_1 (car seq))
              (list (car seq)))
          (flatten_1 (cdr seq))) ))
;\A

(flatten_1 '((1) 2)) ;(1 2) 
(flatten_1 '((4 (3)) (+ 7 2))) ;(4 3 + 7 2)

(flatten_1 (quote ((1) 2)) ) ;(1 2) 
(flatten_1 (quote ((4 (3)) (+ 7 2))) ) ;(4 3 + 7 2)

'(1 2 3) ;(1 2 3) 
'((1) 2) ;((1)  2)
(quote ((1) 2)) ;((1)  2)
(quote (1 2)) ;(1 2)


(cons '(3) '(5)) ;((3)  5)
; (cons '(3) '(5) '(22)) ;catch
; (cons 8) ;catch

"\n//-N4--------------------------------------------------//\n\n"

(car '(1 2 3 4 5))             ;1
(caar '((1) 2 3 4 5))          ;1
(caaar '(((1)) 2 3 4 5))       ;1
(caaaar '((((1))) 2 3 4 5))    ;1

(cdr '(1 2 3 4 5))             ;(2 3 4 5) 
(cddr '(1 2 3 4 5))            ;(3 4 5) 
(cdddr '(1 2 3 4 5))           ;(4 5) 
(cddddr '(1 2 3 4 5))          ;(5)

(cadr '(1 2 3 4 5))            ;2
(caddr '(1 2 3 4 5))           ;3
(cadadr '(1 (2 3) 4))          ;3

(caddddddr '(1 2 3 4 5 6 7 8)) ;(7)

"\n//-N5--------------------------------------------------//\n\n"

; NOTE
; valgrind -s ./a ;passed
; valgrind -s ./kawa ;passed


'(1 "str")   ;(1 "str") 
"(+ 2 3)\n"  ;(+ 2 3)
""(+ 2 3)""  ;5

"hi: " (+ 3 4) ;hi: 7

"hi--\n--hp\n"

; "kk_force_me_endl" ; if last --> forceEndl

;; NOTE:
;; Terminal supports full line strings, 
;; but if above functionality is needed, 
;; please, use input file. 
;; \NOTE

"\n//-N6--------------------------------------------------//\n\n"

;; NOTE:
;; Aside from "apply", "unary-map" you 
;; can use "pred-apply" and "pred-map", but only for
;; predefined functions (can be seen inside function
;; body with path: Kava.cpp -> 
;; void populate_s_fn(SymbolFunction* symFn) {...});
;;
;; "pred-map" can take multiple arguments
;; \NOTE

;; A 
(define (double-num x) (* x 2))
(unary-map double-num '(1 2 3)) ;(2 4 6)

(cons (apply double-num '(1)) 
    (cons (apply double-num '(2)) 
    (cons (apply double-num '(3)) '()))) ; SAME as map ;(2 4 6)

;apply
(define (ff1 x) (* x 100))
(apply ff1 '(2)) ; SAME apply ;200
(eval (cons ff1 '(2))) ; SAME apply ;200
(ff1 2) ; SAME apply ;200
((lambda (x) (* x 100)) 2) ; SAME apply ;200
;\apply
;; \A

(apply + '(1 2 3))       ;6
(eval (cons + '(1 2 3))) ;6
(cons + '(1 2 3))        ;(FUNC 1 2 3)

(unary-map sqrt '(1 2 3)) ;(1 1.414214 1.732051)
(apply + '(1 2 3)) ;6
(unary-map sqrt '(2 4 16)) ;(1.414214 2 4)
(unary-map + '(1 2 3)) ;(1 2 3)

"\n//-N7--------------------------------------------------//\n\n"

(unary-map double-num '(1 2 3)) ;(2 4 6)

(unary-map sqrt '(1 2 3)) ;(1 1.414214 1.732051) 

(apply double-num '()) ;()
(apply double-num '(9)) ;18

; (multi-map double-num '((1 2) (3 4) (5 6)))
; (map double-num '((1 2) (3 4) (5 6)))

"\n//-N8--------------------------------------------------//\n\n"

(cond '( (#f 1)
         ((and #t #f) 2)
         (#t 3)
       )
) ;3


(and #t #f) ;#f ;valid
(= 1 2) ;#f ;valid
;;(= #t #f) ;not valid


(define (sorted? seq)
 (cond '( ((< (length seq) 2) #t)
          ((and (<= (car seq) (cadr seq)) 
                (sorted? (cdr seq))) #t)
          (#t #f)
        )
 )
)

(sorted? '(1 3 5)) ;#t
(sorted? '(20 3 5)) ;#f

((lambda (x y)
    (+ x y)
 )
 1 2
) ;3

"\n//-N9--------------------------------------------------//\n\n"

;; NOTE:
;; Aside from "apply", "unary-map" you 
;; can use "pred-apply" and "pred-map", but only for
;; predefined functions (can be seen inside function
;; body with path: Kava.cpp -> 
;; void populate_s_fn(SymbolFunction* symFn) {...});
;;
;; "pred-map" can take multiple arguments
;; \NOTE

(define (my-add vl1 vl2)
    (if (or (null? vl1) (null? vl2)) '(0)
        (+ (car vl1) (car vl2))
    )
)
(my-add '(1) '(2)) ;3

; (apply my-add '( (quote (1)) (quote (2)) )) ;catch
; (apply my-add '('(1) '(2))) ;catch
(apply my-add '((1) (2))) ;3

(apply  + '(1 2)) ;3
(pred-apply + '(1 2)) ;3
(pred-map + '(1 2) '(3 4) '(5 6)) ;(9 12)

(define (incr seq num)
    (unary-map (lambda (elem) (+ elem num))
        seq
    )
)
(incr '(1 2 3) 10) ;(11 12 13)

"\n//-N10-------------------------------------------------//\n\n"

(inQuote '()) ;(quote ())
(inQuote '(+ 1 2)) ;(quote (+ 1 2))
(eval (eval (inQuote '(+ 1 2)))) ;3
(unary-map inQuote '((1) (2))) ;((quote (1))  (quote (2)))

(apply append '((1) (2))) ;(1 2)
(apply + '(1 2 3)) ;6
(apply append '((1 2) (3 4) (5 6))) ;(1 2 3 4 5 6)

(define (addme x y) (+ x y))
(apply addme '(1 2)) ;3

(pred-apply + '(1 2 3)) ;6
(pred-map + '(1 2) '(3 4) '(5 6)) ;(9 12)

"\n//-N11-------------------------------------------------//\n\n"

(+ 2 3) ;5
(plus 2 3) ;5
(- 2 3) ;-1
(minus 2 3) ;-1
(* 2 3) ;6
(multp 2 3) ;6
(/ 2 3) ;0.666667
(div 2 3) ;0.666667
(= 2 2) ;#t
(= 2 3) ;#f
(< 2 3) ;#t
(< 3 2) ;#f
(> 3 2) ;#t
(> 2 3) ;#f
(<= 2 2) ;#t
(<= 3 2) ;#f
(>= 2 2) ;#t
(>= 2 3) ;#f

(abs 3) ;3
(abs (- 0 2)) ;2
(mod 3 2) ;1
(min 4 2 3) ;2
(max 4 2 3) ;4
(sqrt 2) ;1.414214

"\n//-N12-------------------------------------------------//\n\n"

; ADD TESTS HERE



"\n//-----------------------END---------------------------//\n"
