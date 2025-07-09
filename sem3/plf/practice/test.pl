% candidate([H|_], H).

% candidate([_|T], R) :- candidate(T,R).

% util(_, K, P, K, P, C, C) :- !.

% util(L, CURLEN, CURPROD, K, P, C, R) :- candidate(L, E), 
%                                         not(candidate(C, E)),
%                                         NEWLEN is CURLEN + 1,
%                                         NEWLEN =< K,
%                                         NEWPROD is CURPROD * E,
%                                         NEWPROD =< P,
%                                         util(L, NEWLEN, NEWPROD, K, P, [E|C], R).

% main(L, K, P, R) :- findall(R0, util(L, 0, 1, K, P, [], R0), R).

% ---

util([], 0, SUM, []) :- SUM mod 3 =:= 0.

util([_|T], LEFTLEN, SUM, R) :- util(T, LEFTLEN, SUM, R).


util([H|T], 0, SUM, [H|R]) :- !,
                              NEWSUM is SUM+H,
                              util(T, 0, NEWSUM, R).

util([H|T], LEFTLEN, SUM, [H|R]) :- NEWLEN is LEFTLEN - 1,
                                    NEWSUM is SUM+H,
                                    util(T, NEWLEN, NEWSUM, R).


main(L, N, R) :- findall(R0, util(L,N,0,R0),R).