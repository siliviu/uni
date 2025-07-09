function test4(f,x,k,x0)
    a=-2;b=2;
    fh=matlabFunction(f);
    T=taylor(f,x,0,'order',k+1)
    Th=matlabFunction(T);
    clf;hold on;grid on;
    aprox = double(subs(T, x, x0-1));
    disp("aprox with degree " + k + ": " + aprox);
    fplot(fh,[a,b],'-g','linewidth',2);
    fplot(Th,[a,b],'--b','linewidth',1.5);
    h=legend({'f', 'Taylor'},'location','northeastoutside');
    set(h,'fontsize',15);
end