f=@(x) sqrt(2)./sqrt(x+3);
I=double(int(1/sqrt(sin(X)),X,0,pi/2))
I=double(int(sqrt(2)/sqrt((1-X^2)*(X+3)),X,-1,1))

R0=gauss_quad_type('Jacobi',f,1,-1/2,-1/2);
R1=gauss_quad_type('Jacobi',f,2,-1/2,-1/2);
nr=2;
while abs(R0-R1)>=1e-8
    R0=R1;
    nr=nr+1;
    R1=gauss_quad_type('Jacobi',f,nr,-1/2,-1/2);
end
disp("int = " + R1);
disp("error: " + abs(I-R1));