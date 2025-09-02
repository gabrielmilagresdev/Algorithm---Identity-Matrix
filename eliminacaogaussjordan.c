#include <stdio.h>
#include <stdlib.h>

//Assinando as funções do algoritmo
int inserirTamanho();
void liberarMatriz(double**, int);
void verificarMatriz(double**, int);
void imprimirMatriz(double**, int);
double** inserirMatriz(int);
double** eliminacaoGaussJordan(double**, int);
double** normalizarPivos(double**, int);
void verificarZeros(double**, int);
double** trocaDeLinhasTI(double**, int);
double** operacoesLinhasTI(double**, int);
double** operacoesLinhasTS(double**, int);
void encerrarPrograma(double**, int);

//Função para encerrar o programa
void encerrarPrograma(double** encerrarMatriz, int tamanhoMatriz){
    liberarMatriz(encerrarMatriz, tamanhoMatriz);
    fflush(stdout);
    exit(-1);
}
//Função para liberar a alocação dinâmica de uma matriz
void liberarMatriz(double** matrizLiberar, int tamanhoMatriz){
    for(int i = 0; i < tamanhoMatriz ; i++){
        free(matrizLiberar[i]); //Liberando colunas
    }
    free(matrizLiberar); //Liberando linhas
}

//Função para verificar se a matriz foi alocada com sucesso
void verificarMatriz(double** matrizVerificar, int tamanhoMatriz){
    if(matrizVerificar == NULL){
        printf("ERRO AO ALOCAR LINHAS\n"); //Erro caso não aloque as linhas
        encerrarPrograma(matrizVerificar, tamanhoMatriz);
    }
    for(int i = 0; i < tamanhoMatriz ; i++){
        if(matrizVerificar[i] == NULL){
            printf("ERRO AO ALOCAR COLUNAS\n"); //Erro caso não aloque as colunas
            encerrarPrograma(matrizVerificar, tamanhoMatriz);
        }
    }
}

//Função para imprimir uma matriz
void imprimirMatriz(double** matrizImprimir, int tamanhoMatriz){
    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = 0 ; j < tamanhoMatriz; j++){
            printf("%.2lf ",matrizImprimir[i][j]); //Imprimindo cada elemento da matriz
        }
        printf("\n");
    } 
    printf("\n");
}

//Função para gerar uma matriz inversa
double** alocarMatrizInversa(int tamanhoMatriz){
    double** matrizInversa;
    matrizInversa = (double **)malloc(tamanhoMatriz * sizeof(double *)); //Alocando as linhas
    for(int i = 0; i < tamanhoMatriz ; i++)
        matrizInversa[i] = (double *)malloc(tamanhoMatriz * sizeof(double)); //Alocando as colunas
    verificarMatriz(matrizInversa, tamanhoMatriz);
    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = 0; j < tamanhoMatriz; j++){
            if(i == j)
                matrizInversa[i][j] = 1;
            else
                matrizInversa[i][j] = 0;
        }
    }
}

//Função para inserir a matriz que vai inverter
double** inserirMatriz(int tamanhoMatriz){
    double **matrizInserir, **matrizInversa;
    matrizInversa = alocarMatrizInversa(tamanhoMatriz);
    matrizInserir = (double **)malloc(tamanhoMatriz * sizeof(double *)); //Alocando as linhas
    for(int i = 0; i < tamanhoMatriz ; i++)
        matrizInserir[i] = (double *)malloc(tamanhoMatriz * sizeof(double)); //Alocando as colunas
    verificarMatriz(matrizInserir, tamanhoMatriz);
    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = 0 ; j < tamanhoMatriz; j++){
            printf("Digite o Elemento [%d][%d]: ",i,j);
            scanf("%lf",&matrizInserir[i][j]); //Inserindo os elementos dentro da matriz
        }
    } 
    return matrizInserir;
}

