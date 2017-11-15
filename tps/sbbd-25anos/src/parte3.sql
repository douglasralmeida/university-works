/*QUESTAO 1*/
SELECT DISTINCT ano, edicao_num FROM edicao JOIN
	sessao ON edicao.id = edicao_id JOIN
    artigo ON sessao.id = sessao_id JOIN
    autoria ON artigo.id = artigo_id JOIN
    autor ON autor.id = autor_id JOIN (
		SELECT instituicao.id FROM instituicao JOIN
			pais ON pais_id = pais.id
		WHERE pais.nome != 'brasil')
    AS instituicao ON instituicao_id = instituicao.id
ORDER BY edicao_num;

/*QUESTAO 2*/
SELECT * FROM (
	SELECT nome, count(nome) AS c FROM (
		SELECT pesquisador_id, nome, count(pesquisador_id) FROM sessao JOIN
			artigo ON sessao.id = sessao_id JOIN
			autoria ON artigo.id = artigo_id JOIN
			autor ON autor.id = autor_id JOIN 
			pesquisador ON pesquisador.id = pesquisador_id
		GROUP BY sessao.titulo, pesquisador_id) as temp
	GROUP BY pesquisador_id
	ORDER BY c DESC LIMIT 3) as temp2
ORDER BY c, nome;

/*QUESTAO 3*/
SELECT titulo, AVG(c) FROM (
	SELECT sessao.titulo, count(artigo.id) AS c FROM sessao JOIN
        artigo ON sessao.id = sessao_id
    GROUP BY sessao_id)
AS temp GROUP BY titulo;

/*QUESTAO 4*/
SELECT artigo.titulo, ano FROM artigo JOIN
	sessao ON sessao_id = sessao.id JOIN
	edicao ON edicao_id = edicao.id WHERE sessao_id = (
		SELECT id FROM sessao WHERE titulo = 'XML' ORDER BY edicao_id DESC LIMIT 1)
ORDER BY artigo.titulo;

/*QUESTAO 5*/
SELECT ano, edicao_num, sexo, COUNT(pesquisador_id) FROM edicao JOIN
	sessao ON edicao.id = edicao_id JOIN
    artigo ON sessao.id = sessao_id JOIN
    autoria ON artigo.id = artigo_id JOIN
    autor ON autor.id = autor_id JOIN 
	pesquisador ON pesquisador.id = pesquisador_id
GROUP BY sexo, edicao_num
ORDER BY ano;