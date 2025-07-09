f=@(x) exp(-x.^2);
I=double(int(exp(-X^2)*sqrt(1-X^2),X,-1,1))
R=gauss_quad_type('Cebisev2',f,10)
disp("int = " + R);
disp("error: " + abs(I-R));