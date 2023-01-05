#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"funcionalidades.h"

/*   ↓ Limpa o stdin ↓   */
void limpaInput()
{
    while (getchar() != '\n');
}

/*   ↓ Imprime as informações necessárias da questão ↓   */
void mostraPerguntas(asks pr)
{
    printf("➤  Identificador: %s\n", pr.identificador);
    printf("   Questão: %s\n", pr.questao);
    printf("   Resposta certa: %s\n", pr.respostaCerta);
    printf("   Respostas erradas: %s, %s, %s\n", pr.respostaErrada1, pr.respostaErrada2, pr.respostaErrada3);
    printf("   Dificuldade: %s\n", pr.dificuldade);
}

/*   ↓ Transforma uma palavra qualquer nela mesma em minúsculas ↓   */
void minuscula(char *original, char *final)
{
    int i;
    for(i=0; original[i] != '\0'; i++)
        final[i] = tolower(original[i]);
    final[i] = '\0';
}

/*
 * Dado um nome, a função procura dentro do array pr todas as questões e respetivas 
 * informações que contenham esse nome e imprime-as
 */
void indicePergunta(char *nome, asks *pr)
{
    int i = 0, cont = 0;
    char *o, *p, *q, *r, *s, *t, *u;
    char procuradoMinus[257];
    
    while (i < N && strlen(pr[i].questao) > 0)
    {
        char min0[strlen(pr[i].identificador)+1], min1[strlen(pr[i].questao)+1], min2[strlen(pr[i].respostaCerta)+1], min3[strlen(pr[i].respostaErrada1)+1], min4[strlen(pr[i].respostaErrada2)+1], min5[strlen(pr[i].respostaErrada3)+1], min6[strlen(pr[i].dificuldade)+1];

        /*   ↓ Transforma todas as questões e respetivo conjunto de infos em minúsculas (Case insensitive) ↓   */
        minuscula(pr[i].identificador, min0);
        minuscula(pr[i].questao, min1);
        minuscula(pr[i].respostaCerta, min2);
        minuscula(pr[i].respostaErrada1, min3);
        minuscula(pr[i].respostaErrada2, min4);
        minuscula(pr[i].respostaErrada3, min5);
        minuscula(pr[i].dificuldade, min6);
        minuscula(nome, procuradoMinus);

        /*   ↓ Verifica se a palavra procurada está presente em cada uma das questões, respostas etc ↓   */
        /*   o, p, q, r, s, t, u são apontadores para o a primeira letra da palavra procurada(procuradoMinus), 
                            que aparece dentro da palavra/frase principal (min)   */
        o = strstr(min0, procuradoMinus);
        p = strstr(min1, procuradoMinus);
        q = strstr(min2, procuradoMinus);
        r = strstr(min3, procuradoMinus);
        s = strstr(min4, procuradoMinus);
        t = strstr(min5, procuradoMinus);
        u = strstr(min6, procuradoMinus);
        
        if(o || p || q || r || s || t || u) // Se sim, então mostra essas mesmas questões
        {
            mostraPerguntas(pr[i]);
            cont++;
            printf("\n");
        }
        i++;
    }
    if(cont==0) // Se não encontrar nenhuma, imprime a seguinte mensagem
        printf("- Não foram encontrados resultados que correspondem à sua pesquisa! ☹ \n");
}

/*   ↓  Abre o ficheiro 'fnome' no modo 'modo'  ↓   */
FILE *abreFicheiro(char *fnome, char *modo) 
{
    FILE *f = fopen(fnome, modo);

    if (f == NULL)
    {
        fprintf(stderr, "Falhou abertura de %s.\n", fnome);
        exit(EXIT_FAILURE);
    }

    return f;
}

/*   ↓  Fecha o ficheiro 'f' que se chama 'fnome'  ↓   */
void fechaFicheiro(FILE *f, char *fnome)
{
    if (fclose(f) == EOF)
    {
        fprintf(stderr, "Falhou o fecho de %s.\n", fnome);
        exit(EXIT_FAILURE);
    }
}

