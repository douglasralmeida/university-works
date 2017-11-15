/*MATRICULA 2015112728
  QUESTÕES 1,2,3,7,4,8*/

/*QUESTAO 1*/
SELECT artigo.titulo, count(artigo_id) as quantautores, ano FROM artigo JOIN 
	sessao ON sessao_id = sessao.id JOIN 
    edicao ON edicao_id = edicao.id JOIN 
    autoria ON artigo.id = artigo_id 
GROUP BY artigo.id
ORDER BY ano ASC, quantautores DESC;

/*QUESTAO 2*/
SELECT AVG(numartigos) FROM (
	SELECT COUNT(artigo.id) AS numartigos FROM artigo JOIN 
		sessao ON sessao_id = sessao.id JOIN 
		edicao ON edicao_id = edicao.id
	GROUP BY edicao.id) AS temp;

/*QUESTAO 3*/
SELECT ano, edicao_num, cidade.nome AS cidade, estado.nome AS estado, pais.nome AS pais, count(artigo.id) FROM artigo JOIN
	sessao ON sessao_id = sessao.id JOIN
    edicao ON edicao_id = edicao.id JOIN
    cidade ON cidade_id = cidade.id JOIN
    estado ON estado_id = estado.id JOIN
    pais ON pais_id = pais.id
GROUP BY edicao.id ORDER BY ano;

/*QUESTAO 4*/
SELECT pais.nome, count(pesquisador.id) AS quantpesquisadores FROM pesquisador JOIN (
	SELECT id, nome FROM pais WHERE pais.nome != 'brasil') as pais
ON pais_id = pais.id GROUP BY pais_id ORDER BY quantpesquisadores DESC;

/*QUESTAO 7*/
SELECT ano, edicao_num, count(instituicao_id) FROM edicao JOIN 
	sessao ON edicao.id = edicao_id JOIN
    artigo ON sessao.id = sessao_id JOIN
    autoria ON artigo.id = artigo_id JOIN
    autor ON autor_id = autor.id
GROUP BY edicao.id ORDER BY ano;

/*QUESTAO 8*/
SELECT instituicao.nome, count(pesquisador_id) AS c FROM instituicao JOIN 
	autor ON instituicao.id = instituicao_id
GROUP BY instituicao.id ORDER BY c DESC;