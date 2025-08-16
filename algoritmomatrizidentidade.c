#include <stdio.h>
#include <stdlib.h>
int** algoritmoMatrizI(int** matriz, int tamanho){
    int** matrizAuxiliar;
    int contador=0;
    matrizAuxiliar = (int**)malloc(tamanho * sizeof(int*));
    for(int i = 0; i < tamanho; i++){
        matrizAuxiliar[i] = (int*)malloc(tamanho * sizeof(int));
    }
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++)
            matrizAuxiliar[i][j] = 0;
        }
    if(matriz == NULL || tamanho <= 0){
        printf("Matriz invalida ou tamanho invalido.\n");
        return NULL;
    }
    for(int w = 0; w<tamanho ;w++){
        for(int i = 0; i < tamanho ; i++){
            if(matriz[w][w] == 0){
                for(int j = 1; j<tamanho;j++){
                    if(matriz[j][w] != 0){
                        matrizAuxiliar[0][0] = matriz[j][w];
                        matriz[j][w] = matriz[w][w];
                        matriz[w][w] = matrizAuxiliar[0][0];
                        matrizAuxiliar[0][0] = 0;
                    }else{
                        contador++;
                    }
                }
                if(contador == (tamanho-1)){
                    printf("A MATRIZ NAO E INVERSIVEL!\n");
                    return matrizAuxiliar;
                }
            }
            for(int j = w+1 ; j<tamanho ; j++){
                if(matriz[j][w] != 0)
                    matriz[j][w] = (matriz[w][w] * (-matriz[j][w] / matriz[w][w])) + matriz[j][w];
            }
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
    matriz = algoritmoMatrizI(matriz, tamanho);
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}