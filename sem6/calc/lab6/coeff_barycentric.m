function w=coeff_barycentric(x,type)
    if nargin < 2, type='none'; end
    w=x;m=length(x)-1;
    switch type
    case 'none'
        for j=0:m
            w(j+1)=1/prod(x(j+1)-x([1:j,j+2:end]));
        end
    case 'equidistant'
        for j=0:m
            w(j+1)=(-1)^j*nchoosek(m,j);
        end
    case 'cebisev1'
        for j=0:m
            w(j+1)=(-1)^j*sin((2*j+1)*pi/(2*m+2));
        end
    case 'cebisev2'
        w(1)=1/2;w(m+1)=(-1)^m/2;
        for j=1:m-1
            w(j+1)=(-1)^j;
        end
    end
end