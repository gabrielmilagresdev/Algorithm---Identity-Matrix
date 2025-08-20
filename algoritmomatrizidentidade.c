#include <stdio.h>
#include <stdlib.h>

double** algoritmoMatrizI(double** matriz, int tamanho){
    if(matriz == NULL || tamanho <= 0){
        printf("Matriz invalida ou tamanho invalido.\n");
        return NULL;
    }
    double** matrizAuxiliar;
    int contador=0;
    double valorOposto;

    matrizAuxiliar = (double**)malloc(tamanho * sizeof(double*));
    for(int i = 0; i < tamanho; i++){
        matrizAuxiliar[i] = (double*)malloc(tamanho * sizeof(double));
    }

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++)
            matrizAuxiliar[i][j] = 0.0;
    }

    for(int w = 0; w<tamanho ;w++){
        if(matriz[w][w] == 0){
            for(int j = w+1 ; j<tamanho;j++){
                if(matriz[j][w] != 0){
                    for(int z = w ; z<tamanho ; z++){
                        matrizAuxiliar[0][z] = matriz[j][z];
                        matriz[j][z] = matriz[w][z];
                        matriz[w][z] = matrizAuxiliar[0][z];
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

    for (int z = 0; z<tamanho-1; z++){
        for (int j = z+1; j<tamanho; j++){
            valorOposto = -matriz[j][z]/matriz[z][z];
            for (int l = 0; l<tamanho; l++){
                matriz[j][l] = matriz[z][l]*valorOposto + matriz[j][l];
            }
        }
    }
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

    printf("Matriz escolhida:\n");
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            printf("%.2lf ", matriz[i][j]);
        }
        printf("\n");
    }

    matriz = algoritmoMatrizI(matriz, tamanho);

    printf("Matriz resultante:\n");
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            printf("%.2lf ", matriz[i][j]);
        }
        printf("\n");
    }
}
