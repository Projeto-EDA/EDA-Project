#include<stdio.h>
#include<stdlib.h>

//Dados do Processo
struct Processo {
  char label[30];
  float kbytes;
};
typedef struct Processo processo;

//Nó da lista
struct No{
  void *info;
  struct No *prev,*prox;
};
typedef struct No no;

//cabeçalho

struct Head{
  int tam;
  struct No *inicio;
  struct No *fim;

};
typedef struct Head head;

int main(){

  head *l=inicializar();

  return 0;
}

head* criar_no(void *processo){
  no *novo = (no*)malloc(sizeof(no));
  novo->info=processo;
  novo->prev=novo->prox=NULL;
  return novo;
}

void inserir_ini(head *l,char *s,float label){
  no *tmp = criar_no(processo);
  tmp->prox = l->inicio;
  l->inicio->prev = tmp;
  l->inicio = tmp;
  l->tam++;
}

head *inicializar(){
  head *novo = (head*) malloc(sizeof(head));
  novo->inicio=novo->fim=NULL;
  novo->tam = 0;
  return novo;
}
