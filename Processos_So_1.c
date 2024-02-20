#include <stdio.h>
#include <stdlib.h>

#define NUM_PROCESSOS 5
#define TAM_MEMORIA 100
int memoria[TAM_MEMORIA];
int index_ultimo_processo = 0;

typedef struct {
  int id;
  int tamanho;
} Processo;

void inicializar_memoria() {
  for (int i = 0; i < TAM_MEMORIA; i++) {
    memoria[i] = -1;
  }
}

void imprimir_memoria() {
  for (int i = 0; i < TAM_MEMORIA; i++) {
    if (i % 10 == 0) {
      printf("\n");
    }
    printf("%d\t", memoria[i]);
  }
  printf("\n\n");
}

int First_Fit(int tamanho_processo) {
int espaco_livre_atual = 0;
  int posicao_primeiro_espaco_livre = 0;

  for (int i = 0; i < TAM_MEMORIA; i++) {

    if (memoria[i] == -1) {
        espaco_livre_atual++;

      if (espaco_livre_atual >= tamanho_processo) {
          posicao_primeiro_espaco_livre = i - tamanho_processo + 1;
          return posicao_primeiro_espaco_livre;
    }

    } else {
      espaco_livre_atual = 0;
    }
  }
  return posicao_primeiro_espaco_livre;
}

int Next_Fit(int tamanho_processo) {
  int espaco_livre_atual = 0;
  int posicao_primeiro_espaco_livre = -1;
  
  for (int i = index_ultimo_processo; i < TAM_MEMORIA; i++) {
    
    if (memoria[i] == -1) {
        espaco_livre_atual++;
    
      if (espaco_livre_atual >= tamanho_processo) {
        index_ultimo_processo = i;
        posicao_primeiro_espaco_livre = i - tamanho_processo + 1;
        
        printf("Pos %d  ", index_ultimo_processo);
        
        return posicao_primeiro_espaco_livre;
        
      }
      
    } else {
      espaco_livre_atual = 0;
    }
  }
  return posicao_primeiro_espaco_livre;
}


int Best_Fit(int tamanho_processo) {
  int espacos_livre_atual = 0;
  int melhor_espaco_livre = -1;
  int tam_melhor_espaco = TAM_MEMORIA;
  
  for (int i = 0; i < tam_melhor_espaco; i++) {
    
    if (memoria[i] == -1) {
      espacos_livre_atual++;
      
      if (espacos_livre_atual >= tamanho_processo && espacos_livre_atual <= tam_melhor_espaco) {
        melhor_espaco_livre = i - espacos_livre_atual + 1;
        tam_melhor_espaco = espacos_livre_atual;
        
      }
      
    } else {
      espacos_livre_atual = 0;
    }
  }
  return melhor_espaco_livre;
}
  
int alocar_processo(Processo processo) {
  int posicao_inicio =  Best_Fit(processo.tamanho);
  if (posicao_inicio == -1) {
    return -1;
  }
  for (int i = posicao_inicio; i < posicao_inicio + processo.tamanho; i++) {
    memoria[i] = processo.id;
  }
  return posicao_inicio;
}

int main() {
  inicializar_memoria();
  Processo processos[NUM_PROCESSOS] = {{1, 30}, {2, 20}, {3, 10}, {4, 40}, {5, 25}};

  printf("Memoria antes da alocacao:\n");
  imprimir_memoria();

  for (int i = 0; i < NUM_PROCESSOS; i++) {

    int posicao_inicio = alocar_processo(processos[i]);
    if (posicao_inicio == -1) {
      printf("Nao foi possivel alocar o processo %d\n", processos[i].id);

    } else {

      printf("Processo %d alocado na posicao %d\n", processos[i].id, posicao_inicio);
    }

    imprimir_memoria();
  }
  return 0;
}