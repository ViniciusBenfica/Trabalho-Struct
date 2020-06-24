#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHOFICHA 10
#define TAMANHOCAMPO 50
/* Registro: Alunos */

typedef struct alunos
{
    char Nome[TAMANHOCAMPO];
    char Sexo[TAMANHOCAMPO];
    float Peso;
    int Colocacao;
    char Telefone[TAMANHOCAMPO];

}ALUNOS;

void carregar_arquivo(struct alunos vetor_alunos[TAMANHOFICHA]);
void exibir_alunos(ALUNOS vetor_alunos[TAMANHOFICHA]);
void ordenar_alunos(struct alunos vetor_alunos[TAMANHOFICHA]);
int pesquisar_alunos(struct alunos vetor_alunos[TAMANHOFICHA], int valor_pesquisar);
void gravar_dados_ordenados(struct alunos vetor_alunos[TAMANHOFICHA]);

int main()
{
    int Opcao;     //Opcao do Menu
    struct alunos vetor_alunos[TAMANHOFICHA];
    do{
        printf("********************************* \n");
        printf("MENU DE OPCAO: \n");
        printf("\t  [1]: Carregar arquivo e exibir\n");
        printf("\t  [2]: Ordenar dados e exibir\n");
        printf("\t  [3]: Pesquisar dados e exibir\n");
        printf("\t  [4]: Gravar os dados ORDENADOS\n");
        printf("\t  [0]: Sair do programa\n");
        printf("\t  Sua opcao: ");scanf("%i", &Opcao);
        /* Opcao: Carregar arquivo e exibir */
        if (Opcao == 1)
        {
            carregar_arquivo(vetor_alunos);
            exibir_alunos(vetor_alunos);
        }
        /* Opcao: Ordenar dados e exibir */
        else if(Opcao == 2)
        {
            system("cls");
            ordenar_alunos(vetor_alunos);
        }
        /* Opcao: Pesquisa (Bin�ria) de dados e exibir */
        else if(Opcao == 3)
        {
            int resposta, posi;
            system("cls");
            printf("Insira o valor para pesquisar por colocacao 101 ate 110: ");
            scanf("%i", &resposta);
            posi = pesquisar_alunos(vetor_alunos, resposta);
            printf("%i", posi);
            printf("Vendedor %i:\n", posi);
            printf("\t  Nome      : %s\n", vetor_alunos[posi].Nome);
            printf("\t  Sexo      : %s\n", vetor_alunos[posi].Sexo);
            printf("\t  Peso      : %.2f\n", vetor_alunos[posi].Peso);
            printf("\t  Colocacao : %i\n", vetor_alunos[posi].Colocacao);
            printf("\t  Telefone  : %s\n", vetor_alunos[posi].Telefone);
        }
        /* Opcao: Gravar os dados ORDENADOS (Opcional) */
        else if(Opcao == 4)
        {
            system("cls");
            printf("Gravar os dados ORDENADOS (Opcional): \n\n");
            gravar_dados_ordenados(vetor_alunos);
            printf("DISCO GRAVADO COM SUCESSO\n");
        }
        /* Opcao: Sair do Programa */
        else if(Opcao == 0)
        {
            system("cls");
            printf("FIM DO PROGRAMA.\n\n\n");
        }
    }while(Opcao);
    return 0;
}
void carregar_arquivo(struct alunos vetor_alunos[TAMANHOFICHA])
{
    int i = 0;     //Indice de contagem do vetor Auxiliar (Aux)
    char C;        //Caractere Auxiliar: Ler um a um do arquivo
    int Quant = 0; //Conta a quantidade de Registros no arquivo
    int Campo = 1; //Acessa os Campos dos Registros: Vetor Ficha
    FILE *Arquivo; //Arquivo: Vari�vel do tipo File (arquivo)
    char Aux[TAMANHOCAMPO]; //Monta a linha do arquivo
    Arquivo = fopen("Arquivo.txt", "r");
    if (Arquivo == 0){
        printf("Erro na abertura do arquivo.\n\n\n");
        fclose(Arquivo);
    }
    else
    {
        i = 0; Quant = 0; Campo = 1;
        do
        {
            /* Ler caractere por caractere do arquivo */
            C = getc(Arquivo);
            if (C != '\n' && C != EOF)
            {
                /* Monta um vetor (Aux) com os caracteres da linha */
                /* Monta linha por linha do arquivo */
                Aux[i] = C;
                i++;
                }
            else
            {
                /* Monta o vetor Ficha: Campo por Campo */
                Aux[i] = '\0'; //Finaliza a linha (String)
                /* Salva a linha no Registro no seu Respectivo Campo */
                switch (Campo)
                {
                    case 1:
                        strcpy(vetor_alunos[Quant].Nome, Aux);
                        break;
                    case 2:
                        strcpy(vetor_alunos[Quant].Sexo, Aux);
                        break;
                    case 3:
                        vetor_alunos[Quant].Peso = atof(Aux);
                        break;
                    case 4:
                        vetor_alunos[Quant].Colocacao = atoi(Aux);
                        break;
                    case 5:
                        strcpy(vetor_alunos[Quant].Telefone, Aux);

                        Campo = 0; //Reinicia para o pr�ximo registro
                        Quant++;   //Incrementa 1 para o pr�ximo registro
                    }
                    Campo++; //Pr�ximo Campo
                    i = 0;   //Reinicia o Indice do vetor auxiliar (Aux)
            }
                /* Enquanto: Caractere (C) for diferente do 'End Of File' (EOF)*/
        }while (C != EOF);
        /* Fechar o arquivo (FILE) */
        fclose(Arquivo);
    }
}
void exibir_alunos(ALUNOS vetor_alunos[TAMANHOFICHA])
{
    /* Exibe os dados do Arquivo (Registros: Aluno) */
    int i;
    for (i = 0; i < TAMANHOFICHA; i++)
    {
        printf("Vendedor %i:\n", i + 1);
        printf("\t  Nome      : %s\n", vetor_alunos[i].Nome);
        printf("\t  Sexo      : %s\n", vetor_alunos[i].Sexo);
        printf("\t  Peso      : %.2f\n", vetor_alunos[i].Peso);
        printf("\t  Colocacao : %i\n", vetor_alunos[i].Colocacao);
        printf("\t  Telefone  : %s\n", vetor_alunos[i].Telefone);
    }
}
void ordenar_alunos(struct alunos vetor_alunos[TAMANHOFICHA]){
    int Opcao;
        do{
        printf("********************************* \n");
        printf("MENU DE OPCAO: \n");
        printf("\t  [1]: Ordenar por Nome(A-Z)\n");
        printf("\t  [2]: Ordenar por Nome(Z-A)\n");
        printf("\t  [3]: Ordenar por Sexo(F-M)\n");
        printf("\t  [4]: Ordenar por Sexo(M-F)\n");
        printf("\t  [5]: Ordenar por Peso\n");
        printf("\t  [6]: Colocacao\n");
        printf("\t  [0]: Sair do programa\n");
        printf("\t  Sua opcao: ");scanf("%i", &Opcao);
        // Ordernar por Nome
        if(Opcao == 1){
            carregar_arquivo(vetor_alunos);
            int i,j,comparar;
            struct alunos aux;

            for(i = 0; i < TAMANHOFICHA; i++){
                for(j = i + 1; j < TAMANHOFICHA; j++){
                    comparar = strcmp(vetor_alunos[i].Nome, vetor_alunos[j].Nome);
                if(comparar > 0){
                aux = vetor_alunos[i];
                vetor_alunos[i] = vetor_alunos[j];
                vetor_alunos[j] = aux;
                }
            }
        }
            for(i = 0; i < TAMANHOFICHA; i++){
                printf("Vendedor %i:\n", i + 1);
                printf("\t  Nome      : %s\n", vetor_alunos[i].Nome);
                printf("\t  Sexo      : %s\n", vetor_alunos[i].Sexo);
                printf("\t  Peso      : %.2f\n", vetor_alunos[i].Peso);
                printf("\t  Colocacao : %i\n", vetor_alunos[i].Colocacao);
                printf("\t  Telefone  : %s\n", vetor_alunos[i].Telefone);
            }
        }
        // Ordernar por Nome
        else if(Opcao == 2){
            carregar_arquivo(vetor_alunos);
            int i,j,comparar;
            struct alunos aux;

            for(i = 0; i < TAMANHOFICHA; i++){
                for(j = i + 1; j < TAMANHOFICHA; j++){
                    comparar = strcmp(vetor_alunos[i].Nome, vetor_alunos[j].Nome);
                if(comparar < 0){
                aux = vetor_alunos[i];
                vetor_alunos[i] = vetor_alunos[j];
                vetor_alunos[j] = aux;
                }
            }
        }
            for(i = 0; i < TAMANHOFICHA; i++){
                printf("Vendedor %i:\n", i + 1);
                printf("\t  Nome      : %s\n", vetor_alunos[i].Nome);
                printf("\t  Sexo      : %s\n", vetor_alunos[i].Sexo);
                printf("\t  Peso      : %.2f\n", vetor_alunos[i].Peso);
                printf("\t  Colocacao : %i\n", vetor_alunos[i].Colocacao);
                printf("\t  Telefone  : %s\n", vetor_alunos[i].Telefone);
            }
        }
        //Ordernar por Sexo
        else if(Opcao == 3){
        carregar_arquivo(vetor_alunos);
        int i, j, comparar;
        struct alunos aux;

        for(i = 0; i < TAMANHOFICHA; i++){
            for(j = i + 1; j < TAMANHOFICHA; j++){
                comparar = strcmp(vetor_alunos[i].Sexo, vetor_alunos[j].Sexo);
                if(comparar > 0){
                    aux = vetor_alunos[i];
                    vetor_alunos[i] = vetor_alunos[j];
                    vetor_alunos[j] = aux;
                }
            }
        }
            for(i = 0; i < TAMANHOFICHA; i++){
                printf("Vendedor %i:\n", i + 1);
                printf("\t  Nome      : %s\n", vetor_alunos[i].Nome);
                printf("\t  Sexo      : %s\n", vetor_alunos[i].Sexo);
                printf("\t  Peso      : %.2f\n", vetor_alunos[i].Peso);
                printf("\t  Colocacao : %i\n", vetor_alunos[i].Colocacao);
                printf("\t  Telefone  : %s\n", vetor_alunos[i].Telefone);
            }

        }
        //Ordernar por Sexo
        else if(Opcao == 4){
             carregar_arquivo(vetor_alunos);
        int i, j, comparar;
        struct alunos aux;

        for(i = 0; i < TAMANHOFICHA; i++){
            for(j = i + 1; j < TAMANHOFICHA; j++){
                comparar = strcmp(vetor_alunos[i].Sexo, vetor_alunos[j].Sexo);
                if(comparar < 0){
                    aux = vetor_alunos[i];
                    vetor_alunos[i] = vetor_alunos[j];
                    vetor_alunos[j] = aux;
                }
            }
        }
            for(i = 0; i < TAMANHOFICHA; i++){
                printf("Vendedor %i:\n", i + 1);
                printf("\t  Nome      : %s\n", vetor_alunos[i].Nome);
                printf("\t  Sexo      : %s\n", vetor_alunos[i].Sexo);
                printf("\t  Peso      : %.2f\n", vetor_alunos[i].Peso);
                printf("\t  Colocacao : %i\n", vetor_alunos[i].Colocacao);
                printf("\t  Telefone  : %s\n", vetor_alunos[i].Telefone);
            }
        }
        //Ordernar por Peso
        else if(Opcao == 5){
        carregar_arquivo(vetor_alunos);
        int i, j;
        struct alunos aux;

        for(i = 0; i < TAMANHOFICHA; i++){
            for(j = i + 1; j < TAMANHOFICHA; j++){
                    if(vetor_alunos[i].Peso > vetor_alunos[j].Peso){
                        aux = vetor_alunos[i];
                        vetor_alunos[i] = vetor_alunos[j];
                        vetor_alunos[j] = aux;
                    }
                }
            }
            for(i = 0; i < TAMANHOFICHA; i++){
                printf("Vendedor %i:\n", i + 1);
                printf("\t  Nome      : %s\n", vetor_alunos[i].Nome);
                printf("\t  Sexo      : %s\n", vetor_alunos[i].Sexo);
                printf("\t  Peso      : %.2f\n", vetor_alunos[i].Peso);
                printf("\t  Colocacao : %i\n", vetor_alunos[i].Colocacao);
                printf("\t  Telefone  : %s\n", vetor_alunos[i].Telefone);
            }
        }
        //Ordenar por colocacao
        else if(Opcao == 6){
        carregar_arquivo(vetor_alunos);
        int i, j;
        struct alunos aux;

        for(i = 0; i < TAMANHOFICHA; i++){
            for(j = i + 1; j < TAMANHOFICHA; j++){
                if(vetor_alunos[i].Colocacao > vetor_alunos[j].Colocacao){
                    aux = vetor_alunos[i];
                    vetor_alunos[i] = vetor_alunos[j];
                    vetor_alunos[j] = aux;
                }
            }
        }

        for(int i = 0; i < TAMANHOFICHA; i++){
                printf("Vendedor %i:\n", i + 1);
                printf("\t  Nome      : %s\n", vetor_alunos[i].Nome);
                printf("\t  Sexo      : %s\n", vetor_alunos[i].Sexo);
                printf("\t  Peso      : %.2f\n", vetor_alunos[i].Peso);
                printf("\t  Colocacao : %i\n", vetor_alunos[i].Colocacao);
                printf("\t  Telefone  : %s\n", vetor_alunos[i].Telefone);
            }
        }
        }while(Opcao);
}
void ordenar_alunosCol(struct alunos vetor_alunos[TAMANHOFICHA]){
 carregar_arquivo(vetor_alunos);
        int i, j;
        struct alunos aux;

        for(i = 0; i < TAMANHOFICHA; i++){
            for(j = i + 1; j < TAMANHOFICHA; j++){
                if(vetor_alunos[i].Colocacao > vetor_alunos[j].Colocacao){
                    aux = vetor_alunos[i];
                    vetor_alunos[i] = vetor_alunos[j];
                    vetor_alunos[j] = aux;
                }
            }
        }
}

