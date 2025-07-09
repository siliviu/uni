; sub_main(l1 l2 ... ln) =  ()                                  l is null
;                           sub_list(l1) U sub_main(l2 ... ln), l is not null ^ l1 is a list
;                           l1 U sub_main(l2 ... ln),           l is noot null ^ l1 is not a list

; sub_main(l)
; l - list to replace

(defun sub_main (l)
    (cond ((null l)         nil)
        ((listp (first l))  (cons (sub_list (first l)) (sub_main(rest l))))
        (T                  (cons (first l) (sub_main (rest l))))
    )
)

; sub_list(l1 l2 ... ln) =  sub_list(l2 ... ln), n > 1
;                           sub_list(l1),        n = 1 ^ l1 is a list
;                           l1,                  n <= 1 ^ l1 is not a list

(defun sub_list (l)
    (if (null (rest l)) 
        (if (listp (first l)) 
            (sub_list (first l))
            (first l))
        (sub_list (rest l))
    )
)