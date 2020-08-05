#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct nod{
	int timestamp;
	double value;
	struct nod *next;
	struct nod *prev;
}Nod;	//Se defineste structura de lista dublu inlantuita.

typedef struct cel{
	double number;
	struct cel *urm;
}Lista;		//Se defineste structura de lista simplu inlantuita.

void addLast(Nod **head,int time,double nr){
	if(*head==NULL){ //Daca lista este nula.
		Nod *nou=malloc(sizeof(Nod));	//Se aloca memorie nodului nou.
		nou->timestamp=time;	//I se atribuie un timestamp.
		nou->value=nr;	//I se atribuie o valoare reala.
		nou->next=NULL;	//Se atribuie pointerul catre urmatorul element.
		nou->prev=NULL;	//Se atribuie pointerul catre elementul anterior.
		*head=nou;	//Pentru ca lista e goala nodul nou va fi cap de lista.
	}
	else{
		Nod *curent=*head;	//Se atribuie un nod pentru parcurgere.
		Nod *nou=malloc(sizeof(Nod));	//Se aloca memorie nodului nou.
		nou->timestamp=time;	//I se atribuie un timestamp.
		nou->value=nr;	//I se atribuie o valoare reala.
		nou->next=NULL;	//Nodul urmator va fi NULL pentru ca e ultimul element.
		while(curent->next!=NULL)	
			curent=curent->next;	//Parcurg lista pana la ultimul element.
		curent->next=nou;	//Nodul nou va fi ultimul element.
		nou->prev=curent;	//Se face legatura cu nodul anterior.
	}
}	//Adauga un nod cu informatie la sfarsitul listei.

void printL(Nod *head){
	Nod *curent=head;	//Se atribuie un pointer pentru parcurgere.
	while(curent!=NULL){
		printf("%d %.2lf\n",curent->timestamp,curent->value);
		//Se afiseaza elementul curent.
		curent=curent->next;	//Se trece la urmatorul element.
	}
}	//Afiseaza lista dublu inlantuita.

void delVal(Nod **head,double nr){
	if((*head)->value==nr){	//Daca se sterge primul element.
		Nod *temp=*head; //Se atribuie un nod auxiliar.
		*head=temp->next;	//Se atribuie noul cap de lista.
		free(temp);	//Se sterge nodul.
		(*head)->prev=NULL;	//Se atribuie legatura cu noul nod precedent.
	}
	else{
		Nod *curent=*head;	//Se atribuie un nod de parcurgere.
		while(curent->next->value!=nr)
			curent=curent->next;	//Se parcurge lista pana la nodul de sters.
		if(curent->next->value==nr){
			if(curent->next->next==NULL){	//Daca se sterge ultimul element.
				Nod *temp=curent->next; //Se atribuie un nod auxiliar.
				curent->next=NULL;	//Se refac legaturile.
				free(temp);	//Se sterge nodul.
				}
			else{
				Nod *temp=curent->next;	//Se atribuie un nod auxiliar.
				curent->next=temp->next;	//Se atribuie nodul next.
				curent->next->prev=curent;	//Se atribuie nodul prev pentru next.
				free(temp);	//Se sterge nodul.
				}
			}
		}
}	//Sterge nodul cu valoarea reala nr.

void clearL(Nod **head){
	if(*head==NULL) return; //Daca lista e nula nu e nimic de sters.
	Nod *curent=*head;	//Se atribuie un nod pentru parcurgere.
	Nod *next;	//Se declara un nod auxiliar.
	while(curent!=NULL){	
		next=curent->next;	//Nodul auxiliar pointeaza catre nodul urmator.
		curent->prev=NULL;	//Se sterge legatura anterioara pentru nodul curent.
		free(curent);	//Se sterge nodul curent.
		curent=next;	//Se trece la urmatorul nod.
	}
	*head=NULL;
}	//Sterge lista dublu inlantuita in totalitate.

