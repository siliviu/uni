% desc(n:int, nr:int, start:int, r:list)

decomp(0,_,1,[]) :- !.
decomp(N,Nr,0,R):-  Nr < N,  
                    Nr1 is Nr+1,
                    decomp(N,Nr1,0,R).
decomp(N,Nr,_,[Nr|R]):- Nr =< N,
                        N1 is N-Nr,
                        Nr1 is Nr+1,
                        decomp(N1,Nr1,1,R).

decompose(N, L) :- findall(R,decomp(N,0,0,R),L).
