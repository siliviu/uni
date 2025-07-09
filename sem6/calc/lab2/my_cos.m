function y=my_cos(x)

    x=reduce2pi(x);

    sign=1;
    if x>3*pi/2
        x=2*pi-x;
    elseif x>pi
        x=x-pi; sign=-1;
    elseif x>pi/2
        x=pi-x; sign=-1;
    end

    if x<=pi/4
        y=cossmall(x);
    else
        y=sinsmall(pi/2-x);
    end
    
    y=sign*y;
end