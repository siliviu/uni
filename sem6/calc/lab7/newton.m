function L=newton(nodes,f,points)
    dif=divdif1(nodes,f);
    coefs=dif(1,:);
    L=[];
    for k=1:length(points)
        P=1; L(k)=coefs(1);
        for i=1:length(nodes)-1
            P=P*(points(k)-nodes(i));
            L(k)=L(k)+coefs(i+1)*P;
        end
    end
end