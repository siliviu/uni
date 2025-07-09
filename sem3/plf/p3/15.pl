% desc(N:int, Nr:int, Start:int, R:list)
% (i, i, i, o) nedet
% N - number to decompose
% Nr - current term to try
% Start - 0/1 flag if we are adding to result or not
% R - result

decomp(0, _, 1, []) :- !.

decomp(N, Nr, 0, R) :-  Nr < N,  
                        Nr1 is Nr + 1,
                        decomp(N, Nr1, 0, R).

decomp(N, Nr, _, [Nr | R]) :-   Nr =< N,
                                N1 is N - Nr,
                                Nr1 is Nr + 1,
                                decomp(N1, Nr1, 1, R).

% decompose(N:int, L:list)
% (i, o) nedet
% N - number to decompose
% L - list with all possible decompositions

decompose(N, T) :- findall(R, decomp(N, 0, 0, R), [_ | T]).
