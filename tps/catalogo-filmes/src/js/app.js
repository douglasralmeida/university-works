angular.module('FilmesApp', ['winjs', 'ui.router']).controller("appController", function ($scope, $state) {
    $scope.splitViewElement = document.getElementById("splitView");
	
	 $scope.irParaInicio = function() {
        $state.go('inicio');
    };
	$scope.irParaAdicFilme = function() {
        $state.go('adfilme');
    };
	$scope.irParaAdicPessoa = function() {
        $state.go('adpessoa');
    };

    $scope.carregarImagem = function() {
        var fp = document.getElementById("pessoafp");
        fp.click();
    };

    $scope.carregarPoster = function() {
        var fp = document.getElementById("filmefp");
        fp.click();
    };
});

angular.module('FilmesApp').config(['$stateProvider', function($stateProvider){
    $stateProvider.state('inicio', {
        url: '/',
        templateUrl: '/inicio.html'
      })
      .state('adfilme',{
        url:'/adfilme',
		templateUrl: '/adfilme.html'
      })
	  .state('adpessoa',{
        url:'/adpessoa',
		templateUrl: '/adpessoa.html'
      });
}]);