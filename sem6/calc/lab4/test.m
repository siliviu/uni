% test 1

[A, b] = generate_system(10)

display('gauss');
display(gauss(A,b));

display('lup');
display(lup(A,b));

% test 2


[A, b] = generate_system_cholesky(10)

display('gauss');
display(gauss(A,b));

display('lup');
display(lup(A,b));

display('cholesky');
display(cholesky(A,b));