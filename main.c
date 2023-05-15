#include "Tarb.h"

// TODO pt maine
// modificare functii laborator pentru tema
// doar cu adaugare si afisare fac primele 3 taskuri

int touch(TDArb parinte, TFArb *a, char* x)
{
	TFArb aux, p, n;
	TDArb m;
	m = parinte->directories;
	while(m){
		if(strcmp(x, m->nume) == 0) 
			return -1;
		if(strcmp(x, m->nume) < 0)
			m = m->st;
		else	
			m = m->dr;
	}

	if(*a == NULL)
	{	
		*a = ConstrFrF(x);
		if(!*a) return 0;
		(*a)->parinte = parinte;
		return 1;
	}
	n = *a;
	while(n)
	{
		p = n;
		if(strcmp(x, n->nume) == 0) 
			return 0;
		if(strcmp(x, n->nume) < 0)
			n = n->st;
		else	
			n = n->dr;
	}
	aux = ConstrFrF(x);
	if(!aux) return 0;

	if(strcmp(x, p->nume) < 0)
		p->st = aux;
	else	
		p->dr = aux;
	(*a)->parinte = parinte;
	return 1;
}

int mkdir(TDArb parinte, TDArb* a, char* x)
{
	TDArb aux, p, n;
	TFArb m;

	m = parinte->fisiere;
	while(m){
		if(strcmp(x, m->nume) == 0) 
			return -1;
		if(strcmp(x, m->nume) < 0)
			m = m->st;
		else	
			m = m->dr;
	}

	if(*a == NULL)
	{	
		*a = ConstrFrDir(x);
		if(!*a) return 0;
		(*a)->parinte = parinte;
		return 1;
	}

	n = *a;
	while(n)
	{
		p = n;
		if(strcmp(x, n->nume) == 0) 
			return 0;
		if(strcmp(x, n->nume) < 0)
			n = n->st;
		else	
			n = n->dr;
	}
	aux = ConstrFrDir(x);
	if(!aux) return 0;

	if(strcmp(x, p->nume) < 0)
		p->st = aux;
	else	
		p->dr = aux;
	(*a)->parinte = parinte;
	return 1;
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

void SRD_Dir(TDArb a)
{
	if(!a)
		return;

	SRD_Dir(a->st);
	printf("%s ", a->nume);
	SRD_Dir(a->dr);
}

void SRD_Files(TFArb a)
{
	if(!a)
		return;
	SRD_Files(a->st);
	printf("%s ", a->nume);
	SRD_Files(a->dr);
}

int main()
{
	TDArb root, director_curent;
	root->nume = malloc(5*sizeof(char));
	char *nume_root = "root";
	memmove(root->nume, nume_root, sizeof(nume_root)+1);
	director_curent = root;
	char *line;
	char *inst;
	line = malloc(10*sizeof(char));
	int len = 0;
	char *nume; //numele directorului/fisierului de creat/sters
	int contor;
	while(scanf("%s",line) == 1) {
		if(!strcmp(line, "touch"))
		{
			inst = malloc(256*sizeof(char));
			fgets(inst, 256, stdin);
			nume = strtok(inst, " \n");
			contor = touch(director_curent, &(director_curent->fisiere), nume);
			if (contor == 0)
				printf("File %s already exists!\n", nume);
			else if(contor == -1)
				printf("Directory %s already exists!\n", nume);
		}

		else if (!strcmp(line, "mkdir")) {

			inst = malloc(256*sizeof(char));
			fgets(inst, 256, stdin);
			nume = strtok(inst, " \n");
			contor = mkdir(director_curent, &(director_curent->directories), nume);
			if (contor == 0)
				printf("Directory %s already exists!\n", nume);
			else if(contor == -1)
				printf("File %s already exists!\n", nume);

		}

		else if (!strcmp(line, "ls")) {
		SRD_Dir(director_curent->directories);
		SRD_Files(director_curent->fisiere);
		printf("\n");
		}

		else if (!strcmp(line, "rm")) {

			// TODO rm

		}

		else if (!strcmp(line, "rmdir")) {

			//TODO rmdir

		}

		else if (!strcmp(line, "cd")) {

			// TODO cd

		}

		else if (!strcmp(line, "find")) {

			// TODO find

		}
		else if (!strcmp(line, "quit")) {
			return 0;
		}

	}

}
