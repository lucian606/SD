#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct memorie {
	char *adresa;
	struct memorie *next_adr;
}Adrese;	//Memoria de adrese

typedef struct nod {
	int id;
	int parent_id;
	Adrese *adrese;
	struct nod *first_child;
	struct nod *next_child;
}tree;	//Structura unui nod din retea

typedef struct node {
	int id;
	int parent_id;
	Adrese *adrese;
	struct node *next_input;
}input;	//Structura unui nod din lista de inputuri

typedef struct user {
	int user_id;
	int server_id;
	struct user *next_user;
}User;	//Structura unui utilizator

User *initUser(int user_id, int server_id) {
	User *nou=malloc(sizeof(struct user));
	nou->user_id=user_id;
	nou->server_id=server_id;
	nou->next_user=NULL;
	return nou;
}	//Initializeaza lista de utilizatori

User *addUser(User *utilizatori, int user_id, int server_id) {
	if(utilizatori == NULL)
		return initUser(user_id, server_id);
	else {
		User *curent=utilizatori;
		while(curent->next_user != NULL)
			curent=curent->next_user;
		User *nou=initUser(user_id, server_id);
		curent->next_user=nou;
		return utilizatori;
	}
}	//Adauga utilizatorul in lista de utilizatori

User *findUser(User *utilizatori, int user_id) {
	if(utilizatori->user_id == user_id)
		return utilizatori;
	else {
		User *curent=utilizatori;
		while(curent->user_id != user_id && curent->next_user != NULL)
			curent=curent->next_user;
		return curent;
	}
}	//Cauta utilizatorul cu un anumit id

User *findServer(User *utilizatori, int server_id) {
	if(utilizatori->server_id == server_id)
		return utilizatori;
	else {
		User *curent=utilizatori;
		while(curent->server_id != server_id && curent->next_user != NULL)
			curent=curent->next_user;
		return curent;
	}
}	//Cauta utilizatorul conecta la un server

void addAdr(Adrese **adrese, char *adresa) {
	if((*adrese) == NULL) {
		Adrese *nou=(Adrese *)malloc(sizeof(struct memorie));
		nou->adresa=malloc(sizeof(char) *(strlen(adresa)+1));
		strcpy(nou->adresa, adresa);
		nou->next_adr=NULL;
		*adrese=nou;
	}
	else {
		Adrese *curent;
		curent=*adrese;
		while(curent->next_adr != NULL)
			curent=curent->next_adr;
		Adrese *nou=malloc(sizeof(struct memorie));
		nou->adresa=malloc(sizeof(char) *(strlen(adresa)+1));
		strcpy(nou->adresa, adresa);
		nou->next_adr=NULL;
		curent->next_adr=nou;
	}
}	//Adauga o adresa in lista de adrese

void printAdr(Adrese *adrese, FILE *fisier) {
	if(adrese == NULL)
		return;
	fprintf(fisier, "%s", adrese->adresa);
	Adrese *curent=adrese->next_adr;
	while(curent != NULL) {
		fprintf(fisier, " %s", curent->adresa);
		curent=curent->next_adr;
	}
}	//Afiseaza lista de adrese

void clearAdr(Adrese **adrese) {
	if(adrese == NULL) return;
	Adrese *curent=*adrese;
	Adrese *urm;
	while(curent != NULL) {
		urm=curent->next_adr;
		free(curent->adresa);
		free(curent);
		curent=urm;
	}
	*adrese=NULL;
}	//Sterge lista de adrese

int search(Adrese *adrese, char *adresa) {
	if(adrese == NULL) return 0;
	else {
		if(strcmp(adrese->adresa, adresa) == 0)
			return 1;
		else
			return search(adrese->next_adr, adresa);
	}
}	//Cauta o adresa in lista de adrese

