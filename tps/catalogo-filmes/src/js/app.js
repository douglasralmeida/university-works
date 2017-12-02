var FilmesApp = angular.module('FilmesApp', ['winjs', 'ui.router']);

FilmesApp.controller('appController', function ($scope, $state, $location) {
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

    $scope.resultado = [];
    $scope.carregarFilmes = function() {
        $scope.resultado = [];
        var db = require('./js/db').executarConsulta('SELECT * FROM `filmes`;', [], function(err, res) {
            res.forEach( (filme) => {
                var obj = {};
                obj['id'] = filme.idfilme;
                obj['nome'] = filme.nometraduzido;
                $scope.resultado.push(obj);
              });
            $scope.$apply();
        });
    };

    $scope.aoConsultar = function($event) {
        var queryText = $event.detail.queryText;
        $location.path('/pesquisa/' + queryText);
    };

    $scope.carregarFilmes();
});

FilmesApp.controller('addFilmeController', function($scope, $location, $timeout) {
    var Filme = require('./js/filme');

    $scope.filmeData = null;
    $scope.formTitulo = 'Adicionar filme';
    $scope.imagemEscolhida = false;
    Filme.criar().then(function(Obj) {
        $timeout(function() {
            $scope.filmeData = Obj;
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
                $location.path('/');
            }, 0);
        }).catch(e => {
            console.log(e);
        });
    };
});

FilmesApp.controller('editFilmeController', function($scope, $location, $stateParams, $timeout) {
    var Filme = require('./js/filme');
    $scope.formTitulo = 'Editar filme';
    $scope.imagemEscolhida = false;
    $scope.filmeData = null;
    Filme.abrir($stateParams.id).then(function(Obj) {
        $timeout(function() {
            $scope.filmeData = Obj;
            if ($scope.filmeData.poster) {
                document.getElementById("filmeposter").src = atob($scope.filmeData.poster);
                $scope.imagemEscolhida = true;
            }
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
                $location.path('/');
            }, 0);
        }).catch(e => {
            console.log(e);
        });
    };
});

FilmesApp.controller('verFilmeController', function($scope, $stateParams, $timeout) {
    var Filme = require('./js/filme');
    
    Filme.abrir($stateParams.id).then(function(Obj) {
        $timeout(function() {
            $scope.filmeData = Obj;
            if ($scope.filmeData.poster) {
                document.getElementById("filmeposter").src = atob($scope.filmeData.poster);
            }
        }, 0);
    }).catch(e => {
        console.log(e);
    });
});

FilmesApp.controller('addPessoaController', function($scope, $location, $timeout) {
    var Pessoa = require('./js/pessoa');
    $scope.formTitulo = 'Adicionar pessoa';
    $scope.imagemEscolhida = false;
    $scope.pessoaData = null;
    Pessoa.criar(function(Obj) {
        $timeout(function() {
            $scope.pessoaData = Obj;
        }, 0);
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
    $scope.formTitulo = 'Editar pessoa';
    $scope.imagemEscolhida = false;
    $scope.pessoaData = null;
    Pessoa.abrir($stateParams.id).then(function(Obj) {
        $timeout(function() {
            $scope.pessoaData = Obj;
            if ($scope.pessoaData.foto) {
                document.getElementById("pessoafoto").src = atob($scope.pessoaData.foto);
                $scope.imagemEscolhida = true;
            }
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
        templateUrl: 'html/home.html'
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