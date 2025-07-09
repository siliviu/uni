function graph_cubic(a, b, fa, fb, dfa, dfb)
    % Nodes
    nodes = [a, b];
    
    f_values = [fa, fb];
    
    df_values = [dfa, dfb];
    
    points = linspace(a, b, 200);
    
    [H, dH] = hermite(nodes, f_values, df_values, points);
    
    figure;
    subplot(2,1,1);
    plot(points, H, 'r-', 'LineWidth', 2);
    hold on;
    plot(nodes, f_values, 'ko', 'MarkerFaceColor', 'k'); % plot the interpolation points
    title('Cubic Hermite Interpolation H(x)');
    xlabel('x');
    ylabel('H(x)');
    grid on;
    hold off;
    
    subplot(2,1,2);
    plot(points, dH, 'b-', 'LineWidth', 2);
    hold on;
    plot(nodes, df_values, 'ko', 'MarkerFaceColor', 'k'); % plot the slopes
    title('Derivative of Cubic Hermite Interpolation dH(x)');
    xlabel('x');
    ylabel('dH(x)');
    grid on;
