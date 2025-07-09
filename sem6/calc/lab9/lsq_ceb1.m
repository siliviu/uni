function y=lsq_ceb1(f,n)
    T=@(n,t) cos(n*acos(t));
    c0=integral(@(t) f(t)./sqrt(1-t.^2),-1,1)/pi;
    y=@(t) c0*T(0,t);
    for i=1:n
        ci=integral(@(t) T(i,t).*f(t)./sqrt(1-t.^2),-1,1)*2/pi;
        y=@(t) y(t)+ci*T(i,t);
    end
end