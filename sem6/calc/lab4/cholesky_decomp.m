function x=cholesky_decomp(A)
    n=length(A);
    x=A;
    for k=1:n
        for j=k+1:n
            x(j,j:n)=x(j,j:n)-x(k,j:n)*x(k,j)'/x(k,k);
        end
        x(k,k:n)=x(k,k:n)/sqrt(x(k,k));
    end
    x=triu(x);
end