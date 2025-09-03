#include <stdio.h>
#include <stdlib.h>
#define EPSILON 1e-9 //Declaração de uma constante pequena para valores pequenos (mais precisão do que o número zero)

//Assinando as funções do algoritmo
int inserirTamanho();
void liberarMatriz(double**, int);
void verificarMatriz(double**, int);
void imprimirMatriz(double**, int);
double** inserirMatriz(int);
double** eliminacaoGaussJordan(double**, int);
double** normalizarPivos(double**, int);
void verificarZeros(double**, int);
double** trocaDeLinhas(double**, int);
double** operacoesLinhasTI(double**, int);
double** operacoesLinhasTS(double**, int);
void encerrarPrograma(double**, int);
void verificarMatrizAumentada(double**, int);
double** alocarMatrizInversa(int);
double dbabs(double);


//Função para encerrar o programa
void encerrarPrograma(double** encerrarMatriz, int tamanhoMatriz){
    liberarMatriz(encerrarMatriz, tamanhoMatriz);
    fflush(stdout);
    exit(-1);
}

//Função para pegar o valor absoluto de um número
double dbabs(double valor){
    if(valor < 0)
        valor = valor*(-1);
    return valor;
}

//Função para liberar a alocação dinâmica de uma matriz
void liberarMatriz(double** matrizLiberar, int tamanhoMatriz){
    for(int i = 0; i < tamanhoMatriz; i++){
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

//Função para verificar se a matriz aumentada foi alocada com sucesso
void verificarMatrizAumentada(double** matrizVerificar, int tamanhoMatriz){
    if(matrizVerificar == NULL){
        printf("ERRO AO ALOCAR LINHAS\n"); //Erro caso não aloque as linhas
        encerrarPrograma(matrizVerificar, tamanhoMatriz);
    }
    for(int i = 0; i < tamanhoMatriz ; i++){
        if(matrizVerificar[i] == NULL){
            printf("ERRO AO ALOCAR COLUNAS\n"); //Erro caso não aloque as colunas
            encerrarPrograma(matrizVerificar, 2 * tamanhoMatriz);
        }
    }
}

//Função para imprimir uma matriz
void imprimirMatriz(double** matrizImprimir, int tamanhoMatriz){
    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = 0 ; j < (tamanhoMatriz * 2) ; j++){   
            if(j == tamanhoMatriz)    
                printf(" | ");
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
    return matrizInversa;
}

//Função para inserir a matriz que vai inverter
double** inserirMatriz(int tamanhoMatriz){
    double **matrizInserir, **matrizInversa;
    matrizInversa = alocarMatrizInversa(tamanhoMatriz);
    matrizInserir = (double **)malloc(tamanhoMatriz * sizeof(double *)); //Alocando as linhas
    for(int i = 0; i < tamanhoMatriz ; i++)
        matrizInserir[i] = (double *)malloc(2 * tamanhoMatriz * sizeof(double)); //Alocando as colunas
    verificarMatrizAumentada(matrizInserir, tamanhoMatriz);

    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = 0 ; j < tamanhoMatriz; j++){
            printf("Digite o Elemento [%d][%d]: ",i,j);
            scanf("%lf",&matrizInserir[i][j]); //Inserindo os elementos dentro da matriz
        }
    } 
    for(int i = 0; i < tamanhoMatriz; i++){
        for(int j = tamanhoMatriz ; j < tamanhoMatriz * 2; j++){
            matrizInserir[i][j] = matrizInversa[i][j-tamanhoMatriz];
        }
    } 
    liberarMatriz(matrizInversa, tamanhoMatriz);
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
            if(dbabs(matrizVerificarZeros[i][j]) < EPSILON) //Caso tenha uma linha só de zeros, a matriz não é reversível
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
            if(dbabs(matrizVerificarZeros[j][i]) < EPSILON) //Caso tenha uma coluna só de zeros, a matriz não é reversível
            contadorZeros++;
        }
        if(contadorZeros == tamanhoMatriz){
            printf("MATRIZ IRREVERSIVEL : COLUNA DE ZEROS\n");
            encerrarPrograma(matrizVerificarZeros, tamanhoMatriz);
        }
    } 
}

double** trocaDeLinhas(double** matrizTrocaLinhas, int tamanhoMatriz) {
    double* linhaAuxiliar = malloc((2 * tamanhoMatriz) * sizeof(double)); //Declaração de um vetor que irá armazenar uma linha durante a permutação
    for (int i = 0; i < tamanhoMatriz; i++) {
        //Procurando o maior pivô (em valor absoluto) da coluna i, da linha i em diante
        int indiceMaiorValorPossivel = i;
        double maiorPivoPossivel = dbabs(matrizTrocaLinhas[i][i]);
        for (int j = i + 1; j < tamanhoMatriz; j++) {
            if (dbabs(matrizTrocaLinhas[j][i]) > maiorPivoPossivel) {
                maiorPivoPossivel = dbabs(matrizTrocaLinhas[j][i]);
                indiceMaiorValorPossivel = j;
            }
        }
        //Caso seja necessário, faz a troca de linhas
        if (indiceMaiorValorPossivel != i) {
            for (int z = 0; z < 2 * tamanhoMatriz; z++) {
                linhaAuxiliar[z] = matrizTrocaLinhas[i][z];
                matrizTrocaLinhas[i][z] = matrizTrocaLinhas[indiceMaiorValorPossivel][z];
                matrizTrocaLinhas[indiceMaiorValorPossivel][z] = linhaAuxiliar[z];
            }
        }
        // Verifica se o pivô ficou zero (não dá pra inverter)
        if (dbabs(matrizTrocaLinhas[i][i]) < EPSILON) {
            printf("MATRIZ NAO REVERSIVEL : PIVO NULO NA LINHA %d\n", i);
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
        for(int j = 0 ; j < 2 * tamanhoMatriz; j++){
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
            if(dbabs(matrizOperacoesTI[j][i]) < EPSILON)
                continue; //Não precisa realizar operação caso o elemento seja zero
            if(dbabs(matrizOperacoesTI[i][i]) < EPSILON)
                matrizOperacoesTI = trocaDeLinhas(matrizOperacoesTI,tamanhoMatriz);
            if(dbabs(matrizOperacoesTI[i][i]) < EPSILON)
                encerrarPrograma(matrizOperacoesTI, tamanhoMatriz); //Para evitar divisão por zero
            valorOposto = -matrizOperacoesTI[j][i]/matrizOperacoesTI[i][i]; //Pegando o valor que, quando multiplicado pelo abaixo do pivô, dará zero
            for(int w = 0; w < 2 * tamanhoMatriz; w++){
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
            if(dbabs(matrizOperacoesTS[j][i]) < EPSILON)
                continue;
            if(dbabs(matrizOperacoesTS[i][i]) < EPSILON)
                matrizOperacoesTS = trocaDeLinhas(matrizOperacoesTS,tamanhoMatriz);
            if(dbabs(matrizOperacoesTS[i][i]) < EPSILON)
                encerrarPrograma(matrizOperacoesTS, tamanhoMatriz);
             valorOposto = -matrizOperacoesTS[j][i]/matrizOperacoesTS[i][i]; //Pegando o valor que, quando multiplicado pelo acima do pivô, dará zero
             for(int w = 0; w < 2 * tamanhoMatriz; w++){
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
    matrizGauss = trocaDeLinhas(matrizGauss, tamanhoMatriz); //Chamando a função para não deixar os pivôs zerados
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
//*ALGORITMO SENSÍVEL A MATRIZES SINGULARES