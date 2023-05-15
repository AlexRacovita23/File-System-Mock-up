/* RACOVITA Alexandru Catalin - grupa 312CB */

#include "Tarb.h"

TArb constr_fr(TInfo x)     /* -> adresa frunza cu informatia x, sau
					NULL daca nu exista spatiu */
{
	TArb aux = (TArb)malloc (sizeof(TNod));
	if (!aux) return NULL;
	aux->info = x; aux->st = aux->dr = NULL;

	return aux;
}

TFArb constr_fr_f(char *x) 
{
	TFArb aux = (TFArb)malloc (sizeof(TFisier));
	if (!aux) return NULL;
	aux->nume = malloc(sizeof(x) + 1);
	memmove(aux->nume, x, strlen(x)+1);
	aux->st = aux->dr = NULL;
	return aux;
}

TDArb constr_fr_dir(char *x, TDArb parinte)
{
	TDArb aux = (TDArb)malloc (sizeof(TDirector));
	if (!aux) return NULL;
	aux->nume = malloc(sizeof(x)+1);
	memmove(aux->nume, x, strlen(x)+1);
	aux->st = aux->dr = NULL;
	aux->directories = NULL;
	aux->fisiere = NULL;
	aux->parinte = parinte;

	return aux;
}

void distr_subarb_fisiere(TFArb r) 	/* functie auxiliara - distruge toate fisierele */
{	
	if (!r) return;
	distr_subarb_fisiere (r->st);     /* distruge subarborele stang */
	distr_subarb_fisiere (r->dr);     /* distruge subarborele drept */
	free(r->nume);
	free (r);             /* distruge nodul radacina */
}

void distr_arb_fisiere(TFArb *a) /* distruge toate nodurile arborelui de la adresa a */
{
	if (!(*a)) return;       /* arbore deja vid */
	distr_subarb_fisiere (*a);           /* distruge toate nodurile */
	*a = NULL;               /* arborele este vid */
}

void distr_subarb_directoare(TDArb r) 	/* functie auxiliara - distruge toate directoarele */
{
	if (!r) return;
	distr_subarb_directoare (r->st);     /* distruge subarborele stang */
	distr_subarb_directoare (r->dr);     /* distruge subarborele drept */
	distr_arb_fisiere(&(r->fisiere));
	distr_arb_directoare(&(r->directories));
	free(r->nume);
	free (r);             /* distruge nodul radacina */
}

void distr_arb_directoare(TDArb *a) /* distruge toate nodurile arborelui de la adresa a */
{
	if (!(*a)) return;       /* arbore deja vid */
	distr_subarb_directoare (*a);           /* distruge toate nodurile */
	*a = NULL;               /* arborele este vid */
}

TFArb rm(TFArb a, char *nume, int *contor)
{
    if (a == NULL)
        return a;
 
    if (strcmp(nume, a->nume) < 0)
        a->st = rm(a->st, nume, contor);
 
    else if (strcmp(nume, a->nume) > 0)
        a->dr = rm(a->dr, nume, contor);
 
    else {
		*contor+=1;
        if (a->st == NULL || a->dr == NULL) {
			TFArb temp;
			if(a->st == NULL)
            	temp = a->dr;
			else
				temp = a->st;
			free(a->nume);
            free(a);
            return temp;
        }
 
        TFArb temp;
		temp = a->st;
		while(temp->dr){
			temp = temp->dr;
		}

		strcpy(a->nume, temp->nume);
        a->st = rm(a->st, temp->nume, contor);

    	}

    return a;

}


TDArb rmdir(TDArb a, char *nume, int *contor)
{
    if (!a)
        return a;
 
    if (strcmp(nume, a->nume) < 0)
        a->st = rmdir(a->st, nume, contor);

    else if (strcmp(nume, a->nume) > 0)
        a->dr = rmdir(a->dr, nume, contor);

    else {
		*contor+=1;
        if (a->st == NULL || a->dr == NULL) {
			TDArb temp;
			if(a->st == NULL)
            	temp = a->dr;
			else
				temp = a->st;
			distr_arb_fisiere(&(a->fisiere));
			distr_arb_directoare(&(a->directories));
            free(a->nume);
			free(a);
            return temp;
        }
        TDArb temp;
		temp = a->st;
			while(temp->dr){
				temp = temp->dr;
			}
		strcpy(a->nume, temp->nume);
        a->st = rmdir(a->st, temp->nume, contor);
    	}
    return a;
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