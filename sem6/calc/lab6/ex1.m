nodes=[100 121 81 144];
values=[10 11 9 12];
points = [64, 169];



disp(lagrange_sym(nodes,values));
disp(lagrange_points(points, nodes, values));