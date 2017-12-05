"use strict";

const mysql = require('mysql2');

const bd = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    database: 'catalogo',
    password: 'mswin98',
    charset : 'utf8'
});

module.exports.abrirItemSimples = function (entidade, nomechave, id) {
    return new Promise(function(resolve, reject) {
        bd.execute('SELECT * FROM ' + entidade + ' WHERE ? = ?;', [nomechave, id], function(err, res) {
            if (err)
                return reject(err);
            resolve(res[0]);
        });
    });
};

module.exports.abrirItem = function (consulta, id) {
    return new Promise(function(resolve, reject) {
        bd.execute(consulta, [id], function(err, res) {
            if (err)
                return reject(err);
            resolve(res[0]);
        });
    });
};

module.exports.abrirItems = function (consulta, id) {
    return new Promise(function(resolve, reject) {
        bd.execute(consulta, [id], function(err, res) {
            if (err)
                return reject(err);
            resolve(res);
        });
    });
};

module.exports.alterarItem = function (entidade, filtro, param) {
    return new Promise(function(resolve, reject) {
        bd.query('UPDATE '+entidade+' SET ? WHERE ?;', [param, filtro], function(err, res) {
            if (err)
                return reject(err);
            resolve();
        });
    });
};

module.exports.filtrar = function (entidade, param, campo, filtro) {
    return new Promise(function(resolve, reject) {
        bd.execute('SELECT '+ param.toString() +' FROM '+entidade+' WHERE '+campo+' LIKE ' + mysql.escape('%'+filtro+'%')+';', function(err, res) {
            if (err)
                return reject(err);
            resolve(res);
        });
    });
};

module.exports.listar = function (entidade, param) {
    return new Promise(function(resolve, reject) {
        bd.execute('SELECT '+ param.toString() +' FROM '+entidade+';', function(err, res) {
            if (err)
                return reject(err);
            resolve(res);
        });
    });
};

module.exports.listarLimitado = function (entidade, param, limite) {
    return new Promise(function(resolve, reject) {
        bd.execute('SELECT '+ param.toString() +' FROM '+entidade+' LIMIT '+limite+';', function(err, res) {
            if (err)
                return reject(err);
            resolve(res);
        });
    });
};

module.exports.pesquisar = function (consulta) {
    return new Promise(function(resolve, reject) {
        bd.execute('SELECT id, tipo, nome1 AS nome, imagem FROM pesquisagenerica WHERE nome1 LIKE ? OR nome2 LIKE ?;', ['%'+consulta+'%', '%'+consulta+'%'], function(err, res) {
            if (err)
                return reject(err);
            resolve(res);
        });
    });
};

module.exports.executarConsulta = function (consulta, param, callback) {
    bd.execute(consulta, param, callback);
};

module.exports.inserirItem = function (entidade, param) {
    return new Promise(function(resolve, reject) {
        bd.query('INSERT INTO '+entidade+' SET ?;', [param], function(err, res) {
            if (err)
                return reject(err);
            resolve(res.insertId);
        });
    });
};
