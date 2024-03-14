; linearise_num(L1...LN) =  {L}, if L = number
;                           U linearise_num(L_i), if L = list
;                           NIL, otherwise
;
(defun linearise_num (L)
    (cond ((numberp L) (list L))
          ((listp L) (mapcan #'linearise_num L))
          (T NIL)
    )
)

; mountain(L1...LN, FLAG) = T, if FLAG=-1 ^ N = 1
;                           F, if FLAG!=-1 ^ N <= 1
;                           mountain(L2...LN, 1), if N >= 2 ^ FLAG != -1 ^ L2 > L1
;                           mountain(L2...LN, -1), if N>= 2 ^ FLAG != 0 ^ L1 < L2
;                           F, otherwise 
(defun mountain(L FLAG)
    (cond   ((AND (= FLAG -1) (NOT (NULL L)) (NULL (REST L))) T)
            ((NULL (REST L)) NIL)
            ((AND (NOT (= FLAG -1)) (> (SECOND L) (FIRST L))) (mountain (REST L) 1))
            ((AND (NOT (= FLAG 0)) (< (SECOND L) (FIRST L))) (mountain (REST L) -1))
            (T NIL)
    )
)

; main(L) = mountain(linearise_num(L),0)
(defun main (L)
    (mountain (linearise_num L) 0)
)

; '(1(A B(5)(6(7 J))(9)4)K)


