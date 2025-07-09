f=@(x) sin(x);
I=double(int(exp(-X)*sin(X),X,0,inf));
R0=gauss_quad_type('Laguerre',f,1,0);
R1=gauss_quad_type('Laguerre',f,2,0);
nr=2;
while abs(R0-R1)>=1e-8
    R0=R1;
    nr=nr+1;
    R1=gauss_quad_type('Laguerre',f,nr,0);
end
disp("int = " + R1);
disp("error: " + abs(I-R1));


f=@(x) cos(x);
I=double(int(exp(-X)*cos(X),X,0,inf));
R0=gauss_quad_type('Laguerre',f,1,0);
R1=gauss_quad_type('Laguerre',f,2,0);
nr=2;
while abs(R0-R1)>=1e-8
    R0=R1;
    nr=nr+1;
    R1=gauss_quad_type('Laguerre',f,nr,0);
end
disp("int = " + R1);
disp("error: " + abs(I-R1));
