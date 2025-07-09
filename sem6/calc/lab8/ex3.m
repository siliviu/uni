nodes = 0:11;

values_x = [3, 1.75, 0.90, 0, 0.50, 1.50, 3.25, 4.25, 4.25, 3, 3.75, 6.00];
values_y = [4, 1.60, 0.50, 0, 1.00, 0.50, 0.50, 2.25, 4.00, 4, 4.25, 4.25];

X = linspace(0, 11, 1000);

vals_x = eval_spline(nodes, values_x, 'natural', [], X);
vals_y = eval_spline(nodes, values_y, 'natural', [], X);

figure;
plot(vals_x, vals_y, 'b-', 'LineWidth', 2);
hold on;
plot(values_x, values_y, 'ro', 'MarkerFaceColor', 'r'); % plot original points
title('Handwritten Letter using Parametric Splines');
xlabel('x');
ylabel('y');
axis equal;
grid on;
hold off;
