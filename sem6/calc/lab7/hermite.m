function [H,dH]=hermite(nodes,f,df,points)
    dif=divdif2(nodes,f,df);
    coefs=dif(1,:);
    z=repelem(nodes,2);
    H=[];dH=[];
    for k=1:length(points)
        P=1; DP=0; H(k)=coefs(1); dH(k)=0;
        for i=1:length(z)-1
            DP=DP*(points(k)-z(i))+P;
            P=P*(points(k)-z(i));
            H(k)=H(k)+coefs(i+1)*P;
            dH(k)=dH(k)+coefs(i+1)*DP;
        end
    end
end