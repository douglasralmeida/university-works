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

FilmesApp.controller('addFilmeController', function($scope, $timeout) {
    var Filme = require('./js/filme');
    $scope.formTitulo = 'Adicionar novo filme';

    Filme.criar().then(function(Obj) {
        $timeout(function() {
            $scope.filmeData = Obj;
        }, 0);
    }).catch(e => {
        console.log(e);
    });

    $scope.carregarImagem = function() {
        var fp = document.getElementById('pessoafp');
        fp.click();
    };
    $scope.processarForm = function() {
        alert('manda tudo pro SQL Server!');
    };
});

FilmesApp.controller('editFilmeController', function($scope, $stateParams, $timeout) {
    var Filme = require('./js/filme');
    $scope.formTitulo = 'Editar filme';
    
    Filme.abrir($stateParams.id).then(function(Obj) {
        $timeout(function() {
            $scope.filmeData = Obj;
        }, 0);
    }).catch(e => {
        console.log(e);
    });

    $scope.carregarImagem = function() {
        var fp = document.getElementById('pessoafp');
        fp.click();
    };
    $scope.processarForm = function() {
        alert('manda tudo pro SQL Server!');
    };
});

FilmesApp.controller('verFilmeController', function($scope, $stateParams, $timeout) {
    var Filme = require('./js/filme');
    
    Filme.abrir($stateParams.id).then(function(Obj) {
        $timeout(function() {
            $scope.filmeData = Obj;
        }, 0);
    }).catch(e => {
        console.log(e);
    });
});

FilmesApp.controller('addPessoaController', function($scope, $location, $timeout) {
    var Pessoa = require('./js/pessoa');
    $scope.imagemEscolhida = false;
    $scope.pessoaData = null;
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

    Pessoa.criar(function(Obj) {
        $timeout(function() {
            $scope.pessoaData = Obj;
        }, 0);
    });

    $scope.carregarImagem = function() {
        var fp = document.getElementById('pessoafp');
        fp.click();
    };
    $scope.processarForm = function() {
        if ($scope.pessoaData == null)
            alert('Erro');
        Pessoa.salvar($scope.pessoaData).then(function() {
            $timeout(function() {
                $location.path('/');
            }, 0);
        }).catch(e => {
            console.log(e);
        });
    };
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
      });
}]);