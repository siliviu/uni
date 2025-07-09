% 1
A = [22 33 34 33
     46 2 38 9;
     40 43 38 36;
     48 47 20 2];

b = [122; 95; 157; 117];

display('1.');
display('lup');
display(lup(A,b));

display('qr');
display(qr_solve(A,b));


% 2

display('2.');
[A,b] = generate_system_cholesky(10);
display('gauss');
display(gauss(A,b));
display('cholesky');
display(cholesky(A,b));