int elemNr(Nod *head){
	if(head==NULL) return 0;	//Daca lista e nula nu are elemente.
	else{
		Nod *curent=head;	//Se atribuie un nod pentru parcurgere.
		int nr=1;	//Se incepe numaratoarea de la 1 deoarece exista capul.
		while(curent->next!=NULL){	
			curent=curent->next;	//Se trece la urmatorul nod.
			nr++;	//Creste contorul.
		}
	return nr;	//Returneaza numarul de elemente din lista.
	}
}	//Numara elementele dintr-o lista dublu inlantuita.

double media(Nod *head){
	if(head==NULL) return 0;	//Daca lista e nula returneaza 0.
	else{
		int nr=elemNr(head);	//Se numara elementele din lista.
		double sum=0;	//Se declara suma elementelor.
		Nod *curent=head;	//Se atribuie un nod de parcurgere.
		while(curent!=NULL){	//Cat timp se parcurge lista.
			sum=sum+curent->value;	//Se adauga valoarea lui 'curent' in suma.
			curent=curent->next;	//Se trece la urmatorul nod.
		}
		double medie=(double)sum/nr;	//Se calculeaza media aritmetica.
		return medie;	//Returneaza media aritmetica.
	}
}	//Calculeaza media aritmetica unei liste dublu inlantuite.

double deviatia(Nod *head){
	Nod *curent=head;	//Se atribuie un nod de parcurgere.
	double deviatie,sum=0;	//Se declara deviatia si suma elementelor.
	int nr=elemNr(head);	//Se numara elementele listei.
	if(head==NULL) return 0;	//Daca lista este goala returneaza 0.
	while(curent!=NULL){	//Cat timp se parcurge lista.
		double a=curent->value;	//Se declara a=valoarea nodului 'curent'.
		a=a-media(head);	//Se scade din a media aritmetica a listei.
		sum=sum+powf(a,2);	//Se adauga patratul lui a modificat in suma.
		curent=curent->next;	//Se trece la urmatorul nod.
	}
	deviatie=(double)sum/nr;	//Se imparte deviatia la numarul de elemente.
	deviatie=sqrt(deviatie);	//Se scoate radicalul din deviatie.
	return deviatie;	//Se returneaza deviatia listei.
}	//Calculeaza deviatia unei liste dublu inlantuite.

void insLast(Lista **cap,double nr){
	if(*cap==NULL){	//Daca lista este nula.
		Lista *nou=malloc(sizeof(Lista));	//Se aloca memorie nodului nou.
		nou->number=nr;	//I se atribuie o valoare reala nodului.
		nou->urm=NULL;	//Se face legatura urmatoare cu nodul NULL.
		*cap=nou;	//Nodul 'nou' va fi capul listei.
	}
	else{
		Lista *nou=malloc(sizeof(Lista));	//Se aloca memorie nodului nou.
		Lista *curent=*cap;	//Se atribuie un nod de parcurgere.
		nou->number=nr;	//I se atribuie o valoare reala nodului.
		nou->urm=NULL;	//Se face legatura urmatoare cu nodul NULL.
		while(curent->urm!=NULL)
			curent=curent->urm;	//Se parcurge lista pana la ultimul element.
		curent->urm=nou;	//Ultimul element va deveni nodul 'nou'.
	}
}	//Adauga un element la finalul listei simplu inlantuite.

void removeL(Lista **cap){
	Lista * curent=*cap;	//Se atribuie un nod de parcurgere.
	Lista * next;	//Se declara un nod auxiliar.
	while(curent!=NULL){
		next=curent->urm;	//Nodul auxiliar va fi nodul urmator celui curent.
		free(curent);	//Se sterge nodul curent.
		curent=next;	//Se trece la urmatorul nod.
	}
	*cap=NULL;
}	//Sterge lista simplu inlantuita.

