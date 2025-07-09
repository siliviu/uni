
function numar_min_normalizat = calculeaza_numar_min_normalizat()
    numar_min_normalizat = 1;
    while numar_min_normalizat / 2 > 0
        numar_min_normalizat = numar_min_normalizat / 2;
    end;
    numar_min_nenormalizat = numar_min_normalizat / eps;
    disp("MIN: real: " + realmin + ",calc nenorm: " + numar_min_normalizat + ", calc norm: " + numar_min_nenormalizat)
end