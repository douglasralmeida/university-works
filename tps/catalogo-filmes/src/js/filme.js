"use strict";

const bancodados =  require('./db');

module.exports.criar = function() {
    return new Promise(function(resolve) {
        var Filme = {
            nomeoriginal: null,
            nometraduzido: null,
            ano: null,
            nota: null,
            linktrailer: null,
            imdb: null,
            diretores: [],
            atores: [],
            imagens: [],
            generos: [],
            poster: null
        };
        resolve(Filme);
    });
}

module.exports.abrir = function (id) {
    var sqlFilme = 'SELECT idfilme, nometraduzido, nomeoriginal, ano, linktrailer, imdb, poster, nota FROM filmes WHERE idfilme = ?;';
    var sqlElenco = 'SELECT nomeartistico AS nomeator, idpessoa, foto, indicadooscar, ganhouoscar, indicadoglobo, ganhouglobo FROM filme_ator JOIN pessoas ON pessoas_idpessoa = idpessoa WHERE filmes_idfilme = ?;'
    var sqlDirecao = 'SELECT nomeartistico AS nomediretor, idpessoa, foto, indicadooscar, ganhouoscar, indicadoglobo, ganhouglobo FROM filme_diretor JOIN pessoas ON pessoas_idpessoa = idpessoa WHERE filmes_idfilme = ?;'
    var sqlImagens = 'SELECT imagem FROM filme_imagem WHERE filmes_idfilme = ?;'
    var sqlGeneros = 'SELECT descricao FROM filme_genero JOIN generos ON generos_idgenero = idgenero WHERE filmes_idfilme = ?;'
    var dataElenco = [];
    var dataDirecao = [];
    var dataImagens = [];
    var dataGeneros = [];

    return new Promise(function(resolve, reject) {
        //Abre o filme
        bancodados.abrirItem(sqlFilme, id).then(function (dataFilme) {
            //Abre a relação filme-ator
            bancodados.abrirItems(sqlElenco, id).then(function(dataElenco) {
                dataFilme.atores = dataElenco;
                
                //Abre a relação filme-diretor
                bancodados.abrirItems(sqlDirecao, id).then(function(dataDirecao) {
                    dataFilme.diretores = dataDirecao;

                    //Abre as imgens do filme
                    bancodados.abrirItems(sqlImagens, id).then(function(dataImagens) {
                        dataFilme.imagens = dataImagens;

                        //Abre os generos do filme
                        bancodados.abrirItems(sqlGeneros, id).then(function(dataGeneros) {
                            dataFilme.generos = dataGeneros;
                            dataFilme.generos.toString = function() {
                                var s = '';
                                this.forEach((g, index) => {
                                    s += g.descricao;
                                    if (index < this.length - 1)
                                        s += ', ';
                                });
                                return s;
                            };
                            resolve(dataFilme);
                        }).catch(e => {
                            reject(e);
                        });
                    }).catch(e => {
                        reject(e);
                    });
                }).catch(e => {
                    reject(e);
                });
            }).catch(e => {
                reject(e);
            }); 
        }).catch(e => {
            reject(e);
        });
    });
};

module.exports.salvar = function(dataFilme) {
    return new Promise  (function(resolve, reject) {
        var Filme = {
            nomeoriginal: dataFilme.nomeoriginal,
            nometraduzido: dataFilme.nometraduzido,
            ano: dataFilme.ano,
            linktrailer: dataFilme.linktrailer,
            imdb: dataFilme.imdb,
            nota: dataFilme.nota,
            poster: dataFilme.poster
        };
        if (dataFilme.idfilme === undefined) {
            bancodados.inserirItem('filmes', Filme).then(function(id) {
                dataFilme.idfilme = id;
                resolve();
            }).catch(e => {
                reject(e);
            });
        } else {
            bancodados.alterarItem('filmes', {idfilme: dataFilme.idfilme}, Filme).then(function() {
                resolve();
            }).catch(e => {
                reject(e);
            });
        }
    });
};