#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define initial_capacity 10
#define initial_length 1000
#define initial_nodes 5
#define MAX 10000000

typedef struct vector {
	int n;	//Numar de elemente
	int capacitate;	//Capacitatea alocata vectorului
	char **nume;	//Elementele vectorului sunt nume actori
} Vector;	//Structura unui vector de nume

typedef struct nod {
	int value;
	struct nod *next;
	struct nod *prev;
}*Nod;	//Nod de lista dublu inlantuita

typedef struct graph {
	int nr_varfuri;	//Numarul de varfuri
	Nod *adjLists;	//Vector de liste de adiacenta
	int *vizitat;	//Vector de noduri vizitate
	Vector nume_din_graf;	//Vectorul de nume introduse in graf
}*Graph;	//Structura unui graf

typedef struct stack {
	int value;
	struct stack *next;
}*Stack;	//Structura unei stive

typedef struct node {
	int value;
	struct node *next;
}Node;	//Nod de lista simplu inlantuita

typedef struct queue {
	Node *head,*tail;
	int size;
}*Queue;	//Structura unei cozi

void init_Vector(Vector *v, int nr) {
	v->n=0;
	v->capacitate=nr;
	v->nume=malloc(sizeof(char *) * nr);
}	//Aloca memorie vectorului

int cauta_nume_in_Vector(Vector v, char *nume_cautat) {
	int gasit=-1, i;
	for(i=0; i < v.n; i++) {
		if(strcmp(v.nume[i], nume_cautat) == 0)
			gasit=i;
	}
	return gasit; //Daca nu e in vector se returneaza -1
}	//Returneaza indexul numelui cautat

void adauga_nume_in_Vector(Vector *v, char *nume_adaugat) {
	if(cauta_nume_in_Vector(*v, nume_adaugat) == -1) {	
		if(v->n >= v->capacitate) {
			v->capacitate=v->capacitate+1;
			v->nume=realloc(v->nume,v->capacitate * sizeof(char *));
		}
		v->nume[v->n]=malloc(sizeof(char) * (strlen(nume_adaugat) + 1));
		strcpy(v->nume[v->n],nume_adaugat);
		v->n=v->n+1;
	}
}	//Adauga numele in vector

void cauta_index_in_Vector(Vector v, int index, char *nume_gasit) {
	if(v.n <= index)
		return ;
	else {
		strcpy(nume_gasit,v.nume[index]);
	}
}	//Returneaza numele actorului cu indexul cautat

void clear_Vector(Vector *v) {
	int i;
	for (i=0; i< v->n; i++)
		free(v->nume[i]);
	free(v->nume);
	v->n=0;
	v->capacitate=0;
}	//Elibereaza memoria alocata vecotului

Nod initList(int nr) {
	Nod nou;
	nou=malloc(sizeof(struct nod));
	nou->value=nr;
	nou->next=NULL;
	nou->prev=NULL;
	return nou;
}	//Initializeaza lista dublu inlantuita

Nod addLast(Nod list, int nr) {
	Nod nou,curent;
	if(list == NULL)
		return initList(nr);
	nou=initList(nr);
	curent=list;
	while(curent->next != NULL)
		curent=curent->next;
	curent->next=nou;
	nou->prev=curent;
	return list;
}	//Adauga o valoare la sfarsitul liste

Nod deleteValue(Nod list, int nr) {
	if(list == NULL)
		return NULL;
	else {
		Nod curent=list, previous;
		if(curent->value == nr) {
			list=curent->next;
			free(curent);
			list->prev=NULL;
			return list;
		}
		else {
			previous=curent;
			curent=curent->next;
		}
		while(curent != NULL) {
			if(curent->value == nr) {
				previous->next=curent->next;
				if(curent->next != NULL)
					curent->next->prev=previous;
				free(curent);
				return list;
			}
			previous=curent;
			curent=curent->next;
		}
		return list;
	}
}	//Sterge valoarea din lista

Nod clearList(Nod list) {
	Nod curent;
	if(list == NULL)
		return list;
	while(list != NULL) {
		curent=list;
		list=list->next;
		free(curent);
	}
	return NULL;
}	//Sterge lista

int is_in_list(Nod list, int valoare_cauparent) {
	Nod curent=list;
	int ok=0;
	while(curent != NULL) {
		if(curent->value == valoare_cauparent) {
			ok=1;
			return ok;
		}
		curent=curent->next;
	}
	return ok;
}	//Verifica daca se afla valoarea in lista

int is_Stack_Empty(Stack stiva) {
	if(stiva == NULL)
		return 1;
	return 0;
}	//Verifica daca stiva e goala

