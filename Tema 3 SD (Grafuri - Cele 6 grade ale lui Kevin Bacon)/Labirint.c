#include <stdio.h>
#include <stdlib.h>
#define MARE 100000

typedef struct list {
    int end;
    int time;
    struct list *next;
} *List;    //Lista de adiacenta

typedef struct timelist {
	int guardian_time;
	struct timelist *next;
} *TimeList;	//Lista de timpi ai gardienilor

typedef struct  graph {
	int nr_camere;	//Numarul de camere
	List *adjLists;	//Listele de adiacenta
	TimeList *timeLists;	//Timpii gardienilor pentru fiecare camera
} *Graph;	//Graful

typedef struct vector {
	int n; //Numar elemente
	int capacitate;
	int *iesiri;
}Vector;	//Vector de intregi

void init_Vector(Vector *v, int capacitate) {
	v->n=0;
	v->capacitate=capacitate;
	v->iesiri=malloc(sizeof(int) * capacitate);
}	//Initializeaza vectorul de iesiri

void adauga_iesire_in_Vector(Vector *v, int timp_adaugat) {
	if(v->n >= v->capacitate) {
		v->capacitate=v->capacitate+1;
		v->iesiri=realloc(v->iesiri, sizeof(int) * v->capacitate);
	}
	v->iesiri[v->n]=timp_adaugat;
	v->n=v->n+1;
}	//Adauga iesirea in vectorul de iesiri

int is_in_Vector(Vector v, int room) {
	int i;
	for(i=0; i < v.n; i++)
		if(v.iesiri[i] == room)
			return 1;
	return 0;	
}	//Verifica daca room este iesire

void clear_Vector(Vector *v) {
	free(v->iesiri);
	v->n=0;
	v->capacitate=0;
} 	//Elibereaza memoria alocata vectorului

void print_Exit(Vector v, FILE *output) {
	int i;
	for(i=v.n-1; i >= 0; i--)
		fprintf(output, "%d ", v.iesiri[i]);
	fprintf(output, "\n");
}	//Afiseaza iesirile disponibile

List initList(int end, int time) {
    List new;
    new=malloc(sizeof(struct list));
    new->end=end;
    new->time=time;
    new->next=NULL;
    return new;
}   //Initializeaza lista

List addLast(List list, int end, int time) {
    List new, curent;
    if(list == NULL)
		return initList(end, time);
	new=initList(end, time);
	curent=list;
	while(curent->next != NULL)
		curent=curent->next;
	curent->next=new;
	return list;        
}	//Adauga o valoare la sfarsitul listei

List delete_From_list(List list, int end) {
	if(list->end == end) {
		List sterge=list;
		list=list->next;
		free(sterge);
		return list;
	}
	else {
		List curent=list;
		while(curent->next->end != end)
			curent=curent->next;
		List sterge=curent->next;
		curent->next=sterge->next;
		free(sterge);
		return list;
	}
}	//Sterge o valoare din lista

List freeList(List list) {
	List curent;
	if(list == NULL)
		return list;
	while(list != NULL) {
		curent=list;
		list=list->next;
		free(curent);
	}
	return NULL;
}	//Sterge lista

TimeList initTimeList(int guardian_time) {
	TimeList new;
	new=malloc(sizeof(struct timelist));
	new->guardian_time=guardian_time;
	new->next=NULL;
	return new;
}	//Initializeaza lista de timpi

TimeList addTimeLast(TimeList timelist, int guardian_time) {
	TimeList new, curent;
	if(timelist == NULL)
		return initTimeList(guardian_time);
	new=initTimeList(guardian_time);
	curent=timelist;
	while(curent->next != NULL)
		curent=curent->next;
	curent->next=new;
	return timelist;
}	//Adauga un timp la lista de timpi

TimeList freeTimeList(TimeList timelist) {
	TimeList curent;
	if(timelist == NULL)
		return timelist;
	while(timelist != NULL) {
		curent=timelist;
		timelist=timelist->next;
		free(curent);
	}
	return NULL;
}	//Sterge lista de timpi

int is_in_timelist(TimeList timelist, int timp_cautat) {
	TimeList curent=timelist;
	int ok=0;
	if(timelist == NULL)
		return 0;
	while(curent != NULL) {
		if(curent->guardian_time == timp_cautat) {
			ok=1;
			return ok;
		}
		curent=curent->next;
	}
	return ok;
}	//Verifica daca se afla timpul in lista

Graph initGraph(int nr_camere) {
	Graph nou=malloc(sizeof(struct graph));
	nou->nr_camere=nr_camere;
	nou->adjLists=malloc(sizeof(List) * nr_camere);
	nou->timeLists=malloc(sizeof(TimeList) * nr_camere);
	int i;
	for(i=0; i < nou->nr_camere; i++) {
		nou->adjLists[i]=NULL;
		nou->timeLists[i]=NULL;
	}
	return nou;
}	//Initializeaza labirintul

Graph insertEdge(Graph g, int start, int end, int time) {
	g->adjLists[start]=addLast(g->adjLists[start], end, time);
	g->adjLists[end]=addLast(g->adjLists[end], start, time);
	return g;
}	//Adauga portalul

