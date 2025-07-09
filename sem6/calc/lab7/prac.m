% 1

f = @(x) exp(x);

x = [0, 1, 2];
y = f(x);
dy = f(x);
point = [0.25];

y0 = f(point);
y1 = newton(x,y,point);
[y2, dy2] = hermite(x,y,dy,point);

display(y0 + " " + y1 + " " + y2);
display("error: " + abs(y2-y0));

% 2

f = @(x) sin(x);
df = @(x) cos(x);
x=[0.30, 0.32, 0.35];
y=[0.29952, 0.31457, 0.34290];
dy=[0.9554, 0.94924, 0.9337];
point = [0.34];

y0 = f(point);
[y1,dy1]=hermite(x,y,dy,point);
display(y0 + " " + y1);


x=[0.30, 0.32, 0.33, 0.35];
y = f(x);
dy = df(x);

[y1,dy1]=hermite(x,y,dy,point);
display(y0 + " " + y1);

% 3

x=[0,3,5,8,13];
y=[0,225,383,623,993];
dy=[75,77,80,74,72];

point = [10];

[y1,dy1]=hermite(x,y,dy,point);
display(y1+ " " +dy1);