/*   ↓  Lê as asks que estão no ficheiro BINÁRIO chamado 'fnome'  ↓   */
void leBin(asks *pr, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "rb");

    fread(pr, sizeof(asks), N, f); // Lê a partir do ficheiro f, N elementos de tamanho sizeof(asks), começando pelo início do bloco de dados

    fechaFicheiro(f, fnome);
}

/*   ↓  Lê as asks que estão no ficheiro TEXTO chamado 'fnome'  ↓   */
void leTXT(asks *pr, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "r");

    int i = 0;
    /*             ↓  Lê o input formatado através da stream  ↓                       */
    /* Tudo o que estiver no lugar de %[^|], é guardado em pr[i].identificador etc... */
    while (fscanf(f, "ID %[^|]|QUESTÃO: %[^|]|RESPOSTA CERTA: %[^|]|RESPOSTAS ERRADAS: %[^,], %[^,], %[^|]|DIFICULDADE: %[^.].\n", pr[i].identificador, pr[i].questao, pr[i].respostaCerta, pr[i].respostaErrada1, pr[i].respostaErrada2, pr[i].respostaErrada3, pr[i].dificuldade) == 7)
    {
        i++; // precorre posições até que não consiga coletar tudo o que é desejado 
    }

    fechaFicheiro(f, fnome);
}

/*   ↓  Mostra o array de perguntas armazenado  ↓   */
void mostraArray(asks *pr, int n)
{
    int saida;

    for (int i = 0; i < n && strlen(pr[i].questao) > 0 && saida != 1; i++) // Precorre posições enquanto existe alguma questão
    {
        mostraPerguntas(pr[i]);
        printf("\n");

        if ((i + 1) % 5 == 0) // Quando forem mostrados 5/10/15... perguntas, é dada a opção de sair(q) ou continuar(enter)
        {
            printf(" - Prima enter para ver os próximos ou 'q' para sair.\n");
            if(getchar() == 'q')
                saida = 1;
            printf("\n");
        }
    }
}

/*   ↓  Pergunta se queremos repetir a ação que fizemos e retorna a opção escolhida, para ser usada na main  ↓   */
int repetirAcao()
{
    int opcaoEscolhida;

    printf("↪  1. REPETIR AÇÃO\n");
    printf("↪  2. VOLTAR AO MENU\n\n");
    printf("Opção -> ");
    while(scanf("%d", &opcaoEscolhida) != 1)
    {
        limpaInput();
        printf(" ✘  Input inválido! Digite algo válido: ");
    }
    while(opcaoEscolhida < 1 || opcaoEscolhida > 2)
    {
        limpaInput();
        printf(" ✘  Opção inválida! Digite algo válido: ");
        while(scanf("%d", &opcaoEscolhida) != 1)
        {
            limpaInput();
            printf(" ✘  Input inválido! Digite algo válido: ");
        }
    }

    return opcaoEscolhida;
}

/*   ↓  Cria uma pergunta pr, a partir das infos dadas: identificador, questao ...  ↓   */
asks criaPergunta(asks pr, char *identificador, char *questao, char *respostaCerta, char *respostaErrada1, char *respostaErrada2, char *respostaErrada3, char *dificuldade)
{
    strcpy(pr.identificador, identificador);
    strcpy(pr.questao, questao);
    strcpy(pr.respostaCerta, respostaCerta);
    strcpy(pr.respostaErrada1, respostaErrada1);
    strcpy(pr.respostaErrada2, respostaErrada2);
    strcpy(pr.respostaErrada3, respostaErrada3);
    strcpy(pr.dificuldade, dificuldade);

    return pr;
}

