; merge_distinct(a1 a2 ... an, b1 b2 ... bm) =  a,                                          b is null
;                                               b,                                          a is null ^ b is not null
;                                               a1 U merge_distinct(a2 ... an, b),          a and b are not null ^ a1 < b1
;                                               b1 U merge_distinct(a, b2 ... bm),          a and b are not null ^ b1 < a1
;                                               a1 U merge_distinct(a2 ... an, b2 ... bm),  a and b are not null ^ a1 = b1

; merge_distinct(l1 l2)
; l1 - first sorted list to merge
; l2 - second sorted list to merge
(defun merge_distinct (l1 l2)
    (cond ((null l1)                l2)
        ((null l2)                  l1)
        ((< (first l1) (first l2))  (cons (first l1) (merge_distinct (rest l1) l2))) 
        ((< (first l2) (first l1))  (cons (first l2) (merge_distinct l1 (rest l2)))) 
        (T                          (cons (first l1) (merge_distinct (rest l1) (rest l2))))
    )
)