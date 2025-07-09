function L=lagrange_barycentric(x,f,X,type)
    if nargin < 4, type='none'; end
    w=coeff_barycentric(x,type);
    L=zeros(size(X));
    for k=1:length(X)
        x_pos_nod=find(x==X(k));
        if x_pos_nod
            L(k)=f(x_pos_nod);
        else
            L(k)=sum(w.*f./(X(k)-x))/sum(w./(X(k)-x));
        end
    end
end