int pesquisar_alunos(struct alunos vetor_alunos[TAMANHOFICHA], int valor_pesquisar){
    ordenar_alunosCol(vetor_alunos);
    int inf,sup,meio;
    inf = 0;
    sup = TAMANHOFICHA - 1;
    while(inf<=sup){
      meio=(inf+sup)/2;
      if (valor_pesquisar == vetor_alunos[meio].Colocacao)
           return meio;
      else if (valor_pesquisar < vetor_alunos[meio].Colocacao)
           sup=meio-1;
      else
           inf=meio+1;
 }
 return meio;
}

void gravar_dados_ordenados(struct alunos vetor_alunos[TAMANHOFICHA]){
        ordenar_alunosCol(vetor_alunos);
        FILE *output = fopen("Saida.txt", "w"); // Abre o arquivo para escrever
        if (!output) {
            return -1; // Erro
        }
        for (int i = 0; i < TAMANHOFICHA; ++i) {
            fprintf(output, "%s\n%s\n%.2f\n%i\n%s", vetor_alunos[i].Nome,vetor_alunos[i].Sexo, vetor_alunos[i].Peso, vetor_alunos[i].Colocacao, vetor_alunos[i].Telefone);
        }
        fclose(output); // Fecha o arquivo
        return 1;
    }

