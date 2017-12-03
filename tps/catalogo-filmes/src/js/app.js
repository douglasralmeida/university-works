var FilmesApp = angular.module('FilmesApp', ['winjs', 'ui.router']);

FilmesApp.controller('appController', function ($scope, $state, $location, $timeout) {
    var Pesquisa = require('./js/pesquisa');
    $scope.resultado = [];
    $scope.splitViewElement = document.getElementById('splitView');
	
	$scope.irParaInicio = function() {
        $state.go('inicio');
    };
	$scope.irParaAdicFilme = function() {
        $state.go('adfilme');
    };
	$scope.irParaAdicPessoa = function() {
        $state.go('adpessoa');
    };
    $scope.carregarPoster = function() {
        var fp = document.getElementById('filmefp');
        fp.click();
    };
    $scope.carregarFilmes = function() {
        $scope.resultado = [];

        Pesquisa.listar('filmes', ['idfilme', 'nometraduzido', 'poster']).then(function(res) {
            $timeout(function() {         
                $scope.resultado = res;
                res.forEach(r => {
                    if (r.poster != null) {
                        r.poster = atob(r.poster);
                    } else {
                        r.poster = 'img/filme.png';
                    }});
            }, 0);
        }).catch(e => {
            console.log(e);
        });
    };
    $scope.aoConsultar = function($event) {
        var queryText = $event.detail.queryText;
        $location.path('/pesquisa/' + queryText);
    };

    $scope.carregarFilmes();
});

FilmesApp.controller('addFilmeController', function($scope, $window, $timeout) {
    var Filme = require('./js/filme');
    var Pesquisa = require('./js/pesquisa');
    $scope.filmeData = null;
    $scope.formTitulo = 'Adicionar filme';
    $scope.generos = [];
    $scope.imagemEscolhida = false;
    $scope.podeAddRelacoes = false;
    $scope.dialogoAdicAtorOculto = true;
    Filme.criar().then(function(Obj) {
        $timeout(function() {
            $scope.filmeData = Obj;
        }, 0);
    }).catch(e => {
        console.log(e);
    });
    Pesquisa.listar('generos', ['idgenero', 'descricao']).then(function(res) {
        $timeout(function() {         
            $scope.generos = res;
        }, 0);
    }).catch(e => {
        console.log(e);
    });
    document.getElementById("filmefp").addEventListener("change", function() {
        if (this.files && this.files[0]) {
            var FR= new FileReader();
            FR.addEventListener("load", function(e) {
                document.getElementById("filmeposter").src = e.target.result;
                $scope.filmeData.poster = btoa(e.target.result);
                $scope.imagemEscolhida = true;
                $scope.$apply();
            });   
            FR.readAsDataURL( this.files[0] );
        };
    });

    $scope.carregarPoster = function() {
        var fp = document.getElementById('filmefp');
        fp.click();
    };
    $scope.processarForm = function() {
        Filme.salvar($scope.filmeData).then(function() {
            $timeout(function() {
                $window.location.href = '#/';
            }, 0);
        }).catch(e => {
            console.log(e);
        });
    };
});

