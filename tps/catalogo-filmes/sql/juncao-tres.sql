-- EXIBIR FILMES DE COMÉDIA DE JIM EM ORDEM ALFABÉTICA
SELECT nometraduzido FROM filmes JOIN filme_ator ON filme_ator.filmes_idfilme = idfilme JOIN pessoas ON idpessoa = pessoas_idpessoa JOIN filme_genero ON filme_genero.filmes_idfilme = idfilme JOIN generos ON generos_idgenero = idgenero WHERE nomeartistico = 'Jim Carrey' AND descricao = 'Comédia' ORDER BY nometraduzido;

-- EXIBIR FILMES COM ATOR BRASILEIRO EM ORDEM ALFABÉTICA
SELECT nometraduzido FROM filmes JOIN filme_ator ON filmes_idfilme = idfilme JOIN pessoas ON idpessoa = pessoas_idpessoa JOIN paises ON pais = idpais WHERE nome = 'Brasil' GROUP BY nometraduzido ORDER BY nometraduzido;

-- EXIBIR FILMES COM DIRETOR BRASILEIRO EM EM ORDEM ALFABÉTICA
SELECT nometraduzido FROM filmes JOIN filme_diretor ON filmes_idfilme = idfilme JOIN pessoas ON idpessoa = pessoas_idpessoa JOIN paises ON pais = idpais WHERE nome = 'Brasil' GROUP BY nometraduzido ORDER BY nometraduzido;