/* Lista 6 - Douglas Rodrigues de Almeida */

/* 1 - soma(X, S) = s é a soma dos itens de X */
soma([], 0).
soma([A|X], B) :- soma(X, Y), B is A + Y.

/* 2 - pref(X, Y) = x é prefixo de Y */
pref([], _).
pref([A|X], [A|Y]) :- pref(X, Y).

/* 3 - suf(X,Y) = X é sufixo de Y. */
suf([], _).
suf([A|X], [A|X]).
suf([A|X], [_|Y]) :- suf([A|X], Y).

/* 4 - sublista(L, X) = L é uma sublista de X */
sublista([], _).
sublista([A|L], [B|X]) :- (A is B, sublista(L, X)); sublista([A|L], X).

/* 5 - subseq(L, X) = L é uma subsequencia de X */
concac([], A, A).
concac([X|XS], A, [X|YS]) :- concac(XS, A, YS).
subseq(L, X) :- concac(_, X2, X), concac(L, _, X2).

/* 6 - X1 e X2 sao a metade esquerda e a metade direita da lista X; se X tiver um numero impar de elementos, X1 tem um elemento a mais que X2. */
quebraNoMeio(X, X1 ,X2) :- length(X, N), Meio is ceil(N / 2), length(X1, Meio), length(X2, L), L is N-Meio, append(X1, X2, X).