Stack initStack(int value) {
	Stack nou=malloc(sizeof(struct stack));
	nou->value=value;
	nou->next=NULL;
	return nou;
}	//Initializeaza stiva

Stack push(Stack stiva, int value) {
	Stack nou;
	if (is_Stack_Empty(stiva) == 1)
		return initStack(value);
	nou=initStack(value);
	nou->next=stiva;
	return nou;
}	//Adauga valoarea in stiva

Stack pop(Stack stiva) {
	Stack curent;
	if(is_Stack_Empty(stiva) == 1)
		return stiva;
	curent=stiva;
	stiva=stiva->next;
	free(curent);
	return stiva;
}	//Sterge valoarea din varful stivei

int top(Stack stiva) {
	if(is_Stack_Empty(stiva) == 1)
		return -1;
	return stiva->value;
}	//Returneaza valoarea din varful stivei

Node *initNode(int value) {
	Node *nou;
	nou=malloc(sizeof(struct node));
	nou->value=value;
	nou->next=NULL;
	return nou;
}	//Aloca memorie unui nod de lista simplu inlantuita

Node *freeNode(Node *nod) {
	if(nod != NULL)
		free(nod);
	return NULL;
}	//Elibereaza memoria alocata nodului

Queue initQueue(int value) {
	Queue coada;
	coada=malloc(sizeof(struct queue));
	coada->head=initNode(value);
	coada->tail=coada->head;
	coada->size=1;
	return coada;
}	//Initializeaza coada

int is_Queue_empty(Queue coada) {
	if(coada == NULL || coada->head == NULL || coada->size == 0)
		return 1;
	return 0;
}	//Verifica daca este coada vida

Queue enQueue(Queue coada, int value) {
	Node *nou;
	if(is_Queue_empty(coada) == 1) {
		if(coada == NULL)
			return initQueue(value);
		free(coada);
		return initQueue(value);
	}
	nou=initNode(value);
	coada->tail->next=nou;
	coada->tail=nou;
	coada->size++;
	return coada;
}	//Adauga valoarea in coada

Queue deQueue(Queue coada) {
	Node *curent;
	if (is_Queue_empty(coada) != 1) {
		curent=coada->head;
		coada->head=coada->head->next;
		curent=freeNode(curent);
		coada->size--;
	}
	return coada;
}	//Sterge primul element din coada

int first(Queue coada) {
	if (is_Queue_empty(coada) != 1)
		return coada->head->value;
	else
		return -1;
}	//Intoarce primul element din coada

Queue freeQueue(Queue coada) {
	while( is_Queue_empty(coada) != 1)
		coada=deQueue(coada);
	if (coada != NULL)
		free(coada);
	return NULL;
}	//Sterge coada

Graph initGraph(int nr_varfuri) {
	Graph nou=malloc(sizeof(struct graph));
	nou->nr_varfuri=nr_varfuri;
	nou->vizitat=calloc(nr_varfuri, sizeof(int));
	nou->adjLists=malloc(sizeof(Nod) * nr_varfuri);
	init_Vector(&(nou->nume_din_graf),nr_varfuri);
	int i;
	for(i=0; i < nr_varfuri; i++)
		nou->adjLists[i]=NULL;
	return nou;
}	//Initializeaza graful neorientat

Graph adauga_nod(Graph g) {
	g->nr_varfuri=g->nr_varfuri+1;
	g->vizitat=realloc(g->vizitat,g->nr_varfuri * sizeof(int));
	g->adjLists=realloc(g->adjLists,g->nr_varfuri * sizeof(Nod));
	g->adjLists[(g->nr_varfuri)-1]=NULL;
	return g;
}	//Adauga un nod la graf

Graph adauga_muchie(Graph g, int start, int finish) {
	if(is_in_list(g->adjLists[start], finish) == 0)
		g->adjLists[start]=addLast(g->adjLists[start], finish);
	if(is_in_list(g->adjLists[finish], start) == 0)
		g->adjLists[finish]=addLast(g->adjLists[finish], start);
	return g;
}	//Adauga muchia la graf

void freeGraph(Graph g) {
	int i;
	for(i=0; i < g->nr_varfuri; i++)
		g->adjLists[i]=clearList(g->adjLists[i]);
	free(g->adjLists);
	free(g->vizitat);
	g->adjLists=NULL;
	clear_Vector(&(g->nume_din_graf));
	free(g);
}	//Sterge graful

void DFS(Graph g, int start) {
	g->vizitat[start]=1;
	Stack stiva=NULL;
	stiva=push(stiva,start);
	while(is_Stack_Empty(stiva) != 1) {
		int varf=top(stiva);
		stiva=pop(stiva);
		Nod curent=g->adjLists[varf];
		while(curent != NULL) {
			if(g->vizitat[curent->value] != 1) {
				stiva=push(stiva,curent->value);
				g->vizitat[curent->value]=1;
			}
			curent=curent->next;
		}
	}
}	//Face parcurgerea DFS asupra grafului

