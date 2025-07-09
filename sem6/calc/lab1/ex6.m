% sum (-1)^n x^(2n+1)/(2n+1)
% in x=1 |abs(R_n)| < 1/2n+3

rest = @(n) 1 / (2*n + 3);
for k = 49990:500000
    r = rest(k);            
    disp(k);               
    if abs(r) < 1e-5     
        fprintf('First k where abs(rest(k)) < 1e-5 is: %d\n', k);
        break;  
    end
end