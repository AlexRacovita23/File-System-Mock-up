# File-System-Mock-up
Incep programul cu initializarea radacinii: aloc memorie pentru ea si pentru numele "root", apoi fac citirea
si in functie de primul cuvant aleg si ce functie apelez, nimic nou sau wow. Initializez si o alta structura de tip
director numita director_curent care pointeaza la aceeasi zona de memorie ca root. Pe aceasta o voi folosi pentru cd
pwd si find.
	Functiile touch si mkdir sunt aproape identice asa ca o sa abordez cazul mai complex reprezentat de mkdir
Parcurg mai intai arborele care contine fisierele din directorul in care vreau sa adaug directorul
pentru a verifica daca nu exista deja numele. Daca nu exista niciun fisier cu acest nume, verific daca in parinte
se mai afla alte directoare. Daca nu se afla, initializez arborele de directoare.
Fac aceeasi parcurgere si pentru arborele care contine directoarele. Daca am gasit un director cu acel nume, ies
din functie, daca nu il inserez in locul corespunzator. Functiile de construire de nod de arbore, fie el fisier sau
director doar aloca memorie pentru nod si numele lui, copiaza numele dat in campul structurii si in rest lasa NULL
in celelalte campuri.
	Functia de ls e reprezentata de doua parcurgeri SRD doar, odata a arborelui de fisiere din directorul curent
si inca o data a arborelui de directoare.
	Functia cd "merge" un pas inapoi, la parinte daca primeste ca input ".." sau daca primeste ca input un nume,
il cauta in arborele de directoarele. Daca il gaseste, director_curent devine directorul gasit.
	Functiile rm si rmdir sunt, la fel ca la touch si mkdir, foarte asemenatoare asa ca din nou, abordez rmdir acum
Parcurc arborele de directoare pana gasesc nodul pe care vreau sa il elimin. Daca acesta este frunza sau are un singur fiu,
schimb valoarea fiului cu cea a nodului de eliminat, sterg arborii de fisiere si directoare.
Arborele de director e sters recursiv pentru a sterge de asemenea si fiecare subdirector, dau free la numele nodului si la
acesta.
Daca nodul pe care vreau sa il elimin are 2 fii, caut valoarea cea mai mare din arborele stang(cea mai mare valoare dupa cea
eliminata) si ii dau nodului "eliminat" numele acesteia. Apelez recursiv functia pentru a elimina apoi nodul duplicat: daca
acesta are la randul lui un fiu(2 nu poate sa aiba deoarece este cel mai mare nod de pe ramura stanga, deci fiu de dreapta
nu exista), fiul devine nodul de eliminat, iar info din el ia locul nodului care a avut valoarea cea mai mare din subarborele
stang.
	Pentru functia pwd pur si simplu merg recursiv pana la radacina si printez de fiecare data numele directorului curent.
