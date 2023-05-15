/* RACOVITA Alexandru Catalin - grupa 312CB */

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
    char *nume;
    struct director* parinte, *st, *dr, *directories;
    struct fisier *fisiere;
}TDirector, *TDArb, **ADArb;

typedef struct fisier {
    char* nume;
    struct fisier *st, *dr;
    struct director *parinte;
}TFisier, *TFArb, **AFArb;

/*-- Operatii elementare --*/

TFArb constr_fr_f(char *x);
TDArb constr_fr_dir(char *x, TDArb parinte);

void distr_subarb_directoare(TDArb r);
void distr_arb_directoare(TDArb *a);
void distr_subarb_fisiere(TFArb r);
void distr_arb_fisiere(TFArb *a);
int NrNoduri(TArb);     /* numar noduri */
int NrNiv(TArb);        /* numar niveluri (0 pentru arbore vid) */

/*-- Operatii suplimentare --*/

int find_fisier(TFArb fisiere, char* nume);
TFArb rm(TFArb a, char *nume, int *contor);
TDArb rmdir(TDArb a, char *nume, int *contor);
#endif

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned int)time(NULL)))
#endif
