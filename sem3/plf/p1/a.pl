% change(L:list, I:int, V:int, A:list)
% I I I O
% L = given list
% I = index to replace element (assumed to be >= 1)
% V = value
% A = answer list

change([], I, _, []).

change([H | T], 1, V, [V | T]) :- !.

change([H | T], I, V, [H | A1]) :- I > 1,
                            I1 is I - 1,
                            !,
                            change(T, I1, V, A1).
                    

% change2(L:list, O:int, N:int, A:list)
% I I I O
% L = given list
% O = values to replace
% N = replacement values 
% A = answer list

change2([], _, _, []).


change2([H | T], I, V, [V | A1]) :- H is I,
                                    !,
                                    change2(T, I, V, A1).


change2([H | T], I, V, [H | A1]) :- change2(T, I, V, A1).


/*
change([1,2,3,4,5,6,7],4,44,B).
change([1,2,3],5,44,B).

change2([1,1,2,2,1,2,1,2,1],2,3,B).
change2([1,1,2,2,1,2,1,2,1],1,2,B).
change2([1,2,1,2,1],3,4,B).
*/