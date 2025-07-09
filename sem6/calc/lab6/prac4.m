function prac4(type,col,m)
    %prac4({'equidistant','cebisev1','cebisev2'},{'r','g','m'},11)
    if nargin < 3, m=40; end
    if nargin < 2, col={'r','g'}; end
    if nargin < 1, type={'equidistant','cebisev2'}; end
    
    clf; hold on; grid on; xlim([-5 5]); xticks(-5:5);axis square;
    f=@(x) 1./(1+x.^2);
    x=linspace(-5,5,501);
    plot(x,f(x),'b','linewidth',2);
    l={'f'};
    for i=1:length(type)
        nodes=gen_nodes(-5,5,m,type{i});
        values=f(nodes);
        plot(nodes,values,'ok','markerfacecolor',col{i},'markersize',8);
        plot(x,lagrange_barycentric(nodes,values,x),col{i},'linewidth',2)
        l{end+1}=type{i};
        l{end+1}=['L cu ' type{i}];
    end
    legend(l,"location", "northeastoutside")
    set(gca,"fontsize", 17)
    axis([-5.5 5.5 -0.5 1.5])
end