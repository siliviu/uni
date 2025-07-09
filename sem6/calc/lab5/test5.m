% rand 1

% 1

disp('sistem din test:');

A = [22 33 34 33
     46 2 38 9;
     40 43 38 36;
     48 47 20 2];

b = [122; 95; 157; 117];

disp('jacobi');
disp(jacobi(A,b));
disp('gauss-seidel');
disp(gauss_seidel(A,b));

disp('sistem care sa se poata rezolva cu jacobi + gauss-seidel:');
A = [22 3 4 3
     2 46 8 9 ;
     4 3 38 6;
     8 7 0 48]

b = [32; 65; 51; 63]

disp('jacobi');
disp(jacobi(A,b));
disp('gauss-seidel');
disp(gauss_seidel(A,b));

% 2

% generat astfel incat sa fie diagonal dominanta 
% (si sa se poata aplica metoda)
n = 5;
A = randi([-5, 5], n, n); 
for i = 1:n
    A(i, i) = sum(abs(A(i, :))) + randi([0,5]);
end
x=(1:n)';
b=A*x;

disp('sor');
disp(sor(A,b));