function [I,nodes,coefs]=gauss_quad_type(type,f,n,aa,bb)
    if nargin < 5, bb=[]; end
    if nargin < 4, aa=[]; end

    [alpha,beta]=type_coeff(type,0:n-1,aa,bb);
    [I,nodes,coefs]=gauss_quad(f,alpha,beta);
end