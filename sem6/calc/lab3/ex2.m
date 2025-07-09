n_values = 10:15;

for n = n_values
    H = hilb(n);
    
    cond_H = cond(H, 2);
    
    fprintf('Condition number of Hilbert matrix H_%d (2-norm): %.2e\n', n, cond_H);
end