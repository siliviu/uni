f=@(x) x.*exp(-x.^2);
syms X;
I=double(int(X*exp(-X^2)/sqrt(1-X^2),X,-1,1));
R=gauss_quad_type('Cebisev1',f,10);
disp("int = " + R);
disp("error: " + abs(I-R));
