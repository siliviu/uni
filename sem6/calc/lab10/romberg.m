function area=romberg(f,a,b,n)
    T=NaN(n);
    for i=1:n
        T(i,1)=reptrap(f,a,b,2^(i-1));
        for j=2:i
            T(i,j)=(4^(-j+1)*T(i-1,j-1)-T(i,j-1))/(4^(-j+1)-1);
        end
    end
    area=T(n,n);
end