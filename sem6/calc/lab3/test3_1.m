A = [14 35 22 10;
     3 16 20 25;
     5 48 39 23;
     42 2 40 33];

b = [81;64;115;117];

x_exact = A \ b;

disp('Old Solution:');
disp(x_exact); 

A_perturbed = [14.2 35.2 22.5 10.3;
               3.3 15.7 19.8 24.8;
               4.8 47.6 39.1 23.0;
               42.2 2.0 39.7 33.2];

x_perturbed_A = A_perturbed \ b;

relative_input_error_A = norm(A_perturbed - A) / norm(A);
relative_output_error_A = norm(x_perturbed_A - x_exact) / norm(x_exact);
condition_number_estimate_A = relative_output_error_A / relative_input_error_A;

disp('Perturbation in A');
disp('New Solution:');
disp(x_perturbed_A);
disp(['Error Amplification (Condition Estimate): ', num2str(condition_number_estimate_A)]);