#include<stdio.h>
#include<stdlib.h>

//Dados

struct Dados{
  float kbytes;
  char label[30];
  struct Memoria *ant;
  struct Memoria *prox;
};
typedef struct Dados dados;

struct Memoria{
  dados *inicio;
  dados *fim;
  int tam;

};
typedef struct Memoria ram;

ram *inicializar();
void insere_ini(ram* l,/*char *s,*/int kbyt);
void imprimir(ram *l);

int main(int argc, char const *argv[]) {

  ram* l;
  l = inicializar();
  insere_ini(l,12);
  imprimir(l);
  return 0;
}

ram *inicializar(){
  ram *novo = (ram*)malloc(sizeof(ram));
  novo->inicio=NULL;
  novo->fim= NULL;
  novo->tam=0;
  return novo;
}


void insere_ini(ram *l,/*char *s*/int kbyt){

  if(l!= NULL){
    dados *no = (dados*)malloc(sizeof(dados));
    no->kbytes= kbyt;

    if(l->tam == 0)
      {
        l->inicio = no;
        l->fim = no;
        no->ant = no;
        no->prox = no;
        l->tam++;
        return;
      }
    if(l->tam == 1)
    {
      l->inicio->ant = no;
      l->inicio->prox = no;
      no->prox = l->inicio;
      no->ant = l->fim;
      l->inicio = no;
      l->tam++;
      return;
    }
    l->inicio->ant = no;
    l->fim->prox = no;
    no->ant = l->fim;
    no->prox = l->inicio;
    l->inicio = no;
    l->tam++;
  }
}
void imprimir(ram *l){
  if((l->tam == 0) || (l==NULL))
    return;
  dados *no = l->inicio;
  printf("%d\n",no->kbytes);
  no = no->prox;
  while(no != l->inicio){
    printf("%d\n",no->kbytes);
    no = no->prox;
  }
}
void remover_ini(ram *l){
  if((l->tam == 0) || (l==NULL))
    return;
  if(l->tam == 1)
  {
    free(l->inicio);
    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
    return;
  }
  dados *no = l->inicio->prox;
}
