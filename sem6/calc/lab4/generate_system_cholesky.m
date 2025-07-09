function [A, b] = generate_system_cholesky(n)
    R=rand(n,n);
    A = R*R'; 
    %x = ones(n, 1);
    x=(1:n)';
    b = A * x;
end
