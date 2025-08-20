#include <stdio.h>
#include <stdlib.h>

void verificarMatriz(double** matrizVerificar, int tamanho){
    if(matrizVerificar == NULL || tamanho <= 0){
        printf("Matriz invalida ou tamanho invalido.\n");
    }
}
void liberarMatriz(double** matrizLiberar, int tamanho){
    verificarMatriz(matrizLiberar,tamanho);
    for(int i = 0; i < tamanho; i++){
        free(matrizLiberar[i]);
    }
    free(matrizLiberar);
}
void imprimirMatriz(double** matrizImprimir, int tamanho){
    verificarMatriz(matrizImprimir,tamanho);
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            printf("%.2lf ", matrizImprimir[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
double** trocarLinhas(double** matrizTrocar, int tamanho){
    verificarMatriz(matrizTrocar,tamanho);
    double** matrizAuxiliar;
    int contador=0;

    matrizAuxiliar = (double**)malloc(tamanho * sizeof(double*));
    for(int i = 0; i < tamanho; i++){
        matrizAuxiliar[i] = (double*)malloc(tamanho * sizeof(double));
    }

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++)
            matrizAuxiliar[i][j] = 0.0;
    }

    for(int w = 0; w<tamanho ;w++){
        if(matrizTrocar[w][w] == 0){
            for(int j = w+1 ; j<tamanho;j++){
                if(matrizTrocar[j][w] != 0){
                    for(int z = w ; z<tamanho ; z++){
                        matrizAuxiliar[0][z] = matrizTrocar[j][z];
                        matrizTrocar[j][z] = matrizTrocar[w][z];
                        matrizTrocar[w][z] = matrizAuxiliar[0][z];
                        matrizAuxiliar[0][z] = 0.0;
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
    }
    liberarMatriz(matrizAuxiliar,tamanho);
    return matrizTrocar;
}

double** operacoesLinhas(double** matrizOperacoes, int tamanho){
    verificarMatriz(matrizOperacoes,tamanho);
    double valorOposto;
    for (int z = 0; z<tamanho-1; z++){
        for (int j = z+1; j<tamanho; j++){
            valorOposto = -matrizOperacoes[j][z]/matrizOperacoes[z][z];
            for (int l = 0; l<tamanho; l++){
                matrizOperacoes[j][l] = matrizOperacoes[z][l]*valorOposto + matrizOperacoes[j][l];
            }
        }
    }
    return matrizOperacoes;
}

double** algoritmoMatrizIInferior(double** matriz, int tamanho){
    verificarMatriz(matriz,tamanho);
    matriz = trocarLinhas(matriz,tamanho);
    matriz = operacoesLinhas(matriz,tamanho);

    return matriz;
}

int main(){
    double **matriz;
    int tamanho;

    printf("Digite o numero de linhas e colunas da matriz quadrada: ");
    scanf("%d", &tamanho);
    matriz = (double**)malloc(tamanho * sizeof(double*));
    for(int i = 0; i < tamanho; i++){
        matriz[i] = (double*)malloc(tamanho * sizeof(double));
    }
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%lf", &matriz[i][j]);
        }
    }

    printf("Matriz Escolhida:\n");
    imprimirMatriz(matriz, tamanho);
    matriz = algoritmoMatrizIInferior(matriz, tamanho);
    printf("Matriz Resultante:\n");
    imprimirMatriz(matriz, tamanho);
    liberarMatriz(matriz,tamanho);
}
