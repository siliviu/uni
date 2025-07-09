f = @(x) exp(x);

n = 2;

y = lsq_ceb1(f, n); 

xx = linspace(-1, 1, 200);
plot(xx, f(xx), 'k--', 'LineWidth', 2, 'DisplayName', 'f(x) = e^x');
hold on;
plot(xx, y(xx), 'b-', 'LineWidth', 2, 'DisplayName', ['Aproximare Chebyshev (n=' num2str(n) ')']);
legend show;
grid on;
xlabel('x'); ylabel('f(x)');
title('Aproximare Least Squares cu Polinoame Chebyshev de ordinul I');