tree *initTree(int id, int parent_id, Adrese *adrese) {
	tree *nou=malloc(sizeof(struct nod));
	nou->id=id;
	nou->parent_id=parent_id;
	nou->adrese=NULL;
	Adrese *curent=adrese;
	while(curent!=NULL) {
		addAdr(&nou->adrese, curent->adresa);
		curent=curent->next_adr;
	}
	nou->first_child=NULL;
	nou->next_child=NULL;
	return nou;
}	//Initializeaza arborele retelei

void addNod(tree *retea, int id, int parent_id, Adrese *adrese) {
	if(retea == NULL)
		return;
	if(retea->id == parent_id) {
		tree *fiu=retea->first_child;
		if(fiu == NULL) retea->first_child=initTree(id, parent_id, adrese);
		else {
			while(fiu->next_child != NULL)
				fiu=fiu->next_child;
			tree *nou=initTree(id, parent_id, adrese);
			fiu->next_child=nou;
		}
		return;
	}
	tree *aux;
	for(aux=retea->first_child; aux!=NULL; aux=aux->next_child)
		addNod(aux, id, parent_id, adrese);
	return;
}	//Adauga un nod in arborele reteli

void printTree(tree * retea, FILE *fisier){
	if(retea == NULL)
		return;
	fprintf(fisier, "%d ", retea->id);
	printAdr(retea->adrese, fisier);
	fprintf(fisier, "\n");
	tree *aux;
	for(aux=retea->first_child; aux!=NULL; aux=aux->next_child)
		printTree(aux, fisier);
}	//Afiseaza id-ul serverelor din retea si adresele lor in fisier

void Root_and_children(tree *retea, FILE *fisier) {
	if(retea == NULL)
		return;
	fprintf(fisier, "%d", retea->id );
	tree *copil;
	for(copil=retea->first_child; copil!=NULL; copil=copil->next_child)
		fprintf(fisier, " %d", copil->id );
	fprintf(fisier, "\n");
	for(copil=retea->first_child; copil!=NULL; copil=copil->next_child)
		Root_and_children(copil, fisier);
}	//Afiseaza id-ul serverelor din retea si id-ul fiilor in fisier

input *initInput(int id, int parent_id, Adrese *adrese) {
	input *nou=malloc(sizeof(struct node));
	nou->id=id;
	nou->parent_id=parent_id;
	Adrese *curent=adrese;
	while(curent!=NULL) {
		addAdr(&nou->adrese, curent->adresa);
		curent=curent->next_adr;
	}
	nou->next_input=NULL;
	return nou;	
}	//Initializeaza lista de inputuri

input *addInput(input *input_list, int id, int parent_id, Adrese *adrese) {
	input *nou=initInput(id, parent_id, adrese);
	if(input_list == NULL)
		return nou;
	else {
		input *curent=input_list;
		while (curent->next_input != NULL)
			curent=curent->next_input;
		curent->next_input=nou;
		return input_list;
	}
}	//Adauga inputul in lista

void search_id(tree *retea, int id, int *ok) {
	if(retea == NULL)
		return;
	if(retea->id == id) {
		*ok=1;
		return;
	}
	else {
		tree *aux;
		for(aux=retea->first_child; aux!=NULL; aux=aux->next_child)
			search_id(aux, id, ok);
	}
}	//Verifica daca exista serverul cu un anumit id in retea

input *deleteInput(input *input_list, int id) {
	if(input_list == NULL)
		return NULL;
	if(input_list->id == id) {
		input *sters=input_list;
		input_list=sters->next_input;
		clearAdr(&sters->adrese);
		sters->next_input=NULL;
		free(sters);
	}
	else {	
		input *curent=input_list;
		while(curent->next_input->id != id)
			curent=curent->next_input;
		input *sters=curent->next_input;
		curent->next_input=sters->next_input;
		clearAdr(&sters->adrese);
		sters->next_input=NULL;
		free(sters);
	}
		return input_list;
}	//Sterge inputul din lista

