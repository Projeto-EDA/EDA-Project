/*
Relatório - Projeto de Pesquisa de EDA – Parte 1

Alunos:

-João Lucas Sousa Reis    /160009758
-João Vítor Morandi Lemos /160010195
-Luciano dos Santos Silva /160013321

Professor: Fernando W. Cruz
Disciplina: Estrutura de Dados e Algoritmos
*/

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

//Inicializa o cabeçalho;
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

//Função para imprimir a situação atual da memória
void printar(Menu *l){
  int c=0,v=0;
  if((l->tam == 0) || (l==NULL)){
    return;
  }
  Elemento *no = l->inicio;
  printf("\nEspaço %d: ",no->pos);
  printf("%c - ",no->band);
  printf("%c\n",no->nome);
  no = no->prox;
  if(no->band == 'H'){
    v++;
  }
  if(no->band == 'P'){
    c++;
  }
  while(no != l->inicio){
    printf("Espaço %d: ",no->pos);
    printf("%c - ",no->band);
    if(no->band == 'H'){
      v++;
    }
    if(no->band == 'P'){
      c++;
    }
    printf("%c\n",no->nome);
    no = no->prox;
  }

  printf("\n\t\t\tEspaço ocupado:    %d",c);
  printf("\n\t\t\tEspaço disponível: %d",v);

}

/*Insere um novo processo na memória de acordo com o tamanho dele */
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
  int tam,comp,tam2,temp,opcao,Chronos=0,t;
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
    printf("Digite quanto tempo deseja passar: ");
    scanf("%d",&t);
    Chronos = Chronos + t;
    comp = tam;
    tam = remover(l,tam,Chronos);
    printf("\n\t\t\tEspaço liberado na memória: %d\n",(tam-comp));
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
    //Se extrapolar a quantidade de memória disponivel retorna uma mensagem;
    else{
      printf("\n\t\t\tMemória insuficiente\n");
      printf("\t\tResete o tempo dos processos ou Sai do Programa e retorne\n");
    }
}
  if(opcao==3){
    printar(l);
  }

  if(opcao>=4){
    printf("\n\t\t\t\tERRO!\n");
    printf("\t\tPorfavor, digite uma opcao VALIDA!\n");
  }
}while(opcao!=0);

  return 0;
}
