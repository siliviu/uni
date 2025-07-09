function x=jacobi(A,b)
    x=solve_it(A,b,tril(A)); 
end