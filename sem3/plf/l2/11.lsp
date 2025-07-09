; combine(a1..an, b1..bm) = b, n=0
;                          a, m=0
;                          (a1+b1) U combine(a2...an, b2..bn), otherwise
(defun combine (l1 l2)
    (cond   ((null l1)  l2)
            ((null l2)  l1)
            (T          (cons (+ (first l1) (first l2)) (combine (rest l1) (rest l2))))
    )
)

; getlevellist(l1 l2 l3) = NIL, n = 0
;                          1 U merge(getlevellist(l2),getlevellist(l3))
(defun getlevellist (l)
    (if (null l)
        ()
        (cons 1 (combine (getlevellist(second l)) (getlevellist(third l))))
    )   
)

; max2(a1.a2, b1.b2) = a, b is null
;                      a, a1>b1
;                      b, otherwise

(defun max2 (a b)
    (cond   ((null b)               a)
            ((> (car a) (car b))    a)
            (T                      b)
    )
)

; getmax(l1...ln, cur) = NIL, n = 0
;                        max2(l1.cur, getmax(l2...ln,cur+1))
(defun getmax (l cur)
    (if (null l)   
        ()
        (max2 (cons (first l) cur) (getmax (rest l) (+ cur 1)))
    )
)

; getnodes(l1l2l3, nr) = NIL, n = 0
;                        (l1), nr = 0
;                        getnodes(l2, nr - 1) U getnodes(l3, nr - 1), otherwise
(defun getnodes (l nr)
    (cond   ((null l) ())
            ((= nr 0) (list (first l)))
            (T (append (getnodes (second l) (- nr 1)) (getnodes (third l) (- nr 1))))
    )
)

; main(l) 
; prints no. of level with most nodes (and the no. of nodes)
; prints all nodes
(defun main(l)
    (
    (lambda (nr)
        (format t "Level ~d has ~d nodes:~%" (cdr nr) (car nr))
        (getnodes l (cdr nr))
    ) 
    (getmax (getlevellist l) 0))
)