void initializare_ierarhie(tree *retea) {
	if (retea == NULL)
		return;
	tree *copil;
	for(copil=retea->first_child; copil != NULL; copil=copil->next_child) {
		initializare_ierarhie(copil);
		Adrese *curent;
		for (curent=copil->adrese; curent != NULL; curent=curent->next_adr) {
			if(search(retea->adrese, curent->adresa) == 0)
			addAdr(&retea->adrese, curent->adresa);
		}
	}
}	//Initializeaza ierarhia din retea

void delete_Tree(tree *retea) {
	if (retea == NULL)
		return;
	tree *copil;
	for(copil=retea->first_child; copil != NULL; copil=copil->next_child) {
		delete_Tree(copil);
		clearAdr(&copil->adrese);
		copil->first_child=NULL;
		free(copil);
	}
}	//Sterge tot arborele retelei mai putin radacina

void parent_node(tree *retea, tree **parent, int id) {
	if (retea == NULL)
		return;
	tree *copil;
	for(copil=retea->first_child; copil != NULL; copil=copil->next_child) {
		if (copil->id == id) {
			*parent=retea;
			return;
		}
		else parent_node(copil, parent, id);
	}
}	//Gaseste parintele serverului cu un anumit id

void find_id(tree *retea, tree **found, int id) {
	if (retea == NULL)
		return;
	if (retea->id == id) {
		*found=retea;
		return;
	}
	tree *copil;
	for(copil=retea->first_child; copil != NULL; copil=copil->next_child) {
		find_id(copil,found,id);
	}
}	//Gaseste serverul cu un anumit id

void resolve_queries(tree *retea, int server_id, char *adresa_cautata, 
FILE *users_out) {
	tree *server_conectat=NULL;
	find_id(retea, &server_conectat, server_id);
	if(server_conectat == NULL)
		return;
	if(search(server_conectat->adrese, adresa_cautata) == 1) {
		fprintf(users_out, "%d\n", server_conectat->id);
		return;
	}
	else {
		tree *curent=server_conectat;
		while(search(curent->adrese, adresa_cautata) == 0) {
			fprintf(users_out, "%d ", curent->id);
			addAdr(&curent->adrese, adresa_cautata);
			parent_node(retea, &curent, curent->id);
		}
		fprintf(users_out, "%d\n", curent->id );
	}
}	//Rezolva cererile utilizatorilor

void server_defection(tree *retea, int server_id, User *utilizatori) {
	tree *broken_server=NULL;
	find_id(retea, &broken_server, server_id);	//Se gaseste serverul defect
	if(broken_server == NULL)
		return;
	else {
		tree *new_server=NULL;
		parent_node(retea, &new_server, server_id);
		tree *new_server_son=new_server->first_child;
		while(new_server_son->next_child != NULL)
			new_server_son=new_server_son->next_child;
		User *curent_user;
		for(curent_user=utilizatori; curent_user != NULL;
			curent_user=curent_user->next_user) {
			if(curent_user->server_id == server_id) 
				curent_user->server_id=new_server->id;
		}	//Se schimba serverul utilizatorilor conectati
		tree *broken_son=broken_server->first_child;
		if(broken_son != NULL) {
			new_server_son->next_child=malloc(sizeof(struct nod));
			new_server_son->next_child=broken_son;
		}	//Se adauga primul copil al serverului defect in lista de fii
		new_server_son=new_server->first_child;
		if(new_server_son->id == server_id) {
			tree *next=new_server_son->next_child;
			new_server_son->first_child=NULL;
			clearAdr(&new_server_son->adrese);
			free(new_server_son);
			new_server_son=next;
		}	//Se sterge serverul defect din retea
	}
}	//Sterge serverul defect din ierarhie

void clear_Users(User **utilizatori) {
	if(*utilizatori == NULL) return;
	User *curent=*utilizatori;
	User *urm;
	while(curent != NULL) {
		urm=curent->next_user;
		free(curent);
		curent=urm;
	}
	*utilizatori=NULL;
}	//Sterge lista de utilizatori

