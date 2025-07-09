f = @(x)sin(x);
a = 0;
b = pi;
eps = 1e-2;

disp("real " + 2);

disp("trap " + adquad(f,a,b,@reptrap,eps));
disp("simpson " + adquad(f,a,b,@repsimpson,eps));
disp("rect " + adquad(f,a,b,@reprect,eps));