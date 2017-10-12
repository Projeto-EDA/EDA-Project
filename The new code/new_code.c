#include <stdio.h>
#include <stdlib.h>

struct elemento {
  char band;
  char nome;
  int pos;
  struct elemento *ant;
  struct elemento *prox;
};

typedef struct elemento Elemento;

struct menu{
  int tam;
  struct elemento *inicio;
  struct elemento *fim;
};

typedef struct menu Menu;

Menu *lst_cria(){
  Menu *novo = (Menu *)malloc(sizeof(Menu));
  novo->inicio = NULL;
  novo->fim = NULL;
  novo->tam = 0;
  return (novo);
}

Menu *cria_lista(Menu *l,int tam){
  if(l!=NULL){
    int i;
    for(i=tam;i>0;i--){
      Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
      novo->band = 'H';
      novo->nome = '*';
      novo->pos = i;
      if(l->tam == 0){
        l->inicio = novo;
        l->fim = novo;
        novo->ant = novo;
        novo->prox = novo;
      }
      if(l->tam >= 1){
        l->inicio->ant = novo;
        l->fim->prox = novo;
        novo->ant = l->fim;
        novo->prox = l->inicio;
        l->inicio = novo;
      }
      l->tam++;
    }
  }
  return (l);
}

void printar(Menu *l){
  if((l->tam == 0) || (l==NULL)){
    return;
  }
  Elemento *no = l->inicio;
  printf("Nó %d\n",no->pos);
  printf("%c\n",no->band);
  printf("%c\n",no->nome);
  no = no->prox;
  while(no != l->inicio){
    printf("Nó %d\n",no->pos);
    printf("%c\n",no->band);
    printf("%c\n",no->nome);
    no = no->prox;
  }
}


int main(){
  Menu *l;
  int tam;
  printf("Digite o tamanho da memória: ");
  scanf("%d",&tam);
  l = lst_cria();
  l = cria_lista(l,tam);

  printar(l);



  return 0;
}
