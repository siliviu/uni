; linearise(l)= NIL,                n = 0
;               (l),                l is an atom
;               U linearise(li),    where l=l1...ln
(defun linearise (l)
    (cond   ((null l) nil)
            ((atom l) (list l))
            (T (mapcan #'linearise l)) 
    )
)