void sortL(Lista *cap){
	Lista *i,*j;	//Se declara doua noduri 'contor' pentru parcurgere.
	double aux;	//Se declara o valoare auxiliara.
	i=cap;	//Lui 'i' i se atribuie capul listei.
	while(i->urm!=NULL){
		j=i->urm;	//j va fi nodul urmator al lui i.
		while(j!=NULL){
			if((i->number) >(j->number)){	//Daca nodul departat e mai mic.
				aux=i->number;
				i->number=j->number;
				j->number=aux;
			}	//Se interschimba valorile lui 'i' si 'j'.
			j=j->urm;	//j trece la nodul urmator.
		}
		i=i->urm;	//i trece la nodul urmator.
	}
}	//Sorteaza crescator lista simplu inlantuita.

void exceptions(Nod **head){
	Nod *win=NULL;	//Se declara o fereastra (lista dublu inlantuita).
	Nod *curent=*head;	//Se atribuie un nod de parcurgere.
	Lista * de_sters=NULL;	//Se declara un nod de lista simplu inlantuita.
	curent=curent->next->next;	//Se trece la al 3-lea element din lista dubla.
	while(curent->next->next!=NULL &&curent->next!=NULL){
		addLast(&win,curent->prev->prev->timestamp,curent->
			prev->prev->value); //Se adauga	nodul cu doua pozitii anterioare.
		addLast(&win,curent->prev->timestamp,curent->prev->
			value);	//Se adauga nodul anterior.
		addLast(&win,curent->timestamp,curent->value);	//Se adauga nodul curent.
		addLast(&win,curent->next->timestamp,curent->next->
			value);	//Se adauga nodul urmator.
		addLast(&win,curent->next->next->timestamp,curent->
			next->next->value);	//Se adauga nodul cu doua pozitii urmatoare.
		//Prin aceste adaugari se formeaza fereastra de valori in jurul nodului.
		double medie=media(win);	//Se calculeaza media ferestrei.
		double deviatie=deviatia(win);	//Se calculeaza deviatia ferestrei.
		double x=curent->value;	//I se atribuie lui x valoarea nodului curent.
		if(x<(medie-deviatie) || x>(medie+deviatie))	//Daca x e exceptie
				insLast(&de_sters,x);	//Se adauga la lista de sters.
			curent=curent->next;	//Se trece la nodul urmator.
			clearL(&win);	//Se sterge fereastra.
		}
	Lista *act=de_sters;	//Se atribuie un nod de parcurgere.
	while(act!=NULL){
		delVal(head,act->number);	//Se sterge exceptia din lista initiala.
		act=act->urm;	//Se trece la urmatorul nod.
		}	//Se sterg toate valorile care trebuie sterse din lista.
	removeL(&de_sters);	//Se sterge fereastra cu exceptii.
} 	//Sterge exceptiile dintr-o lista data.

void mediana(Nod **head){
	Lista *win=NULL;	//Se declara o fereastra (lista simplu inlantuita).
	Nod *mediane=NULL;	//Se declara lista de mediane.
	Nod *curent=*head;	//Se atribuie un nod de parcuregere.
	curent=curent->next->next;	//Se trece la al 3-lea element din lista.
	while(curent->next->next!=NULL && curent->next!=NULL){
		insLast(&win,curent->prev->prev->value);	 	
		insLast(&win,curent->prev->value);
		insLast(&win,curent->value);
		insLast(&win,curent->next->value);
		insLast(&win,curent->next->next->value);
		//Se formeaza fereastra cu valori reale in jurul nodului curent.
		sortL(win);	//Se sorteaza valorile.
		addLast(&mediane,curent->timestamp,win->urm->urm->number);
		//Se adauga elementul median in lista de mediane.
		removeL(&win);	//Se sterge fereastra.
		curent=curent->next;	//Se trece la nodul urmator.
	}
	clearL(head);	//Se sterge lista initiala.
	curent=mediane;	//Se incepe parcurgerea listei de mediane.
	while(curent!=NULL){
		addLast(head,curent->timestamp,curent->value); //Se adauga mediana.
		curent=curent->next;	//Se trece la urmatoarea mediana.
	}
	clearL(&mediane);	//Se sterge lista de mediane.
}	//Face filtrarea folosind elementele mediane.

