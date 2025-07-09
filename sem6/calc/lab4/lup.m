function x=lup(A,b)
    [L,U,P]=lup_decomp(A);
    y=forwardsubs(L,P*b);
    x=backsubs(U,y);
end