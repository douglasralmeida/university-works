"use strict";

const mysql = require('mysql2');

const bd = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    database: 'catalogo',
    password: 'mswin98'
});

module.exports.abrirItem = function (entidade, nomechave, id) {
    return new Promise(function(resolve, reject) {
        bd.execute('SELECT * FROM ' + entidade + ' WHERE ' + nomechave + ' = ?;', [id], function(err, res) {
            if (err)
                return reject(err);
            resolve(res[0]);
        });
    });
};

module.exports.executarConsulta = function (consulta, param, callback) {
    bd.execute(consulta, param, callback);
};

module.exports.inserirItem = function (entidade, param) {
    return new Promise(function(resolve, reject) {
        bd.query('INSERT INTO ' + entidade + ' SET ?;', param, function(err, res) {
            if (err)
                return reject(err);
            resolve(res.insertId);
        });
    });
};
