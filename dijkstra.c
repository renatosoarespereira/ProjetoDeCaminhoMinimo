#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXN 1000
#define bool int
#define true 1
#define false 0

typedef struct q{
	int chave;
	int valor;
}queue;

int tam = 0, MaxFila = 5000000;
int dist[MAXN];
int grafo[MAXN][MAXN];
const int INF = 1e8;

queue *fila;

void push(int priority, int valor){
	tam++;
	if(tam >= MaxFila){
		MaxFila <<= 1;
		queue *ok = (queue*) realloc(fila, MaxFila * sizeof(queue));
		if(ok == NULL){ printf("Erro ao realocar memoria!\n"); exit(1); }
	}
	int v = tam;
	while( (v >> 1) && priority > fila[(v >> 1)].chave){
		fila[v] = fila[(v >> 1)];
		v >>= 1;
	}
	fila[v].chave = priority;
	fila[v].valor = valor;
}

int topValor(){
	if(!tam){ printf("Erro! Fila esta vazia\n"); exit(1); }
	return fila[1].valor;
}

int topPrioridade(){
	if(!tam){ printf("Erro! Fila esta vazia\n"); exit(1); }
	return fila[1].chave;
}

int pop(){
	if(!tam){ printf("Erro! Fila esta vazia\n"); exit(1); }
	int ret = fila[1].valor, valor = fila[tam].valor, priority = fila[tam].chave, v = 1;
	tam--;
	while((v << 1) <= tam && (priority < fila[(v << 1)].chave || priority < fila[(v << 1) + 1].chave)){
		if(fila[(v << 1)].chave > fila[(v << 1) + 1].chave){ fila[v] = fila[(v << 1)]; v <<= 1; }
		else{ fila[v] = fila[(v << 1) + 1]; v = (v << 1) + 1 ; }
	}
	fila[v].chave = priority;
	fila[v].valor = valor;
	return ret;
}

int size(){ return tam; }

bool empty(){
	if(!tam) return true;
	return false;
}

void dijkstra(int origem, int n){
	int i, no_prox, custo_atual, no_atual, custo_prox;
	for(i = 0; i < n; i++){
		dist[i] = INF;
	}

	fila = (queue*) malloc(MaxFila*sizeof(queue));
	push(0,origem);
	dist[origem] = 0;

	while( empty() == false ){
		custo_atual = -topPrioridade();
		no_atual = topValor();

		pop();

		for(no_prox = 0; no_prox < n; no_prox++){
			if( grafo[no_atual][no_prox] != -1 && no_prox != no_atual ){
				custo_prox = custo_atual + grafo[no_atual][no_prox];

				if(dist[no_prox] > custo_prox){
					dist[no_prox] = custo_prox;

					push(-dist[no_prox], no_prox);
				}
			}
		}
	}

}

int main(){

	int n, m, i, j, de, para, custo;
	printf("Digite o tamanho da matriz de adjacencia:\n");
	scanf("%d",&n);
	printf("Digite a quantidade de arestas:\n");
    scanf("%d",&m);

	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			grafo[i][j] = -1;
		}
	}

	for(i = 0; i < m; i++){
        printf("Digite a origem:\n");
		scanf("%d", &de);
        printf("Digite o destino:\n");
        scanf("%d",&para);
        printf("Digite o peso do caminho:\n");
        scanf("%d",&custo);
		grafo[de][para] = custo;
		grafo[para][de] = custo;
	}

	for(de = 0; de < n; de++){
		dijkstra(de, n);
		printf("Distancia do no [%d] para todos os outros nos:\n", de);

		for(i = 0; i < n; i++){
			if( i == de ) printf("%d: 0\n", i);
			else if( dist[i] == INF ) printf("%d: INF\n", i);
			else printf("%d: %d\n", i, dist[i]);
		}

		printf("\n");
	}

	return 0;
}
