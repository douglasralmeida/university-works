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
    var sql = 'SELECT idfilme, nometraduzido, nomeoriginal, ano, linktrailer, imdb, poster, nota FROM filmes WHERE idfilme = ?;';

    return new Promise(function(resolve, reject) {
        bancodados.abrirItem(sql, id).then(function (res) {
            res.diretores = [];
            res.atores = [];
            res.generos = [];
            res.imagens = [];
            resolve(res);
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