/*   ↓  Pede ao utilizador os dados necessários para poder criar uma pergunta. Verifica/valida o input  ↓   */
asks criaPerguntaIO()
{
    asks pr;
    int len;
    char *pos;
    char minus[257];
    char ident[4];
    char pergunta[257];
    char respostaCerta[257];
    char respostaErrada1[257];
    char respostaErrada2[257];
    char respostaErrada3[257];
    char dificuldade[257];

    do
    {
        printf("Identificador [Máximo 2 caracters]: ");
        fgets(ident, 257, stdin);
        pos = strchr(ident, '\n');
        *pos = '\0';
        len = strlen(ident);
        if (len == 0)
            printf(" ✘ Identificador vazio!!\n");
        if(len > 2)
            printf(" ✘ Identificador demasiado longo!!\n");
    } while (len == 0 || len > 2);

    do
    {
        printf("Pergunta: ");
        fgets(pergunta, 257, stdin);
        pos = strchr(pergunta, '\n');
        *pos = '\0';
        len = strlen(pergunta);
        if (len == 0)
            printf(" ✘ Pergunta vazia. Indique outra.\n");
    } while (len == 0);

    do
    {
        printf("Resposta Certa: ");
        fgets(respostaCerta, 257, stdin);
        pos = strchr(respostaCerta, '\n');
        *pos = '\0';
        len = strlen(respostaCerta);
        if (len == 0)
            printf(" ✘ Resposta vazia. Indique outra.\n");
    } while (len == 0);

    do
    {
        printf("Resposta Errada 1: ");
        fgets(respostaErrada1, 257, stdin);
        pos = strchr(respostaErrada1, '\n');
        *pos = '\0';
        len = strlen(respostaErrada1);
        if (len == 0)
            printf(" ✘ Resposta vazia. Indique outro.\n");
    } while (len == 0);

    do
    {
        printf("Resposta Errada 2: ");
        fgets(respostaErrada2, 257, stdin);
        pos = strchr(respostaErrada2, '\n');
        *pos = '\0';
        len = strlen(respostaErrada2);
        if (len == 0)
            printf(" ✘ Resposta vazia. Indique outro.\n");
    } while (len == 0);

    do
    {
        printf("Resposta Errada 3: ");
        fgets(respostaErrada3, 257, stdin);
        pos = strchr(respostaErrada3, '\n');
        *pos = '\0';
        len = strlen(respostaErrada3);
        if (len == 0)
            printf(" ✘ Resposta vazia. Indique outro.\n");
    } while (len == 0);

    do
    {
        printf("Diciculdade (facil/medio/dificil sem acentuação): ");
        fgets(dificuldade, 257, stdin);
        pos = strchr(dificuldade, '\n');
        *pos = '\0';
        minuscula(dificuldade, minus);
        len = strlen(minus);
        /*   ↓  Caso a 'dificuldade' escrita não esteja na forma pretendida, esta acaba não sendo aceite  ↓   */
        if (len == 0 || (strcmp(minus, "facil") != 0 && strcmp(minus, "medio") != 0 && strcmp(minus, "dificil") != 0))
            printf(" ✘ Dificuldade inválida. Indique outra.\n");
    } while (len == 0 || (strcmp(minus, "facil") != 0 && strcmp(minus, "medio") != 0 && strcmp(minus, "dificil") != 0));

    /*   ↓  Cria pergunta com a informação dada  ↓   */
    return criaPergunta(pr, ident, pergunta, respostaCerta, respostaErrada1, respostaErrada2, respostaErrada3, dificuldade);
}

/*Adiciona a pergunta 'p' ao array de asks 'pr' na posicao 'indice' */
void adicionaPergunta(asks p, int indice, asks *pr)
{
    pr[indice] = p;
}

/*   ↓  Devolve o índice da última pergunta do array de asks pr ↓   */
int indice(asks *pr)
{
    int ret = 0;
    int i = 0;

    while (i < N && strlen(pr[i].questao) > 0)
    {
        i++;
    }
    
    if (i == N)
        ret = -1; // Se estiver cheio, devolve -1
    else
        ret = i;

    return ret;
}

/*   ↓  Adiciona uma pergunta à primeira posição LIVRE do array de asks pr  ↓   */
void adicionaPerguntaIO(asks *pr)
{
    int op, ind = 0;

    do // Está constantemente a adicionar asks até o user digitar algum número para além de 1
    {
        ind = indice(pr);
        if (ind == -1)
        {
            printf(" ✘  Atingiu o limite máximo de asks guardadas (%d).\n", N);
        }
        else
        {
            adicionaPergunta(criaPerguntaIO(), ind, pr);
            printf("\n --> Prima 1 para adicionar nova pergunta ou qualquer outro número para sair.\n");
            while (scanf("%d", &op) != 1)
            {
                limpaInput();
                printf(" ✘  Prima 1 para adicionar nova pergunta ou qualquer outro número para sair.\n");
            }
            limpaInput();
            printf("\n");
        }
    } while (op == 1 && ind != -1);
}

