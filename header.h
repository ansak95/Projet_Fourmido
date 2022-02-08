#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define SIZE 8
#define GOLD 50
struct Fourmi {
  char color;
  int type;//1:Fourmilliere, 2:Reine, 3:Ouvriere, 4: Soldat
  int pos[2];
  int dest[2];
  struct Fourmi* suiv;
  struct Fourmi* prec;
  int immo;
  int typeF;
  int tp_prod;
  struct Fourmi* next;
  struct Fourmi* prev;
};

struct Case {
  //struct Fourmi* fourmilliere;
  struct Fourmi* fourmi;
};

struct Monde {
  struct Case plateau[SIZE][SIZE];
  struct Fourmi* Frouge;
  struct Fourmi* Fnoir;
};

struct Maillon {
  struct Fourmi* next;
  struct Fourmi* prev;
};


int lire(char *chaine, int longueur);
void viderBuffer();
long lireLong();
void afficher_plateau(struct Case tab[SIZE][SIZE]);
void Combat (struct Monde* m,struct Fourmi* ant1, struct Fourmi* ant2);
int ordre_fourmi (struct Monde* plat, char *ordre, int lignedep, int colonnedep,int lignearr, int colonnearr, int*lignetmp, int*colonnetmp);
void CreerFourmiliere (struct Fourmi* ant, char color, int ligne, int colone);
void CreerReine (struct Fourmi* ant, char color, int ligne, int colone);
void CreerOuvriere (struct Fourmi* ant, char color, int ligne, int colone);
void CreerSoldat (struct Fourmi* ant, char color, int ligne, int colone);
int Libre (struct Monde* world, int ligne, int colonne, int* i, int* j);
int produire_agent (struct Monde* plat, int ligne, int colonne, int code,char color, struct Fourmi* ant);
void init_monde (struct Monde* m,struct Fourmi* Fn, struct Fourmi* Fr, struct Fourmi* Or, struct Fourmi* On, struct Fourmi* Rn, struct Fourmi* Rr );
void ChangeReineFourmi(struct Monde* m, struct Fourmi* ant, int r2, int r3, char color);

