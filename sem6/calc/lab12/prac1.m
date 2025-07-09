syms x y;
F=[x^2+y^2-1; x^3-y];
J=jacobian(F);
Fh=matlabFunction(F);
Jh=matlabFunction(J);
f=@(X) Fh(X(1),X(2));
df=@(X) Jh(X(1),X(2));
x=newton(f,df,[1;1])
y=f(x)