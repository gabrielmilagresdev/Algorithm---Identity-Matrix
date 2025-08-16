#include <stdio.h>
#include <stdlib.h>
int** algoritmoMatrizI(int** matriz, int tamanho){
    if(matriz == NULL || tamanho <= 0){
        printf("Matriz invalida ou tamanho invalido.\n");
        return NULL;
    }
    int** matrizAuxiliar;
    int contador=0;
    int valorOposto;
    matrizAuxiliar = (int**)malloc(tamanho * sizeof(int*));
    for(int i = 0; i < tamanho; i++){
        matrizAuxiliar[i] = (int*)malloc(tamanho * sizeof(int));
    }
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++)
            matrizAuxiliar[i][j] = 0;
        }
    for(int w = 0; w<tamanho ;w++){
        if(matriz[w][w] == 0){
            for(int j = w+1 ; j<tamanho;j++){
                if(matriz[j][w] != 0){
                    for(int z = w ; z<tamanho ; z++){
                        matrizAuxiliar[0][z] = matriz[j][z];
                        matriz[j][z] = matriz[w][z];
                        matriz[w][z] = matrizAuxiliar[0][z];
                        matrizAuxiliar[0][z] = 0;
                    }
                    break;
                }else{
                    contador++;
                }
            }
            if(contador == (tamanho-1)){
                printf("A MATRIZ NAO E INVERSIVEL!\n");
                return NULL;
            }
        }
            for(int j = w+1 ; j<tamanho ; j++){
                valorOposto =  (float)-matriz[j][w]/matriz[w][w] * matriz[w][w];
                if(matriz[j][w] != 0)
                    matriz[j][w] = valorOposto + matriz[j][w];
            }
    }
    return matriz;
}
int main(){
    int **matriz;
    int tamanho;
    printf("Digite o numero de linhas e colunas da matriz quadrada: ");
    scanf("%d", &tamanho);
    matriz = (int**)malloc(tamanho * sizeof(int*));
    for(int i = 0; i < tamanho; i++){
        matriz[i] = (int*)malloc(tamanho * sizeof(int));
    }
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    printf("Matriz escolhida:\n");
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    matriz = algoritmoMatrizI(matriz, tamanho);
    printf("Matriz resultante:\n");
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}