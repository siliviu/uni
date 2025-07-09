function cond_num = cond_poly(polynom, polynomRoots)

    if nargin < 2
        polynomRoots = roots(polynom);
    end
    
    n = length(polynom) - 1;                  
    dp = [n : -1 : 1] .* polynom(1 : end - 1);  
    
    diff = polyval(dp, polynomRoots);
    polyv = polyval(abs(polynom(2 : end)), abs(polynomRoots));

    cond_num = polyv ./ (abs(polynomRoots .* diff));
end