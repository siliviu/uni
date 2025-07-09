nodes=[0 pi/6 pi/4 pi/3 pi/2];
values=[0 1/2 sqrt(2)/2 sqrt(3)/2 1];
points = [pi/12];

disp(lagrange_points(points, nodes, values));
disp(sin(pi/12));

values=[1 sqrt(3)/2 sqrt(2)/2 1/2 0];

disp(lagrange_points(points, nodes, values));
disp(cos(pi/12));