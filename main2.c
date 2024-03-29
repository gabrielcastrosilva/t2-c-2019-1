#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Node
{
    int valor;
    char let;
    struct Node* esq;
    struct Node* dir;
};

typedef struct Node NODO;

// prototipos
void inserir(NODO** arv, int val, char c);
int pesquisar(NODO* arv, char caracter, char letras[]);

//variaveis globais
int freqs[256];
NODO* listaArvores;


// código

void inserir(NODO** arv, int val, char c) {
    if ( *arv == NULL ) {
        NODO* novo;
        novo = malloc(sizeof(NODO));
        novo->valor = val;   //(*novo).valor = val;
        novo->let = c;
        novo->esq = NULL;
        novo->dir = NULL;

        *arv = novo;
    } else {
        //if ( val < (**arv)valor)
        if ( val < (*arv)->valor)
           //inserir(&((**arv).esq),val);
           inserir(&((*arv)->esq), val, c);
        else
           inserir(& ((*arv)->dir), val, c);
    }
}




void bubbleSort(NODO* vet[], int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (vet[j]->valor < vet[i]->valor)
            {
                NODO* aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }
}





void padding ( char ch, int n )
{
    int i;

    for ( i = 0; i < n; i++ )
        putchar ( ch );
}


void printree( NODO* root, int level )
{
    int i;

    if(root == NULL)
    {
        padding ('\t', level);
        puts ("~");
    }
    else
    {
        // Vai para a direita
        printree(root->dir, level + 1 );
        padding('\t', level );
        printf("%c:%d\n", root->let, root->valor);
        // Vai para a esquerda
        printree(root->esq, level + 1 );

    }
}





int pesquisar(NODO* arv, char character, char c[])
{
    if(arv == NULL)
    {
        return 0;
    }
    if(arv->let == character)
    {
        return 1;
    }
    int lefSearch = pesquisar(arv->esq, character, c);
    if(lefSearch == 1)
    {
        strcat(c, "0");
        return 1;
    }
    int buscaD = pesquisar(arv->dir, character, c);
    if(buscaD == 1)
    {
        strcat(c, "1");
        return 1;
    }
    return 0;

}




int main()
{
    /*Leitura de Arquivo*/

    listaArvores = malloc(sizeof(NODO)*256);


    FILE* arq = fopen("teste.txt", "r");
    if(arq == NULL)
    {
        printf("Erro! Arquivo nao encontrado!\n");
        exit(EXIT_FAILURE);
    }


    char c;
    int freqs[256] = {0};
    int count = 0;


    while ((c = fgetc(arq)) != EOF)
    {
        freqs[c]++;

        if(freqs[c] == 1)
        {

            count++;
        }
    }


    fclose(arq); //Fecha o arquivo


    int tamArvores = 0;
    NODO* listaArvores[] = {NULL};


    for(int i=0; i<256; i++)
    {
        if (freqs[i]>0)
        {
            inserir(&listaArvores[tamArvores], freqs[i], i);
            tamArvores++;
            printf("freq(%c): %d\n", i, freqs[i]);

        }
    }
///////////////////////////////////////////////////////////////////////
//Prints dos elementos nao ordenados e ordenados
    printf("lista arvores nao ordenado...\n");
    for(int i=0; i<tamArvores; i++)
    {
        printf("(%c:%d) ", listaArvores[i]->let, listaArvores[i]->valor);
    }
    printf("size: %d\n", tamArvores);

    bubbleSort(listaArvores,tamArvores);

    printf("\nOrdenado...\n");
    for(int i=0; i<tamArvores; i++)
    {
        printf("(%c:%d)", listaArvores[i]->let, listaArvores[i]->valor);
    }
    printf("\n");
///////////////////////////////////////////////////////////////////////////


    char listaArvoresOLD[tamArvores];
    for(int i=0; i<tamArvores; i++) //Clone da arvore atual antes das operacoes realizadas
    {
        listaArvoresOLD[i] = listaArvores[i]->let;
    }



    for(int i = tamArvores-1  ; i> 0  ; i--)   //Arvore e montada
    {
        NODO* t = NULL;
        inserir(&t, listaArvores[i]->valor + listaArvores[i-1]->valor, 'Z');
        t->esq = listaArvores[i];
        t->dir = listaArvores[i-1];
        listaArvores[i-1] = t;
        bubbleSort(listaArvores, i);
    }
    printree(listaArvores[0],0);
//////////////////////////////////////////////////////////////////////////////////


    FILE* writtenArq = fopen("tabela.piz", "w"); //Arquivo de escrita
    if(writtenArq == NULL)
    {
        printf("Impossível criar arq!\n");
        perror("Erro");
        exit(EXIT_FAILURE);
    }

    FILE* codificacaoArq = fopen("resultados.piz", "w");


    for(int i = 0; i < tamArvores; i++) //Escreve os caracteres e seus respectivos binarios
    {
        char ssss[] = {0};
        pesquisar(*listaArvores,listaArvoresOLD[i], ssss);
        fprintf(codificacaoArq,"Caracter: %c\tBinario: %s\n", listaArvoresOLD[i],strrev(ssss));
    }
    /*char z[] = {0};
    pesquisar(*listaArvores,'m', z);
    printf("\n%c\n",strrev(z));*/



    FILE* arq2 = fopen("teste.txt", "r");



    while ((c = fgetc(arq2)) != EOF)  //Escreve a mensagem codificada
    {
        char caract[] = {0};
        pesquisar(*listaArvores,c, caract);
        fprintf(arq, "%s", strrev(caract));


    }


    fclose(arq);
    fclose(arq2);
    fclose(codificacaoArq);
    fclose(writtenArq);
    printf("\nDados gravados em resultados.piz\n");
    printf("\nDados gravados em tabela.piz\n");

    return 0;
}



