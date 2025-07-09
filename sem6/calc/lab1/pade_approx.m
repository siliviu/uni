function ret = pade_approx(f, m, k, x)
    if k == 0 
        ret = taylor(f, 'order', m + 1);
        return;
    end
    
    max_order = m + k;
    coef = sym(zeros(1, max_order + 1));
    
    for n = 0:max_order
        coef(n + 1) = subs(diff(f, n), 0) / factorial(n); 
    end

    c = sym(zeros(1, k)); 
    r = sym(zeros(1, k)); 
    d = sym(zeros(1, k));

    for i = 0:k-1
        c(i + 1) = coef(m + i + 1);
        r(i + 1) = coef(m - i + 1);
        d(i + 1) = -coef(m + i + 2);
    end

    C = toeplitz(c, r);
    b = C \ d';
    b = [1; b];
    
    a = sym(zeros(m + 1, 1));
    for j = 0:m
        for l = 0:min([j, k])
            a(j + 1) = a(j + 1) + coef(j - l + 1) * b(l + 1);
        end
    end

    ret = (x.^(0:m) * a) / (x.^(0:k) * b);
end
