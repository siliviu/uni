x = [2010 2012 2014 2016];
y = [2500 2700 3100 3600];

point = 2025;

R=lagrange_sym(x, y);

% polinom
disp(R);

% populatie 2025
disp(floor(subs(R,point)));


% grafic
f = matlabFunction(R);

t_vals = linspace(2010, 2016, 100);
y_vals = f(t_vals);

figure;
plot(t_vals, y_vals, 'b-', 'LineWidth', 2); hold on;

plot(x, y, 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');

xlabel('An');
ylabel('Population');
title('Polinom Lagrange');
grid on;
legend('Polinom Lagrange', 'Puncte', 'Location', 'northwest');