; (defun f (l)
;     (cond ((numberp l) 3)
;           ((null l) 0)
;           ((atom l) 2)
;           ((listp l) (cons 1 (mapcar #'f l)))
;     )
; )

;---

; (defun f(x) (if (equal x 0) () (+ x 1)))

; (defun fct(f l)
;     (cond ((null l) NIL)
;           ((funcall f (car l)) (cons (funcall f (car l)) (fct f (cdr l))))
;           (T NIL)
;     )
; )

; (defun fct0(f l)
;     ((lambda (c)
;     (cond ((null l) NIL)
;           (c (cons c (fct0 f (cdr l))))
;           (T NIL)
;     ))
;     (funcall f (car l)))
; )

; (defun g(l) (list (car l) (car l)))
; (setq q 'g)
; (setq p q)

;---

; (defun work (tree level e)
;     (if (null tree) NIL
;         (cons 
;             (if (= (mod level 2) 1) e
;                 (first tree)
;             ) 
;             (mapcar (lambda (tree)(work tree (+ level 1) e)) (rest tree))
;         )
;     )
; )

; (defun main (tree e) (work tree 0 e))

;---

; (defun work(l level k)
;     (if (atom l)
;         (if (= level k) 0 l)
;         (mapcar (lambda (list) (work list (+ level 1) k)) l) 
;     )
; )

; (defun main (l k) (work l 0 k))


(defun path(tree e)
    ((lambda (res)
        (cond
                ((equal (first tree) e) (list (first tree)))
                ((null res) NIL)
                (T (cons (first tree) res))
        )
    ) (mapcan (lambda (l) (path l e)) (rest tree)))
)