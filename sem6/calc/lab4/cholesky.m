function x=cholesky(A,b)
    R=cholesky_decomp(A);
    y=forwardsubs(R',b);
    x=backsubs(R,y);
end