FilmesApp.controller('editFilmeController', function($scope, $timeout, $stateParams, $window) {
    var Filme = require('./js/filme');
    var Pesquisa = require('./js/pesquisa');
    $scope.formTitulo = 'Editar filme';
    $scope.imagemEscolhida = false;
    $scope.filmeData = null;
    $scope.pesquisaTextoPessoas = '';
    $scope.podeAddRelacoes = true;
    $scope.dialogoAdicAtorOculto = true;
    $scope.atoreselecionados = [];
    Filme.abrir($stateParams.id).then(function(Obj) {
        $timeout(function() {
            $scope.filmeData = Obj;
            if ($scope.filmeData.poster) {
                document.getElementById("filmeposter").src = atob($scope.filmeData.poster);
                $scope.imagemEscolhida = true;
            }
            $scope.filmeData.imagens.forEach(i => i.imagem = atob(i.imagem));
        }, 0);
    }).catch(e => {
        console.log(e);
    });
    document.getElementById("filmefp").addEventListener("change", function() {
        if (this.files && this.files[0]) {
            var FR= new FileReader();
            FR.addEventListener("load", function(e) {
                document.getElementById("filmeposter").src = e.target.result;
                $scope.filmeData.poster = btoa(e.target.result);
                $scope.imagemEscolhida = true;
                $scope.$apply();
            });   
            FR.readAsDataURL( this.files[0] );
        };
    });
    document.getElementById("imagemfp").addEventListener("change", function() {
        var bdados =  require('./js/db');

        if (this.files && this.files[0]) {
            var FR= new FileReader();
            FR.addEventListener("load", function(e) {
                var Data = {
                    filmes_idfilme: $scope.filmeData.idfilme,
                    imagem: btoa(e.target.result)
                };
                var Img = {
                    imagem: e.target.result
                };
                bdados.inserirItem('filme_imagem', Data).then(function(id) {
                    $scope.filmeData.imagens.push(Img);
                    $scope.$apply();
                }).catch(e => {
                    console.log(e);
                });
            });   
            FR.readAsDataURL( this.files[0] );
        };
    });
    $scope.carregarPoster = function() {
        var fp = document.getElementById('filmefp');
        fp.click();
    };
    $scope.clicarAddImg = function() {
        var fp = document.getElementById('imagemfp');
        fp.click();
    };
    $scope.exibirdialogoAdicAtor = function () {
        $scope.pessoas = [];
        $scope.pesquisaTextoPessoas = '';
        $scope.dialogoAdicAtorOculto = false;
    };
    $scope.pesquisarPessoas = function(consulta) {
        if (consulta.length > 2) {
            Pesquisa.filtrar('pessoas', ['idpessoa', 'nomeartistico'], 'nomeartistico', consulta).then(function(res) {
                $timeout(function() {
                    $scope.pessoas = res;
                }, 0);
            }).catch(e => {
                console.log(e);
            });     
        }
    }
    $scope.processarForm = function() {
        Filme.salvar($scope.filmeData).then(function() {
            $timeout(function() {
                $window.location.href = '#/';
            }, 0);
        }).catch(e => {
            console.log(e);
        });
    };
});

FilmesApp.controller('verFilmeController', function($scope, $stateParams, $timeout) {
    var Filme = require('./js/filme');
    $scope.temImagem = false;
    
    Filme.abrir($stateParams.id).then(function(Obj) {
        $timeout(function() {
            $scope.filmeData = Obj;
            if ($scope.filmeData.poster) {
                document.getElementById("filmeposter").src = atob($scope.filmeData.poster);
                $scope.temImagem = true;
            }
            else {
                document.getElementById("filmeposter").src = 'img/filme.png';
                $scope.temImagem = true;
            }
            $scope.filmeData.atores.forEach(a => a.foto = atob(a.foto));
            $scope.filmeData.diretores.forEach(d => d.foto = atob(d.foto));
            $scope.filmeData.imagens.forEach(i => i.imagem = atob(i.imagem));
        }, 0);
    }).catch(e => {
        console.log(e);
    });
});