void medii_aritmetice(Nod **head){
	Nod *win=NULL;	//Se declara fereastra.
	Nod *medii=NULL;	//Se declara lista de medii aritmetice.
	Nod *curent=*head;	//Se atribuie un nod de parcurgere.
	curent=curent->next->next;	//Se trece la al 3-lea element din lista.
	while(curent->next->next!=NULL && curent->next!=NULL){
		//Fereastra se formeaza la fel ca in functia exceptions.
		addLast(&win,curent->prev->prev->timestamp,curent->
			prev->prev->value);
		addLast(&win,curent->prev->timestamp,curent->prev->
			value);
		addLast(&win,curent->timestamp,curent->value);
		addLast(&win,curent->next->timestamp,curent->next->
			value);
		addLast(&win,curent->next->next->timestamp,curent->
			next->next->value);
		//Prin aceste adaugari se formeaza fereastra de valori in jurul nodului.
		double medie=media(win);	//Se calculeaza media ferestrei.
		addLast(&medii,curent->timestamp,medie);	//Se adauga media in lista.
		clearL(&win);	//Se sterge fereastra.
		curent=curent->next;	//Se trece la urmatorul nod.
	}
	clearL(head);	//Se sterge lista initiala.
	curent=medii;	//Se incepe parcurgerea listei de medii.
	while(curent!=NULL){
		addLast(head,curent->timestamp,curent->value);	//Se adauga media.
		curent=curent->next;	//Se trece la urmatoarea medie.
	}
	clearL(&medii);	//Se sterge lista de medii.
}	//Face filtrarea folosind media aritmetica.

void uniformizare(Nod *head){
	Nod *curent=head;	//Se atribuie un nod de parcurgere.
	curent=curent->next;	//Se trece la al 2-lea element din lista.
	while(curent!=NULL){
		double d=(curent->timestamp)-(curent->prev->timestamp);	
		//Se calculeaza diferenta de timestampuri intre doua noduri vecine.
		if(d>=100 && d<=1000){	//Daca diferenta nu este in interval.
			curent->timestamp=((curent->timestamp)+(curent->prev->timestamp))/2;
			//Noul timestamp va fi media timestampului lui 'prev' si 'curent'.
			curent->value=((curent->value)+(curent->prev->value))/2;
			//Noua valoare va fi media valorilor lui 'prev' si 'curent'.
		}
		curent=curent->next;	//Se trece la nodul urmator.
	}
}	//Uniformizeaza lista data folosind media vecinilor.

int extract_number(char *sir){
	int i,num=0;	//Se declara un contor i si num(numarul din sir).
	for(i=0;i<strlen(sir);i++)	//Se parcurge sirul de caractere.
		if(sir[i]>='0' && sir[i]<='9')	//Daca este gasita o cifra.
			num=num*10+(sir[i]-'0');	//Cifra se va adauga la numar.
	return num;	//Se returneaza numarul din sirul de caractere.
}	//Extrage un numar dintr-un sir de caractere.

int interval(double nr,int left,int right){
	if(nr>=left && nr<=right) return 1;	//1 daca nr se afla in interval.
	else return 0;	//0 daca nr nu se afla in interval.
}	//Verifica daca numarul nr se afla in [left,right].

double wi(int i){
	int j;	//Se declara un contor.
	double nr,numarator,numitor=0;	//Se declara niste valori reale.
	numarator=(double)i/2;	//Se calculeaza numaratorul fractiei.
	numarator=pow(numarator,2)*0.9+0.1; //Se actualizeaza numaratorul.
	for ( j= 0; j<=2;j++)
	{	
		nr=j/2.0f;	//Se calculeaza j/2.
		nr=pow(nr,2)*0.9+0.1;	//Se calculeaza nr^2*0.9+0.1.
		numitor=numitor+nr;	//Se adauga nr obtinut la numitor.
	}		
	return numarator/numitor;	//Se returneaza coeficientul wi.
}	//Calculeaza coeficientul wi.

