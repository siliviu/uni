function [I,nodes,coefs]=gauss_quad(f,alpha,beta)
    J=diag(alpha)+diag(sqrt(beta(2:end)),-1)+diag(sqrt(beta(2:end)),1);
    [V,nodes]=eig(J,'vector');
    coefs=beta(1)*V(1,:).^2;
    I=coefs*f(nodes);
    nodes=nodes';
end