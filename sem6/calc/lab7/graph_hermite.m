function graph_hermite(f, nodes, a, b)
    syms x

    f_sym = f(x);
    
    df_sym = diff(f_sym, x);
    
    f_numeric = matlabFunction(f_sym);
    df_numeric = matlabFunction(df_sym);

    f_values = f_numeric(nodes);
    df_values = df_numeric(nodes);

    points = linspace(a, b, 500);

    [H, dH] = hermite(nodes, f_values, df_values, points);

    f_points = f_numeric(points);
    df_points = df_numeric(points);

    figure;
    
    subplot(2,1,1);
    hold on;
    plot(points, f_points, 'b-', 'LineWidth', 2);
    plot(points, H, 'r--', 'LineWidth', 2);
    legend('True f(x)', 'Hermite H(x)', 'Location', 'best');
    title('Function vs Hermite Interpolation');
    xlabel('x');
    ylabel('Value');
    grid on;
    hold off;

    subplot(2,1,2);
    hold on;
    plot(points, df_points, 'b-', 'LineWidth', 2);
    plot(points, dH, 'r--', 'LineWidth', 2);
    legend('True f''(x)', 'Hermite dH(x)', 'Location', 'best');
    title('Derivative vs Hermite Derivative');
    xlabel('x');
    ylabel('Derivative Value');
    grid on;
    hold off;
end
