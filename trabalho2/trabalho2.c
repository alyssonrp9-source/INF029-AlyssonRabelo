#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

// Estrutura auxiliar para cada posição do vetor principal
typedef struct {
    int *vetor;
    int tamanho;   // tamanho total alocado
    int qtd;       // quantidade atual de elementos
} EstruturaAuxiliar;

// Vetor principal de ponteiros para estruturas auxiliares
EstruturaAuxiliar *vetorPrincipal[TAM];

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    // Verificar se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verificar se já existe estrutura auxiliar na posição
    if (vetorPrincipal[posicao - 1] != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    // Verificar se o tamanho é válido
    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }

    // Alocar a estrutura auxiliar
    EstruturaAuxiliar *nova = (EstruturaAuxiliar*) malloc(sizeof(EstruturaAuxiliar));
    if (nova == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    // Alocar o vetor de inteiros
    nova->vetor = (int*) malloc(tamanho * sizeof(int));
    if (nova->vetor == NULL) {
        free(nova);
        return SEM_ESPACO_DE_MEMORIA;
    }

    // Inicializar a estrutura
    nova->tamanho = tamanho;
    nova->qtd = 0;

    // Atribuir ao vetor principal
    vetorPrincipal[posicao - 1] = nova;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    // Verificar se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verificar se existe estrutura auxiliar
    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];
    if (estrutura == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    // Verificar se há espaço
    if (estrutura->qtd >= estrutura->tamanho) {
        return SEM_ESPACO;
    }

    // Inserir o valor
    estrutura->vetor[estrutura->qtd] = valor;
    estrutura->qtd++;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    // Verificar se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verificar se existe estrutura auxiliar
    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];
    if (estrutura == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    // Verificar se a estrutura não está vazia
    if (estrutura->qtd == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    // Excluir (decrementar a quantidade)
    estrutura->qtd--;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    // Verificar se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verificar se existe estrutura auxiliar
    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];
    if (estrutura == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    // Verificar se a estrutura não está vazia
    if (estrutura->qtd == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    // Procurar o número
    int encontrou = 0;
    for (int i = 0; i < estrutura->qtd; i++) {
        if (estrutura->vetor[i] == valor) {
            encontrou = 1;
            // Deslocar os elementos para frente
            for (int j = i; j < estrutura->qtd - 1; j++) {
                estrutura->vetor[j] = estrutura->vetor[j + 1];
            }
            estrutura->qtd--;
            break;
        }
    }

    if (!encontrou) {
        return NUMERO_INEXISTENTE;
    }

    return SUCESSO;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    return SUCESSO;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    // Verificar se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verificar se existe estrutura auxiliar
    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];
    if (estrutura == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    // Copiar os elementos
    for (int i = 0; i < estrutura->qtd; i++) {
        vetorAux[i] = estrutura->vetor[i];
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/

// Função auxiliar para ordenar um vetor
void ordenarVetor(int vetor[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    // Primeiro, obter os dados sem ordenação
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno != SUCESSO) {
        return retorno;
    }

    // Ordenar o vetorAux
    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];
    ordenarVetor(vetorAux, estrutura->qtd);

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int total = 0;
    int vazias = 1; // assume que todas estão vazias

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            EstruturaAuxiliar *estrutura = vetorPrincipal[i];
            if (estrutura->qtd > 0) {
                vazias = 0;
                for (int j = 0; j < estrutura->qtd; j++) {
                    vetorAux[total] = estrutura->vetor[j];
                    total++;
                }
            }
        }
    }

    if (vazias) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (retorno != SUCESSO) {
        return retorno;
    }

    // Contar o total de elementos
    int total = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            total += vetorPrincipal[i]->qtd;
        }
    }

    // Ordenar o vetorAux
    ordenarVetor(vetorAux, total);

    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    // Verificar se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verificar se existe estrutura auxiliar
    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];
    if (estrutura == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    // Calcular o novo tamanho total
    int novoTamanhoTotal = estrutura->tamanho + novoTamanho;

    // Verificar se o novo tamanho total é válido (>=1)
    if (novoTamanhoTotal < 1) {
        return NOVO_TAMANHO_INVALIDO;
    }

    // Realocar o vetor
    int *novoVetor = (int*) realloc(estrutura->vetor, novoTamanhoTotal * sizeof(int));
    if (novoVetor == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    // Atualizar a estrutura
    estrutura->vetor = novoVetor;
    estrutura->tamanho = novoTamanhoTotal;

    // Se a quantidade atual for maior que o novo tamanho, ajustar a quantidade
    if (estrutura->qtd > novoTamanhoTotal) {
        estrutura->qtd = novoTamanhoTotal;
    }

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    // Verificar se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verificar se existe estrutura auxiliar
    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];
    if (estrutura == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    // Retornar a quantidade
    return estrutura->qtd;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    // Verificar se há elementos em alguma estrutura
    int totalElementos = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            totalElementos += vetorPrincipal[i]->qtd;
        }
    }

    if (totalElementos == 0) {
        return NULL;
    }

    // Criar o nó cabeçote
    No *cabecote = (No*) malloc(sizeof(No));
    if (cabecote == NULL) {
        return NULL;
    }
    cabecote->prox = NULL;

    No *ultimo = cabecote;

    // Percorrer todas as estruturas e adicionar os elementos na lista
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            EstruturaAuxiliar *estrutura = vetorPrincipal[i];
            for (int j = 0; j < estrutura->qtd; j++) {
                No *novoNo = (No*) malloc(sizeof(No));
                if (novoNo == NULL) {
                    // Em caso de erro, liberar a lista já criada
                    No *atual = cabecote->prox;
                    while (atual != NULL) {
                        No *proximo = atual->prox;
                        free(atual);
                        atual = proximo;
                    }
                    free(cabecote);
                    return NULL;
                }
                novoNo->conteudo = estrutura->vetor[j];
                novoNo->prox = NULL;
                ultimo->prox = novoNo;
                ultimo = novoNo;
            }
        }
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    if (inicio == NULL) {
        return;
    }

    No *atual = inicio->prox;
    int i = 0;
    while (atual != NULL) {
        vetorAux[i] = atual->conteudo;
        atual = atual->prox;
        i++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    if (inicio == NULL || *inicio == NULL) {
        return;
    }

    No *atual = *inicio;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/
void inicializar()
{
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i] = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/
void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            free(vetorPrincipal[i]->vetor);
            free(vetorPrincipal[i]);
            vetorPrincipal[i] = NULL;
        }
    }
}

/*
Função exemplo para o cabeçalho (não utilizada nas operações principais)
*/
void dobrar(int *x) {
    if (x != NULL) {
        *x = *x * 2;
    }
}