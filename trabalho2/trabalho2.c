#include <stdio.h>
#include <stdlib.h>
#include "trabalho2.h"

// Definição da estrutura auxiliar (somente aqui no .c)


// Vetor global principal
EstruturaAuxiliar *vetorPrincipal[TAM];

// Função auxiliar para ordenação (bubble sort)
void ordenarVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao' com tamanho 'tamanho'
*/
int criarEstruturaAuxiliar(int posicao, int tamanho) {
    // Validação da posição (1 a 10 conforme a Figura 1)
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }

    if (vetorPrincipal[posicao - 1] != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    // Alocação dinâmica para a estrutura de controle
    EstruturaAuxiliar *novaEstrutura = malloc(sizeof(EstruturaAuxiliar));
    if (novaEstrutura == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    // Alocação dinâmica para o vetor que guardará os números
    novaEstrutura->vetorAuxiliar = malloc(tamanho * sizeof(int));
    if (novaEstrutura->vetorAuxiliar == NULL) {
        free(novaEstrutura);
        return SEM_ESPACO_DE_MEMORIA;
    }

    novaEstrutura->tamanho = tamanho;
    novaEstrutura->quantidadeElementos = 0;
    vetorPrincipal[posicao - 1] = novaEstrutura;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
    // Verifica se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verifica se existe estrutura auxiliar
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];

    // Verifica se tem espaço
    if (estrutura->quantidadeElementos >= estrutura->tamanho) {
        return SEM_ESPACO;
    }

    // Insere o valor
    estrutura->vetorAuxiliar[estrutura->quantidadeElementos] = valor;
    estrutura->quantidadeElementos++;

    return SUCESSO;
}

/*
Objetivo: excluir o número 'valor' da estrutura auxiliar no final da estrutura
*/
int excluirNumeroDoFinaldaEstrutura(int posicao) {
    // Verifica se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verifica se existe estrutura auxiliar
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];

    // Verifica se a estrutura está vazia
    if (estrutura->quantidadeElementos == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    // Exclusão lógica (apenas decrementa a quantidade)
    estrutura->quantidadeElementos--;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'
*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    // Verifica se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verifica se existe estrutura auxiliar
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];

    // Verifica se a estrutura está vazia
    if (estrutura->quantidadeElementos == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    // Procura o valor na estrutura
    int encontrado = 0;
    for (int i = 0; i < estrutura->quantidadeElementos; i++) {
        if (estrutura->vetorAuxiliar[i] == valor) {
            encontrado = 1;
            // Move os elementos posteriores para preencher o espaço
            for (int j = i; j < estrutura->quantidadeElementos - 1; j++) {
                estrutura->vetorAuxiliar[j] = estrutura->vetorAuxiliar[j + 1];
            }
            estrutura->quantidadeElementos--;
            break;
        }
    }

    if (!encontrado) {
        return NUMERO_INEXISTENTE;
    }

    return SUCESSO;
}

/*
Objetivo: verificar se posição é válida
*/
int ehPosicaoValida(int posicao) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    return SUCESSO;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao'
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    // Verifica se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verifica se existe estrutura auxiliar
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];

    // Copia os dados para o vetor auxiliar
    for (int i = 0; i < estrutura->quantidadeElementos; i++) {
        vetorAux[i] = estrutura->vetorAuxiliar[i];
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    // Primeiro obtém os dados normalmente
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno != SUCESSO) {
        return retorno;
    }

    // Obtém a quantidade de elementos
    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];
    
    // Ordena o vetor
    ordenarVetor(vetorAux, estrutura->quantidadeElementos);

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int totalElementos = 0;
    int todasVazias = 1;

    // Percorre todas as estruturas
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            EstruturaAuxiliar *estrutura = vetorPrincipal[i];
            if (estrutura->quantidadeElementos > 0) {
                todasVazias = 0;
                // Copia os elementos
                for (int j = 0; j < estrutura->quantidadeElementos; j++) {
                    vetorAux[totalElementos] = estrutura->vetorAuxiliar[j];
                    totalElementos++;
                }
            }
        }
    }

    if (todasVazias) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    // Primeiro obtém todos os dados
    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (retorno != SUCESSO) {
        return retorno;
    }

    // Conta o total de elementos
    int totalElementos = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            totalElementos += vetorPrincipal[i]->quantidadeElementos;
        }
    }

    // Ordena todos os elementos
    ordenarVetor(vetorAux, totalElementos);

    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    // Verifica se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verifica se existe estrutura auxiliar
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    // Verifica se o novo tamanho é válido
    if (novoTamanho < 0) {
        return NOVO_TAMANHO_INVALIDO;
    }

    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];
    int novoTamanhoTotal = estrutura->tamanho + novoTamanho;

    if (novoTamanhoTotal < 1) {
        return NOVO_TAMANHO_INVALIDO;
    }

    // Realoca o vetor auxiliar
    int *novoVetor = realloc(estrutura->vetorAuxiliar, novoTamanhoTotal * sizeof(int));
    if (novoVetor == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    // Atualiza a estrutura
    estrutura->vetorAuxiliar = novoVetor;
    estrutura->tamanho = novoTamanhoTotal;
    
    // Se o novo tamanho for menor que a quantidade atual, ajusta a quantidade
    if (estrutura->quantidadeElementos > novoTamanhoTotal) {
        estrutura->quantidadeElementos = novoTamanhoTotal;
    }

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    // Verifica se a posição é válida
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    // Verifica se existe estrutura auxiliar
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *estrutura = vetorPrincipal[posicao - 1];

    // Verifica se a estrutura está vazia
    if (estrutura->quantidadeElementos == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    return estrutura->quantidadeElementos;
}

/*
Objetivo: montar lista encadeada com cabeçote
*/
No* montarListaEncadeadaComCabecote() {
    // Verifica se há elementos em alguma estrutura
    int temElementos = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL && vetorPrincipal[i]->quantidadeElementos > 0) {
            temElementos = 1;
            break;
        }
    }

    if (!temElementos) {
        return NULL;
    }

    // Cria o nó cabeçote
    No *cabecote = malloc(sizeof(No));
    if (cabecote == NULL) {
        return NULL;
    }
    cabecote->valor = 0; // Valor qualquer para o cabeçote
    cabecote->prox = NULL;

    No *ultimo = cabecote;

    // Percorre todas as estruturas
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            EstruturaAuxiliar *estrutura = vetorPrincipal[i];
            
            // Adiciona cada elemento na lista
            for (int j = 0; j < estrutura->quantidadeElementos; j++) {
                No *novoNo = malloc(sizeof(No));
                if (novoNo == NULL) {
                    // Em caso de erro, libera a lista inteira
                    destruirListaEncadeadaComCabecote(&cabecote);
                    return NULL;
                }
                
                novoNo->valor = estrutura->vetorAuxiliar[j];
                novoNo->prox = NULL;
                ultimo->prox = novoNo;
                ultimo = novoNo;
            }
        }
    }

    return cabecote;
}

/*
Objetivo: retorna os dados da lista encadeada
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    if (inicio == NULL) {
        return;
    }

    No *atual = inicio->prox;
    int i = 0;
    
    while (atual != NULL) {
        vetorAux[i] = atual->valor;
        atual = atual->prox;
        i++;
    }
}

/*
Objetivo: destruir a lista encadeada
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
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
Objetivo: inicializar o programa
*/
void inicializar() {
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i] = NULL;
    }
}

/*
Objetivo: finalizar o programa
*/
void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            free(vetorPrincipal[i]->vetorAuxiliar);
            free(vetorPrincipal[i]);
            vetorPrincipal[i] = NULL;
        }
    }
}
