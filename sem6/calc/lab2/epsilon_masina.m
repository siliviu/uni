function eps_masina = calculeaza_epsilon_masina()
    eps_masina = 1;
    while 1 + eps_masina > 1
        eps_masina = eps_masina / 2;
    end
    eps_masina = eps_masina * 2;
    disp("EPS real: " + eps + ", calc: " + eps_masina)
end