double leftSum(Nod *left){
	double sum=0;	//Se declara suma.
	Nod *curent=left;	//Se atribuie un nod de parcurgere.
	int i;	//Se declara un contor.
	for(i=0;i<=2;i++){	
		double nr=(double)((curent->value)*wi(i));
		//Valoarea curenta se inmulteste cu wi in folosind distanta de interval.
		sum=sum+nr;	//Se adauga rezultatul la suma.
		curent=curent->next;	//Se trece la urmatorul nod.
	}
	return sum;	//Se returneaza suma.
}	//Calculeaza suma lui left.

double rightSum(Nod *right){
	double sum=0;	//Se declara suma.
	int i;	//Se declara un contor.
	Nod *curent=right;	//Se atribuie un nod de parcurgere.
	for (i = 2; i >= 0;i--){
		double nr=(double)((curent->value)*wi(i));
		//Valoarea curenta se inmulteste cu wi in folosind distanta de interval.
		sum=sum+nr;	//Se adauga rezultatul la suma.
		curent=curent->next;	//Se trece la urmatorul nod.
	}
	return sum;	//Se returneaza suma.
}	//Calculeaza suma lui right.

void completare(Nod *head){
	Nod *curent=head;	//Se atribuie un nod de parcurgere.
	Nod *left=NULL;	//Se declara fereastra left.
	Nod *right=NULL;	//Se declara fereastra right.
	curent=curent->next->next;	//Se trece la al 3-lea nod.
	while(curent->next!=NULL){
		if((curent->next->timestamp)-(curent->timestamp)<=1000)
			//Daca diferenta intre doua timestampuri <=1 secunda.
			curent=curent->next;	//Se trece la nodul urmator.
		else{
			int capat=curent->next->timestamp;	//Capatul mare al intervalului.
			addLast(&left,curent->prev->prev->timestamp,
				curent->prev->prev->value);	//Adauga nodul prev->prev in left.
			addLast(&left,curent->prev->timestamp,
				curent->prev->value);	//Adauga nodul prev in left.
			addLast(&left,curent->timestamp,curent->value);	
			//Adauga nodul curent in left.
			addLast(&right,curent->next->timestamp,
				curent->next->value);	//Adauga nodul next in right.
			addLast(&right,curent->next->next->timestamp,
				curent->next->next->value);	//Adauga nodul next->next in right.
			addLast(&right,curent->next->next->next->timestamp,
				curent->next->next->next->value);
			//Adauga nodul next->next->next in right.
			while((curent->timestamp)<capat-200){
				int timestamp_new=(curent->timestamp)+200;
				//Se calculeaza timestampul cu care se completeaza.
				double C=(double)(timestamp_new-(left->next->next->timestamp));
				//Calculeaza factorul de scalare C.
				C=(double)C/((right->timestamp)-(left->next->next->timestamp));
				//Actualizeaza factorul de scalara C.
				double new_val=((1-C)*(leftSum(left)))+(C*(rightSum(right)));
				//Calculeaza valoarea cu care se va completa.
				Nod *nou=malloc(sizeof(Nod));	//Aloca memorie pentru 'nou'.
				nou->value=new_val;	//Se adauga noua valoare in 'nou'.
				nou->timestamp=timestamp_new;	//Adauga timestampul in 'nou'.
				nou->next=curent->next;	//Se face legatura cu next.
				curent->next->prev=nou;	//Se face legatura prev pentru next.
				curent->next=nou;	//Se face legatura next pentru prev.
				nou->prev=curent;	//Se face legatura cu prev.
				curent=curent->next;	//Se trece la nodul urmator.
			} 	
			clearL(&left);	//Se sterge fereastra left.
			clearL(&right);	//Se sterge fereastra right.
		}
	}
}	//Completeaza lista data daca sunt intervale lipsa prea mari.

