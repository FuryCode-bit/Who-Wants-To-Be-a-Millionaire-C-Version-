#include<stdio.h>
#include"funcionalidades.h"

int main()
{
    int formatoLeitura, gerirOuIniciar, gerirConcurso, escolha;
    char palavraProcurada[257];
    char *pos;

    asks p[N] = {}; 

    linha();
    printf("\t\t\t★  - QUEM QUER SER MILIONÁRIO - ★\n");
    linha();
    printf("• Em que formato gostaria que as perguntas fossem lidas?\n\n");
    printf("↪  1. TEXTO\n");
    printf("↪  2. BINÁRIO\n\n");
    printf("Opção -> ");
    do
    {
        if (scanf("%d", &formatoLeitura) != 1) 
        {
            limpaInput();
            printf(" ✘  Input inválido! Digite algo válido: ");
            continue;
        }

        switch (formatoLeitura)
        {
        case 1:
            leTXT(p, "db.txt");
            break;
        case 2:
            leBin(p, "db.bin");
            break;
        default:
            printf(" ✘  Opção inválida! Digite algo válido: ");
            break;
        }
    }while(formatoLeitura != 1 && formatoLeitura != 2);

    do
    {
        linha();
        printf("___________________________| ⇒  - MENU PRINCIPAL - ⇐  |_____________________________\n\n");
        printf("• Escolha uma das opções disponíveis: \n\n");
        printf("↪  1. GERIR CONCURSO\n");
        printf("↪  2. INICIAR CONCURSO\n\n");
        printf("↪  0. SAIR\n\n");
        printf("Opção -> ");
        while(scanf("%d", &gerirOuIniciar) != 1)
        {
            limpaInput();
            printf(" ✘  Input inválido! Digite algo válido: ");
        }
        while(gerirOuIniciar < 0 || gerirOuIniciar > 2)
        {
            limpaInput();
            printf(" ✘  Opção inválida! Digite algo válido: ");
            while(scanf("%d", &gerirOuIniciar) != 1)
            {
                limpaInput();
                printf(" ✘  Input inválido! Digite algo válido: ");
            }
        }
        linha();
        if(gerirOuIniciar == 1)
        {
            do
            {
                printf("___________________________| ⇒  - GERIR CONCURSO - ⇐  |_____________________________\n\n");
                printf("• Escolha uma das opções disponíveis: \n\n");
                printf("↪  1. LISTAR QUESTÕES\n");
                printf("↪  2. PROCURAR QUESTÕES\n");
                printf("↪  3. ADICIONAR QUESTÃO\n");
                printf("↪  4. ELIMINAR QUESTÃO\n");
                printf("↪  5. VOLTAR AO MENU PRINCIPAL\n\n");
                printf("Opção -> ");
                while(scanf("%d", &gerirConcurso) != 1)
                {
                    limpaInput();
                    printf(" ✘  Input inválido! Digite algo válido --> ");
                }
                while(gerirConcurso < 1 || gerirConcurso > 5)
                {
                    limpaInput();
                    printf(" ✘  Opção inválida! Digite algo válido --> ");
                    while(scanf("%d", &gerirConcurso) != 1)
                    {
                        limpaInput();
                        printf(" ✘  Input inválido! Digite algo válido --> ");
                    }
                }
                switch (gerirConcurso)
                {
                case 1:
                    do
                    {
                        linha();
                        printf("__________________| ⇒  - GERIR CONCURSO / LISTAR QUESTÕES - ⇐  |___________________\n\n");
                        limpaInput();
                        mostraArray(p, N);
                        gravaBin(p, "db.bin");
                        gravaTXT(p, "db.txt");
                        escolha = repetirAcao();
                    } while (escolha == 1);
                    break;
                case 2:
                    do
                    {
                        linha();
                        printf("__________________| ⇒  - GERIR CONCURSO / PROCURAR QUESTÕES - ⇐  |__________________\n\n");
                        limpaInput();
                        printf("• Escreva uma palavra / frase e será remetido para a(s) pergunta(s) que a(s) contêm.\n");
                        printf("🔎 -> ");
                        fgets(palavraProcurada, 100, stdin);
                        pos = strchr(palavraProcurada, '\n');
                        *pos = '\0';
                        printf("\n");
                        indicePergunta(palavraProcurada, p);
                        escolha = repetirAcao();
                    } while (escolha == 1);
                    break;
                case 3:
                    linha();
                    printf("_________________| ⇒  - GERIR CONCURSO / ADICIONAR QUESTÕES - ⇐  |__________________\n\n");
                    printf("• Nesta secção pode criar novas questões, adicionando-as ao programa.\n\n");
                    limpaInput();
                    adicionaPerguntaIO(p);
                    gravaBin(p, "db.bin");
                    gravaTXT(p, "db.txt");
                    break;
                case 4:
                    linha();
                    printf("__________________| ⇒  - GERIR CONCURSO / ELIMINAR QUESTÕES - ⇐  |__________________\n\n");
                    printf("❗ -> CASO O IDENTIFICADOR SE REPITA, SERÁ REMOVIDA A PERGUNTA CUJO MESMO APARECER\n");
                    printf("  PRIMEIRO NA LISTA (EM CASO DE DÚVIDA VERIFICAR OPÇÃO 1.LISTAR QUESTÕES).\n\n");
                    limpaInput();
                    removePerguntaIO(p);
                    gravaBin(p, "db.bin");
                    gravaTXT(p, "db.txt");
                default:
                    break;
                }
                if(gerirConcurso != 5)
                    linha();
            }while(gerirConcurso != 5);
        }
        if(gerirOuIniciar == 2)
        {
            // Aqui será colocado o código referente ao jogo em si.
            int asks[3], n = 0, perg = 0, acumulado = 0, patamarSeguranca = 0, perdeu = 0, fimJogo = 0;
            int certaPos, erradaumPos, erradadoisPos, nivelRecompensa, opcaoFim, escolha, ajuda;
            char nome[50], apelido[50], *nivel, letraPos, respch, resposta;
            int rondaFinal = 0, hcinq = 1, htroca = 1;
            int index[50], opcoes[4];

            /*Check name input, i think it is done;
            *Começou a dar problemas com a identificação da dificuldade das perguntas;
            *Sempre que um concurso termina, o nome do jogador e a quantia ganha s˜ao registados num ficheiro com o nome resultados.txt que mant´em a informa¸c˜ao de todos os
                concursos que decorreram e os resultados obtidos.*/

            printf("Digite o seu nome: ");  
            while(scanf("%s", &nome) > 40)
            {
                printf(" \n✘  Nome inválido! ");
                printf("Digite um nome válido --> ");  
                scanf("%s", &nome); 
            }

            printf("Digite o seu apelido: ");  

            while(scanf("%s", &apelido) > 40)
            {
                printf(" \n✘  Apelido inválido! ");
                printf("Digite um apelido válido --> ");  
                scanf("%s", &apelido);
            }

            printf("%d : %d\n", strlen(nome), strlen(apelido));

            //0: facil     1: medio    2: dificil
            while(fimJogo == 0)
            {
                for(int dificuldade = 0; dificuldade < 3 && (perdeu == 0 && fimJogo == 0); dificuldade++) // <-- em principio este for pode ir a vida, mas n custa testar.
                {
                switch(dificuldade)
                {
                    case 0: 
                        nivel= "facil";
                        break;

                    case 1: 
                        nivel= "medio";
                        break;

                    case 2: 
                        nivel= "dificil";
                        break;
                }

                if(dificuldade == 2)
                {
                    rondaFinal = 1;
                }

                printf("\nNome: %s %s\n", nome, apelido);

                for(int j = 0; j < 150; j++)
                    {   
                        if(strcmp(p[j].dificuldade, nivel) == 0)
                        {
                            printf("perguntas: %d - %s\n", j, p[j].dificuldade);
                            index[n] = j;
                            n++;
                        } 
                    }
                    printf("\nnº de perguntas nivel %s: %d\n", nivel, n);

                    if(strcmp(nivel, "facil") == 0)
                    {
                        nivelRecompensa = 200;
                    }
                    else if(strcmp(nivel, "medio") == 0)
                    {
                        nivelRecompensa = 1500;
                    }
                    else if(strcmp(nivel, "dificil") == 0)
                    {
                        nivelRecompensa = 5000;
                    }

                    n = n+1;

                do
                {
                    srand(time(0));

                    asks[0] = rand()%n;
                    asks[1] = rand()%n;
                    asks[2] = rand()%n;
                    asks[3] = rand()%n;

                } while(asks[0] == asks[1] || asks[0] == asks[2] || asks[1] == asks[2] || asks[0] == asks[3] || asks[0] == asks[3] || asks[1] == asks[3] || asks[2] == asks[3]);

                printf("\nIndice da pergunta: %d : %d : %d\n", asks[0], asks[1], asks[2]);
                printf("Indice no ficheiro: %d : %d : %d\n\n", index[asks[0]]+1, index[asks[1]]+1, index[asks[2]]+1);

                for(int perguntas = 0; perguntas < 3 && perdeu == 0 && fimJogo == 0; perguntas++)
                {
                    //falta check se a pergunta de indice x existe
                    do
                    {
                        certaPos = rand()%4;
                        erradaumPos = rand()%4;
                        erradadoisPos = rand()%4;

                    } while(certaPos == erradaumPos || certaPos == erradadoisPos || erradaumPos == erradadoisPos);

                    perg++;
                    printf("acumulado: %d", acumulado);
                    printf("\n------------------------------------------------------------------\n");
                    printf("\n\tPergunta nº%d\n\n", perg);
                    printf("----------------------------\n");
                    printf("\t   Nivel   Quantia\n");
                    printf("- Questão 1: Fácil - 100$\n");
                    printf("- Questão 2: Fácil - 300$\n");
                    printf("> Questão 3: Fácil - 500$\n");
                    printf("- Questão 4: Médio - 2000$\n");
                    printf("- Questão 5: Médio - 3500$\n");
                    printf("> Questão 6: Médio - 5000$\n");
                    printf("- Questão 7: Difícil - 10000$\n");
                    printf("- Questão 8: Difícil - 15000$\n");
                    printf("> Questão 9: Difícil - 20000$\n");
                    printf("----------------------------\n");

                    printf("%d\n------------------------------------------------------------------\n",index[asks[perguntas]]);
                    printf("\n");
                    printf("\n ---> %s: %s\n",p[index[asks[perguntas]]].identificador, p[index[asks[perguntas]]].questao);
                    printf("\n");

                    for(int pos = 0; pos < 4; pos++){
                        switch(pos)
                            {
                            case 0:
                                letraPos = 'A';
                                break;

                            case 1:
                                letraPos = 'B';
                                break;
                            
                            case 2:
                                letraPos = 'C';
                                break;

                            case 3:
                                letraPos = 'D';
                                break;
                            }

                        if(pos == certaPos)
                        {
                            printf("->%c - %s\n", letraPos, p[index[asks[perguntas]]].respostaCerta);
                            respch = tolower(letraPos);
                        }
                        else if(pos == erradaumPos)
                        {
                            printf("->%c - %s\n", letraPos, p[index[asks[perguntas]]].respostaErrada1);
                        }
                        else if(pos == erradadoisPos)
                        {
                            printf("->%c - %s\n", letraPos, p[index[asks[perguntas]]].respostaErrada2);
                        }
                        else
                        {
                            printf("->%c - %s\n", letraPos, p[index[asks[perguntas]]].respostaErrada3);
                        }
                    }
                    if(hcinq == 1 || htroca == 1)
                    {
                        printf("\t\t\t\tAjudas disponiveis:");
                        if(hcinq == 1)
                        {
                            printf("\t1: 50:50 - (%d)", hcinq);
                        }
                        if(htroca == 1)
                        {
                            printf("\t2: Troca - (%d)\n", htroca);
                        }
                    }
                printf("\nresposta: ");
                    //scanf("%c", &resposta);
                    //limpaInput();
                    //printf("resp: %c", resposta);
                    limpaInput();
                    while(scanf("%c", &resposta) != 1)
                    {
                        limpaInput();
                        printf(" \n✘  Opção inválida! Digite algo válido --> ");
                        scanf("%c", &resposta);
                    }

/*
                    //Check for invalid outputs

                    // Falta Checkar para outputs invalidos

                    while (resposta != 'a' && resposta != 'b' && resposta != 'c' && resposta != 'd');
                    */
                   resposta = tolower(resposta);
                   printf("%d\n", isdigit(resposta));

                    if(isalpha(resposta) > 0)
                    {
                        resposta = tolower(resposta);
                    }

                    if(isdigit(resposta))
                    {
                        resposta = resposta - 48;
                        //printf("%d\n", resposta);
                        while(resposta != 1 && resposta != 2)
                        {
                            limpaInput();
                            printf(" ✘  Input inválido! Digite algo válido --> ");
                            scanf("%d", &resposta);
                            printf("%d\n", resposta);
                        }
                    }

                    if(resposta == respch)
                    {
                        if(strcmp(nivel, "facil") == 0 && perguntas == 0)
                        {
                            acumulado = 100;
                        }
                        else
                        {
                            acumulado = acumulado + nivelRecompensa;
                        }
                        
                        printf("\nEstá certo!\n");
                    }
                    else if(resposta == 'x' || resposta == 'X')
                    {
                        printf("\n--------------------------------------------\n");
                        printf("Bem jogado %s %s, o jogo acabou!\n", nome, apelido);
                        guardaResultado(nome, apelido, acumulado);
                        fimJogo = 1;
                    }
                    else if(resposta == 1 || resposta == 2)
                    {
                        switch(resposta)
                        {
                            case 1:
                                hcinq = 0;
                                printf("%d\n------------------------------------------------------------------\n",index[asks[perguntas]]);
                                printf("\n");
                                printf("\n ---> %s: %s\n",p[index[asks[perguntas]]].identificador, p[index[asks[perguntas]]].questao);
                                printf("\n");

                                for(int pos = 0; pos < 4; pos++){
                                    switch(pos)
                                        {
                                        case 0:
                                            letraPos = 'A';
                                            break;

                                        case 1:
                                            letraPos = 'B';
                                            break;
                                        
                                        case 2:
                                            letraPos = 'C';
                                            break;

                                        case 3:
                                            letraPos = 'D';
                                            break;
                                        }

                                    if(pos == certaPos)
                                    {
                                        printf("->%c - %s\n", letraPos, p[index[asks[perguntas]]].respostaCerta);
                                        respch = tolower(letraPos);
                                    }
                                    else if(pos == erradaumPos)
                                    {
                                        printf("->%c - %s\n", letraPos, p[index[asks[perguntas]]].respostaErrada1);
                                    }
                                    else if(pos == erradadoisPos)
                                    {
                                        printf("->%c -\n", letraPos);
                                    }
                                    else 
                                    {
                                        printf("->%c -\n", letraPos);
                                    }
                                }
                                printf("\nresposta: ");
                                //scanf("%c", &resposta);
                                //limpaInput();
                                //printf("resp: %c", resposta);
                                limpaInput();
                                scanf("%c", &resposta);
                                resposta = tolower(resposta);

                                if(resposta == respch)
                                {
                                    if(strcmp(nivel, "facil") == 0 && perguntas == 0)
                                    {
                                        acumulado = 100;
                                    }
                                    else
                                    {
                                        acumulado = acumulado + nivelRecompensa;
                                    }
                                    
                                    printf("\nEstá certo!\n");
                                }
                                else
                                {
                                    printf("\nLamentamos mas está errado\n");

                                    if(patamarSeguranca != 0)
                                    {
                                        acumulado = patamarSeguranca;
                                    }
                                    else
                                    {
                                        acumulado = 0;
                                    }

                                    printf("Acabou o jogo com um acumulado de %d$\n", acumulado);
                                    guardaResultado(nome, apelido, acumulado);
                                    perdeu = 1;
                                    
                                }
                                
                                printf("\n------------------------------------------------------------------\n");
                                break;

                            case 2:
                                htroca = 0;
                                printf("%d\n------------------------------------------------------------------\n",index[asks[perguntas]]);
                                printf("\n");
                                printf("\n ---> %s: %s\n",p[index[asks[3]]].identificador, p[index[asks[3]]].questao);
                                printf("\n");

                                for(int pos = 0; pos < 4; pos++){
                                    switch(pos)
                                        {
                                        case 0:
                                            letraPos = 'A';
                                            break;

                                        case 1:
                                            letraPos = 'B';
                                            break;
                                        
                                        case 2:
                                            letraPos = 'C';
                                            break;

                                        case 3:
                                            letraPos = 'D';
                                            break;
                                        }

                                    if(pos == certaPos)
                                    {
                                        printf("->%c - %s\n", letraPos, p[index[asks[3]]].respostaCerta);
                                        respch = tolower(letraPos);
                                    }
                                    else if(pos == erradaumPos)
                                    {
                                        printf("->%c - %s\n", letraPos, p[index[asks[3]]].respostaErrada1);
                                    }
                                    else if(pos == erradadoisPos)
                                    {
                                        printf("->%c - %s\n", letraPos, p[index[asks[3]]].respostaErrada2);
                                    }
                                    else
                                    {
                                        printf("->%c - %s\n", letraPos, p[index[asks[3]]].respostaErrada3);
                                    }
                                }

                                printf("\nresposta: ");
                                //scanf("%c", &resposta);
                                //limpaInput();
                                //printf("resp: %c", resposta);
                                limpaInput();
                                scanf("%c", &resposta);
                                resposta = tolower(resposta);

                                if(resposta == respch)
                                {
                                    if(strcmp(nivel, "facil") == 0 && perguntas == 0)
                                    {
                                        acumulado = 100;
                                    }
                                    else
                                    {
                                        acumulado = acumulado + nivelRecompensa;
                                    }
                                    
                                    printf("\nEstá certo!\n");
                                }
                                else
                                {
                                    printf("\nLamentamos mas está errado\n");

                                    if(patamarSeguranca != 0)
                                    {
                                        acumulado = patamarSeguranca;
                                    }
                                    else
                                    {
                                        acumulado = 0;
                                    }

                                    printf("Acabou o jogo com um acumulado de %d$\n", acumulado);
                                    guardaResultado(nome, apelido, acumulado);
                                    perdeu = 1;
                                    
                                }
                                
                                printf("\n------------------------------------------------------------------\n");
                                break;
                        }
                    } 
                    else
                    {
                        printf("\nLamentamos mas está errado\n");

                        if(patamarSeguranca != 0)
                        {
                            acumulado = patamarSeguranca;
                        }
                        else
                        {
                            acumulado = 0;
                        }

                        printf("Acabou o jogo com um acumulado de %d$\n", acumulado);
                        guardaResultado(nome, apelido, acumulado);
                        perdeu = 1;
                        
                    }
                    
                    printf("\n------------------------------------------------------------------\n"); 

                                  

                    if(perguntas == 2)
                    {
                        if(rondaFinal == 0 && perdeu == 0 && fimJogo == 0)
                        {
                            printf("--------------------------------------------\n");
                            printf("\nParabéns chegou a um patamar de segurança dos %d$!\n", acumulado);
                            patamarSeguranca = acumulado;
                            printf("O que pretende fazer agora?\n");
                            printf("- Continuar a jogar (1)\n");
                            printf("- Sair com o valor acumulado (0)\n");
                            printf("\n");
                            printf("Escolha: ");

                            while(scanf("%d", &escolha) != 1 && scanf("%d", &escolha) != 0 )
                            {

                                printf(" ✘  Input inválido! Digite algo válido --> ");
                            }

                            if(escolha == 0)
                            {
                                printf("\n--------------------------------------------\n");
                                printf("Bem jogado %s %s, o jogo acabou!\n", nome, apelido);
                                guardaResultado(nome, apelido, acumulado);
                                fimJogo = 1;
                            }
                            else if(escolha == 1)
                            {
                                printf("\n--------------------------------------------\n");
                                printf("Bem jogado, continuaremos então o jogo!\n");
                                printf("\n--------------------------------------------\n");
                            }
                        }
                        else if(perdeu == 0 && dificuldade == 2)
                        {
                            printf("\n--------------------------------------------\n");
                            printf("\n\t Parabens %s %s você ganhou o jogo! \t\n", nome, apelido);
                            guardaResultado(nome, apelido, acumulado);
                        }
                        
                    }
                }
                n = 0;
            }
            }

            printf("\n--------------------------------------------\n");
            printf("\n %s %s acabou o jogo com a quantia %d$! o que deseja fazer agora? \n", nome, apelido, acumulado);
            printf("- opção 1: Ir para o menu principal.\n");
            printf("- opção 2: Terminar o programa.\n");
            printf("\nOpçao: ");

            while(scanf("%d", &opcaoFim) != 1 && scanf("%d", &opcaoFim) != 2)
                {
                    printf(" ✘  Input inválido! Digite algo válido --> ");
                }

            if(opcaoFim == 1)
            {
                break;
            }
            else if(opcaoFim == 2)
            {
                fimJogo = 1;
                gerirOuIniciar = 0;
            }

            printf("\n--------------------------------------------\n");
        }
    }while(gerirOuIniciar != 0);
    printf("*\t\t\t     Trabalho elaborado por:\t\t\t\t   *\n");
    printf("\t        Guilherme Teixeira (45667) e Marco Bernardes (45703)\n");
    printf("\t     ENGENHARIA INFORMÁTICA - PROGRAMAÇÃO - 1ºANO - 2020/2021\n");
    linha();
    return 0;
}