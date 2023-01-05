#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <time.h>

#define N 150 // Número máximo de asks

/*   ↓ Representa a estrutura simplificada de uma pergunta ↓   */
typedef struct
{
    char identificador[4];
    char questao[257];
    char respostaCerta[257];
    char respostaErrada1[257];
    char respostaErrada2[257];
    char respostaErrada3[257];
    char dificuldade[10];
} asks;

/*   ↓ Limpa o stdin ↓   */
void limpaInput();

/*   ↓ Imprime as informações necessárias da questão ↓   */
void mostraasks(asks pr);

/*   ↓ Transforma uma palavra qualquer nela mesma em minúsculas ↓   */
void minuscula(char *original, char *final);

/*
 * Dado um nome, a função procura dentro do array pr todas as questões e respetivas 
 * informações que contenham esse nome e imprime-as
 */
void indicePergunta(char *nome, asks *pr);


/*   ↓  Abre o ficheiro 'fnome' no modo 'modo'  ↓   */
FILE *abreFicheiro(char *fnome, char *modo);

/*   ↓  Fecha o ficheiro 'f' que se chama 'fnome'  ↓   */
void fechaFicheiro(FILE *f, char *fnome);

/*   ↓  Lê as asks que estão no ficheiro BINÁRIO chamado 'fnome'  ↓   */
void leBin(asks *pr, char *fnome);

/*   ↓  Lê as asks que estão no ficheiro TEXTO chamado 'fnome'  ↓   */
void leTXT(asks *pr, char *fnome);

/*   ↓  Mostra o array de asks armazenado  ↓   */
void mostraArray(asks *pr, int n);

/*   ↓  Pergunta se queremos repetir a ação que fizemos e retorna a opção escolhida, para ser usada na main  ↓   */
int repetirAcao();

/*   ↓  Cria uma pergunta pr, a partir das infos dadas: identificador, questao ...  ↓   */
asks criaPergunta(asks pr, char *identificador, char *questao, char *respostaCerta, char *respostaErrada1, char *respostaErrada2, char *respostaErrada3, char *dificuldade);

/*   ↓  Pede ao utilizador os dados necessários para poder criar uma pergunta. Verifica/valida o input  ↓   */
asks criaPerguntaIO();

/*Adiciona a pergunta 'p' ao array de asks 'pr' na posicao 'indice' */
void adicionaPergunta(asks p, int indice, asks *pr);

/*   ↓  Devolve o índice da última pergunta do array de asks pr ↓   */
int indice(asks *pr);

/*   ↓  Adiciona uma pergunta à primeira posição LIVRE do array de asks pr  ↓   */
void adicionaPerguntaIO(asks *pr);

/*   ↓  Grava o conteúdo do array de asks pr no ficheiro BINÁRIO "fnome"  ↓   */
void gravaBin(asks *pr, char *fnome);

/*   ↓  Grava o conteúdo do array de asks pr no ficheiro de TEXTO "fnome"  ↓   */
void gravaTXT(asks *pr, char *fnome);

/*   ↓ Dado um identificador e um array de asks, 
devolve o índice do identificador no array  ↓   */
int indiceRemove(char *indentificador, asks *pr);

/* Remove a pergunta com o identificador 'identificador' do array de oerguntas 'pr'.
 * Se existir mais do que uma pergunta com o mesmo nome, remove a primeira
 * Devolve 1 se a pergunta não existir, 0 caso contrario */
int removePergunta(char *identificador, asks *pr);

/* Remove a(as) pergunta(s) pretendidas(s) e dá feedback  */
void removePerguntaIO(asks *pr);

void linha();

/* Guarda o resultado do concurso no ficheiro resultados.txt*/
void guardaResultado(char nome[50], char apelido[50], int acumulado);
