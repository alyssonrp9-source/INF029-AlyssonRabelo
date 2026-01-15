#ifndef TRABALHO2_ESTRUTURAVETORES_H
#define TRABALHO2_ESTRUTURAVETORES_H

// enumeracoes (enum) ajudam a deixar o codigo mais legivel, possibilitando que voce de significado
// as suas constantes, para mais informacoes https://en.cppreference.com/w/c/language/enum
// as constantes do enum em sua inicialização vao representar o numero resultante da soma do valor da
// constante anterior mais 1, caso nao haja valor algum na primeira constante ela vai ser inicializada com 0
enum { TODAS_ESTRUTURAS_AUXILIARES_VAZIAS = -11, NOVO_TAMANHO_INVALIDO, NUMERO_INEXISTENTE,
       ESTRUTURA_AUXILIAR_VAZIA, TAMANHO_INVALIDO, SEM_ESPACO_DE_MEMORIA, POSICAO_INVALIDA,
       JA_TEM_ESTRUTURA_AUXILIAR, SEM_ESTRUTURA_AUXILIAR, SEM_ESPACO, SUCESSO };

typedef struct reg {
    int conteudo;
    struct reg *prox;
} No;

int criarEstruturaAuxiliar(int posicao, int tamanho);
int inserirNumeroEmEstrutura(int posicao, int valor);
int excluirNumeroDoFinaldaEstrutura(int posicao);
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor);
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]);
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]);
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho);
int getQuantidadeElementosEstruturaAuxiliar(int posicao);
No *montarListaEncadeadaComCabecote();
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]);
void destruirListaEncadeadaComCabecote(No **inicio);

void inicializar();
void finalizar();
void dobrar(int *x);

#endif  // TRABALHO2_ESTRUTURAVETORES_H



/*         MEU CODIGO DE OPCAO 1 E 2
#ifndef TRABALHO2_H
#define TRABALHO2_H
#define TAM 10
// Definicao das constantes de retorno
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

// Definicao da estrutura auxiliar
typedef struct {
    int *vetorAuxiliar;
    int tamanho;
    int quantidadeElementos;
} EstruturaAuxiliar;

// Declaracao das funcoes
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
*/