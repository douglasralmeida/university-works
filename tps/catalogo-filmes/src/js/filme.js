"use strict";

const bancodados =  require('./db');

module.exports.criar = function() {
    return new Promise(function(resolve) {
        var Filme = {
            idfilme: null,
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
            ]
        };
        resolve(Filme);
    });
}

module.exports.abrir = function (id) {
    return new Promise(function(resolve, reject) {
        bancodados.abrirItem('filmes', 'idfilme', id).then(function (res) {
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
