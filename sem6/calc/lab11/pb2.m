syms X;
f=@(x) sin(x.^2);

I=double(int(sin(X^2),X,-1,1));
R0=gauss_quad_type('Legendre',f,1);
R1=gauss_quad_type('Legendre',f,2);
nr=2;
while abs(R0-R1)>=1e-7
    R0=R1;
    nr=nr+1;
    R1=gauss_quad_type('Legendre',f,nr);
end
disp("int = " + R1);
disp("error: " + abs(I-R1));

f=@(x) cos(x.^2);
I=double(int(cos(X^2),X,-1,1));
R0=gauss_quad_type('Legendre',f,1);
R1=gauss_quad_type('Legendre',f,2);
nr=2;
while abs(R0-R1)>=1e-7
    R0=R1;
    nr=nr+1;
    R1=gauss_quad_type('Legendre',f,nr);
end
disp("int = " + R1);
disp("error: " + abs(I-R1));
