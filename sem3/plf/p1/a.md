## Model 1

$
\text{change}(l_1l_2...l_n, index, element)  = \begin{cases}
\emptyset &\text{if } n = 0 \\
l_1 + change(l_2...l_n,index-1,element ) &\text{if } n \neq 0 \land index \neq 1 \\
element + l_2...l_n &\text{otherwise}
\end{cases}
$

## Model 2

$
\text{change2}(l_1l_2...l_n, old, new)  = \begin{cases}
\emptyset &\text{if } n = 0 \\
l_1 + change(l_2...l_n,old,new ) &\text{if } n \neq 0 \land l_1 \neq old \\
new + change(l_2...l_n,old,new ) &\text{otherwise}
\end{cases}
$
