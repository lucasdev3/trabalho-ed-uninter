#include <stdlib.h> // inclui as bibliotecas a serem usadas
#include <stdio.h>
#include <locale.h>
#include <string.h>

void inicializarTabela(); // função de espalhamento (resto da divisão do numeroRU por M). Inicializa a tabela com o valor -1.
void inserirAluno(); // função para inserir um aluno na tabela.
void listarTabela(); //funcao para listar todos os alunos da tabela.
int criarCodigoHash(int numeroRU); // função para gerar um código hash para cada elemento da tabela.

#define M 11 // valor constante chamado "M" para representar o tamanho da tabela

// estrutura dadosAluno com nome, matrícula e email
typedef struct
{
    int ru;
    char nome[50];
    char email[50];
}dadosAluno; 

// tabela hash do tipo dadosAluno
dadosAluno tabelaHash[M]; 

// função para ler e retornar os dados do aluno
dadosAluno lerdadosAluno()
{
    dadosAluno Aluno;
    printf("Digite o RU do aluno:\n");
    scanf_s("%d", &Aluno.ru);
    scanf_s("%*c");
    printf("Digite o nome do Aluno:\n");
    fgets(Aluno.nome, 50 - 1, stdin);
    printf("Digite o e-mail do Aluno:\n");
    fgets(Aluno.email, 50 - 1, stdin);
    printf("\nDados inseridos com sucesso!\n");
    printf("\nRU:\t%d\n", Aluno.ru);
    printf("Aluno:\t%s", Aluno.nome);
    printf("E-mail\t%s", Aluno.email);
    system("pause");
    return Aluno;
}

// função para procurar um aluno na tabela
dadosAluno* procurar(int numeroRU)
{
    int indice = criarCodigoHash(numeroRU);
    while (tabelaHash[indice].ru != -1)
    {
        if (tabelaHash[indice].ru == numeroRU)
        {
            return &tabelaHash[indice];
        }
        else
        {
            indice = criarCodigoHash(indice + 1);
        }
    }
    return NULL;
}

//função principal
int main()
{
    setlocale(LC_ALL, "Portuguese"); // prepara o código para portugues BR.
    

    int opcao, numeroRU;
    dadosAluno* Aluno;

    inicializarTabela(); // inicializa a tabela com os índices para cada aluno.

    // menu de opções
    do
    {
        system("cls");
        printf("SISTEMA DE CADASTRO DE ALUNOS\n\n");
        printf("\tMENU PRINCIPAL\n\n");
        printf("(1) - Inserir novo aluno\n");
        printf("(2) - Procurar aluno por RU\n");
        printf("(3) - Listar todos os alunos\n");
        printf("(4) - Sair\n\n");
        printf("Digite a opcao:\n");
        scanf_s("%d", &opcao);

        switch (opcao)
        {
        case 1:
            system("cls");
            printf("SISTEMA DE CADASTRO DE ALUNOS\n\n");
            printf("     MENU DE INSERÇÃO DE ALUNO\n\n");
            inserirAluno(); // chama a função para inserir.
            break;
        case 2:
            system("cls");
            printf("SISTEMA DE CADASTRO DE ALUNOS\n\n");
            printf("\tMENU DE BUSCA\n\n");
            printf("Digite o RU do aluno a ser buscado:\n");
            scanf_s("%d", &numeroRU);
            Aluno = procurar(numeroRU);// chama a função para procurar o ru, usando como parâmetro o ru informado.
            if (Aluno)
            {
                printf("\nDados encontrados!\n");
                printf("\nRU:\t%d\n", Aluno->ru);
                printf("Nome:\t%s", Aluno->nome);
                printf("E-mail:\t%s", Aluno->email);
                printf("\n");
                system("pause");
            }
            else
            {
                printf("\nRU nao encontrado!\n");
                system("pause");
            }
            break;
        case 3:
            listarTabela(); // chama a função para listagem dos alunos cadastrados.
            break;
        case 4:
            system("cls"); // encerra o código.
            
            printf("SISTEMA ENCERRADO!\n\n");
            break;
        default:
            printf("Opcao inválida!\n");
        }

    } while (opcao != 4); // fica no menu até que o usuário escolha sair
    return 0;
}

// função de espalhamento (resto da divisão do numeroRU por M). Inicializa a tabela com o valor -1.
void inicializarTabela()
{
    int i;
    for (i = 0; i < M; i++)
    {
        tabelaHash[i].ru = -1;
    }
}

// função para inserir um aluno na tabela.
void inserirAluno()
{
    dadosAluno alu = lerdadosAluno();
    int indice = criarCodigoHash(alu.ru);
    while (tabelaHash[indice].ru != -1)
    {
        indice = criarCodigoHash(indice + 1);
    }
    tabelaHash[indice] = alu;
}

//funcao para listar todos os alunos da tabela.
void listarTabela()
{
    system("cls");
    printf("SISTEMA DE CADASTRO DE ALUNOS\n\n");
    printf("\tMENU DE LISTAGEM\n\n");
    int i;
    for (i = 0; i < M; i++)
    {
        if (tabelaHash[i].ru != -1)
        {
            printf("RU:\t%d\n", tabelaHash[i].ru);
            printf("Nome:\t%s", tabelaHash[i].nome);
            printf("E-mail\t%s\n", tabelaHash[i].email);
        }
    }
    printf("\n");
    system("pause");
}

// função para gerar um código hash para cada elemento da tabela.
int criarCodigoHash(int numeroRU)
{
    return numeroRU % M;
}
// fim do programa