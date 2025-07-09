function [A, b] = generate_system(n)
    A = randn(n); 
    x = ones(n, 1);
    b = A * x;
end
