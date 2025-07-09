 n=10;
 A=diag(5*ones(1,n))...
 +diag(-ones(1,n-1),1)...
 +diag(-ones(1,n-1),-1)...
 +diag(-ones(1,n-3),3)...
 +diag(-ones(1,n-3),-3)
 b=[3;2;2;ones(n-6,1);2;2;3]

 disp('jacobi');
 disp(jacobi(A,b));
 disp('gauss-seidel');
 disp(gauss_seidel(A,b));
 disp('sor');
 disp(sor(A,b));

 A=diag(5*ones(1,n))...
 +diag(-ones(1,n-1),1)...
 +diag(-ones(1,n-1),-1)...
 +diag(-ones(1,n-3),3)...
 +diag(-ones(1,n-3),-3)
 b=[3;2;2;ones(n-6,1);2;2;3]
 
 disp('jacobi');
 disp(jacobi(A,b));
 disp('gauss-seidel');
 disp(gauss_seidel(A,b));
 disp('sor');
 disp(sor(A,b));