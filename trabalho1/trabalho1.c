// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Alysson Rabelo Pereira
//  email: alyssonrp9@gmail.com
//  Matrícula: 20251160003
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <ctype.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */

int q1(char data[]){

  DataQuebrada dq = quebraData(data);
  if (dq.valido == 0){
    return 0;
  }

  int dia = dq.iDia;
  int mes = dq.iMes;
  int ano = dq.iAno;

  // validação do mês

  if(mes < 1 || mes > 12){
    return 0;
  }

  //Determinar dias no mês
  int diasNoMes;
  switch(mes){
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      diasNoMes = 31;
      break;
    case 4: case 6: case 9: case 11:
      diasNoMes = 30;
      break;
    case 2:
      //verificar se é ano bissexto
      if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
        diasNoMes = 29;
      }else{
        diasNoMes = 28;
      }
      break;
    default:
      return 0; // mês inválido
  }

  // validação do dia
  if(dia < 1 || dia > diasNoMes){
    return 0;
  }

  return 1; // data válida

}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    DiasMesesAnos dma;

    //Valida as datas usando a Q1

    if(q1(datainicial) == 0){
      dma.retorno = 2; // datainicial inválida
      return dma;
    }

    if(q1(datafinal) == 0){
      dma.retorno = 3; // datafinal inválida
      return dma;
    }
    
    //Converte as strings para estruturas DataQuebrada
    DataQuebrada dq1 = quebraData(datainicial);
    DataQuebrada dq2 = quebraData(datafinal);

    //Verifica se data Inicial é maior que data final
    if(dq1.iAno > dq2.iAno || 
       (dq1.iAno == dq2.iAno && dq1.iMes > dq2.iMes) || 
       (dq1.iAno == dq2.iAno && dq1.iMes == dq2.iMes && dq1.iDia > dq2.iDia)){
      dma.retorno = 4; // datainicial > datafinal
      return dma;
    }

    // Cálculo da diferença
    int dias = dq2.iDia - dq1.iDia;
    int meses = dq2.iMes - dq1.iMes;
    int anos = dq2.iAno - dq1.iAno;

    // Ajuste para dias negativos
    if (dias < 0) {
        // Pega o último dia do mês anterior
        int ultimoDiaMesAnterior;
        if (dq2.iMes == 1) {
            ultimoDiaMesAnterior = 31; // Dezembro tem 31 dias
        } else {
            // Precisa verificar fevereiro e anos bissextos
            DataQuebrada temp = quebraData("01/01/2000"); // data dummy
            // Implementação simplificada - na prática precisa calcular corretamente
            int mesAnterior = dq2.iMes - 1;
            switch (mesAnterior) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    ultimoDiaMesAnterior = 31;
                    break;
                case 4: case 6: case 9: case 11:
                    ultimoDiaMesAnterior = 30;
                    break;
                case 2:
                    if ((dq2.iAno % 4 == 0 && dq2.iAno % 100 != 0) || (dq2.iAno % 400 == 0))
                        ultimoDiaMesAnterior = 29;
                    else
                        ultimoDiaMesAnterior = 28;
                    break;
                default:
                    ultimoDiaMesAnterior = 30;
            }
        }
        dias += ultimoDiaMesAnterior;
        meses--;
    }

    // Ajuste para meses negativos
    if (meses < 0) {
        meses += 12;
        anos--;
    }

    dma.qtdDias = dias;
    dma.qtdMeses = meses;
    dma.qtdAnos = anos;
    dma.retorno = 1;

    return dma;
}








