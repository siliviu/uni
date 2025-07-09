## 4a

$
\text{reverse\_aux}(l_1...l_n) = \text{reverse}(l_1...l_n, \emptyset) \\
\text{reverse\_aux}(l_1l_2...l_n, ans) = \begin{cases}
\emptyset                                       &\text{if } l = \emptyset \\
\text{reverse\_aux}(l_2...l_n, l_1 \oplus ans ) &\text{otherwise}
\end{cases}
$

## 4b

$
\text{max2}(a, b)  = \begin{cases}
a &\text{if } a \ge b \\
b &\text{otherwise} \\
\end{cases} \\
$

$
\text{max}(l_1...l_n) = \begin{cases}
-\infin                                 &\text{if } l = \emptyset \\
\text{max2}(l_1, \text{max}(l_2...l_n)) &\text{otherwise}
\end{cases}
$

## 9a
$
\text{addEnd}(l_1l_2...l_n, e) =	
\begin{cases}	
[e]                         &\text{if } l = \emptyset \\
l_1 \oplus \text{addEnd}(l_2...l_n, e) 	&\text{otherwise}
\end{cases}
$


## 9b
$
\text{concat}(a_1a_2...a_n, b_1b_2...b_n) =
\begin{cases}	
\emptyset                                                           &\text{if } a = \emptyset \land b = \emptyset \\
b_1 \oplus \text{concat}(a_1a_2...a_n, b_2...b_n)                          &\text{if } a = \emptyset \land b \neq \emptyset \\
a_1 \oplus \text{concat}(a_2...a_n, b_1...b_n)    	                        &\text{otherwise}
\end{cases}
$

$
\text{concat}(a_1a_2...a_n, b_1b_2...b_n) =
\begin{cases}	
b_1...b_n                                                           &\text{if } a = \emptyset \\
a_1 \oplus \text{concat}(a_2...a_n, b_1...b_n)    	                        &\text{otherwise}
\end{cases}
$