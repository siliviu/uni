% sublist(L:list, N:int, M:int, A:list)
% I I I O
% L = given list
% N = left index of sublist
% M = right index of sublist (assumed to be >= N)
% A = answer list

sublist([], _, _, []) :- !.
sublist(_, _, 0, []) :- !.

sublist([H | T], N, M, A) :- N \= 1,
                            !,
                            N1 is N-1,
                            M1 is M-1,
                            sublist(T, N1, M1, A).


sublist([H | T], N, M, [H|A]) :- M1 is M-1,
                                sublist(T, N, M1, A).

/*
sublist([1,2,3,4,5,6,7,8],4,6,B).
sublist([1,2,3,4,5,6,7,8],5,10,B).
sublist([1,2,3,4,5,6,7,8],10,12,B).
*/