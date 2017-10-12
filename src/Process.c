/*
Relatório - Projeto de Pesquisa de EDA – Parte 1

Alunos:

-João Lucas Sousa Reis    /160009758
-João Vítor Morandi Lemos /160010195
-Luciano dos Santos Silva /160013321

Professor: Fernando W. Cruz
Disciplina: Estrutura de Dados e Algoritmos

*/

#include<stdio.h>
#include<stdlib.h>

void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}
//Dados

struct Dados{
  int kbytes;
  char label;
  int tempo;
  struct Dados *ant;
  struct Dados *prox;
};
typedef struct Dados dados;

struct Memoria{
  dados *inicio;
  dados *fim;
  int tam;

};
typedef struct Memoria ram;

ram *inicializar();
void insere_ini(ram* l,int kbyt, int tempo, char nome);
void imprimir(ram *l);
void remover(ram *l,int time);
void menu();

int main(int argc, char const *argv[]) {
  int mem,esp,temp,escolha,chronos=0;
  char nome,cont;
  printf("Digite o tamanho da memória disponível: ");
  scanf("%d",&mem);
  ram* l;
  l = inicializar();
  do{
    printf("\n0-Sair\n");
    printf("1-Apenas passar o tempo\n");
    printf("2-Adicionar um novo processo\n\n");
    printf("Escolha uma opção: ");
    scanf("%d",&escolha);
    flush_in();
    if(escolha == 1){
      chronos++;
    }
    if(escolha == 2){
        printf("Informe o tamanho do processo: ");
        scanf("%d",&esp);
        printf("Informe o tempo de duração: ");
        scanf("%d",&temp);
        flush_in();
        printf("Informe o nome do processo: ");
        scanf("%c",&nome);
        flush_in();
      if(mem > esp){
        mem = mem - esp;
        insere_ini(l,esp,(temp+chronos),nome);
      }
      else{
        printf("Memória insuficiente\n");
      }
    }
    imprimir(l);
    remover(l,chronos);
    mem = mem + esp;
    if(escolha!=0){
    printf("Continuar? S/n ");
    scanf("%c",&cont);
  }
}while(cont == 'S' && escolha != 0);
  return 0;
}

ram *inicializar(){
  ram *novo = (ram*)malloc(sizeof(ram));
  novo->inicio=NULL;
  novo->fim= NULL;
  novo->tam=0;
  return novo;
}


void insere_ini(ram *l, int kbyt, int temp,char s){

  if(l!= NULL){
    dados *no = (dados*)malloc(sizeof(dados));
    no->kbytes= kbyt;
    no->label = s;
    no->tempo = temp;

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
  printf("%d\n",no->tempo);
  printf("%c\n",no->label);
  no = no->prox;
  while(no != l->inicio){
    printf("%d\n",no->kbytes);
    printf("%d\n",no->tempo);
    printf("%c\n",no->label);
    no = no->prox;
  }
}
void remover(ram *l,int temp){
  if((l->tam == 0) || (l==NULL)){
    return;
  }
  dados *aux;
  dados *no;
  no = l->inicio;
  if(l->tam == 1)
  {
    if(no->tempo <= temp){
    free(l->inicio);
    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
  }
    return;
  }

  while(no->tempo > temp){
    no = no->prox;
  }
  if(no = l->inicio){
    return;
  }
else{
    no->prox->ant = no->ant;
    no->ant->prox = no->prox;
    free(no);
}
}
/*
void inserirPosicao(int valor, int posicao, ldec *l)
{
    if ((l == NULL) || (posicao > l->tamanho))
        return;
    int i;
    No *no = l->cabeca, *novo;
    for (i = 1; i < posicao; i++)//i inicializa em 1 para parar na posicao correta         no = no->proximo;
    novo = (No*) malloc(sizeof(No));
    novo->info = valor;
    no->proximo->anterior = novo;
    novo->proximo = no->proximo;
    no->proximo = novo;
    novo->anterior = no;
    l->tamanho++;
}
void removerPosicao(int posicao, ldec *l)//Remove o nó de determinada posição da lista
{
    if ((l->tamanho == 0) || (l == NULL))
        return;
    if (l->tamanho == 1)
    {
        removerPrimeiro(l);
        return;
    }
    if (posicao == l->tamanho-1)
    {
        removerUltimo(l);
        return;
    }
    int i;
    No *no = l->cabeca;
    for (i = 0; i < posicao; i++)     {         no = no->proximo;
    }
    no->anterior->proximo = no->proximo;
    no->proximo->anterior = no->anterior;
    free(no);
}*/
