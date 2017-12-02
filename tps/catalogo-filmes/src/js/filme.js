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
            diretores: [
                { nome: "João da Silva", id: "122"},
                { nome: "Maria da Silva", id: "123",}
            ],
            atores: [
                { nome: "José da Silva", id: "121"},
                { nome: "Antônio da Silva", id: "124",}
            ],
            poster: null
        };
        resolve(Filme);
    });
}

module.exports.abrir = function (id) {
    var sql = 'SELECT idfilme, nometraduzido, nomeoriginal, ano, linktrailer, imdb, poster, nota FROM filmes WHERE idfilme = ?;';

    return new Promise(function(resolve, reject) {
        bancodados.abrirItemRelacao(sql, id).then(function (res) {
            res.diretores = [
                { nome: "João da Silva", id: "122"},
                { nome: "Maria da Silva", id: "123"}
            ];
            res.atores = [
                { nome: "José da Silva", id: "121"},
                { nome: "Antônio da Silva", id: "124"}
            ];
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