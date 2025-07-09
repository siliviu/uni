function L = lagrange_aprox_sym(f, nodes)
    values = arrayfun(f, nodes);
    L = lagrange_sym(nodes, values);
end