FilmesApp.controller('addPessoaController', function($scope, $location, $timeout) {
    var Pesquisa = require('./js/pesquisa');
    var Pessoa = require('./js/pessoa');
    $scope.formTitulo = 'Adicionar pessoa';
    $scope.imagemEscolhida = false;
    $scope.paises = [];
    $scope.pessoaData = null;
    $scope.podeAddImagem = false;
    Pessoa.criar(function(Obj) {
        $timeout(function() {
            $scope.pessoaData = Obj;
        }, 0);
    });
    Pesquisa.listar('paises', ['idpais', 'nome']).then(function(res) {
        $timeout(function() {         
            $scope.paises = res;
        }, 0);
    }).catch(e => {
        console.log(e);
    });
    document.getElementById("pessoafp").addEventListener("change", function() {
        if (this.files && this.files[0]) {
            var FR= new FileReader();
            FR.addEventListener("load", function(e) {
                document.getElementById("pessoafoto").src = e.target.result;
                $scope.pessoaData.foto = btoa(e.target.result);
                $scope.imagemEscolhida = true;
                $scope.$apply();
            });   
            FR.readAsDataURL( this.files[0] );
        };
    });
    $scope.carregarImagem = function() {
        var fp = document.getElementById('pessoafp');
        fp.click();
    };
    $scope.onPaisSuggestionsRequested = function($event) {
        var queryText = $event.detail.queryText,

        query = queryText.toLowerCase(),
        suggestionCollection = $event.detail.searchSuggestionCollection;
        if (queryText.length > 2) {
            for (var i = 0, len = $scope.paises.length; i < len; i++) {
                if ($scope.paises[i].nome.substr(0, query.length).toLowerCase() === query) {
                    suggestionCollection.appendQuerySuggestion($scope.paises[i].nome);
                }
            }
        }
    };
    $scope.onPaisQuerySubmitted = function($event) {
        var queryText = $event.detail.queryText;
        $scope.pessoaData.nomepais = queryText;

        query = queryText.toLowerCase();
        for (var i = 0, l = $scope.paises.length; i < l; i++)
            if ($scope.paises[i].nome.toLowerCase() === query) {
                $scope.pessoaData.pais = i+1;
            }
    }
    $scope.processarForm = function() {
        Pessoa.salvar($scope.pessoaData).then(function() {
            $timeout(function() {
                $location.path('/');
            }, 0);
        }).catch(e => {
            console.log(e);
        });
    };
});

FilmesApp.controller('editPessoaController', function($scope, $stateParams, $timeout, $location) {
    var Pessoa = require('./js/pessoa');
    var Pesquisa = require('./js/pesquisa');
    $scope.formTitulo = 'Editar pessoa';
    $scope.imagemEscolhida = false;
    $scope.pessoaData = null;
    $scope.paises = [];
    $scope.podeAddImagem = true;
    Pessoa.abrir($stateParams.id).then(function(Obj) {
        $timeout(function() {
            $scope.pessoaData = Obj;
            if ($scope.pessoaData.foto) {
                document.getElementById("pessoafoto").src = atob($scope.pessoaData.foto);
                $scope.imagemEscolhida = true;
            }
            $scope.pessoaData.imagens.forEach(i => i.imagem = atob(i.imagem));
        }, 0);
    }).catch(e => {
        console.log(e);
    });
    Pesquisa.listar('paises', ['idpais', 'nome']).then(function(res) {
        $timeout(function() {         
            $scope.paises = res;
        }, 0);
    }).catch(e => {
        console.log(e);
    });
    document.getElementById("pessoafp").addEventListener("change", function() {
        if (this.files && this.files[0]) {
            var FR= new FileReader();
            FR.addEventListener("load", function(e) {
                document.getElementById("pessoafoto").src = e.target.result;
                $scope.pessoaData.foto = btoa(e.target.result);
                $scope.imagemEscolhida = true;
                $scope.$apply();
            });   
            FR.readAsDataURL( this.files[0] );
        };
    });
    document.getElementById("imagemfp").addEventListener("change", function() {
        var bdados =  require('./js/db');

        if (this.files && this.files[0]) {
            var FR= new FileReader();
            FR.addEventListener("load", function(e) {
                var Data = {
                    pessoas_idpessoa: $scope.pessoaData.idpessoa,
                    imagem: btoa(e.target.result)
                };
                var Img = {
                    imagem: e.target.result
                };
                bdados.inserirItem('pessoa_imagem', Data).then(function(id) {
                    $scope.pessoaData.imagens.push(Img);
                    $scope.$apply();
                }).catch(e => {
                    console.log(e);
                });
            });   
            FR.readAsDataURL( this.files[0] );
        };
    });
    $scope.onPaisSuggestionsRequested = function($event) {
        var queryText = $event.detail.queryText,

        query = queryText.toLowerCase(),
        suggestionCollection = $event.detail.searchSuggestionCollection;
        if (queryText.length > 2) {
            for (var i = 0, len = $scope.paises.length; i < len; i++) {
                if ($scope.paises[i].nome.substr(0, query.length).toLowerCase() === query) {
                    suggestionCollection.appendQuerySuggestion($scope.paises[i].nome);
                }
            }
        }
    };
    $scope.onPaisQuerySubmitted = function($event) {
        var queryText = $event.detail.queryText;
        $scope.pessoaData.nomepais = queryText;

        query = queryText.toLowerCase();
        for (var i = 0, l = $scope.paises.length; i < l; i++)
            if ($scope.paises[i].nome.toLowerCase() === query) {
                $scope.pessoaData.pais = i+1;
            }
    };
    $scope.clicarAddImg = function() {
        var fp = document.getElementById('imagemfp');
        fp.click();
    };
    $scope.carregarImagem = function() {
        var fp = document.getElementById('pessoafp');
        fp.click();
    };
    $scope.pesquisarPessoas
    $scope.processarForm = function() {
        Pessoa.salvar($scope.pessoaData).then(function() {
            $timeout(function() {
                $location.path('/');
            }, 0);
        }).catch(e => {
            console.log(e);
        });
    };
});

