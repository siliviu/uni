; linear(l1 l2 ... ln) =    T,                  l is null
;                           F,                  l is not null ^ l1 is a list
;                           linear(l2 ... ln),  l is not null ^ l1 is not a list

; linear (l)
; l - list to check if linear
(defun linear (l)
    (cond ((null l)         T)
        ((listp (first l))  nil)
        (T                  (linear (rest l)))
    )
)