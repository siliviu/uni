% valley_util(L:list, F:int)
% (i, i) - deterministic
% L - list to check
% F - flag; 0 = descending, 1 = ascending
valley_util([_], 1) :- !.

valley_util([H1 | [H2 | T]], 0) :-  H1 > H2,
                                    !,
                                    valley_util([H2 | T], 0).

valley_util([H1 | [H2 | T]], _) :-  H1 < H2,
                                    valley_util([H2 | T], 1).


% is_valley(L:list)
% (i) - deterministic
% L - list to check
is_valley([H1 | [H2 | T]])  :-  H1 > H2, 
                                valley_util([H2 | T], 0).