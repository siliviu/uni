syms x
f = exp(x); 
taylor_exp = taylor(f, x, 'ExpansionPoint', 0, 'Order', 5);
disp(taylor_exp);
x_val = 1;
result = double(subs(taylor_exp, x, x_val));
disp(result);
% Rnf=subs(diff(f,x,n+1),x,xi)*x^(n+1)/factorial(n+1)