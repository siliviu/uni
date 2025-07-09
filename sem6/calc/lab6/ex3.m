function ex3()
    f = @(x) exp(x);
    plot_lagrange_vs_function(f, 0, 10, 5)
end

function plot_lagrange_vs_function(f, a, b, n)
    nodes = linspace(a, b, n);

    L_sym = lagrange_aprox_sym(f, nodes);
    L_fun = matlabFunction(L_sym);

    x_vals = linspace(a - 0.5, b + 0.5, 500);

    f_vals = arrayfun(f, x_vals);
    L_vals = L_fun(x_vals);

    figure;
    plot(x_vals, f_vals, 'b', 'LineWidth', 2); hold on;
    plot(x_vals, L_vals, 'r', 'LineWidth', 1);

    title(['Lagrange Interpolation with n = ', num2str(n)]);
    xlabel('x'); ylabel('y');
    legend('f(x)', 'Lagrange Interpolant', 'Interpolation Nodes', 'Location', 'Best');
    grid on;
end
