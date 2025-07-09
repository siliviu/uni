f=@(x) sin(x);
I=double(int(exp(-X^2)*sin(X),X,-inf,inf))
[R,d,d]=gauss_quad_type('Hermite',f,10)
disp("int = " + R);
disp("error: " + abs(I-R));

f=@(x) cos(x);
I=double(int(exp(-X^2)*cos(X),X,-inf,inf))
[R,d,d]=gauss_quad_type('Hermite',f,10)
disp("int = " + R);
disp("error: " + abs(I-R));