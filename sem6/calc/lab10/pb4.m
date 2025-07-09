f = @(x)sin(x);
a = 0;
b = pi;
n=4;

disp("real " + 2);
disp("romberg " + romberg(f,a,b,n));