/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */

 int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    int i = 0;

    // Verifica se o texto é válido
    if (texto == NULL) {
        return 0;
    }

    if (isCaseSensitive == 1) {
        // Pesquisa Case Sensitive (diferença entre maiúsculas e minúsculas)
        while (texto[i] != '\0') {
            if (texto[i] == c) {
                qtdOcorrencias++;
            }
            i++;
        }
    } else {
        // Pesquisa NÃO Case Sensitive (ignora maiúsculas/minúsculas)
        char c_lower = tolower(c);
        while (texto[i] != '\0') {
          if (tolower(texto[i]) == c_lower) {
            qtdOcorrencias++;
          }
          i++;
        }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int i = 0, j = 0, k = 0;
    int inicio = -1;
    int tamBusca = 0;

    // Verifica se as strings são válidas
    if (strTexto == NULL || strBusca == NULL) {
        return 0;
    }

    // Calcula o tamanho da string de busca
    while (strBusca[tamBusca] != '\0') {
        tamBusca++;
    }

    if (tamBusca == 0) {
        return 0;
    }

    // Percorre o texto
    while (strTexto[i] != '\0') {
        // Verifica se a substring coincide
        j = 0;
        while (strBusca[j] != '\0' && strTexto[i + j] == strBusca[j]) {
            j++;
        }

        // Se encontrou a palavra toda
        if (j == tamBusca) {
            inicio = i + 1; // Posição inicial (começa em 1)
            int fim = inicio + tamBusca - 1; // Posição final

            // Armazena no vetor de posições
            posicoes[k] = inicio;
            posicoes[k + 1] = fim;
            k += 2;
            qtdOcorrencias++;

            // Pula para o próximo caractere após a palavra encontrada
            i += j - 1;
        }
        i++;
    }

    // Preenche o restante do vetor com -1, se necessário
    while (k < 30) {
        posicoes[k] = -1;
        k++;
    }

    return qtdOcorrencias;
}
/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int invertido = 0;
    int resto = 0;

    // Caso especial para 0
    if (num == 0) {
        return 0;
    }

    // Lida com números negativos? 
    // Pelo teste, parece que só positivos, mas vamos considerar o sinal.
    int sinal = 1;
    if (num < 0) {
        sinal = -1;
        num = -num;
    }

    while (num != 0) {
        resto = num % 10;
        invertido = invertido * 10 + resto;
        num = num / 10;
    }

    return invertido * sinal;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    // Caso especial: buscar 0 em qualquer número
    if (numerobusca == 0) {
        // Conta quantos 0's tem no numerobase
        int count = 0;
        int temp = numerobase;
        
        if (temp == 0) return 1; // Se ambos são 0
        
        while (temp > 0) {
            if (temp % 10 == 0) {
                count++;
            }
            temp = temp / 10;
        }
        return count;
    }
    
    int qtdOcorrencias = 0;
    int tempBase = numerobase;
    int tamBusca = 0;
    int busca = numerobusca;
    
    // Calcula quantos dígitos tem o número de busca
    while (busca > 0) {
        tamBusca++;
        busca = busca / 10;
    }
    
    // Recria o número de busca
    busca = numerobusca;
    
    // Procura ocorrências
    while (tempBase > 0) {
        int temp = tempBase;
        int encontrou = 1;
        int buscatemp = busca;
        
        // Verifica se os próximos 'tamBusca' dígitos coincidem
        for (int i = 0; i < tamBusca; i++) {
            if (temp % 10 != buscatemp % 10) {
                encontrou = 0;
                break;
            }
            temp = temp / 10;
            buscatemp = buscatemp / 10;
        }
        
        if (encontrou && tamBusca > 0) {
            qtdOcorrencias++;
        }
        
        tempBase = tempBase / 10;
    }
    
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
{
    int achou = 0;
    int tamPalavra = 0;
    
    // Calcula o tamanho da palavra
    while (palavra[tamPalavra] != '\0' && tamPalavra < 5) {
        tamPalavra++;
    }
    
    if (tamPalavra == 0) return 0;
    
    // Direções: direita, esquerda, baixo, cima, 
    // diagonais: superior-direita, superior-esquerda, inferior-direita, inferior-esquerda
    int direcoes[8][2] = {
        {0, 1},   // direita
        {0, -1},  // esquerda  
        {1, 0},   // baixo
        {-1, 0},  // cima
        {-1, 1},  // superior-direita
        {-1, -1}, // superior-esquerda
        {1, 1},   // inferior-direita
        {1, -1}   // inferior-esquerda
    };
    
    // Percorre toda a matriz
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            // Para cada direção possível
            for (int d = 0; d < 8; d++) {
                int match = 1;
                
                // Verifica se a palavra cabe na direção atual
                for (int k = 0; k < tamPalavra; k++) {
                    int novaLinha = i + k * direcoes[d][0];
                    int novaColuna = j + k * direcoes[d][1];
                    
                    // Verifica limites da matriz
                    if (novaLinha < 0 || novaLinha >= 8 || 
                        novaColuna < 0 || novaColuna >= 10) {
                        match = 0;
                        break;
                    }
                    
                    // Verifica se o caractere coincide
                    if (matriz[novaLinha][novaColuna] != palavra[k]) {
                        match = 0;
                        break;
                    }
                }
                
                if (match) {
                    achou = 1;
                    return achou; // Retorna assim que encontrar
                }
            }
        }
    }
    
    return achou;
}



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}