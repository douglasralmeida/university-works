"use strict";

const bancodados =  require('./db');
const tiposItem = ['desconhecido', 'pessoa', 'filme'];
const tiposView = ['', 'verpessoa', 'verfilme'];

module.exports.executar = function(consulta) {
    return new Promise  (function(resolve, reject) {
        bancodados.pesquisar(consulta).then(function(res) {
            res.forEach(e => {
                e.descricaotipo = tiposItem[e.tipo];
                e.nomeview = tiposView[e.tipo];
            });
            resolve(res);
        }).catch(e => {
            reject(e);
        });
    });
};

module.exports.filtrar = function(entidade, param, campo, filtro) {
    return new Promise  (function(resolve, reject) {
        bancodados.filtrar(entidade, param, campo, filtro).then(function(res) {
            resolve(res);
        }).catch(e => {
            reject(e);
        });
    });
};

module.exports.listar = function(entidade, param) {
    return new Promise  (function(resolve, reject) {
        bancodados.listar(entidade, param).then(function(res) {
            resolve(res);
        }).catch(e => {
            reject(e);
        });
    });
};

module.exports.listarLimitado = function(entidade, param, limite) {
    return new Promise  (function(resolve, reject) {
        bancodados.listarLimitado(entidade, param, limite).then(function(res) {
            resolve(res);
        }).catch(e => {
            reject(e);
        });
    });
};