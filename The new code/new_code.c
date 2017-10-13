#include <stdio.h>
#include <stdlib.h>

//Limpa o Buffer do teclado;
void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

//Estrutura para os tipos de dados;
struct elemento {
  char band;
  char nome;
  int tempo;
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

//Inicializa a lista;
Menu *lst_cria(){
  Menu *novo = (Menu *)malloc(sizeof(Menu));
  novo->inicio = NULL;
  novo->fim = NULL;
  novo->tam = 0;
  return (novo);
}

//Cria a Memória;
Menu *cria_lista(Menu *l,int tam){
  if(l!=NULL){
    int i;
    for(i=tam;i>0;i--){
      Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
      novo->band = 'H';
      novo->nome = '*';
      novo->tempo = 0;
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
  printf("Nó %d:",no->pos);
  printf("%c - ",no->band);
  printf("%c\n",no->nome);
  no = no->prox;
  while(no != l->inicio){
    printf("Nó %d:",no->pos);
    printf("%c - ",no->band);
    printf("%c\n",no->nome);
    no = no->prox;
  }
}

/*Tenta reorganizar a lista se o tamanho do processo for muito grande
e não couber;*/
Menu *altera_lista(Menu *l,char name, int p,int temp){
  Elemento *aux;
  aux = l->inicio;
  int cont=0;

  while(cont<p){
    if(aux->band == 'H'){
    aux->band = 'P';
    aux->nome = name;
    aux->tempo = temp;
    aux = aux->prox;
    cont++;
    }
    else{
      aux = aux->prox;
    }
  }

  return (l);
}

/*Remove um processo da memória atribuindo ao lugar que ele ocupava na memória
como vazio*/
int remover(Menu *l,int tam,int temp){
  Elemento *no;
  no = l->inicio;
  if(no->tempo <=temp && no->band == 'P'){
    no->band = 'H';
    no->nome = '*';
    tam++;
  }
  no = no->prox;
  while(no != l->inicio){
    if(no->tempo <=temp && no->band == 'P'){
      no->band = 'H';
      no->nome = '*';
      tam++;
    }
    no = no->prox;
  }
  return tam;
}


int main(){
  Menu *l;
  int tam,tam2,temp,opcao,Chronos=0;
  char name;
  printf("\nDigite o tamanho da memória: ");
  scanf("%d",&tam);
  l = lst_cria();
  l = cria_lista(l,tam);

  do{
  printf("\n0-Sair\n");
  printf("1-Passar o tempo\n");
  printf("2-Adicionar processo\n");
  printf("3-Printar memória\n\n");
  printf("Escolha uma opcao: ");
  scanf("%d",&opcao);
  if(opcao==1){
    Chronos++;
    tam = remover(l,tam,Chronos);
  }
  if(opcao==2){
    flush_in();
    printf("Informe o nome do processo: ");
    scanf("%c",&name);
    flush_in();
    printf("Informe o tamanho do processo: ");
    scanf("%d",&tam2);
    printf("Informe o tempo de duração: ");
    scanf("%d",&temp);
    if(tam >= tam2){
      l = altera_lista(l,name,tam2,(temp+Chronos));
      tam = tam - tam2;
    }
    //Se estrapolar a quantidade de memória disponivel retorna uma mensagem;
    else{
      printf("\nMemória insuficiente\n");
    }
}
  if(opcao==3){
    printar(l);
  }

}while(opcao!=0);

  return 0;
}
