f = @(x)exp(x.^2 - 1);
x=1.25;
L = lagrange_aprox_sym(f, [1 1.1 1.2 1.3 1.4]);
disp(double(subs(L,x)));
disp(f(x));