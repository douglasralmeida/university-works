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