function pade_log()
    syms x;
    f = log(1+x);
    %disp(pade_approx(f,2,2,x))
    %disp(pade_approx(f,3,1,x))
    %pade_test(f,x,2,2)
    pade_test(f,x,3,1)
    %disp(pade_approx(f,2,1,x))
end