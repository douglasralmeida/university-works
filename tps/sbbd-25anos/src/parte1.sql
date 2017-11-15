/*QUESTAO 1*/
SELECT edicao_num, ano, cNome FROM edicao JOIN (
    SELECT id AS cid, nome AS cNome FROM cidade WHERE estado_id = (
        SELECT id FROM estado WHERE	sigla = 'SP'))
AS temp ON cidade_id = cid;

/*QUESTAO 2*/
SELECT nome FROM pesquisador LEFT JOIN (
    SELECT pesquisador_id, nome AS anome FROM pesquisador JOIN
        autor ON pesquisador.id = pesquisador_id)
AS temp ON pesquisador.id = pesquisador_id WHERE pesquisador_id IS NULL;

/*QUESTAO 3*/
SELECT nome AS peNome, paNome FROM pesquisador JOIN (
	SELECT id AS paId, nome As paNome FROM pais WHERE nome != 'brasil')
AS temp ON pais_id = paId WHERE sexo = 'F';

/*QUESTAO 4*/
SELECT pesquisador.nome AS pNome, titulo FROM pesquisador JOIN
    autor ON pesquisador.id = pesquisador_id JOIN
    instituicao ON instituicao_id = instituicao.id JOIN
    autoria ON autor.id = autor_id JOIN
    artigo ON artigo_id = artigo.id
WHERE instituicao.nome = 'UFMG' and sexo = 'M';

/*QUESTAO 5*/
SELECT artigo.titulo AS aTitulo, sessao.titulo AS sTitulo FROM artigo JOIN
	sessao ON sessao_id = sessao.id
WHERE edicao_id = (SELECT id FROM edicao WHERE ano = '2010') AND sessao.titulo = 'Information Retrieval' OR sessao.titulo = 'Web Applications';