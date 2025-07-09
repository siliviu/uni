syms x
f = log(1+x);

% a), b)
% pentru a vedea TnF(x) impreuna cu graficul 
% si aproximarea pentru ln(1.5)
% se ruleaza cu test4(f,x,n,1.5)

%test4(f,x,1, 1.5);
%test4(f,x,2, 1.5);
test4(f, x,3,1.5);
%test4(f,x,4, 1.5);
%test4(f,x,5, 1.5);

% c)


for n = 1:10
    r = 0.5^(n+1)/(n+1);     
    disp([n,r])
    if abs(r) < 1e-3 
        fprintf('first n where abs(rest(n)) < 1e-3 is: %d\n', n);
        break;
    end
end
  
% folosindu-ne de eroare serii taylor, care este alternanta
% obtinem raspunsul corect cu 3 zecimale
% pentru gradul n=7
disp("actual: " + log(1.5))
test4(f,x, 7, 1.5);
test4(f,x, 6, 1.5);



