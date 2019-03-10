## Escreva uma funcao enumerate que se comporte como enumerate.
## A funcao enumerate recebe um iterador it e retorna um iterador 
## sobre pares (i,v), onde i e um indice e v um valor, do iterador it.

def _enumerate(it):
    i = 0
    while i < len(it):
        yield (i, it[i])
        i += 1

lista = list(_enumerate(['a', 'b', 'c']))
print(lista)

for i, c in _enumerate(['1', '2', '3']):
    print(i, c)