#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int sorteia_user(int *usuarios, int tamanho_original);
 
int main(void){
    int *usuarios;
    int escalonador, capacidade, n_usuarios, n_impressoes, tempo_inicial = 0, n_operacao = 1, 
    tamanho_original, n_usuarios_removidos, n_usuarios_vetor = 0, i;
    time_t horaatual;
 
    srand((unsigned)time(NULL));
 
    FILE *arq_saida = fopen("entrada_random.txt", "w");
 
    printf("Digite a capacidade: \n");
    scanf("%d", &capacidade);
 
    printf("Digite o escalonador: \n");
    scanf("%d", &escalonador);
 
    printf("Digite o n de usuarios: \n");
    scanf("%d", &n_usuarios);
 
    printf("Digite o n de impressoes: \n");
    scanf("%d", &n_impressoes);
 
    printf("Digite o n de usuarios a serem removidos: \n");
    scanf("%d", &n_usuarios_removidos);
 
    usuarios = (int *)malloc(sizeof(int) * n_usuarios);
 
    for(i = 0; i < n_usuarios; i++){
        usuarios[i] = 0;
    }
 
    tamanho_original = n_usuarios;
 
    fprintf(arq_saida, "impressora %d %d\n", capacidade, escalonador);
 
 	time(&horaatual);
 	tempo_inicial = horaatual;
    while(n_usuarios != 0 || n_impressoes != 0 || n_usuarios_removidos != 0){
 
        if(n_operacao == 1 && n_usuarios != 0){
            int user;
            do{
                user = rand()%tamanho_original;
            }while(usuarios[user] == 1);
            fprintf(arq_saida,"1 user%d %d\n", user, rand()%5);
            usuarios[user] = 1;
            n_usuarios_vetor++;
            n_usuarios--;
 
        }else if(n_operacao == 2 && n_usuarios_vetor != 0 && n_impressoes != 0){
            int tempo_temp = rand()%100;
            int paginas = rand()%500;
 
            while(paginas%capacidade != 0){
                paginas++;
            }
 
            fprintf(arq_saida, "4 %d user%d %d %d %d\n", tempo_temp + tempo_inicial, sorteia_user(usuarios, tamanho_original), rand()%5, paginas, rand()%100);
            tempo_inicial += tempo_temp;
            n_impressoes--;
 
        }else if(n_operacao == 3 && n_usuarios_vetor != 0 && n_usuarios_removidos != 0){
            int n_usuario;
            do{
                n_usuario = rand()%tamanho_original;
            }while(usuarios[n_usuario] == 0);
 
            fprintf(arq_saida,"2 user%d\n", n_usuario);
            usuarios[n_usuario] = 0;
            n_usuarios_removidos--;
            n_usuarios_vetor--;
        }
 
        n_operacao = rand()%3 + 1;
    }
 
    fprintf(arq_saida,"5\n");
    free(usuarios);
    return 0;
}
 
int sorteia_user(int *usuarios, int tamanho_original){
    int user;
 
    do{
        user = rand()%tamanho_original;
    }while(usuarios[user] != 1);
 
    return user;
}

