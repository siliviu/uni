function x=gen_nodes(a,b,m,type)
    switch type
    case 'equidistant'
        x=linspace(a,b,m);
    case 'cebisev1'
        j=0:m-1;
        x=cos((2*j+1)*pi/(2*m));
        x=(a+b)/2+(b-a)/2*x;
    case 'cebisev2'
        j=0:m-1;
        x=cos(j*pi/(m-1));
        x=(a+b)/2+(b-a)/2*x;
    end
end