f = @(x) sqrt(x);
x=115;
L = lagrange_aprox_sym(f, [100 121 81 144 64]);
disp(double(subs(L,x)));
disp(f(x));