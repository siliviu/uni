function y=my_sin(x)

    x=reduce2pi(x); 

    sign=1;
    if x>3*pi/2
        x=2*pi-x; sign=-1;
    elseif x>pi
        x=x-pi; sign=-1;
    elseif x>pi/2
        x=pi-x;
    end

    if x<=pi/4
        y=sinsmall(x);
    else
        y=cossmall(pi/2-x);
    end
    
    y=sign*y;
end