FilmesApp.controller('verPessoaController', function($scope, $stateParams, $timeout) {
    var Pessoa = require('./js/pessoa');
    
    Pessoa.abrir($stateParams.id).then(function(Obj) {
        $timeout(function() {
            $scope.pessoaData = Obj;
            if ($scope.pessoaData.foto) {
                document.getElementById("pessoaposter").src = atob($scope.pessoaData.foto);
            }
            $scope.pessoaData.Atuacoes.forEach(a => a.poster = atob(a.poster));
            $scope.pessoaData.Direcao.forEach(d => d.poster = atob(d.poster));
            $scope.pessoaData.imagens.forEach(i => i.imagem = atob(i.imagem));
        }, 0);
    }).catch(e => {
        console.log(e);
    });
});

FilmesApp.controller('pesquisaController', function($scope, $stateParams, $timeout) {
    var Pesquisador = require('./js/pesquisa');

    $scope.iniciarPesquisa = function(consulta) {
        $scope.consultaTexto = consulta;

        Pesquisador.executar(consulta).then(function(Obj) {
            $timeout(function() {
                $scope.pesquisaData = Obj;
                Obj.forEach(r => {
                    if (r.imagem) {
                        r.imagem = atob(r.imagem);
                    }
                    else {
                        r.imagem = 'img/filme.png';
                    }
                });
            }, 0);
        }).catch(e => {
            console.log(e);
        });
    };

    $scope.aoConsultar = function($event) {
        $scope.iniciarPesquisa($event.detail.queryText);
    };

    $scope.iniciarPesquisa($stateParams.consultaTexto);
});

angular.module('FilmesApp').config(['$stateProvider', function($stateProvider){
    $stateProvider.state('inicio', {
        url: '/',
        templateUrl: 'html/home.html',
        controller: 'appController'
      })
      .state('pesquisa', {
        url: '/pesquisa/:consultaTexto',
        templateUrl: 'html/pesquisa.html',
        controller: 'pesquisaController'
      })
      .state('adfilme', {
        url:'/adfilme',
        templateUrl: 'html/filme.html',
        controller: 'addFilmeController'
      })
      .state('editfilme', {
        url: '/editfilme/:id',
        templateUrl: 'html/filme.html',
        controller: 'editFilmeController'
      })
      .state('verfilme', {
        url: '/verfilme/:id',
        templateUrl: 'html/verfilme.html',
        controller: 'verFilmeController'
      })
	  .state('adpessoa',{
        url:'/adpessoa',
        templateUrl: 'html/pessoa.html',
        controller: 'addPessoaController'
      })
      .state('editpessoa', {
        url: '/editpessoa/:id',
        templateUrl: 'html/pessoa.html',
        controller: 'editPessoaController'
      })
      .state('verpessoa', {
        url: '/verpessoa/:id',
        templateUrl: 'html/verpessoa.html',
        controller: 'verPessoaController'
      });
}]);