int nr_distributii(Graph g) {
	int nr=0, i;
	for(i=0; i < g->nr_varfuri; i++)
		g->vizitat[i]=0;
	for(i=0; i < g->nr_varfuri; i++) {
		if(g->vizitat[i] == 0) {
			nr++;
			DFS(g,i);
		}
	}
	return nr;	
}	//Calculeaza numarul de distributii

int extract_number(char *sir) {
	int i,num=0;
	for(i=0;i<strlen(sir);i++)
		if(sir[i]>='0' && sir[i]<='9')
			num=num*10+(sir[i]-'0');
	return num;
}	//Extrage un numar dintr-un sir de caractere

int grad_de_rudenie(Graph g, int start, int finish) {
	int i, distanta;
	for(i=0; i < g->nr_varfuri; i++)
		g->vizitat[i]=0;
	int *distance=malloc(sizeof(int) * g->nr_varfuri);
	for(i=0; i < g->nr_varfuri; i++)
		distance[i]=0;
	Queue coada=NULL;
	coada=enQueue(coada,start);
	g->vizitat[start]=1;
	while(!is_Queue_empty(coada)) {
		int x=first(coada);
		coada=deQueue(coada);
		Nod tmp;
		for(tmp=g->adjLists[x]; tmp != NULL; tmp=tmp->next) {
			if(g->vizitat[tmp->value] == 1)
				continue;
			distance[tmp->value]=distance[x]+1;
			coada=enQueue(coada, tmp->value);
			g->vizitat[tmp->value]=1;
		}
	}
	coada=freeQueue(coada);
	distanta=distance[finish];
	free(distance);
	return distanta;
}	//Calculeaza distanta minima dintre doua noduri

int min(int a, int b) {
	if(a < b)
		return a;
	else
		return b;
}	//Returneaza minimul a doua numere

void Swap_Strings(char **str1, char **str2) {
	char *aux=*str1;
	*str1=*str2;
	*str2=aux;
}	//Schimba doua stringuri intre ele

void Sort_Vector(Vector *v) {
	int i,j;
	for(i=0; i < (v->n)-1; i++)
		for(j=i+1; j < v->n; j++)
			if(strcmp(v->nume[i], v->nume[j]) > 0)
				Swap_Strings(&(v->nume[i]),&(v->nume[j]));
}	//Sorteaza in ordine alfabetica vectorul de nume

int DFS_AP(int x, Graph g, int timp, int *status, int *idx, int *parent,
	int *low, int *crit) {
	timp++;
	status[x]=1;	//Este nod la care ma pot intoarce
	g->vizitat[x]=1;
	idx[x]=timp;
	low[x]=timp;
	int y;
	int nr_copii=0;
	Nod crt;
	for(crt=g->adjLists[x]; crt!=NULL; crt=crt->next) {
		if(status[crt->value]==0) {
			y=crt->value;
			parent[y]=x;
			nr_copii++;
			DFS_AP(crt->value,g,timp,status,idx,parent,low,crit);
			low[x]=min(low[x],low[y]);
			if(idx[x]<=low[y])
				crit[x]=1;
		}
		if(status[crt->value]==1)
			if(crt->value!=parent[x])
				low[x]=min(low[x],idx[crt->value]);
	}
	status[x]=2;	//Este nod la care nu ma pot intoarce
	return nr_copii;
}	//Gaseste punctele articula din graf,returnand numarul de copii ai lui x

