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

module.exports.abrir = function(id) {
    var sql = 'SELECT idpessoa, nomenascimento, nomeartistico, localnascimento, ator, diretor, foto, pais, paises.nome AS nomepais FROM pessoas JOIN paises ON pais = idpais WHERE idpessoa = ?;';

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
            pais: dataPessoa.pais,
            ator: dataPessoa.ator,
            diretor: dataPessoa.diretor,
            foto: dataPessoa.foto
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