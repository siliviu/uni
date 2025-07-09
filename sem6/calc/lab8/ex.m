nodes=[0 3 5 8 13 16];
X=linspace(0,16,1000);
values=[300  225  320  560  690 400];

names={'nodes', 'complete' 'natural' 'c2' 'boor'};
splineComplete=eval_spline(nodes, values, names{2}, [-1 1], X);
splineNaturale=eval_spline(nodes, values, names{3}, [], X);
splineDerivative2=eval_spline(nodes, values, names{4}, [-10 10], X);
splineDeBoor=eval_spline(nodes, values, names{5}, [], X);

clf; hold on; grid on;

plot(nodes, values, 'ok', 'markerfacecolor', 'g', 'markersize', 8);
plot(X, splineComplete);
plot(X, splineNaturale);
plot(X, splineDerivative2);
plot(X, splineDeBoor);
legend(names)