int main() 
{	int i,j,n,m,id,parent_id,nr_users,nr_queries,user_id,server_id,broken_id;
	FILE *tree_input=fopen("tree.in","r");
	FILE *tree_output=fopen("tree.out","w");
	FILE *ierarhie=fopen("hierarchy.out","w");
	FILE *utilizatori=fopen("users.in","r");
	FILE *queries=fopen("queries.in","r");
	FILE *users_out=fopen("queries.out","w");
	//S-au deschis fisierele de input si output
	User *conected_users=NULL;	
	if(tree_input == NULL) {
		fclose(tree_output);
		fclose(ierarhie);
	}
	if(utilizatori == NULL || queries == NULL) {
		fclose(users_out);
	}
	fscanf(tree_input,"%d",&n);
	Adrese *adrese=NULL;	
	input *input_list=NULL;
	for(i=0; i<n; i++) {
		fscanf(tree_input, "%d%d%d", &id, &parent_id, &m);
		adrese=NULL;
		input_list=addInput(input_list, id, parent_id, adrese);
		input *curent_input=input_list;
		while(curent_input->next_input != NULL)
			curent_input=curent_input->next_input;
		curent_input->adrese=NULL;
		for(j=0; j<m; j++) {
			char *adresa_citita=malloc(sizeof(char)*15);
			fscanf(tree_input, "%s", adresa_citita);
			addAdr(&(curent_input->adrese), adresa_citita);
			free(adresa_citita);
		}	
	}	//Se adauga nodurile intr-o lista de inputuri
	clearAdr(&adrese);
	tree *retea=NULL;
	retea=initTree(input_list->id, input_list->parent_id, input_list->adrese);
	input_list=deleteInput(input_list, input_list->id); //Se sterge primul nod
	input *aux=NULL;
	while(input_list != NULL) {
		for(aux=input_list; aux != NULL; aux=aux->next_input) {
			addNod(retea, aux->id, aux->parent_id, aux->adrese);
			int ok=0;
			search_id(retea, aux->id, &ok);
			if(ok == 1)
				input_list=deleteInput(input_list, aux->id);
			//Nodul a fost inserat cu succes in arbore
		}
		aux=input_list;	//Se incepe o alta parcuregere a listei
	}	//Lista se parcurge pana cand au fost sterse toate nodurile
	Root_and_children(retea, tree_output);
	initializare_ierarhie(retea);
	printTree(retea, ierarhie);
	fscanf(utilizatori, "%d", &nr_users);
	for(i=0; i<nr_users; i++) {
		fscanf(utilizatori, "%d%d", &user_id, &server_id);
		conected_users=addUser(conected_users, user_id, server_id);
		//Se adauga utilizatorii in list de utilizatori
	}
	fscanf(queries, "%d", &nr_queries);
	for(i=0; i<nr_queries; i++) {
		char *comand,*adr;
		comand=malloc(sizeof(char)*1);
		adr=malloc(sizeof(char)*15);
		int id_user_request;
		fscanf(queries, "%s", comand);
		if(comand[0]=='q') {
			fscanf(queries, "%d%s", &id_user_request, adr);
			User *user_query=findUser(conected_users, id_user_request);
			resolve_queries(retea, user_query->server_id, adr, users_out);
		}
		else if(comand[0]== 'f') {
			fscanf(queries, "%d", &broken_id);
			server_defection(retea, broken_id,conected_users);
		}
		free(adr);
		free(comand);
	}
	delete_Tree(retea);
	clearAdr(&retea->adrese);
	free(retea);
	retea=NULL;
	clear_Users(&conected_users);
	fclose(tree_input);
	fclose(tree_output);
	fclose(ierarhie);
	fclose(utilizatori);
	fclose(queries);
	fclose(users_out);
	return 0;
}