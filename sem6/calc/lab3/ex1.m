A = [10 7 8 7;
     7 5 6 5;
     8 6 10 9;
     7 5 9 10];

b = [32; 23; 33; 31];

x_exact = A \ b;

disp(x_exact); 

b_perturbed = [32.1; 22.9; 33.1; 30.9];
x_perturbed_b = A \ b_perturbed;

relative_input_error = norm(b_perturbed - b) / norm(b);
relative_output_error = norm(x_perturbed_b - x_exact) / norm(x_exact);
condition_number_estimate = relative_output_error / relative_input_error;

disp('Perturbation in b:');
disp('New Solution:');
disp(x_perturbed_b);
disp(['Relative Input Error: ', num2str(relative_input_error)]);
disp(['Relative Output Error: ', num2str(relative_output_error)]);
disp(['Error Amplification (Condition Estimate): ', num2str(condition_number_estimate)]);

% b
A_perturbed = [10   7   8.1 7.2;
               7.08 5.04 6   5;
               8    5.98 9.89 9;
               6.99 4.99 9   9.98];

x_perturbed_A = A_perturbed \ b;

relative_input_error_A = norm(A_perturbed - A) / norm(A);
relative_output_error_A = norm(x_perturbed_A - x_exact) / norm(x_exact);
condition_number_estimate_A = relative_output_error_A / relative_input_error_A;

disp('Perturbation in A:');
disp('New Solution:');
disp(x_perturbed_A);
disp(['Relative Input Error: ', num2str(relative_input_error_A)]);
disp(['Relative Output Error: ', num2str(relative_output_error_A)]);
disp(['Error Amplification (Condition Estimate): ', num2str(condition_number_estimate_A)]);
