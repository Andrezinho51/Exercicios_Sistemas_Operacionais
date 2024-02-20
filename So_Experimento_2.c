#include <stdio.h>
#define QUANTUM 2
// Define o quantum para 2 unidades de tempo
// Estrutura para representar um processo
typedef struct {
  int pid;
  int tempo_restante;
} Processo;
// Função que implementa o escalonamento Round-Robin
void round_robin(Processo processos[], int num_processos) {
  
  int pont_inic = 0;
  int finalizado = 0;
  
  while (finalizado < num_processos) {
    
    if (processos[pont_inic].tempo_restante > 0) {
      
      processos[pont_inic].tempo_restante = processos[pont_inic].tempo_restante - QUANTUM;
      
      if (processos[pont_inic].tempo_restante > 0) {
        
        printf("Tempo restante do processo %d: %d\n", processos[pont_inic].pid,
        processos[pont_inic].tempo_restante);
        
      } else {
        
        printf("Processo %d finalizado!\n", processos[pont_inic].pid);
        finalizado++;
        
      }
    }
    
    pont_inic = (pont_inic + 1) % num_processos;
    
  }
}

int main() {
  // Cria 5 processos com tempo de execução aleatório
  Processo processos[5];
  for (int i = 0; i < 5; i++) {
    processos[i].pid = i + 1;
    processos[i].tempo_restante = 2 * i + 1;
  }
  // Executa o escalonamento Round-Robin para os processos criados
  round_robin(processos, 5);
  return 0;
}