/* RACOVITA Alexandru Catalin - grupa 312CB */

#include "Tarb.h"

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
		*a = constr_fr_f(x);
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
	aux = constr_fr_f(x);
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
		*a = constr_fr_dir(x, parinte);
		if(!*a) return 0;
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
	aux = constr_fr_dir(x, parinte);
	if(!aux) return 0;

	if(strcmp(x, p->nume) < 0)
		p->st = aux;
	else	
		p->dr = aux;
	return 1;
}

void srd_dir(TDArb a)
{
	if(!a)
		return;

	srd_dir(a->st);
	printf("%s ", a->nume);
	srd_dir(a->dr);
}

void srd_files(TFArb a)
{
	if(!a)
		return;
	srd_files(a->st);
	printf("%s ", a->nume);
	srd_files(a->dr);
}

int cd(TDArb *director_curent ,char *nume)
{	
	TDArb aux = (*director_curent)->directories;
	TDArb p;
	if(strcmp(nume, "..")==0){
		*director_curent = (*director_curent)->parinte;
		return 1;
	}
	while(aux){
		if (strcmp(nume, aux->nume) < 0){
			aux = aux->st;
		}
		else if (strcmp(nume, aux->nume) > 0){	
			aux = aux->dr;
		}
		else {
			*director_curent = aux;
			return 1;
		}
	}
	return 0;
}
void pwd(TDArb director) 
{	
	if(!director)
		return;
	pwd(director->parinte);
	printf("/%s", director->nume);
}

int find_d(TDArb director, char* nume)
{
	if(!director)
	
		return 0;
	int n = find_d(director->st, nume);

	//if(n)
	//	return n;
	if(strcmp(nume, director->nume) == 0){
		printf("Directory %s found!\n", nume);
		pwd(director);
		printf("\n");
		return n++;
	}
	if(find_d(director->directories, nume)){
		printf("Directory %s found!\n", nume);
		pwd(director->directories);
		printf("\n");
		return n++;
	}

	n += find_d(director->dr, nume);
	return n;
}
int find_f(TDArb director, char* nume)
{
	if(!director)
		return 0;
	int n = find_f(director->st, nume);

	//if(n)
		//return n;

	if(find_fisier(director->fisiere, nume)){
		printf("File %s found!\n", nume);
		pwd(director->directories);
		printf("\n");
		return n++;
	}
	find_f(director->directories, nume);

	n += find_f(director->dr, nume);
	return n;
}

int find_fisier(TFArb fisiere, char* nume)
{
	if(!fisiere)
		return 0;
	int n = find_fisier(fisiere->st, nume);
	if(strcmp(nume, fisiere->nume) == 0) 
			return n++;
	n += find_fisier(fisiere->dr, nume);
	return n;
}


int main()
{
	TDArb root, director_curent;
	root = (TDArb) malloc(sizeof(TDirector));
	root->nume = malloc(256*sizeof(char));
	strcpy(root->nume, "root");
	root->st = root->dr = root->directories = NULL;
	root->fisiere = NULL;
	director_curent = root;
	char *line;
	char *inst;
	line = malloc(10*sizeof(char));
	int len = 0;
	char *nume_aux;
	char *nume; //numele directorului/fisierului de creat/sters
	int contor;
	while(scanf("%s",line) == 1) {
		if(!strcmp(line, "touch"))
		{
			inst = malloc(256*sizeof(char));
			fgets(inst, 256, stdin);
			nume_aux = strtok(inst, " \n");
			nume = malloc(strlen(nume_aux) + 1);
			memmove(nume, nume_aux, strlen(nume_aux)+1);
			contor = touch(director_curent, &(director_curent->fisiere), nume);
			if (contor == 0)
				printf("File %s already exists!\n", nume);
			else if(contor == -1)
				printf("Directory %s already exists!\n", nume);
			free(inst);
			free(nume);
		}

		else if (!strcmp(line, "mkdir")) {
			inst = malloc(256*sizeof(char));
			fgets(inst, 256, stdin);
			nume_aux = strtok(inst, " \n");
			nume = malloc(strlen(nume_aux) + 1);
			memmove(nume, nume_aux, strlen(nume_aux)+1);
			contor = mkdir(director_curent, &(director_curent->directories), nume);
			if (contor == 0)
				printf("Directory %s already exists!\n", nume);
			else if(contor == -1)
				printf("File %s already exists!\n", nume);
			free(inst);
			free(nume);
		}

		else if (!strcmp(line, "ls")) {
		srd_dir(director_curent->directories);
		srd_files(director_curent->fisiere);
		printf("\n");
		}

		else if (!strcmp(line, "rm")) {
			inst = malloc(256*sizeof(char));
			fgets(inst, 256, stdin);
			nume_aux = strtok(inst, " \n");
			nume = malloc(strlen(nume_aux) + 1);
			memmove(nume, nume_aux, strlen(nume_aux) + 1);
			contor = 0;
			director_curent->fisiere= rm(director_curent->fisiere, nume, &contor);
			if(contor == 0)
				printf("File %s doesn't exist!\n", nume);
			free(inst);
			free(nume);
		}

		else if (!strcmp(line, "rmdir")) {

			inst = malloc(256*sizeof(char));
			fgets(inst, 256, stdin);
			nume_aux = strtok(inst, " \n");
			nume = malloc(strlen(nume_aux) + 1);
			memmove(nume, nume_aux, strlen(nume_aux) + 1);
			contor = 0;
			director_curent->directories = rmdir(director_curent->directories, nume, &contor);
			if(contor == 0)
				printf("Directory %s doesn't exist!\n", nume);
			free(inst);
			free(nume);

		}

		else if (!strcmp(line, "cd")) {
			
			inst = malloc(256*sizeof(char));
			fgets(inst, 256, stdin);
			nume_aux = strtok(inst, " \n");
			nume = malloc(strlen(nume_aux) + 1);
			memmove(nume, nume_aux, strlen(nume_aux) + 1);
			if(!(cd(&director_curent, nume)))
				printf("Directory not found!\n");
			free (inst);
			free (nume);
		}

		else if(!strcmp(line, "pwd")) {
			pwd(director_curent);
			printf("\n");
		}

		else if (!strcmp(line, "find")) {
			inst = malloc(256*sizeof(char));
			fgets(inst, 256, stdin);
			char *tip = strtok(inst, " \n");
			nume = strtok(NULL, " \n");
			if(!strcmp(tip, "-d"))
				find_d(root, nume);
			else if (!strcmp(tip, "-f"))
				find_f(root, nume);
			{
				/* code */
			}
			free(inst);
		}
		else if (!strcmp(line, "quit")) {
			free (line);
			distr_arb_directoare(&root);
			return 0;
		}
	}
}