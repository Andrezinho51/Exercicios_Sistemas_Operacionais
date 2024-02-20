#include <stdbool.h>
#include <stdio.h>
#include <string.h>


void banker(int n, int m, int existent[], int available[], int allocation[][m], int request[][m]) {
    bool fila_processos[n];
    int processo_execuçao = 0;

    memset(fila_processos,false,sizeof(fila_processos)); // iniciando tudo como falso.

    int deadlock = 0;
    int i = 0;
    bool executavel = false;

    while(processo_execuçao < n){  //condiçao de parada é se os processos finalizados for maior q 'n'.
        executavel = true;

        for(int j = 0; j < m; j++){
            if(request[i][j] > available[j] || fila_processos[i] == true){ // o ou serve para a segunda varredura do codigo. 
                executavel = false;
                deadlock += 1;
                break;
            }
        }
      
        if(executavel == false){
            printf("\nProcesso %d já executado ou recursos insuficientes para execuçao", i);
            deadlock++;
            i = (i + 1) % n; // quando o resto for zero significa que um ciclo ja acbou e ele volta pro indice 0.
            continue;
        }

        printf("\nProcesso %d adicionado na fila",i);

        for(int k = 0; k < m; k++){
            available[k] -= request[i][k];      // soma e subtraçao dos recursos.
            allocation[i][k] += request[i][k];
        }
        
        for(int k = 0; k < m; k++){
            available[k] += allocation[i][k];    // quando uma matriz e finalizada.
            request[i][k] = 0;
        }

        fila_processos[i] = true;
        processo_execuçao += 1;
        deadlock = 0;
        i = (i + 1) % n; // quando o resto for zero significa que um ciclo ja acbou e ele volta pro indice 0.
    }
  
    printf("\nProcesso Finalizado\n");     // indica a finalizaçao do codigo.
    
    if(deadlock >= n || processo_execuçao < n){
        printf("\nDeadLock\n");        // se o estado for inseguro ele imprime DeadLock
    }
    else{
      printf("\nEstado seguro: Todos os processos finalizaram com sucesso!\n\n\n");
    }
}

int main() {
  
  int n = 10;                           // número de processos
  int m = 5;                            // número de recursos
  int existent[5] = {10, 11, 8, 12, 7}; // vetor de recursos existentes
  int available[5] = {6, 3, 0, 3, 2};   // vetor de recursos disponiveis
  
  int allocation[10][5] = {             // matriz de alocação corrente
                           {0, 1, 1, 2, 0}, 
                           {1, 1, 3, 3, 0}, 
                           {1, 0, 0, 0, 1},
                           {0, 0, 1, 1, 0}, 
                           {0, 1, 2, 1, 2}, 
                           {0, 1, 0, 1, 0},
                           {0, 0, 0, 1, 0}, 
                           {1, 1, 0, 0, 1}, 
                           {0, 1, 0, 0, 1},
                           {1, 2, 1, 0, 0}};
  
  int request[10][5] = {// matriz de requisição
                        {0, 3, 0, 2, 1}, 
                        {2, 0, 1, 1, 0}, 
                        {1, 1, 8, 0, 0},
                        {0, 0, 1, 0, 0}, 
                        {0, 1, 1, 0, 1}, 
                        {0, 0, 1, 1, 2},
                        {4, 1, 0, 1, 0}, 
                        {0, 0, 3, 1, 0}, 
                        {1, 0, 0, 4, 1},
                        {1, 1, 1, 5, 0}};
  
  printf("Matriz de alocação corrente:\n");
  
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%d ", allocation[i][j]);
      }
      printf("\n");
    }
  
  printf("\n");
  
  printf("Matriz de requisição:\n");
  
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%d ", request[i][j]);
      }
    
    printf("\n");
    
  }
  
  printf("\n");
  
  printf("Vetor de recursos existentes:\n");
  
    for (int i = 0; i < m; i++) {
      printf("%d ", existent[i]);
    }
  
  printf("\n\n");
  banker(n, m, existent, available, allocation, request);
  return 0;
}