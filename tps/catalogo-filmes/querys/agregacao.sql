-- NÚMERO DE FILMES DA ATRIZ MERYL STREEP
SELECT count(*) FROM filmes JOIN filme_ator ON filmes_idfilme = idfilme LEFT JOIN pessoas ON idpessoa = pessoas_idpessoa WHERE nomeartistico = 'Meryl Streep' ORDER BY nometraduzido;

-- NÚMERO DE FILMES POR GÊNERO
SELECT descricao, count(*) FROM filmes JOIN filme_genero ON filmes_idfilme = idfilme LEFT JOIN generos ON idgenero = generos_idgenero GROUP BY descricao;

-- NÚMERO DE PESSOAS POR PAIS
SELECT nome, count(*) FROM pessoas JOIN paises ON pais = idpais GROUP BY nome;