void stats(Nod *head,int period){
	Lista *valori=NULL;	//Se declara lista de valori.
	Nod *curent=head;	//Se atribuie un nod de parcurgere.
	while(curent!=NULL){
		insLast(&valori,curent->value);	//Se introduce valoarea in lista.
		curent=curent->next;	//Se trece la urmatorul nod.
	}
	sortL(valori);	//Se sorteaza valorile.
	int contor=round(valori->number),nr=0,mod=contor%period;
	Lista *camp=valori;	//Se atribuie un nod de parcurgere.
	if(contor<0) contor=contor-(period+mod);	//Calculeaza capatul mic.(<0)
	else contor=contor-mod;	//Calculeaza capatul mic.(>0)
	while(camp!=NULL){
		if(interval(camp->number,contor,contor+period)==1){
			//Daca valoarea se afla in interval.
			nr++;	//Creste numarul de elemente.
			if(camp->urm==NULL){	//Daca se termina valorile.
				printf("[%d, %d] %d\n",contor,contor+period,nr);
				//Se afiseaza intervalul si numarul de elemente.
				removeL(&valori);	//Sterge lista de valori.
				return;	//Se opreste functia.
			}
			else camp=camp->urm;	//Se trece la nodul urmator.
		}
		else{	//Daca valoare nu se afla in interval.
			if(nr>0){	
				printf("[%d, %d] %d\n",contor,contor+period,nr);
				//Se afiseaza intervalul si numarul de elemente,daca are ce.
				nr=0;	//Se reseteaza numarul.
				contor=contor+period;	//Se creste intervalul.
			}	
			else contor=contor+period;	//Se creste intervalul.
		}
	}
}	//Afiseaza intervalele din perioada in perioada si numarul de elemente.

int main(int argc, char *argv[])
{	int i,nr,timp,j;	
	double real;
	Nod *list=NULL;	//Se declara lista initiala.
	scanf("%d",&nr);	//Se citeste numarul de elemente.
	for(i=0;i<nr;i++){
		scanf("%d%lf",&timp,&real);	//Se citesc timestampul si valoarea.
		addLast(&list,timp,real);	//Se adauga timestampul si valoarea in lista.
	}
	for(j=0;j<argc;j++){	//Se parcurg argumentele din linia de comanda.
		if(strcmp(argv[j],"--e1")==0)	
		{
			exceptions(&list);	//Se elimina exceptiile din lista.
			if(j==argc-1){	//Daca e ultimul argument.
				printf("%d\n",elemNr(list));	//Afiseaza numarul de elemente.
				printL(list);	//Afiseaza lista.
			}
		}
		else if(strcmp(argv[j],"--e2")==0){
			mediana(&list);	//Se calculeaza elementele mediane.
			if(j==argc-1){	//Daca e ultimul argument.
				printf("%d\n",elemNr(list));	//Afiseaza numarul de elemente.	
				printL(list);	//Afiseaza lista.
			}
		}
		else if(strcmp(argv[j],"--e3")==0){
			medii_aritmetice(&list);	//Se calculeaza mediile.
			if(j==argc-1){	//Daca e ultimul argument.
				printf("%d\n",elemNr(list));	//Afiseaza numarul de elemente.
				printL(list);	//Afiseaza lista.
			}	
		}
		else if(strcmp(argv[j],"--u")==0){
			uniformizare(list);	//Se uniformizeaza lista.
			if(j==argc-1){	//Daca e ultimul argument.
				printf("%d\n",elemNr(list));	//Afiseaza numarul de elemente.
				printL(list);	//Afiseaza lista.
			}
		}
		else if(strcmp(argv[j],"--c")==0){
			completare(list);	//Se completeaza lista.
			if(j==argc-1){	//Daca e ultimul argument.
				printf("%d\n",elemNr(list));	//Afiseaza numarul de elemente.
				printL(list);	//Afiseaza lista.
			}
		}
		else if(strstr(argv[j],"--st")!=NULL){
			int period=extract_number(argv[j]);	//Extrage perioada din argument.
			stats(list,period);	//Afiseaza intervalele si numarul de elemente.
		}
	}
	clearL(&list);	//Se sterge lista.
	return 0;
}