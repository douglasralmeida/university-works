"use strict";

const bancodados =  require('./db');

module.exports.criar = function(callback) {
    var Pessoa = {
        nomenascimento: null,
        nomeartistico: null,
        localnascimento: null,
        pais: null,
        ator: false,
        diretor: false,
        foto: null
    };

    callback(Pessoa);
};

module.exports.salvar = function(Pessoa) {
    return new Promise  (function(resolve, reject) {
        bancodados.inserirItem('pessoas', Pessoa).then(function(id) {
            Pessoa.id = id;
            resolve();
        }).catch(e => {
            reject(e);
        });
    });
};