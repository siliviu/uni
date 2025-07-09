function x=qr_solve(A,b)
    [Q, R]=qr_decomp(A);
    y=Q'*b;
    x=backsubs(R, y);
end