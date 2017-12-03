"use strict";

const bancodados =  require('./db');

module.exports.criar = function(callback) {
    var Pessoa = {
        nomenascimento: null,
        nomeartistico: null,
        localnascimento: null,
        pais: null,
        nomepais: null,
        foto: null,
        imagens: []
    };

    callback(Pessoa);
};

module.exports.abrir = function(id) {
    var sqlPessoa = 'SELECT idpessoa, nomenascimento, nomeartistico, localnascimento, foto, pais, paises.nome AS nomepais FROM pessoas LEFT JOIN paises ON pais = idpais WHERE idpessoa = ?;';
    var sqlAtuacoes = 'SELECT nometraduzido AS nomefilme, idfilme, poster, indicadooscar, ganhouoscar, indicadoglobo, ganhouglobo FROM filme_ator JOIN filmes ON filmes_idfilme = idfilme WHERE pessoas_idpessoa = ?;'
    var sqlDirecao = 'SELECT nometraduzido AS nomefilme, idfilme, poster, indicadooscar, ganhouoscar, indicadoglobo, ganhouglobo FROM filme_diretor JOIN filmes ON filmes_idfilme = idfilme WHERE pessoas_idpessoa = ?;'
    var sqlImagens = 'SELECT imagem FROM pessoa_imagem WHERE pessoas_idpessoa = ?;'
    var dataAtuacoes = [];
    var dataDirecao = [];
    var dataImagens = [];

    //Abre a pessoa
    return new Promise (function(resolve, reject) {
        bancodados.abrirItem(sqlPessoa, id).then(function(dataPessoa) {
            //Abre a relação filme-ator
            bancodados.abrirItems(sqlAtuacoes, id).then(function(dataAtuacoes) {
                dataPessoa.Atuacoes = dataAtuacoes;
                
                //Abre a relação filme-diretor
                bancodados.abrirItems(sqlDirecao, id).then(function(dataDirecao) {
                    dataPessoa.Direcao = dataDirecao;

                    //Abre as imgens da pessoa
                    bancodados.abrirItems(sqlImagens, id).then(function(dataImagens) {
                        dataPessoa.imagens = dataImagens;
    
                        resolve(dataPessoa);
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

module.exports.salvar = function(dataPessoa) {
    return new Promise  (function(resolve, reject) {
        var Pessoa = {
            nomenascimento: dataPessoa.nomenascimento,
            nomeartistico: dataPessoa.nomeartistico,
            localnascimento: dataPessoa.localnascimento,
            foto: dataPessoa.foto,
            pais: dataPessoa.pais
        };
        if (dataPessoa.idpessoa === undefined) {
            bancodados.inserirItem('pessoas', Pessoa).then(function(id) {
                dataPessoa.idpessoa = id;
                resolve();
            }).catch(e => {
                reject(e);
            });
        } else {
            bancodados.alterarItem('pessoas', {idpessoa: dataPessoa.idpessoa}, Pessoa).then(function() {
                resolve();
            }).catch(e => {
                reject(e);
            });
        }
    });
};