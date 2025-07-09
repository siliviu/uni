% rand 2
% a
disp('1');
numar_max();

% b
% functiile sunt sinsmall, cossmall
% de asemenea my_sin, my_cos 
% care fac reducere la [0, pi/4]
disp('2');
point = 11*pi;

% fara reducere
disp('fara reducere');
realval = 0;
val = sinsmall(point);
display("sin(11pi)="+realval);
display("sin(11pi)~="+val);
display("eroare= "+(val-realval));
display("eroare absoluta= "+abs(realval-val));
display("eroare relativa nu se poate calcula intrucat valoarea reala este 0");

realval = -1;
val = cossmall(point);
display("cos(11pi)="+realval);
display("cos(11pi)~="+val);
display("eroare= "+(val-realval));
display("eroare absoluta= "+abs(realval-val));
display("eroare relativa= "+abs(realval-val)/abs(realval))

display("cos(11pi)="+cossmall(11*pi));

% cu reducere
disp('cu reducere');
reducedpoint = reduce2pi(11*pi);

realval = 0;
% cu reducere la [0, 2pi)
%val = sinsmall(reducedpoint);
% cu reducere la [0, pi/4]
val = my_sin(point);

display("sin(11pi)="+realval);
display("sin(11pi)~="+val);
display("eroare= "+(val-realval));
display("eroare absoluta= "+abs(realval-val));
display("eroare relativa nu se poate calcula intrucat valoarea reala este 0");

realval = -1;
% cu reducere la [0, 2pi)
%val = cossmall(reducedpoint);
% cu reducere la [0, pi/4]
val = my_cos(point);
display("cos(11pi)="+realval);
display("cos(11pi)~="+val);
display("eroare= "+(val-realval));
display("eroare absoluta= "+abs(realval-val));
display("eroare relativa= "+abs(realval-val)/abs(realval))

% c; functia=displayfloat(11)
disp('3')
display("11 = " + displayfloat(11));