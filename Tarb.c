#include "Tarb.h"



TArb ConstrNod(TInfo x, TArb s, TArb d)/* -> adresa nod (cu informatia x, 
				fiu stanga s, fiu dreapta d) sau NULL in caz de eroare */
{
	TArb aux = (TArb)malloc (sizeof(TNod));  /* incearca alocare spatiu */
	if (!aux) return NULL;                   /* spatiu insuficient */
	aux->info = x; aux->st = s; aux->dr = d; /* actualizeaza campurile nodului */

	return aux;                              /* intoarce adresa nodului */
}

TArb ConstrFr(TInfo x)     /* -> adresa frunza cu informatia x, sau
					NULL daca nu exista spatiu */
{
	TArb aux = (TArb)malloc (sizeof(TNod));
	if (!aux) return NULL;
	aux->info = x; aux->st = aux->dr = NULL;

	return aux;
}

TFArb ConstrFrF(char *x)     /* -> adresa frunza cu informatia x, sau
					NULL daca nu exista spatiu */
{
	TFArb aux = (TFArb)malloc (sizeof(TFisier));
	if (!aux) return NULL;
	aux->nume = x; aux->st = aux->dr = NULL;
	return aux;
}

TDArb ConstrFrDir(char *x)     /* -> adresa frunza cu informatia x, sau
					NULL daca nu exista spatiu */
{
	TDArb aux = (TDArb)malloc (sizeof(TDirector));
	if (!aux) return NULL;
	aux->nume = x; aux->st = aux->dr = NULL;
	aux->directories = NULL;
	aux->fisiere = NULL;

	return aux;
}

void DistrSubarb(TArb r) 	/* functie auxiliara - distruge toate nodurile */
{
	if (!r) return;
	DistrSubarb (r->st);     /* distruge subarborele stang */
	DistrSubarb (r->dr);     /* distruge subarborele drept */
	free (r);             /* distruge nodul radacina */
}

void DistrArb(TArb *a) /* distruge toate nodurile arborelui de la adresa a */
{
	if (!(*a)) return;       /* arbore deja vid */
	DistrSubarb (*a);           /* distruge toate nodurile */
	*a = NULL;               /* arborele este vid */
}

int rm(TFArb *a, char *nume)
{
	if(!a)
		return NULL;
	TFArb aux, p, n;
	int contor;
	n = *a;
	while(n){
		if(strcmp(nume, n->nume) == 0){
			contor+=1;
			break;
		}
		p = n;
		if(strcmp(nume, n->nume) < 0)
			n = n->st;
		else	
			n = n->dr;
	}
	if (contor == 0)
		return 0;












}

int NrNoduri(TArb r)        /* numarul de noduri din arborele r -*/
{
	if (!r) return 0;          /* arbore vid => 0 noduri */
	return 1 + NrNoduri(r->st) + NrNoduri(r->dr);
}

int NrNiv(TArb r)           /* numar niveluri (0 pentru arbore vid) */
{
	int ns, nd;
	if (!r) return 0;
	ns = NrNiv(r->st); nd = NrNiv(r->dr);
	return 1 + (ns >= nd ? ns : nd);
}