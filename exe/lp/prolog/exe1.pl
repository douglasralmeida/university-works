/* Lista 6 - Douglas Rodrigues de Almeida */

/* 1 - Y eh uma lista com os N primeiros elementos da lista X. */
pega(N, X, Y) :- append(Y,_,X), length(Y, N).

/* 2 - Y eh a mesma lista X mas sem a primeira ocorrencia de A em X, se essa ocorrer. */
rem(_, [], []).
rem(A, [A|AS], AS).
rem(A, [Y|YS], [Y|YS1]) :- rem(A, YS, YS1).

/* 3 - Y eh a mesma lista X mas sem todas as ocorrencias de A em X. */
remTodos(_, [], []) :- !.
remTodos(A, [A|AS], Y) :- remTodos(A, AS, Y).
remTodos(A, [Y|YS], [Y|YS1]) :- A \= Y, !, remTodos(A, YS, YS1).

/* 4 - X1 e X2 sao a metade esquerda e a metade direita da lista X; se X tiver um numero impar de elementos, X1 tem um elemento a mais que X2. */
quebraNoMeio(X, X1 ,X2) :- length(X, N), Meio is ceil(N / 2), length(X1, Meio), length(X2, L), L is N-Meio, append(X1, X2, X).

/* 5 - X eh a lista ordenada resultante da intercalacao dos elementos das listas ordenadas X1 e X2. */
intercala([], [], []).
intercala(X, [], X).
intercala([], X, X).
intercala([X|XS], [Y|YS], [X|ZS]) :- X =< Y, intercala(XS, [Y|YS], ZS).
intercala([X|XS], [Y|YS], [Y|ZS]) :- X > Y, intercala([X|XS], YS, ZS).

/* 6 - Y eh a lista ordenada com os mesmos elementos de X. Devem ser usados intercala e quebraNoMeio. */
ordenaInterc([], []).
ordenaInterc([X], [X]).
ordenaInterc([X, Y], [X, Y]) :- X =< Y, !.
ordenaInterc([X, Y], [Y, X]) :- X > Y, !.
ordenaInterc(X, Y) :- length(X, L), L > 0, quebraNoMeio(X, XS1, XS2), ordenaInterc(XS1, YS1), ordenaInterc(XS2, YS2), intercala(YS1, YS2, Y), !.

/* 7 - Z eh a intersecao dos conjuntos X e Y, onde conjuntossao representados por listas, considerando que nao ocorrem elementos repetidos. */
intersec([], _, []).
intersec(X, Y, Z) :- false.