//Função para inserir o valor do número de linhas e colunas da matriz quadrada
int inserirTamanho(){
    int tamanhoMatriz;
    printf("Digite o Tamanho da Matriz Quadrada (Linhas/Colunas): "); //Inserindo número de linhas e colunas
    scanf("%d",&tamanhoMatriz);
    return tamanhoMatriz;
}

//Função para verificar se existem linhas ou colunas só de zeros
void verificarZeros(double** matrizVerificarZeros, int tamanhoMatriz){
    int contadorZeros = 0;
    for(int i = 0; i < tamanhoMatriz; i++){
        contadorZeros = 0;
        for(int j = tamanhoMatriz-1 ; j >= 0; j--){
            if(matrizVerificarZeros[i][j] == 0) //Caso tenha uma linha só de zeros, a matriz não é reversível
            contadorZeros++;
        }
        if(contadorZeros == tamanhoMatriz){
            printf("MATRIZ IRREVERSIVEL : LINHA DE ZEROS\n");
            encerrarPrograma(matrizVerificarZeros, tamanhoMatriz);
        }
    } 
    for(int i = 0; i < tamanhoMatriz; i++){
        contadorZeros = 0;
        for(int j = tamanhoMatriz-1 ; j >= 0; j--){
            if(matrizVerificarZeros[j][i] == 0) //Caso tenha uma coluna só de zeros, a matriz não é reversível
            contadorZeros++;
        }
        if(contadorZeros == tamanhoMatriz){
            printf("MATRIZ IRREVERSIVEL : COLUNA DE ZEROS\n");
            encerrarPrograma(matrizVerificarZeros, tamanhoMatriz);
        }
    } 
}

//Função para trocar as linhas caso algum pivô seja 0. Procedimento para o triângulo inferior
double** trocaDeLinhasTI(double** matrizTrocaLinhas, int tamanhoMatriz){
    double* linhaAuxiliar;
    linhaAuxiliar = malloc(tamanhoMatriz * sizeof(double));
    for(int i = 0; i < tamanhoMatriz; i++){
        if(matrizTrocaLinhas[i][i] != 0) //Se o pivô for zero, será necessário trocar a linha para uma que não seja
            continue;    
        for(int j = tamanhoMatriz-1 ; j >= 0; j--){
            if(matrizTrocaLinhas[j][i] != 0){
                for (int w = 0; w < tamanhoMatriz; w++){
                    linhaAuxiliar[w] = matrizTrocaLinhas[i][w]; //Realizando a troca a partir de um vetor auxiliar para armazenar os valores
                    matrizTrocaLinhas[i][w] = matrizTrocaLinhas[j][w];
                    matrizTrocaLinhas[j][w] = linhaAuxiliar[w];
                }
            }
        }
    } 
    for(int i = 0; i < tamanhoMatriz; i++){
        if(matrizTrocaLinhas[i][i] == 0){
            printf("MATRIZ NAO REVERSIVEL : ALGUM PIVO SEMPRE E NULO");
            encerrarPrograma(matrizTrocaLinhas, tamanhoMatriz);
        }
    }
    free(linhaAuxiliar);
    return matrizTrocaLinhas;
}

//Função para normalizar os pivôs da matriz
double** normalizarPivos(double** matrizNormalizar, int tamanhoMatriz){
    double valorNormalizar; //Valor que será usado para normalizar as linhas necessárias
    for(int i = 0; i < tamanhoMatriz; i++){
        if(matrizNormalizar[i][i] != 1 && matrizNormalizar[i][i] != 0) //Caso o pivô não seja 1, realizar a operação de troca
            valorNormalizar = 1.0 / matrizNormalizar[i][i]; //Valor para multiplicar a linha e deixar o pivô com valor 1
        else
            continue;    
        for(int j = 0 ; j < tamanhoMatriz; j++){
            matrizNormalizar[i][j] = matrizNormalizar[i][j] * valorNormalizar; //Normalizando o pivô
        }
    } 
    return matrizNormalizar;
}

