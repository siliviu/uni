f = @(x)sin(x);
a = 0;
b = pi;
n=10;

disp("real " + 2);
disp("trap " + reptrap(f,a,b,n));
disp("simpson " + repsimpson(f,a,b,n));
disp("rect " + reprect(f,a,b,n));