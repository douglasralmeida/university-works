-- EXIBIR FILMES DE TERROR CADASTRADOS EM ORDEM ALFABÉTICA
SELECT nometraduzido FROM filmes JOIN filme_genero ON filmes_idfilme = idfilme LEFT JOIN generos ON idgenero = generos_idgenero WHERE descricao = 'Terror' ORDER BY nometraduzido;

-- EXIBIR FILMES DA ATRIZ SONIA BRAGA EM ORDEM ALFABÉTICA
SELECT nometraduzido FROM filmes JOIN filme_ator ON filmes_idfilme = idfilme LEFT JOIN pessoas ON idpessoa = pessoas_idpessoa WHERE nomeartistico = 'Sonia Braga' ORDER BY nometraduzido;

-- EXIBIR FILMES DO DIRETOR STEVEN SPIELBERG EM ORDEM ALFABÉTICA
SELECT nometraduzido FROM filmes JOIN filme_diretor ON filmes_idfilme = idfilme LEFT JOIN pessoas ON idpessoa = pessoas_idpessoa WHERE nomeartistico = 'Steven Spielberg' ORDER BY nometraduzido;
