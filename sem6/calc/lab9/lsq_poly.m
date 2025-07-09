function [c,err]=lsq_poly(x,f,n)
    x=x(:);
    A=ones(length(x), n+1);
    for i=2:n+1
        A(:,i)=x.*A(:, i-1);
    end
    %display(A);
    [c,err]=lsq(A,f');
end