void clear_Labirint(Graph g) {
	int i;
	for(i=0; i < g->nr_camere; i++) {
		g->adjLists[i]=freeList(g->adjLists[i]);
		g->timeLists[i]=freeTimeList(g->timeLists[i]);
	}
	free(g->adjLists);
	free(g->timeLists);
	g->adjLists=NULL;
	g->timeLists=NULL;
	free(g);
}	//Sterge labirintul

int min_time(int *times,int n,int *unvisited) {
	int i,poz_min=-1,timp_min=MARE;
	for (i=0; i < n; i++) {
		if(times[i] < timp_min && unvisited[i] == 0) {
			timp_min=times[i];
			poz_min=i;
		}
	}
	return poz_min;
}	//Returneaza timpul minim dintre camerele nevizitate

void find_Exit(Graph g, int *timpi, int *prev, int source, Vector exits) {
	int i, k;
	for(i=0; i < g->nr_camere; i++) {
		timpi[i]=MARE;	//Timpul de la source la i
		prev[i]=-1;	//Camera anterioara
	}
	timpi[source]=0;
	int *unvisited=calloc(g->nr_camere, sizeof(int));
	for(k=0; k < g->nr_camere-1; k++) {
		int u=min_time(timpi, g->nr_camere, unvisited);
		unvisited[u]=1;	//Se viziteaza camera cu timp minim
		List j;
		for(j=g->adjLists[u]; j != NULL; j=j->next) {
			int alt;
			if(is_in_Vector(exits, u) == 0) {
				while(is_in_timelist(g->timeLists[u],
					timpi[u]) == 1)	//Daca se afla un paznic in camera
					timpi[u]++;
			}	//Verific daca este iesire sau nu
			else
				goto FINISH_SEARCH;	//Am ajuns la iesire deci se opreste
			alt=timpi[u]+j->time;
			if(alt < timpi[j->end]) {
				timpi[j->end]=alt;
				prev[j->end]=u;
			}
		}
	}
	FINISH_SEARCH:free(unvisited);
}	//Returneaza caile posibile si timpii folosind Dijkstra

int minimum_time(int *times, int n) {
	int i, min_pos=-1,min=MARE;
	for(i=0; i < n; i++)
		if(times[i] < min) {
			min=times[i];
			min_pos=i;
		}
	return min_pos;	
}	//Returneaza valoarea minima dintr-un vector

int main()
{
	FILE *input=fopen("labirint.in", "r");
	FILE *output=fopen("labirint.out", "w");
	Graph labirint;
	int N, M, S, i, u, v, timp_tranzitie, pas;
	fscanf(input , "%d%d%d", &N, &M, &S);
	labirint=initGraph(N);	//Initializez labirintul
	Vector iesiri_Labirint, camere_parcurse;
	init_Vector(&camere_parcurse,1);	/*Initializez vectorul de camere
		parcurse*/
	init_Vector(&iesiri_Labirint,1);	//Initializez vectorul de iesiri
	for(i=0; i < M; i++) {
		fscanf(input, "%d%d%d", &u, &v, &timp_tranzitie);
		labirint=insertEdge(labirint, u-1, v-1, timp_tranzitie); /*Adaug portal
		intre doua camere*/
	}
	for(i=0; i < N; i++) {
		char *is_Exit=malloc(sizeof(char) * 3);
		int nr_timpi, timp_citit;
		fscanf(input, "%s%d", is_Exit, &nr_timpi);
		char decision=is_Exit[0];
		if(decision == 'Y')	//Verific daca se afla o iesire in camera citita
			adauga_iesire_in_Vector(&iesiri_Labirint, i);	/*O adaug in
			vectorul de iesiri*/
		int j;
		for(j=0; j < nr_timpi; j++) {
			fscanf(input, "%d", &timp_citit);	/*Citesc timpii in care se afla
			gardieni*/
			labirint->timeLists[i]=addTimeLast(labirint->timeLists[i],
				timp_citit);	//Ii adaug in lista de timpi ai camerei
		}
		free(is_Exit);
	}
	int *timpi=malloc(sizeof(int) * labirint->nr_camere);
	int *prev=malloc(sizeof(int) * labirint->nr_camere);
	int *timpi_parcurgere=malloc(sizeof(int) * labirint->nr_camere);
	int min_pos;
	find_Exit(labirint, timpi, prev, S-1, iesiri_Labirint);	//Generez drumurile posibile
	for(i=0; i < iesiri_Labirint.n; i++)
		timpi_parcurgere[i]=timpi[iesiri_Labirint.iesiri[i]];	/*Adaug
		timpii rezultat intr-un vector*/
	min_pos=minimum_time(timpi_parcurgere, iesiri_Labirint.n);	/*Aflu
		iesirea corespondenta timpului minim*/
	fprintf(output, "%d\n", timpi_parcurgere[min_pos]);
	pas=iesiri_Labirint.iesiri[min_pos];	/*Setez pasul initial ca fiind
		iesirea*/
	while(pas != -1) {
		adauga_iesire_in_Vector( &camere_parcurse, pas+1);
		pas=prev[pas];	//Ma duc la pasul precedent
	}
	print_Exit(camere_parcurse, output);	//Afisez pasii facuti
	clear_Labirint(labirint);
	clear_Vector(&camere_parcurse);
	clear_Vector(&iesiri_Labirint);
	free(timpi);
	free(prev);
	free(timpi_parcurgere);
	fclose(input);
	fclose(output);
	return 0;
}