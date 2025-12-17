#ifndef TRABALHO2_H
#define TRABALHO2_H
#define TAM 100
// Definição das constantes de retorno
#define SUCESSO 0
#define SEM_ESPACO 1
#define SEM_ESTRUTURA_AUXILIAR 2
#define POSICAO_INVALIDA 3
#define JA_TEM_ESTRUTURA_AUXILIAR 4
#define SEM_ESPACO_DE_MEMORIA 5
#define TAMANHO_INVALIDO 6
#define ESTRUTURA_AUXILIAR_VAZIA 7
#define NUMERO_INEXISTENTE 8
#define TODAS_ESTRUTURAS_AUXILIARES_VAZIAS 9
#define NOVO_TAMANHO_INVALIDO 10

// Estrutura para lista encadeada
typedef struct no {
    int valor;
    struct no *prox;
} No;
// Definição da estrutura auxiliar
typedef struct {
    int *vetorAuxiliar;
    int tamanho;
    int quantidadeElementos;
} EstruturaAuxiliar;

// Declaração das funções
int criarEstruturaAuxiliar(int posicao, int tamanho);

int inserirNumeroEmEstrutura(int posicao, int valor);

int excluirNumeroDoFinaldaEstrutura(int posicao);
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor);

int ehPosicaoValida(int posicao);

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]);
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]);
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho);
int getQuantidadeElementosEstruturaAuxiliar(int posicao);

No* montarListaEncadeadaComCabecote();
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]);
void destruirListaEncadeadaComCabecote(No **inicio);

void inicializar();
void finalizar();

#endif
