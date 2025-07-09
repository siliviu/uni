function [x]=solve_it(A,b,M)
   
    N=M-A;T=M\N;c=M\b;
    p=inf;
    factor=norm(T,p)/(1-norm(T,p));
    spectral_radius = max(abs(eig(T)));
    if(spectral_radius >= 1)
        disp("spectral_radius mai mare ca 1: "+spectral_radius);
        x=[];
        return;
    end
    x_old=zeros(size(b));
    x=x_old;
    it=0;
    while it==0 || it<1e7
        x=T*x_old+c;
        if norm(x-x_old,p)*factor < eps
            break;
        end
        x_old=x;
        it=it+1;
    end 
end