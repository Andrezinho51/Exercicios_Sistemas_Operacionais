#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
// Função para imprimir o cabeçalho da tabela

void imprimir_processo(int pid) {
  printf("| %7d |  %10ld ms |  %10ld ms |\n", pid,
  clock() * 1000 / CLOCKS_PER_SEC,
  (clock() + 2) * 1000 / CLOCKS_PER_SEC);
}

void func_1(){ 
  
  printf(" Executando a func 1\n"); 
  
}

void func_2(){ 
  
  printf(" Executando a func 2\n"); 

}

void func_3(){ 

  printf(" Executando a func 3\n"); 

}

int gerenciar_p(int pid, int count) {
  int status;
  pid = fork();
  if (pid == -1)
    printf("erro pid = -1");
  else if (pid == 0) {
    int PID_status = WEXITSTATUS(status);
    // processo filho
    printf("\n#-------------------------------------------#\n Processo: %d\n ", getpid());
    printf("Processo %d terminado com status: %d\n", getpid(), PID_status);
      
    if (count == 0){
      imprimir_processo(getpid());
      func_1();
    }
    else if (count == 1){
      imprimir_processo(getpid());
      func_2();
    }

    else if (count == 2){
      imprimir_processo(getpid());
      func_3();
    }

    kill(getpid(), SIGKILL);

  } else {
    
    wait(NULL);
    
  }
  return 1;
}

void imprimir_cabecalho() {
  printf("+---------+-------------------+-------------------+\n");
  printf("| Process |  Início do tempo  |  Término do tempo  |\n");
  printf("+---------+-------------------+-------------------+\n");
}
// Função para imprimir um processo na tabela

int main() {
  int pid, count = 0;
  int i, status;
  imprimir_cabecalho();
  // cria 3 processos
  for (i = 0; i < 3; i++) {
    pid = fork();
    if (pid == -1) {
      
      printf("Erro ao criar processo filho.\n"); 
      exit(1);
      
    } else if (pid == 0) { // Processo filho
      
      imprimir_processo(getpid());
      sleep(2);      // Aguarda 2 segundos
      printf("Processo filho %d concluído.\n",getpid());
      exit(0);                // Encerra o processo filho
      
    } else {                  // Processo pai
      
      imprimir_processo(pid); // Imprime informações do processo pai na tabela
      printf("+---------+-------------------+-------------------+\n");
      printf("Processo pai criou processo filho %d.\n",pid);  

    }
  }
  // aguarda os processos filhos terminarem
  for (i = 0; i < 3; i++) {
    
    pid = wait(&status); // Espera um processo filho terminar
    printf("Processo filho %d terminou com status %d.\n", pid, WEXITSTATUS(status));
   
  }
  printf("Todos os processos terminaram.\n");
  
  for (int k = 0; k < 3; k++) {
    
    gerenciar_p(getpid(), count);
    count++;
    
  }
  
  return 0;
}