n = 5;
%A = randi([-5, 5], n, n); 
A=diag(randi([-5,5])*ones(1,n))+diag(randi([-5,5])*ones(1,n-1),1)+diag(randi([-5,5])*ones(1,n-1),-1);
for i = 1:n
    A(i, i) = sum(abs(A(i, :))) + randi([0,5]);
end
x=(1:n)';
b=A*x;
disp(A);
disp(b);

 disp('jacobi');
 disp(jacobi(A,b));
 disp('gauss-seidel');
 disp(gauss_seidel(A,b));
 disp('sor');
 disp(sor(A,b));