//Função para zerar o triângulo inferior da matriz
double** operacoesLinhasTI(double** matrizOperacoesTI, int tamanhoMatriz){
    double valorOposto; //Valor utilizado para zerar os valores abaixo do pivô
    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = i + 1; j < tamanhoMatriz; j++){
            if(matrizOperacoesTI[j][i] == 0)
                continue;
            if(matrizOperacoesTI[i][i] == 0){
                encerrarPrograma(matrizOperacoesTI, tamanhoMatriz);
            }
            valorOposto = -matrizOperacoesTI[j][i]/matrizOperacoesTI[i][i]; //Pegando o valor que, quando multiplicado pelo abaixo do pivô, dará zero
            for(int w = 0; w < tamanhoMatriz; w++){
                matrizOperacoesTI[j][w] = (matrizOperacoesTI[i][w] * valorOposto) + matrizOperacoesTI[j][w]; //Zerando o valor abaixo do pivô
            }
        }
    }
    //Verificando se a matiz continua reversível
    matrizOperacoesTI = normalizarPivos(matrizOperacoesTI, tamanhoMatriz);
    verificarZeros(matrizOperacoesTI, tamanhoMatriz);

    return matrizOperacoesTI;
}
//Função para zerar o triângulo superior da matriz
double** operacoesLinhasTS(double** matrizOperacoesTS, int tamanhoMatriz){
    double valorOposto; //Valor utilizado para zerar os valores acima do pivô
    for(int i = tamanhoMatriz - 1; i >= 0; i--){
        for(int j = i - 1; j >= 0; j--){
            if(matrizOperacoesTS[j][i] == 0)
                continue;
            if(matrizOperacoesTS[i][i] == 0){
                encerrarPrograma(matrizOperacoesTS, tamanhoMatriz);
            }
             valorOposto = -matrizOperacoesTS[j][i]/matrizOperacoesTS[i][i]; //Pegando o valor que, quando multiplicado pelo acima do pivô, dará zero
             for(int w = 0; w < tamanhoMatriz; w++){
                matrizOperacoesTS[j][w] = (matrizOperacoesTS[i][w] * valorOposto) + matrizOperacoesTS[j][w]; //Zerando o valor acima do pivô
             }
        }
    }

    //Verificando se a matiz continua reversível
    matrizOperacoesTS = normalizarPivos(matrizOperacoesTS, tamanhoMatriz);
    verificarZeros(matrizOperacoesTS, tamanhoMatriz);

    return matrizOperacoesTS;
}

//Função geral da Eliminação de Gauss-Jordan
double** eliminacaoGaussJordan(double** matrizGauss, int tamanhoMatriz){
    verificarZeros(matrizGauss, tamanhoMatriz); //Chamando a função para verificar se há alguma coluna ou linha de zeros
    matrizGauss = trocaDeLinhasTI(matrizGauss, tamanhoMatriz); //Chamando a função para não deixar os pivôs zerados
    matrizGauss = normalizarPivos(matrizGauss, tamanhoMatriz); //Chamando a função para normalizar os pivos da matriz
    matrizGauss = operacoesLinhasTI(matrizGauss, tamanhoMatriz); //Chamando a função para fazer a eliminação do triangulo inferior da matriz
    matrizGauss = operacoesLinhasTS(matrizGauss, tamanhoMatriz); //Chamando a função para fazer a eliminação do triangulo superior da matriz
    return matrizGauss;
}
int main(){
    double** matrizMain;
    int tamanhoMain;

    tamanhoMain = inserirTamanho(); //Chamando a função para inserir o tamanho da matriz
    matrizMain = inserirMatriz(tamanhoMain); //Chamando a função para inserir a matriz
    imprimirMatriz(matrizMain, tamanhoMain); 
    matrizMain = eliminacaoGaussJordan(matrizMain, tamanhoMain); //Inicializando o algoritmo da Eliminação de Gauss-Jordan
    imprimirMatriz(matrizMain, tamanhoMain); 
    liberarMatriz(matrizMain, tamanhoMain);
}