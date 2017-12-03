"use strict";

const bancodados =  require('./db');

module.exports.criar = function(callback) {
    var Pessoa = {
        nomenascimento: null,
        nomeartistico: null,
        localnascimento: null,
        pais: null,
        nomepais: null,
        foto: null
    };

    callback(Pessoa);
};

module.exports.abrir = function(id) {
    var sql = 'SELECT idpessoa, nomenascimento, nomeartistico, localnascimento, foto, pais, paises.nome AS nomepais FROM pessoas LEFT JOIN paises ON pais = idpais WHERE idpessoa = ?;';

    return new Promise (function(resolve, reject) {
        bancodados.abrirItemRelacao(sql, id).then(function(dataPessoa) {
            resolve(dataPessoa);
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