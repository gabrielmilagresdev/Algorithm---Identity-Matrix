#include <stdio.h>
#include <stdlib.h>

//Assinando as funcoes do algoritmo
void inserirTamanho();
void liberarMatriz(double**);
void verificarMatriz(double**);
void imprimirMatriz(double**);
double** inserirMatriz();
double** eliminacaoGaussJordan(double**);
double** normalizarPivos(double**);
void verificarZeros(double**);
double** trocaDeLinhasTI(double**);
double** operacoesLinhasTI(double**);
double** operacoesLinhasTS(double**);

//Declarando o tamanho da matriz como global
int tamanhoMatriz;

//Função para liberar a alocação dinâmica de uma matriz
void liberarMatriz(double** matrizLiberar){
    for(int i = 0; i < tamanhoMatriz ; i++){
        free(matrizLiberar[i]); //Liberando colunas
    }
    free(matrizLiberar); //Liberando linhas
}

//Função para verificar se a matriz foi alocada com sucesso
void verificarMatriz(double** matrizVerificar){
    if(matrizVerificar == NULL)
        printf("ERRO AO ALOCAR LINHAS\n"); //Erro caso não aloque as linhas
    for(int i = 0; i < tamanhoMatriz ; i++){
        if(matrizVerificar[i] == NULL)
            printf("ERRO AO ALOCAR COLUNAS\n"); //Erro caso não aloque as colunas
    }
}

//Função para imprimir uma matriz
void imprimirMatriz(double** matrizImprimir){
    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = 0 ; j < tamanhoMatriz; j++){
            printf("%.2lf ",matrizImprimir[i][j]); //Imprimindo cada elemento da matriz
        }
        printf("\n");
    } 
    printf("\n");
}

//Função para inserir a matriz que vai inverter
double** inserirMatriz(){
    double **matrizInserir;
    matrizInserir = (double **)malloc(tamanhoMatriz * sizeof(double *)); //Alocando as linhas
    for(int i = 0; i < tamanhoMatriz ; i++)
        matrizInserir[i] = (double *)malloc(tamanhoMatriz * sizeof(double)); //Alocando as colunas
    verificarMatriz(matrizInserir);
    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = 0 ; j < tamanhoMatriz; j++){
            printf("Digite o Elemento [%d][%d]: ",i,j);
            scanf("%lf",&matrizInserir[i][j]); //Inserindo os elementos dentro da matriz
        }
    } 
    return matrizInserir;
}

//Função para inserir o valor do numero de linhas e colunas da matriz quadrada
void inserirTamanho(){
    printf("Digite o Tamanho da Matriz Quadrada (Linhas/Colunas): "); //Inserindo numero de linhas e colunas
    scanf("%d",&tamanhoMatriz);
}

//Função para verificar se existem linhas ou colunas só de zeros
void verificarZeros(double** matrizVerificarZeros){
    int contadorZeros = 0;
    for(int i = 0; i < tamanhoMatriz; i++){
        contadorZeros = 0;
        for(int j = tamanhoMatriz-1 ; j >= 0; j--){
            if(matrizVerificarZeros[i][j] == 0) //Caso tenha uma linha só de zeros, a matriz nao é reversivel
            contadorZeros++;
        }
        if(contadorZeros == 3)
            printf("MATRIZ IRREVERSIVEL : LINHA DE ZEROS\n");
    } 
    for(int i = 0; i < tamanhoMatriz; i++){
        contadorZeros = 0;
        for(int j = tamanhoMatriz-1 ; j >= 0; j--){
            if(matrizVerificarZeros[j][i] == 0) //Caso tenha uma coluna só de zeros, a matriz nao é reversivel
            contadorZeros++;
        }
        if(contadorZeros == 3)
            printf("MATRIZ IRREVERSIVEL : COLUNA DE ZEROS\n");
    } 
}

//Função para trocar as linhas caso algum pivo seja 0, procedimento para o triangulo inferior
double** trocaDeLinhasTI(double** matrizTrocaLinhas){
    double* linhaAuxiliar;
    linhaAuxiliar = malloc(tamanhoMatriz * sizeof(double));
    for(int i = 0; i < tamanhoMatriz; i++){
        if(matrizTrocaLinhas[i][i] != 0) //Se o pivo for zero, será necessário trocar a linha para uma que não seja
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
            return NULL;
        }
    }
    return matrizTrocaLinhas;
}

