## Model
$
\text{sublist}(l_1l_2...l_n, k, l)  = \begin{cases}
\emptyset &\text{if } n = 0 \lor l = 0\\
sublist(l_2...l_n,k-1,l-1 ) &\text{if } n \neq 0 \land k \neq 1 \\
l_1 \oplus sublist(l_2...l_n,k,l-1 ) &\text{if } n \neq 0 \land k=1
\end{cases}
$