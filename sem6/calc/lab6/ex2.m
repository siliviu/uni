function ex2()
    do(4, [100 121 81 144])
end

function do(m, nodes)

    syms x;
    hold on;
    grid on;
    legend_entries = cell(1, m);
    colors = lines(m); 
    
    x_vals = linspace(min(nodes) - 1, max(nodes) + 1, 500);

    for i = 1:m
        values = zeros(1, m);
        values(i) = 1; 
        Li_sym = lagrange_sym(nodes, values);  
        Li_fun = matlabFunction(Li_sym);       
        y_vals = Li_fun(x_vals);               
        plot(x_vals, y_vals, 'LineWidth', 2, 'Color', colors(i,:));
        legend_entries{i} = ['L_', num2str(i), '(x)'];
    end

    title('Fundamental Lagrange Polynomials');
    xlabel('x');
    ylabel('L_i(x)');
    legend(legend_entries, 'Location', 'Best');
    hold off;
end
