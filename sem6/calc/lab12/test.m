f=@(x) x-cos(x)
g=@(x) cos(x)

clf; hold  on;
plot([0 pi/2],[0 0])
fplot(f,[0,pi/2])

x2=secant(f,0,pi/2)
p=steffensen(g,pi/4)
df=@(x) 1+sin(x);
x1=newton(f,df,pi/4,1e-12,100)
x1=succ(g,pi/4)
phi=@(x) x-f(x)./df(x);
x1=succ(phi,pi/4)

