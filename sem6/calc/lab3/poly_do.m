function poly_do(polynom, polynomRoots)

    if nargin < 2
        polynomRoots = roots(polynom);
    end

    disp(cond_poly(polynom, polynomRoots));
    
    figure(1);
    h = plot(polynomRoots, zeros(1, length(polynomRoots)), 'k.');
    
    set(h, 'Markersize', 20);
    
    hold on;
    
    for i = 1 : 20
    
        % norm dist
        polynom_normdist = polynom + normrnd(0, 1E-10, 1, length(polynom));
        roots_normdist = roots(polynom_normdist);
        h2 = plot(roots_normdist, 'b.');
    
        hold on;
    
        set(h2, 'Markersize', 4);
        
        % uni dist
        polynom_unidist = polynom + unifrnd(0, 1E-10, 1, length(polynom));
        roots_unidist = roots(polynom_unidist);
        
        h3 = plot(roots_unidist, 'r.');
    
        hold on;
    
        set(h3, 'Markersize', 2);
    end
    
    legend("Polynom", "Normal distribution", "Uniform distribution");
    
    hold off;

end
