function y=reduce2pi(x)
    precision=20;
    twopi=vpa(2*sym(pi),precision);
    x=vpa(x,precision);
    y=double(mod(x,twopi));
end 