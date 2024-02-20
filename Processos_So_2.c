#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PROCESSOS 5
#define TAM_MEMORIA 20
int processos_alocados[5];
int processos_nao_alocados[5];
unsigned int bitmap[TAM_MEMORIA];

typedef struct {
  int id;
  int tamanho;
  int posicao_inicio;
  int alocado;
} Processo;

void inicializar_bitmap() {
  for (int i = 0; i < TAM_MEMORIA; i++) {
    bitmap[i] = 0;
  }
}

int First_Fit(int tamanho_processo) {
int espaco_livre_atual = 0;
  int posicao_primeiro_espaco_livre = 0;

  for (int i = 0; i < TAM_MEMORIA; i++) {

    if (bitmap[i] == 0) {
        espaco_livre_atual++;

      if (espaco_livre_atual >= tamanho_processo) {
          posicao_primeiro_espaco_livre = i - tamanho_processo + 1;
          return posicao_primeiro_espaco_livre;
    }

    } else {
      espaco_livre_atual = 0;
    }
  }
  return -1;
}

void imprimir_bitmap() {
  for (int i = 0; i < TAM_MEMORIA; i++) {
    printf("%d ", bitmap[i]);
  }
  printf("\n");
}

int alocar_processo(Processo *processo) {
  int index_inicial = First_Fit(processo-> tamanho);
  
  if (index_inicial == -1) { 
    printf("\n\nNao foi possivel alocar o processo %d\n\n", processo-> id);
    
  } else {
    
    for (int i = index_inicial; i < index_inicial + processo-> tamanho; i++) {
      bitmap[i] = 1;
      
    }
    
    processo-> posicao_inicio = index_inicial;
    processo-> alocado = 1;
    printf("\n\nProcesso %d alocado na posicao %d com sucesso! \n\n", processo-> id, processo-> posicao_inicio);
  }
  
  return 0;
  
}
void liberar_processo(Processo *processo) {
  
  int comeco = processo-> posicao_inicio;
  for (int i = comeco; i < comeco + processo-> tamanho; i++) {
    bitmap[i] = 0;
  }
  processo->alocado = 0;
  printf("\n\nProcesso %d desalocado com sucesso! \n\n", processo-> id);
}
int main() {
  inicializar_bitmap();
  imprimir_bitmap();

  Processo processos[NUM_PROCESSOS] = {{1, 5, 0, 0}, {2, 3, 0, 0}, {3, 4, 0, 0}, {4, 7, 0, 0}, {5, 2, 0, 0}};
  
  alocar_processo(&processos[2]);
  imprimir_bitmap();
  
  alocar_processo(&processos[3]);
  imprimir_bitmap();
  
  liberar_processo(&processos[2]);
  imprimir_bitmap();
  
  alocar_processo(&processos[0]);
  imprimir_bitmap();
  
  alocar_processo(&processos[1]);
  imprimir_bitmap();
  
  alocar_processo(&processos[4]);
  imprimir_bitmap();
  
  return 0;
}