/*   ↓  Grava o conteúdo do array de asks pr no ficheiro BINÁRIO "fnome"  ↓   */
void gravaBin(asks *pr, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "wb");

    fwrite(pr, sizeof(asks), N, f);

    fechaFicheiro(f, fnome);
}

/*   ↓  Grava o conteúdo do array de asks pr no ficheiro de TEXTO "fnome"  ↓   */
void gravaTXT(asks *pr, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "w");

    for (int i = 0; i < N && strlen(pr[i].questao) > 0; i++) // precorre todas as posições do array até encontrar uma questão vazia
    {
        // Imprime no ficheiro o que é pretendido (formatado)
        fprintf(f, "ID %s|QUESTÃO: %s|RESPOSTA CERTA: %s|RESPOSTAS ERRADAS: %s, %s, %s|DIFICULDADE: %s.\n", pr[i].identificador, pr[i].questao, pr[i].respostaCerta, pr[i].respostaErrada1, pr[i].respostaErrada2, pr[i].respostaErrada3, pr[i].dificuldade);
    }
    fechaFicheiro(f, fnome);
}

/*   ↓ Dado um identificador e um array de asks, 
devolve o índice do identificador no array  ↓   */
int indiceRemove(char *indentificador, asks *pr)
{
    int i = 0;
    int res = -1;
    char min1[100], min2[100];

    while (i < N && strlen(pr[i].questao) > 0)
    {
        /* A procura é feita em case sensitive */
        minuscula(pr[i].identificador, min1);
        minuscula(indentificador, min2);
        if (strcmp(min1, min2) == 0)
        {
            res = i;
            break;
        }
        i++;
    }
    return res; // res = indice da pergunta com o identificador pedido
                // Se não encontrar res = -1! 
}

/* Remove a pergunta com o identificador 'identificador' do array de oerguntas 'pr'.
 * Se existir mais do que uma pergunta com o mesmo nome, remove a primeira
 * Devolve 1 se a pergunta não existir, 0 caso contrario */
int removePergunta(char *identificador, asks *pr)
{
    int i, ret = 0;

    i = indiceRemove(identificador, pr);

    if (i >= 0)
    {
        /* Encontrada a pergunta, move todas as posições que estão à sua frente, uma casa para trás */
        while (i < N - 1 && strlen(pr[i].questao) > 0)
        {
            pr[i] = pr[i + 1];
            i++;
        }
        asks per = {}; // A questão "mais avançada" passa então a ser vazia, para não haver repetição
        pr[i] = per;
    }
    else
    {
        ret = 1; // Não encontrou a pergunta
    }
    return ret;
}

/* Remove a(as) pergunta(s) pretendidas(s) e dá feedback  */
void removePerguntaIO(asks *pr)
{
    int op;
    char pnome[100];
    char *pos;

    do // Vai remover asks até que o utilizador digite 1 
    {
        printf("• Escreva o nome do IDENTIFICADOR da pergunta que pretende remover: ");
        fgets(pnome, 100, stdin);
        pos = strchr(pnome, '\n');
        *pos = '\0';
        
        if (removePergunta(pnome, pr) == 1) 
            printf(" ✘  Pergunta Inexistente.\n");
        else
        {
            printf(" ✔ Pergunta relativa ao identificador %s removida com sucesso.\n", pnome);
        }
        printf("\n-> Prima 1 para remover outra pergunta ou qualquer outro número para sair --> ");
        while (scanf("%d", &op) != 1)
        {
            limpaInput();
            printf(" ✘  Prima 1 pvara remover nova pergunta ou qualquer outro número para sair.\n");
        }
        printf("\n");
        limpaInput();
    } while (op == 1);
}

void linha()
{
    printf("――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n");
}

void guardaResultado(char nome[50], char apelido[50], int acumulado)
{
    FILE *res = fopen("resultados.txt", "a");

    fprintf(res,"%s %s acumulou %d$\n", nome, apelido, acumulado);

    fclose(res);
}
