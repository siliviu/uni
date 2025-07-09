function area=adquad(f, a, b, met, eps)
    m=4;
    if abs(met(f, a, b, m) - met(f, a, b, 2*m)) < eps
        area = met(f, a, b,2*m);
    else
        area = adquad(f,a, (a + b)/2, met,eps) + adquad(f,(a + b)/2, b, met,eps);
    end
end