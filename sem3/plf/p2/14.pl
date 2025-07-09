% aux(A:int, F:int, A1:int, F1:int)
% (i,i,o,o)
% A - digit
% F - carry flag
% A1 - new digit
% F1 - new carry flag
aux(0, 1, 9, 1) :- !.
aux(A, 1, A1, 0) :- A1 is A-1, !.
aux(A, 0, A, 0).

% remove_redundant(L:list, A:list)
% (i, o)
% L - given list
% A - answer list
remove_redundant([0, A|L], [A|L]) :- !.
remove_redundant(L, L).

% predecessor_util(L:list, A:list, F:int)
% (i,o,o)
% L - given list
% A - answer list
% F - carry flag

predecessor_util([], [], 1) :- !.

predecessor_util([H|T], [H1|T1], F1):-  predecessor_util(T,T1,F),
                                        aux(H,F,H1,F1).

% predecessor(L:list, A:list)
% (i,o)
% L - given list
% A - answer list
predecessor(L, A1):- predecessor_util(L,A,_),
                     remove_redundant(A,A1).

% predecessor_list(L: list, A:list)
% (i,o)
% L - given list
% A - answer list
predecessor_list([], []).
predecessor_list([H|T], [H1|A]) :-  predecessor(H,H1),
                                    !,
                                    predecessor_list(T,A).
                            
predecessor_list([H|T], [H|A]) :-   predecessor_list(T,A).



% predecessor([1,4,5,0,1], L).
% predecessor([1,4,5,0,0], L).
% predecessor([1,0,0,0], L).
% predecessor([1], L).

% predecessor_list([1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6], L).