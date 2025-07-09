; subs(l1 l2 ... ln, e, n) =    (),                         l is null
;                               subs(l1, e, n) U l2 ... ln  l1 is a list ^ contains(l1, e)
;                               n U l2 ... ln,              l1 = e
;                               l1 U subs(l2 ... ln, e, n), otherwise 

; subs (l e n)
; l - list where to replace first occurence
; e - element to replace
; n - replacement
(defun subs (l e n)
    (cond   ((null l)                                           nil)
            ((AND (listp (first l)) (contains (first l) e))     (cons (subs (first l) e n) (rest l)))
            ((equal (first l) e)                                (cons n (rest l)))
            (T                                                  (cons (first l) (subs (rest l) e n)))
    )
)


; contains (l1 l2 ... ln, e) =  F,                      l is null
;                               T,                      l1 is a list ^ contains(l1, e)
;                               T,                      l1 = e
;                               contains(l2 ... ln),    otherwise
(defun contains(l e)
    (cond  ((null l)                                        nil)
           ((AND (listp (first l)) (contains (first l) e))  T)
           ((equal (first l) e)                             T)
           (T                                               (contains (rest l) e))
    )
)