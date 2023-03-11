#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifndef ARBORE_BINAR
#define ARBORE_BINAR

typedef int TInfo;
typedef struct nod {
	TInfo info;
	struct nod *st, *dr;
} TNod, *TArb, **AArb;

typedef struct director {
    char* nume;
    struct director* parinte, *st, *dr, *directories;
    struct fisier *fisiere;
}TDirector, *TDArb, **ADArb;

typedef struct fisier {
    char* nume;
    struct fisier *st, *dr;
    struct director *parinte;
}TFisier, *TFArb, **AFArb;

/*-- Operatii elementare --*/
TArb ConstrNod(TInfo x, TArb s, TArb d); 
     /* -> adresa nod (cu info x, fiu stanga s, fiu dreapta d)
		   sau NULL daca nu exista spatiu */
TArb ConstrFr(TInfo x);
     /* -> adresa frunza cu informatia x, sau NULL daca nu exista spatiu */

TFArb ConstrFrF(char *x);
TDArb ConstrFrDir(char *x);

void DistrArb(AArb);    /* distruge arbore */
int NrNoduri(TArb);     /* numar noduri */
int NrNiv(TArb);        /* numar niveluri (0 pentru arbore vid) */

/*-- Operatii suplimentare --*/
void AfiArb(TArb r);
	  /*- afiseaza arborele r -*/
int Inserare_ABC(TArb* a, int x);
	  /*- insereaza x in arborele binar de cautare a -*/
#endif

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned int)time(NULL)))
#endif
