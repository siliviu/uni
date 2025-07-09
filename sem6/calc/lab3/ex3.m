n_values = 10:15;

for n = n_values
    % (a) t_k = -1 + (k^2 / n) 
    k = (0:n)'; 
    t_a = -1 + (k.^2 / n);
    
    V_a = vander(t_a);
    
    cond_V_a = cond(V_a, inf);
    
    fprintf('Condition number of V_%d for t_k = -1 + (k^2/n): %.2e\n', n, cond_V_a);

    % (b) t_k = 1/k
    k = (1:n)';
    t_b = 1 ./ k;
    
    V_b = vander(t_b);
    
    cond_V_b = cond(V_b, inf);
    
    fprintf('Condition number of V_%d for t_k = 1/k: %.2e\n', n, cond_V_b);
end
