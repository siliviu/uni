function x=sor(A,b,omega)
    M=diag(diag(A));N=M-A;T=M\N;
    rho=max(abs(eig(T))); 
    optim = 2/(1+sqrt(1-rho^2));
    display("omega opt " + optim);
    if nargin < 3
        omega= optim;
    end
    M=1/omega*diag(diag(A))+tril(A,-1);
    x=solve_it(A,b,M); 
end