x = [1, 2, 3, 4, 5];        
f = [2, 6, 1, 9 ,8];     
n = 3;

[c, err] = lsq_poly(x, f, n);

xx = linspace(min(x), max(x), 100);
yy = zeros(size(xx));
for i = 1:n
    yy = yy + c(i) * xx.^(i-1);
end

plot(x, f, 'ro', 'MarkerSize', 8, 'DisplayName', 'Date');
hold on;
plot(xx, yy, 'b-', 'LineWidth', 2, 'DisplayName', 'Aproximare LS');
legend show;
grid on;
title(['Aproximare Least Squares cu polinom de grad ', num2str(n-1)]);
xlabel('x'); ylabel('f(x)');