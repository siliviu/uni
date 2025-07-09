% lagrange

f = @(x) sqrt(x);
x=115;
nodes = [100 121 81 144 64]
L = lagrange_aprox_sym(f, nodes);
disp("real: " + f(x));
disp(double(subs(L,x)));

% barycentric
X=[115];

val_real=f(X);
values=f(nodes);
disp(lagrange_barycentric(nodes, values, X));
disp(lagrange_barycentric(nodes, values, X, 'equidistant'));
disp(lagrange_barycentric(nodes, values, X, 'cebisev1'));
disp(lagrange_barycentric(nodes, values, X, 'cebisev2'));
