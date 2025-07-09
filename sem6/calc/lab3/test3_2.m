clear

n_values = 15:20;

for n = n_values

    k = (0:n)';
    t_a = -1 + k * (1 / n);
    V_a = vander(t_a);
    cond_V_a = cond(V_a, 2);
    
    fprintf('Condition number of V_%d (Euclidean or 2 norm): %.2e\n', n, cond_V_a);
end