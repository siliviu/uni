function pade_test(f,x,m,k)
    a=-1,b=1
    fh=matlabFunction(f);
    P=pade_approx(f,m,k,x)
    Ph=matlabFunction(P);
    T=taylor(f,x,0,'order',m+k+1)
    Th=matlabFunction(T);
    clf;hold on;grid on;
    fplot(fh,[a,b],'-g','linewidth',2);
    fplot(Ph,[a,b],'--r','linewidth',1.5);
    fplot(Th,[a,b],'--b','linewidth',1.5);
    h=legend({'f','Pade','Taylor'},'location','northeastoutside');
    set(h,'fontsize',15);
end