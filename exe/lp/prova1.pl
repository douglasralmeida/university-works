/*max(A,B,M): M e o maior entre A e B (supondo A e B comparaveis com >=)*/
max(A,B,A) :- A > B.
max(A,B,B) :- B >= A.


/* sublista(L, X) = L é uma sublista de X */
sublista([], _).
sublista([A|L], [B|X]) :- (A is B, sublista(L, X)); sublista([A|L], X).

/* subseq(L, X) = L é uma subsequencia de X */
concac([], A, A).
concac([X|XS], A, [X|YS]) :- concac(XS, A, YS).
subseq(L, X) :- concac(_, X2, X), concac(L, _, X2).