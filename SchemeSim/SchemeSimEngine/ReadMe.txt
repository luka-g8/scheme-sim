// ********** Kawa ********** //

// *** NOTE:
Hi, This is Kawa interpreter,

To use this program read "ReadMe.txt" and "input_default.scm".
You can REPL from either terminal or file,
default test file is included: "input_default.scm",
here you can find and add Kawa expressions, also
here you can find useful notes 
(They can be found by searching for "NOTE:" keyword)

Enjoy,
// *** \NOTE

// *** Build *** //
make
make default
make defOut
make kawa
make kawaOut

make snt
make sntOut
make kawa_snt
make kawa_sntOut
// *** \Build *** //


// *** Run *** //
./a
./a.out
./kawa
./kawa.out

./a_snt
./a_snt.out
./kawa_snt
./kawa_snt.out

valgrind ./a
valgrind ./a.out
valgrind ./kawa
valgrind ./kawa.out
// *** \Run *** //

// *** Clean *** //
make clean
// *** \Clean *** //



// *** Predefined base functions *** //
define
lambda
quote, '
#t, #f
and, or, not
if cond
+, -, *, /, <, >, <=, >=, =
plus, minus, multp, div

abs
mod
min
max
sqrt

eqv?
number?
symbol?
func?
list?
null?

length
list
car
cdr
"combinations of "car" and "cdr" up to length 7"
cons
append
pred-apply
pred-map
apply
unary-map
// *** Predefined base functions *** //

// *** Sample *** //
(cond '( (#f 1)
         ((and #t #f) 2)
         (#t 3)
       )
) ;3

((lambda (x y)
    (+ x y)
 )
 1 2
) ;3

(define (my-add vl1 vl2)
    (if (or (null? vl1) (null? vl2)) '(0)
        (+ (car vl1) (car vl2))
    )
)
(apply my-add '('(1) '(2))) ;3
(pred-apply my-add '('(1) '(2))) ;not valid
(pred-apply + '(1 2)) ;3

(pred-map + '(1 2) '(3 4) '(5 6)) ;(9 12)
(unary-map sqrt '(4 16 25)) ;(2 4 5)
// *** Sample *** //
