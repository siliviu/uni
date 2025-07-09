
function numar_max = calculeaza_numar_max()
    numar_max = 2 - eps;
    while isfinite(numar_max * 2)
        numar_max = numar_max * 2;
    end
    disp("MAX: real:" + realmax + ",calc: " + numar_max)
end
