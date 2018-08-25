#Lista 00

# Exercício 01:
# Crie uma função que, dado dois textos, retorne uma lista (que pode ser vazia)
# em ordem lexicográfica com as palavras que ocorrem em ambos. A função não deve
# ser case sensitive, nesse caso, transforme todo o texto reescrevendo as palavras
# em letra minúscula. Para testar sua função, você pode utilizar os dois poemas
# abaixo, cuja saída esperada é: ['and', 'are', 'is']

def wordinlist(word, list):
  return True if word in list else False

def common_words(text1, text2):  
  words1 = text1.lower()
  words2 = text2.lower()

  #Divide a string em uma lista de palavras
  words1 = words1.split()
  words2 = words2.split()
  
  #Para cada palavra na lista words1 que
  #estiver na lista words2, a adicione
  #no conjunto x
  x = set()
  for word in words1:
    if wordinlist(word, words2):
      x.add(word)

  #Ordene o conjunto em ordem alfabética
  x = sorted(x)

  return x

from nose.tools import assert_equal

poem1 = """The rose is a rose,
And was always a rose.
But the theory now goes
That the apple’s a rose,
And the pear is, and so’s
The plum, I suppose.
The dear only knows
What will next prove a rose.
You, of course, are a rose –
But were always a rose."""

poem2 = """Roses are red,
Violets are blue,
sugar is sweet,
And so are you."""

assert_equal(common_words(poem1, poem2), ['and', 'are', 'is'])

# Exercício 02:
# Crie uma função que, dado uma lista de tuplas representando pares de palavras
# com sua respectiva traduação e uma frase, retorne a frase traduzida. As palavras
# que não possuem uma tradução devem ser impressas como aparecem na frase de entrada.
# Para testar sua função, você pode utilizar a entrada abaixo, cuja saída esperada é:
# o cara tossiu.

def jaspion(tuples_list, sentence):
  #Divide a string em uma lista de palavras
  palavras = sentence.split()
  frase_traduzida = list()

  #Separa a lista de tuplas em listas individuais separadas
  chaves, valores = zip(*tuples_list)  

  for palavra in palavras:
    if palavra in chaves:
      frase_traduzida.append(valores[chaves.index(palavra)])
    else:
      frase_traduzida.append(palavra)

  #Converte a lista em uma string separando cada item por espaço
  return ' '.join(frase_traduzida)

from nose.tools import assert_equal

tl1 = [("galaxy", "cara tossiu"), ("kagayaku", "canalha do"), ("atsuki", "alto que"), ("yuushi", "util")]
s1 = "o galaxy"

assert_equal(jaspion(tl1, s1), "o cara tossiu")