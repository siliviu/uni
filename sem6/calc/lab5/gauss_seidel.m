function x=gauss_seidel(A,b)
    x=solve_it(A,b,diag(diag(A))); 
end