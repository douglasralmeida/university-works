var FilmesApp = angular.module('FilmesApp', ['winjs', 'ui.router']);

FilmesApp.controller('appController', function ($scope, $state) {
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
});

FilmesApp.controller('formFilmeController', function($scope) {
    $scope.formData = {
        nomeoriginal: '',
        nometraduzido: '',
        ano: 2000,
        nota: '',
        link: '',
        imdb: '',
        diretores: [
            { nome: "João da Silva", id: "122"},
            { nome: "Maria da Silva", id: "123",}
        ],
        atores: [
            { nome: "José da Silva", id: "121"},
            { nome: "Antônio da Silva", id: "124",}
        ]
    };

    $scope.carregarImagem = function() {
        var fp = document.getElementById('pessoafp');
        fp.click();
    };
    $scope.processarForm = function() {
        alert('manda tudo pro SQL Server!');
    };
});

FilmesApp.controller('formPessoaController', function($scope) {
    $scope.formData = {
        imagempessoa: '',
        nomenascimento: 'Teste',
        nomeartistico: '',
        localnascimento: '',
        pais: -1,
        ator: false,
        diretor: false
    };

    $scope.carregarImagem = function() {
        var fp = document.getElementById('pessoafp');
        fp.click();
    };
    $scope.processarForm = function() {
        alert('manda tudo pro SQL Server!');
    };
});

angular.module('FilmesApp').config(['$stateProvider', function($stateProvider){
    $stateProvider.state('inicio', {
        url: '/',
        templateUrl: 'html/home.html'
      })
      .state('adfilme',{
        url:'/adfilme',
        templateUrl: 'html/adfilme.html',
        controller: 'formFilmeController'
      })
	  .state('adpessoa',{
        url:'/adpessoa',
        templateUrl: 'html/adpessoa.html',
        controller: 'formPessoaController'
      });
}]);