function R=lagrange_points(points, nodes,values)
    lf = lagrange_sym(nodes, values);
    R = zeros(size(points));
    
    for i = 1:length(points)
        R(i) = double(subs(lf,points(i)));
    end
end