int main(int argc, char *argv[])
{
	FILE *input_file, *output_file;
	input_file=fopen(argv[argc-2],"r");	//Deschid fisierul de intrare
	output_file=fopen(argv[argc-1],"w");	//Deschid fisierul de iesire
	int nr_actori, nr_filme, i, j, k, actori_cititi, *indecsi_actori;
	char *nume_film, *nume_actor, *nr_filme_string, *nr_actori_string;
	Graph graf_actori;
	graf_actori=initGraph(1);	//Se initializeaza graful de actori
	nr_filme_string=malloc(sizeof(char) * initial_length);
	fgets(nr_filme_string, initial_length, input_file);	/*Citesc numarul de
			filme */
	nr_filme=extract_number(nr_filme_string);
	free(nr_filme_string);
	for(i=0; i < nr_filme; i++) {
		nume_film=malloc(sizeof(char) * initial_length);
		fgets(nume_film, initial_length, input_file);	//Citesc nume de film
		nr_actori_string=malloc(initial_length * sizeof(char));
		fgets(nr_actori_string, initial_length, input_file);	/*Citesc 
			numarul de actori */	
		nr_actori=extract_number(nr_actori_string);	
		free(nr_actori_string);
		indecsi_actori=malloc(sizeof(int) * nr_actori);	/*Aloc memorie
			vectorului in care se retin indecsii actorilor din film*/
		actori_cititi=0;
		for(j=0; j < nr_actori; j++) {
			nume_actor=malloc(initial_length * sizeof(char));
			fgets(nume_actor, initial_length, input_file);	/*Citesc nume de
				actor*/
			nume_actor[strlen(nume_actor)-1]='\0';	//Sterg '\n' din nume
			if(graf_actori->nr_varfuri == graf_actori->nume_din_graf.n)
				graf_actori=adauga_nod(graf_actori);	//Adaug nod in graf
			adauga_nume_in_Vector(&(graf_actori->nume_din_graf), 
				nume_actor);	//Adaug numele citit in vectorul grafulu
			indecsi_actori[actori_cititi]=cauta_nume_in_Vector(graf_actori->
				nume_din_graf, nume_actor);	//Adaug indexul in vector
			actori_cititi++;
			free(nume_actor);
		}
		for(k=0; k < nr_actori; k++)
			for(j=k+1; j < nr_actori; j++)
				graf_actori=adauga_muchie(graf_actori, indecsi_actori[k],
				indecsi_actori[j]);	//Adaug muchii intre indecsii din vector
		free(indecsi_actori);
		free(nume_film);
	}	//Citirea si construirea grafului
	if(strcmp(argv[1], "-c1") == 0)
		fprintf(output_file,"%d\n",nr_distributii(graf_actori));
	if(strcmp(argv[1], "-c2") == 0) {
		char *actor_start, *actor_finish;
		int index_start, index_finish;
		actor_start=malloc(initial_length * sizeof(char));
		fgets(actor_start, initial_length, input_file);
		actor_start[strlen(actor_start)-1]='\0';
		actor_finish=malloc(initial_length * sizeof(char));
		fgets(actor_finish, initial_length, input_file);
		actor_finish[strlen(actor_finish)-1]='\0';
		index_start=cauta_nume_in_Vector(graf_actori->nume_din_graf,
			actor_start);	//Caut indexul actorului de inceput
		index_finish=cauta_nume_in_Vector(graf_actori->nume_din_graf,
			actor_finish);	//Caut indexul actorului de sfarsit
		fprintf(output_file, "%d\n",grad_de_rudenie(graf_actori, index_start,
		 index_finish));
		free(actor_start);
		free(actor_finish);
	}
	if(strcmp(argv[1], "-c3") == 0) {
		int *parent=calloc(graf_actori->nr_varfuri, sizeof(int));
		for(i=0; i < graf_actori->nr_varfuri; i++)
			parent[i]=-1;
		for(i=0; i < graf_actori->nr_varfuri; i++)
			graf_actori->vizitat[i]=0;
		Vector articulatii;
		init_Vector(&articulatii, 1);
		int *status=calloc(graf_actori->nr_varfuri, sizeof(int));
		int *idx=calloc(graf_actori->nr_varfuri, sizeof(int));
		int *crit=calloc(graf_actori->nr_varfuri, sizeof(int));
		int *low=calloc(graf_actori->nr_varfuri, sizeof(int));
		for(i=0;i<graf_actori->nr_varfuri;i++) {
			int timp=0;
			if(graf_actori->vizitat[i] == 0) {
				int rez=DFS_AP(i, graf_actori, timp, status, idx, parent, low,
					crit);
				if(rez>1){
				char *actor_articulat=malloc(initial_length*sizeof(char));
				cauta_index_in_Vector(graf_actori->nume_din_graf, i,
					actor_articulat);
				adauga_nume_in_Vector(&articulatii,actor_articulat);
				free(actor_articulat);
			}
		}
		else if(crit[i] == 1) {
			char *actor_articulat=malloc(initial_length*sizeof(char));
			cauta_index_in_Vector(graf_actori->nume_din_graf, i,
				actor_articulat);
			adauga_nume_in_Vector(&articulatii,actor_articulat);
			free(actor_articulat);
		}
	}
	free(status);
	free(idx);
	free(crit);
	free(low);
	free(parent);
	Sort_Vector(&articulatii);
	fprintf(output_file, "%d\n", articulatii.n);
	int j;
	for(j=0;j<articulatii.n;j++) {
		fputs(articulatii.nume[j],output_file);
		fprintf(output_file, "\n");
	}
	clear_Vector(&articulatii);
}
	freeGraph(graf_actori);
	fclose(input_file);	//Inchid fisierul de intrare
	fclose(output_file);	//Inchid fisierul de iesire
	return 0;
}
