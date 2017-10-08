#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct elemento{
  int info;
  struct elemento *ant;
  struct elemento *prox;
};

typedef struct elemento Elemento;

Elemento *lst_cria(){
  return NULL;
}
Elemento *push(Elemento *l, int valior){
  Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
  Elemento *p;
  p=l;
  if(l==NULL){
    novo->info = valior;
    novo->ant = NULL;
    novo->prox = l;
    return (novo);
  }
  else{
  while(p->prox!=NULL){
    p = p->prox;
  }
  if(p->prox==NULL){
    p->prox = novo;
    novo->info = valior;
    novo->ant = p;
    novo->prox = NULL;
  }
  return (l);
  }
}

Elemento *pop(struct elemento *l){
  Elemento *ant = NULL;
  Elemento *p;
  p=l;
  if(l==NULL){
    return l;
  }
  else{
  while(p->prox!=NULL){
    ant = p;
    p = p->prox;
  }
  if(ant==NULL){
    l = p->prox;
  }
  else {
    ant->prox = NULL;
  }
  free(p);
  return l;
}
}

void *lst_imprime(struct elemento *l){
  struct elemento *p;
  p=l;
  while(p!=NULL){
    printf("%d\n",p->info);
    p = p->prox;
  }
}

int main(){
    char expr[40];
    Elemento *pilha;
    int opcao,valor;
    pilha = lst_cria();
    do{
    printf("\n0-Sair\n");
    printf("1-Inserir elemento\n");
    printf("2-Remover elemento\n");
    printf("3-Imprimir pilha\n");
    printf("Selecione uma opcao: ");
    scanf("%d",&opcao);

    if(opcao==1){
      printf("Digite o valor a ser adicionado: ");
      scanf("%d",&valor);
      pilha = push(pilha,valor);
    }

    else if(opcao==2){
      pilha = pop(pilha);
    }

    else if(opcao==3){
      lst_imprime(pilha);
    }

    while(opcao < 0 || opcao > 3){
      printf("Por favor, digite valor valido!\n");
      printf("Selecione uma opcao: ");
      scanf("%d",&opcao);
    }
  }while(opcao!=0);

    return 0;

  }
