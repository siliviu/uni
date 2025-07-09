function pade_exp()
    syms x;
    f = exp(x);
    %disp(pade_approx(f,1,1,x))
    %disp(pade_approx(f,2,2,x))
    %pade_test(f,x,1,1)
    pade_test(f,x,2,2)
    %disp(pade_approx(f,4,4,x))
end