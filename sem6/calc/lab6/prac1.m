x = [1900 1910 1920 1930 1940 1950 1960 1970 1980];
y = [75995 91972 105711 123203 131669 150697 179323 203212 226505];

points = [1975];

res = lagrange_points(points, x, y);
disp(round(res));

x = [1950 1960 1970 1980];
y = [150697 179323 203212 226505];


points = [2018];
res = lagrange_points(points, x, y);
disp(round(res));