//Função para normalizar os pivos da matriz (torna-los 1)
double** normalizarPivos(double** matrizNormalizar){
    double valorNormalizar; //Valor que será usado para normalizar as linhas necessarias
    for(int i = 0; i < tamanhoMatriz; i++){
        if(matrizNormalizar[i][i] != 1 && matrizNormalizar[i][i] != 0) //Caso o pivo nao seja 1, realizar a operação de troca
            valorNormalizar = 1.0 / matrizNormalizar[i][i]; //Valor para multiplicar a linha e deixar o pivo com valor 1
        else
            continue;    
        for(int j = 0 ; j < tamanhoMatriz; j++){
            matrizNormalizar[i][j] = matrizNormalizar[i][j] * valorNormalizar; //Normalizando o pivo
        }
    } 
    return matrizNormalizar;
}

//Função para zerar o triangulo inferior da matriz
double** operacoesLinhasTI(double** matrizOperacoesTI){
    double valorOposto; //Valor utilizado para zerar os valores abaixo do pivo
    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = i + 1; j < tamanhoMatriz; j++){
            if(matrizOperacoesTI[j][i] == 0)
                continue;
             valorOposto = -matrizOperacoesTI[j][i]/matrizOperacoesTI[i][i]; //Pegando o valor que, quando multiplicado pelo abaixo do pivo, dará zero
             for(int w = 0; w < tamanhoMatriz; w++){
                matrizOperacoesTI[j][w] = (matrizOperacoesTI[i][w] * valorOposto) + matrizOperacoesTI[j][w]; //Zerando o valor abaixo do pivo
             }
        }
    }
    //Verificando se a matiz continua reversivel
    matrizOperacoesTI = normalizarPivos(matrizOperacoesTI);
    verificarZeros(matrizOperacoesTI);

    return matrizOperacoesTI;
}
//Função para zerar o triangulo superior da matriz
double** operacoesLinhasTS(double** matrizOperacoesTS){
    double valorOposto; //Valor utilizado para zerar os valores acima do pivo
    for(int i = tamanhoMatriz - 1; i >= 0; i--){
        for(int j = i - 1; j >= 0; j--){
            if(matrizOperacoesTS[j][i] == 0)
                continue;
             valorOposto = -matrizOperacoesTS[j][i]/matrizOperacoesTS[i][i]; //Pegando o valor que, quando multiplicado pelo acima do pivo, dará zero
             for(int w = 0; w < tamanhoMatriz; w++){
                matrizOperacoesTS[j][w] = (matrizOperacoesTS[i][w] * valorOposto) + matrizOperacoesTS[j][w]; //Zerando o valor acima do pivo
             }
        }
    }

    //Verificando se a matiz continua reversivel
    matrizOperacoesTS = normalizarPivos(matrizOperacoesTS);
    verificarZeros(matrizOperacoesTS);

    return matrizOperacoesTS;
}

//Função geral da Eliminação de Gauss-Jordan
double** eliminacaoGaussJordan(double** matrizGauss){
    verificarZeros(matrizGauss);
    matrizGauss = trocaDeLinhasTI(matrizGauss); //Chamando a função para não deixar os pivôs zerados
    matrizGauss = normalizarPivos(matrizGauss); //Chamando a função para normalizar os pivos da matriz
    matrizGauss = operacoesLinhasTI(matrizGauss); //Chamando a função para fazer a eliminação do triangulo inferior da matriz
    matrizGauss = operacoesLinhasTS(matrizGauss); //Chamando a função para fazer a eliminação do triangulo superior da matriz
    return matrizGauss;
}
int main(){
    //Declarando a matriz principal
    double** matrizMain;

    inserirTamanho(); //Chamando a função para inserir o tamanho da matriz
    matrizMain = inserirMatriz(); //Chamando a função para inserir a matriz
    imprimirMatriz(matrizMain); 
    matrizMain = eliminacaoGaussJordan(matrizMain); //Inicializando o algoritmo da Eliminação de Gauss-Jordan
    imprimirMatriz(matrizMain); 
    liberarMatriz(matrizMain);
}