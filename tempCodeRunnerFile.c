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
    int trocou = 1;

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
            trocou = 0;
            for(int j = w+1 ; j<tamanho;j++){
                if(matrizTrocar[j][w] != 0){
                    for(int z = 0 ; z<tamanho ; z++){
                        matrizAuxiliar[0][z] = matrizTrocar[j][z];
                        matrizTrocar[j][z] = matrizTrocar[w][z];
                        matrizTrocar[w][z] = matrizAuxiliar[0][z];
                        matrizAuxiliar[0][z] = 0.0;
                    }
                    trocou = 1;
                    break;
                }
            }
        }
    }
    if(trocou==1){
        liberarMatriz(matrizAuxiliar,tamanho);
        return matrizTrocar;
    }
    if(trocou == 0){
        for(int w = tamanho-1; w>=0 ;w--){
            if(matrizTrocar[w][w] == 0){
                for(int j = w-1 ; j>=0;j--){
                    if(matrizTrocar[j][w] != 0){
                        for(int z = tamanho-1 ; z>=0 ; z--){
                            matrizAuxiliar[0][z] = matrizTrocar[j][z];
                            matrizTrocar[j][z] = matrizTrocar[w][z];
                            matrizTrocar[w][z] = matrizAuxiliar[0][z];
                            matrizAuxiliar[0][z] = 0.0;
                        }
                        trocou = 1;
                        break;
                    }
                }
            }
        }
    }
        
    if(trocou==1){
        liberarMatriz(matrizAuxiliar,tamanho);
        return matrizTrocar;
    }
    liberarMatriz(matrizAuxiliar,tamanho);
    printf("A MATRIZ NAO E INVERSIVEL!\n");
    return NULL;
            
}
double** operacoesLinhasInferior(double** matrizOperacoes, int tamanho){
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
double** operacoesLinhasSuperior(double** matrizOperacoes, int tamanho){
    verificarMatriz(matrizOperacoes,tamanho);
    double valorOposto;
    for (int z = tamanho-1; z>=0; z--){
        for (int j = z-1; j>=0; j--){
            valorOposto = -matrizOperacoes[j][z]/matrizOperacoes[z][z];
            for (int l = 0; l<tamanho; l++){
                matrizOperacoes[j][l] = matrizOperacoes[z][l]*valorOposto + matrizOperacoes[j][l];
            }
        }
    }
    return matrizOperacoes;
}
double** algoritmoMatrizISuperior(double** matriz, int tamanho){
    verificarMatriz(matriz,tamanho);
    matriz = trocarLinhas(matriz,tamanho);
    matriz = operacoesLinhasSuperior(matriz,tamanho);
    return matriz;
}
double** algoritmoMatrizIInferior(double** matriz, int tamanho){
    verificarMatriz(matriz,tamanho);
    matriz = trocarLinhas(matriz,tamanho);
    matriz = operacoesLinhasInferior(matriz,tamanho);

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
    printf("Matriz Inferior:\n");
    imprimirMatriz(matriz,tamanho);
    matriz = algoritmoMatrizISuperior(matriz, tamanho);
    printf("Matriz Resultante:\n");
    imprimirMatriz(matriz, tamanho);
    liberarMatriz(matriz,tamanho);
}
