syms x;
w=sqrt(1-x)
a=-sym(1), b=sym(1)
wa=(x-a)*w
pi2=pi_sym_type('Jacobi',2,sym(1)/2,sym(1))
radacini=solve(pi2==0)
%nodes=[a,radacini]
%coefs=gauss_sym(w,a,b,nodes)

rest_fara_f=coeff_rest(wa,a,b,pi2,3,"Radau")

f=sin(x)
int_gauss_radau=eval(sum(coefs.*subs(f,x,nodes)))

rest_worst=abs(eval(rest_fara_f))