314CC Iliescu Lucian-Marius

In rezolvarea temei s-au folosit doua tipuri de liste:
-Nod (lista dublu inlantuita cu perechea timestamp si valoare reala);
-Lista (lista simplu inlantuita cu valori reale).

S-au utilizat diferite functii in rezolvarea temei:
-Operatii de baza cu liste:
	-addLast (adaugarea la sfarsitul unei liste dublu inlantuite);
	-printL (afisarea unei liste dublu inlantuite);
	-delVal	(stergerea unui nod cu o valoare din lista dublu inlantuita);
	-clearL	(stergerea unei liste dublu inlantuite);
	-elemNr (numara elementele dintr-o lista dublu inlantuita);
	-insLast (adaugarea la sfarsitul unei liste simplu inlantuite);
	-removeL (stergerea unei liste simplu inlantuite);
-Functii necesare in rezolvarea cerintelor:
 	-sortL (sortarea unei liste simplu inlantuite);		
		Mod de functionare:
		1)Se aleg doi pointeri i si j,i se va afla pe pozitie mai mica decat j.
		2)Se incepe cu i de la capul listei si cu j de la i->urm,pana la capat.
		3)Daca valoarea lui j este mai mica decat cea a lui i se interschimba.
		4)Cand j a ajuns la final,i va fi i->urm.
		5)Se repeta 3,4 pana cand i pointeaza ultimul element din lista.
		6)Lista este sortata.
	-media (media aritmetica a unei liste dublu inlantuite);
		Mod de functionare:
		1)Se ia o variabila suma=0.
		2)Se aduna valoarea nodului curent la suma.
		3)Se trece la nodul urmator.
		4)Se repeta 2,3 pana cand se termina lista.
		5)Se imparte suma la numarul de elemente din liste.
	-deviatia (calculeaza deviatia unei liste dublu inlantuite);
		Mod de functionare:
		1)Se ia o variabila suma=0.
		2)Se scade din valoarea nodului curent media listei.
		3)Se ridica la patrat rezultatul si se adauga la suma.
		4)Se repeta 2,3 pana cand se termina lista.
		5)Se imparte suma la numarul de elemente si se scoate radicalul.
	-exceptions (elimina exceptiile din lista dubla inlantuita);
		Mod de functionare:
		1)Se incepe de la al 3-lea element al listei.
		2)Se adauga cele doua noduri anterioare si urmatoare si se face lista.
		3)Se calculeaza media ferestrei.
		4)Se calculeaza deviatia ferestrei.
		5)Daca valoarea nodului nu se afla in [medie-dev,medie+dev]
		se adauga in lista de_sters.
		6)Se trece la nodul urmator.
		7)Se repeta 2,3,4,5,6 pana cand am ajuns la penultimul nod.
		8)Se parcurge lista de_sters si sterg valorile din lista initiala
		folosind delVal.
	-mediana (filtrare cu elemente mediane);
		Mod de functionare:
		1)Se incepe de la al 3-lea element al listei.
		2)Se adauga cele doua noduri anterioare si urmatoare si se face lista.
		3)Se sorteaza fereastra.
		4)Se adauga elementul de pe pozitia mijlocie in lista de mediane.
		5)Se trece la nodul urmator.
		6)Se repeta 2,3,4,5 pana cand am ajuns la penultimul nod.
		7)Se sterge lista initiala.
		8)Se adauga elementele din mediane in lista initiala.
	-medii_aritmetice (filtrarea cu media aritmetica);
		Mod de functionare:
		1)Se incepe de la al 3-lea element al listei.
		2)Se adauga cele doua noduri anterioare si urmatoare si se face lista.
		3)Se calculeaza media aritmetica a ferestrei.
		4)Se adauga media in lista de medii.
		5)Se trece la nodul urmator.
		6)Se repeta 2,3,4,5 pana cand am ajuns la penultimul nod.
		7)Se sterge lista initiala.
		8)Se adauga elementele din medii in lista initiala.
	-uniformizare (uniformizeaza lista);
		Mod de functionare:
		1)Se incepe de la al 2-lea element al listei.
		2)Se face diferenta cu timestampul nodului anterior.
		3)Daca diferenta e in [100,1000] atunci:
		-timestampul lui curent va fi (timestamp prev+timestamp curent)/2;
		-valoarea lui curent va fi (valoare prev+valoare curent)/2;
		4)Se trece la nodul urmator.
		5)Se repeta 2,3,4 pana cand am ajuns la ultimul nod.
	-wi (returneaza valoare lui w(i,3));
	-leftSum (face suma pentru intervalul stang);
		1)Se initializeaza suma=0;
		2)Se ia un contor i=0;
		3)Se inmulteste valoarea lui curent cu w(i,3);
		4)Se adauga la suma;
		5)Se trece la nodul urmator;
		6)Creste i-ul cu 1;
		7)Se repeta 2,3,4,5,6 pana cand i=3.
		Cu cat se avanseaza in lista cu atat se apropie de interval,
		astfel crescand coeficientul w pe masura ce lista avanseaza.
	-rightSum (face suma pentru intervalul drept);
		1)Se initializea suma=2;
		2)Se ia un contor i=2;
		3)Se inmulteste valoarea lui curent cu w(i,3);
		4)Se adauga la suma;
		5)Se trece la nodul urmator;
		6)Scade i-ul cu 1;
		7)Se repeta 2,3,4,5,6 pana cand i=-1.
		Cu cat se avanseaza in lista cu atat se departeaza de interval,
		astfel scazand coeficientul w pe masura ce lista avanseaza.
	-completare (completeaza lista daca sunt intervale lipsa prea mari);
		Mod de functionare:
		1)Se incepe de la al 3-lea element al listei.
		2)Se face diferenta cu timestampul nodului urmator.			
		3)Daca diferenta e mai mare decat 1000:
		-se construiesc left si right;
		-se fac sumele pentru ferestrele respective;
		-noua valoare va fi (1-C)*sumleft+C*sumRight;
		-noul timestamp va fi timestamp curent+200;
		4)Se trece la nodul urmator;
		5)Se repeta 2,3,4 pana cand am ajuns la penultimul nod.
	-stats (afiseaza intervalele in care se incadreaza elementele);
		Mod de functionare:
		1)Se face o lista cu valorile reale.
		2)Se sorteaza lista.
		3)Se aproximeaza minimul la cel mai apropiat divizor al perioadei.
		4)Daca valoarea se afla in [contor,contor+perioada]:
		-creste numaratoarea;
		-se trece la nodul urmator.	
		5)Daca nu:
		-daca numaratoarea e >0 se afiseaza intervalul si numaratoarea;
		-se reseteaza numaratoarea;
		-creste contorul cu perioada.
		6)Se repeta 3,4,5 pana cand am parcurs toata lista.

Pentru argumentele in linia de comanda se verifica cu strcmp ce operatie se va efectua
asupra listei.Pentru bonus s-a utilizat strstr si s-a extras numarul din argument,acesta
fiind dat ca perioada pentru intervale.Daca s-a ajuns la ultimul argument se afisa rezultatul.

