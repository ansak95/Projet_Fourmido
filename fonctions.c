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

int lire(char *chaine, int longueur) {
  char *positionEntree = NULL;
  // On lit le texte saisi au clavier
  if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
  {
    positionEntree = strchr(chaine, '\n'); // On recherche l'"EntrŽe"
    if (positionEntree != NULL) // Si on a trouvŽ le retour ˆ la ligne
    {
      *positionEntree = '\0'; // On remplace ce caractre par \0
    }
    return 1; // On renvoie 1 si la fonction s'est dŽroulŽe sans erreur
  }
  else
  {
    return 0; // On renvoie 0 s'il y a eu une erreur
  }
}

void viderBuffer() {
  int c = 0;
  while (c != '\n' && c != EOF)
  {
    c = getchar();
  }
}

long lireLong() {
  char nombreTexte[256] = {0}; // 100 cases devraient suffire
  if (lire(nombreTexte, 256))
  {
    // Si lecture du texte ok, convertir le nombre en long et le retourner
    return strtol(nombreTexte, NULL, 10);
  }
  else
  {
    // Si problme de lecture, renvoyer 0
    return 0;
  }
}

void afficher_plateau(struct Case tab[SIZE][SIZE]) {
  int i, j;
  printf("  ");
  for (i=0; i<SIZE; i++) {
    printf(" %d  ", i);
  }
  printf("\n  *-------------------------------*\n");
  printf("  |===============================|\n");
  for (i=0; i<SIZE; i++) {
    printf("%d |", i );
    for (j=0; j<SIZE; j++) {
      if (tab[i][j].fourmi==NULL) {
        printf("  ||");
      }
      else {
        int a=tab[i][j].fourmi->type;
        if (tab[i][j].fourmi->color=='r') {
          if (a==1) {
            printf("Fr||");
          }
          else {
            if (a==2) {
              printf("Rr||");
            }
            else {
              if (a==3) {
                printf("Or||");
              }
              else {
                printf("Sr||");
              }
            }
          }
        }
        else {
          if (tab[i][j].fourmi->color=='n') {
            if (a==1) {
              printf("Fn||");
            }
            else {
              if (a==2) {
                printf("Rn||");
              }
              else {
                if (a==3) {
                  printf("On||");
                }
                else {
                  printf("Sn||");
                }
              }
            }
          }
        }
      }
    }
    if(i!=SIZE-1) {
      printf("\n  |==||==||==||==||==||==||==||===|\n");
    }
    else {
      printf("\n  |===============================|\n");
    }
  }
  printf("  *-------------------------------*\n");
}

void Combat (struct Monde* m,struct Fourmi* ant1, struct Fourmi* ant2) {
  struct Fourmi* tmp=malloc(sizeof(struct Fourmi));
  int ligne, colonne;
  srand(time(NULL));
  int a=rand()%(3)+1;
  printf("\n%d\n", a);
  if ((ant1->type!=4 && ant2->type!=4)) {
    if (a>=3) { // ant1 perd !
      if (ant1->suiv!=NULL) {
        tmp=ant1->suiv;
        ant1->prec->suiv=tmp;
        tmp->prec=ant1->prec;
        ant1=NULL;
      }
      else {
        ant1->prec->suiv=NULL;
        ant1=NULL;
      }// On detruit la fourmi //On libere la case du plateau
    }
    else { // ant2 perd !
    ligne=ant2->pos[0];
    colonne=ant2->pos[1];
      if (ant2->suiv!=NULL) {
        tmp=ant2->suiv;
        ant2->prec->suiv=tmp;
        tmp->prec=ant2->prec;
        ant2=NULL;
      }
      else {
        ant2->prec->suiv=NULL;
        ant2=NULL;
      }
      ant1->pos[0]=ligne;
      ant1->pos[1]=colonne;
      m->plateau[ligne][colonne].fourmi=ant1;
      ant1=NULL;
    }
  }
  else {
    if (ant1->type==4) { // ant1 est un soldat
      if(a<4) { // ant1 gagne
      ligne=ant2->pos[0];
      colonne=ant2->pos[1];
        if (ant2->suiv!=NULL) {
          tmp=ant2->suiv;
          ant2->prec->suiv=tmp;
          tmp->prec=ant2->prec;
          ant2=NULL;
        }
        else {
          ant2->prec->suiv=NULL;
          ant2=NULL;
        }
        ant1->pos[0]=ligne;
        ant1->pos[1]=colonne;
        m->plateau[ligne][colonne].fourmi=ant1;
        ant1=NULL;
      }
      else { // ant1 perd
        if (ant1->suiv!=NULL) {
          tmp=ant1->suiv;
          ant1->prec->suiv=tmp;
          tmp->prec=ant1->prec;
          ant1=NULL;
        }
        else {
          ant1->prec->suiv=NULL;
          ant1=NULL;
        }
      }
    }
    else {
      if(a<4) { // ant2 est un soldat et il gagne
        if (ant1->suiv!=NULL) {
          tmp=ant1->suiv;
          ant1->prec->suiv=tmp;
          tmp->prec=ant1->prec;
         ant1=NULL;
        }
        else {
          ant1->prec->suiv=NULL;
          ant1=NULL;
        }
      }
      else { // ant2 perd
      ligne=ant2->pos[0];
      colonne=ant2->pos[1];
        if (ant2->suiv!=NULL) {
          tmp=ant2->suiv;
          ant2->prec->suiv=tmp;
          tmp->prec=ant2->prec;
          ant2=NULL;
        }
        else {
          ant2->prec->suiv=NULL;
          ant2=NULL;
        }
        ant1->pos[0]=ligne;
        ant1->pos[1]=colonne;
        m->plateau[ligne][colonne].fourmi=ant1;
        ant1=NULL;
      }
    }
  }
}

int ordre_fourmi (struct Monde* plat, char *ordre, int lignedep, int colonnedep,int lignearr, int colonnearr, int*lignetmp, int*colonnetmp) {
  struct Fourmi* tmp=malloc(sizeof (struct Fourmi));
  if (lignearr>SIZE || colonnearr>SIZE || plat->plateau[lignedep][colonnedep].fourmi==NULL || (plat->plateau[lignedep][colonnedep].fourmi->type==3 && plat->plateau[lignedep][colonnedep].fourmi->immo==1)) { //verifier condition d'entrer LUDO
    return 0;
  }
  else {
    if (!strcmp(ordre, "bouger")) {
      if ((lignedep==lignearr && colonnedep==colonnearr) /*plat->plateau[lignearr][colonnearr].fourmi!=NULL*/) {
        //~ if (lignearr-lignedep==1 || colonnearr-lignedep==1
        return 1;
      }
      else {
        plat->plateau[lignedep][colonnedep].fourmi->dest[0]=lignearr;
        plat->plateau[lignedep][colonnedep].fourmi->dest[1]=colonnearr;
        if (lignedep!=lignearr || colonnedep!=colonnearr) {
          if (plat->plateau[lignedep][colonnedep].fourmi->type!=1 || (plat->plateau[lignedep][colonnedep].fourmi->type==3 && plat->plateau[lignedep][colonnedep].fourmi->immo==0)) {
            //verifier si on se deplace sur la mm ligne ou la mm colonne pour bouger de 1 a chaque fois
            if (lignearr==lignedep) {
              if (colonnedep<colonnearr) {
                if (plat->plateau[lignedep][colonnedep+1].fourmi==NULL) {
                  plat->plateau[lignedep][colonnedep].fourmi->pos[1]++;
                  plat->plateau[lignedep][colonnedep+1]=plat->plateau[lignedep][colonnedep];
                  *lignetmp=lignedep;
                  *colonnetmp=colonnedep+1;
                }
                else {
                  if(plat->plateau[lignedep][colonnedep].fourmi->color!=plat->plateau[lignedep][colonnedep+1].fourmi->color) {
                    Combat(plat,plat->plateau[lignedep][colonnedep].fourmi, plat->plateau[lignedep][colonnedep+1].fourmi);
                  }
                  else {
                    return -1;
                  }
                }
              }
              else {
                if (plat->plateau[lignedep][colonnedep-1].fourmi==NULL) {
                  plat->plateau[lignedep][colonnedep].fourmi->pos[1]--;
                  plat->plateau[lignedep][colonnedep-1]=plat->plateau[lignedep][colonnedep];
                  *lignetmp=lignedep;
                  *colonnetmp=colonnedep-1;
                }
                else {
                  if(plat->plateau[lignedep][colonnedep].fourmi->color!=plat->plateau[lignedep][colonnedep-1].fourmi->color) {
                    Combat(plat, plat->plateau[lignedep][colonnedep].fourmi, plat->plateau[lignedep][colonnedep-1].fourmi);
                  }
                  else {
                    return -1;
                  }
                }
              }
            }
            else {
              if (colonnearr==colonnedep) {
                if (lignedep<lignearr) {
                  if(plat->plateau[lignedep+1][colonnedep].fourmi==NULL) {
                    plat->plateau[lignedep][colonnedep].fourmi->pos[0]++;
                    plat->plateau[lignedep+1][colonnedep]=plat->plateau[lignedep][colonnedep];
                    *lignetmp=lignedep-1;
                    *colonnetmp=colonnedep;
                  }
                  else {
                    if(plat->plateau[lignedep][colonnedep].fourmi->color!=plat->plateau[lignedep+1][colonnedep].fourmi->color) {
                      Combat(plat, plat->plateau[lignedep][colonnedep].fourmi,plat->plateau[lignedep+1][colonnedep].fourmi );
                    }
                    else {
                      return -1;
                    }
                  }
                }
                else {
                  if (plat->plateau[lignedep-1][colonnedep].fourmi==NULL) {
                    plat->plateau[lignedep][colonnedep].fourmi->pos[0]--;
                    plat->plateau[lignedep-1][colonnedep]=plat->plateau[lignedep][colonnedep];
                    *lignetmp=lignedep+1;
                    *colonnetmp=colonnedep;
                  }
                  else {
                    if(plat->plateau[lignedep][colonnedep].fourmi->color!=plat->plateau[lignedep-1][colonnedep].fourmi->color) {
                      Combat(plat, plat->plateau[lignedep][colonnedep].fourmi, plat->plateau[lignedep-1][colonnedep].fourmi);
                    }
                    else {
                      return -1;
                    }
                  }
                }
              }
              // si on est en diagonale faire ligne+ ou colonne-, ou ligne+ colonne+ etc ...
              else {
                if (colonnearr>colonnedep) {
                  if (lignearr>lignedep) {
                    if(plat->plateau[lignedep+1][colonnedep+1].fourmi==NULL) {
                      plat->plateau[lignedep][colonnedep].fourmi->pos[0]++;
                      plat->plateau[lignedep][colonnedep].fourmi->pos[1]++;
                      plat->plateau[lignedep+1][colonnedep+1]=plat->plateau[lignedep][colonnedep];
                      *lignetmp=lignedep+1;
                      *colonnetmp=colonnedep+1;
                    }
                    else {
                      if(plat->plateau[lignedep][colonnedep].fourmi->color!=plat->plateau[lignedep+1][colonnedep+1].fourmi->color) {
                        Combat(plat, plat->plateau[lignedep][colonnedep].fourmi, plat->plateau[lignedep+1][colonnedep+1].fourmi);
                      }
                      else {
                        return -1;
                      }
                    }
                  }
                  else {
                    if (plat->plateau[lignedep-1][colonnedep+1].fourmi==NULL) {
                      plat->plateau[lignedep][colonnedep].fourmi->pos[0]--;
                      plat->plateau[lignedep][colonnedep].fourmi->pos[1]++;
                      plat->plateau[lignedep-1][colonnedep+1]=plat->plateau[lignedep][colonnedep];
                      *lignetmp=lignedep+1;
                      *colonnetmp=colonnedep-1;
                    }
                    else {
                      if(plat->plateau[lignedep][colonnedep].fourmi->color!=plat->plateau[lignedep-1][colonnedep+1].fourmi->color) {
                        Combat(plat, plat->plateau[lignedep][colonnedep].fourmi, plat->plateau[lignedep-1][colonnedep+1].fourmi);
                      }
                      else {
                        return -1;
                      }
                    }
                  }
                }
                else {
                  if (lignearr>lignedep ) {
                    if(plat->plateau[lignedep+1][colonnedep-1].fourmi==NULL) {
                      plat->plateau[lignedep][colonnedep].fourmi->pos[0]++;
                      plat->plateau[lignedep][colonnedep].fourmi->pos[1]--;
                      plat->plateau[lignedep+1][colonnedep-1]=plat->plateau[lignedep][colonnedep];
                      *lignetmp=lignedep+1;
                      *colonnetmp=colonnedep-1;
                    }
                    else {
                      if(plat->plateau[lignedep][colonnedep].fourmi->color!=plat->plateau[lignedep+1][colonnedep-1].fourmi->color) {
                        Combat(plat, plat->plateau[lignedep][colonnedep].fourmi, plat->plateau[lignedep+1][colonnedep-1].fourmi);
                      }
                      else {
                        return -1;
                      }
                    }
                  }
                  else {
                    if (plat->plateau[lignedep-1][colonnedep-1].fourmi==NULL) {
                      plat->plateau[lignedep][colonnedep].fourmi->pos[0]--;
                      plat->plateau[lignedep][colonnedep].fourmi->pos[1]--;
                      plat->plateau[lignedep-1][colonnedep-1]=plat->plateau[lignedep][colonnedep];
                      *lignetmp=lignedep-1;
                      *colonnetmp=colonnedep-1;
                    }
                    else {
                      if(plat->plateau[lignedep][colonnedep].fourmi->color!=plat->plateau[lignedep-1][colonnedep-1].fourmi->color) {
                        Combat(plat, plat->plateau[lignedep][colonnedep].fourmi, plat->plateau[lignedep-1][colonnedep-1].fourmi);
                      }
                      else {
                        return -1;
                      }
                    }
                  }
                }
              }
            }
            plat->plateau[lignedep][colonnedep].fourmi=NULL;
            //plat->plateau[lignedep][colonnedep].fourmilliere=NULL;
            return 1;
          }
          else {
            printf("\nVous ne pouvez pas deplacer une fourmilliere\n");
            return -1;
          }
        }
      }
    }   else {
      if (!strcmp(ordre, "immobiliser")) {
        if (plat->plateau[lignedep][colonnedep].fourmi->type==3) {
          plat->plateau[lignedep][colonnedep].fourmi->immo=1;
        }
        return 1;
      }

      else {
        if (!strcmp(ordre, "detruire")) {
          if (plat->plateau[lignedep][colonnedep].fourmi->suiv!=NULL) {
            tmp=plat->plateau[lignedep][colonnedep].fourmi->suiv;
            plat->plateau[lignedep][colonnedep].fourmi->prec->suiv=tmp;
            tmp->prec=plat->plateau[lignedep][colonnedep].fourmi->prec;
            plat->plateau[lignedep][colonnedep].fourmi=NULL;
          }
          else {
            plat->plateau[lignedep][colonnedep].fourmi->prec->suiv=NULL;
            plat->plateau[lignedep][colonnedep].fourmi=NULL;
          }
        }
        //plat->plateau[lignedep][colonnedep].fourmilliere=NULL;
        return 1;
      }
    }
  }
  //afficher_plateau(plat);
  return 0;
}

void CreerFourmiliere (struct Fourmi* ant, char color, int ligne, int colone) {
  ant->color=color;
  ant->type=1;
  ant->pos[0]=ligne;
  ant->pos[1]=colone;
  ant->dest[0]=ligne;
  ant->dest[1]=colone;
  ant->suiv=NULL;
  ant->prec=NULL;
  ant->prev=NULL;
  ant->next=NULL;
  ant->immo=1;
  ant->typeF=0;
  ant->tp_prod=0.0;
}

void CreerReine (struct Fourmi* ant, char color, int ligne, int colone) {
  ant->color=color;
  ant->type=2;
  ant->pos[0]=ligne;
  ant->pos[1]=colone;
  ant->dest[0]=ligne;
  ant->dest[1]=colone;
  ant->suiv=NULL;
  ant->prec=NULL;
  ant->prev=NULL;
  ant->next=NULL;
  ant->immo=0;
  ant->typeF=0;
  ant->tp_prod=0.0;
}

void CreerOuvriere (struct Fourmi* ant, char color, int ligne, int colone) {
  ant->type=3;
  ant->color=color;
  ant->pos[0]=ligne;
  ant->pos[1]=colone;
  ant->dest[0]=ligne;
  ant->dest[1]=colone;
  ant->suiv=NULL;
  ant->prec=NULL;
  ant->prev=NULL;
  ant->next=NULL;
  ant->immo=0;
  ant->typeF=0;
  ant->tp_prod=0.0;
}

void CreerSoldat (struct Fourmi* ant, char color, int ligne, int colone) {
  ant->color=color;
  ant->dest[0]=ligne;
  ant->dest[1]=colone;
  ant->immo=0;
  ant->pos[0]=ligne;
  ant->pos[1]=colone;
  ant->suiv=NULL;
  ant->prec=NULL;
  ant->prev=NULL;
  ant->next=NULL;
  ant->tp_prod=0.0;
  ant->type=4;
  ant->typeF=0;
}

int Libre (struct Monde* world, int ligne, int colonne, int* i, int* j) {
  *i=1;
  *j=1;
  if (!ligne && !colonne) { //haut gaucheOK
    printf("\n\t1\n");
    if (world->plateau[ligne][colonne+(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne+1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne+(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne+1;
      return 1;
    }
    return 0;
  }
  if (!ligne && colonne<SIZE-1) { //hautOK
    printf("\n\t2\n");
    if (world->plateau[ligne][colonne+(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne+1;
      return 1;
    }
    if (world->plateau[ligne][colonne-(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne-(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne+(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne+1;
      return 1;
    }
    return 0;
  }
  if (!ligne && colonne==SIZE-1) { //haut droitOK
    printf("\n\t3\n");
    if (world->plateau[ligne][colonne-(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne-(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne-1;
      return 1;
    }
    return 0;
  }
  if (ligne<SIZE-1 && !colonne) { //gaucheOK
    printf("\n\t4\n");
    if (world->plateau[ligne][colonne+(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne+1;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne+(*j)].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne+1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne+(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne+1;
      return 1;
    }
    return 0;
  }
  if (ligne<SIZE-1 && colonne<SIZE-1) { //centreOK
    printf("\n\t5\n");
    if (world->plateau[ligne][colonne+(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne+1;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne+(*j)].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne+1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne+(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne+1;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne-(*j)].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne][colonne-(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne-(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne-1;
      return 1;
    }
    return 0;
  }
  if (ligne<SIZE-1 && colonne==SIZE-1) { //droitOK
    printf("\n\t6\n");
    if (world->plateau[ligne][colonne-(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne-(*j)].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne-(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne-1;
      return 1;
    }
    return 0;
  }
  if (ligne==SIZE-1 && !colonne) { //bas gaucheOK
    printf("\n\t7\n");
    if (world->plateau[ligne][colonne+(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne+1;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne+(*j)].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne+1;
      return 1;
    }
    return 0;
  }
  if (ligne==SIZE-1 && colonne<SIZE-1) { //basOK
    printf("\n\t8\n");
    if (world->plateau[ligne][colonne-(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne-(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne][colonne-(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne+(*i)][colonne+(*j)].fourmi==NULL) {
      *i=ligne+1;
      *j=colonne+1;
      return 1;
    }
    return 0;
  }
  if (ligne==SIZE-1 && colonne==SIZE-1) { //bas droitOK
    printf("\n^^\n");
    if (world->plateau[ligne][colonne-(*j)].fourmi==NULL) {
      *i=ligne;
      *j=colonne-1;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne;
      return 1;
    }
    if (world->plateau[ligne-(*i)][colonne-(*j)].fourmi==NULL) {
      *i=ligne-1;
      *j=colonne-1;
      return 1;
    }
    return 0;
  }
  return 0;
}

int produire_agent (struct Monde* plat, int ligne, int colonne, int code,char color, struct Fourmi* ant) {

  struct Fourmi* tmp= malloc(sizeof (struct Fourmi));

  int i;

  int j;

  if (plat->plateau[ligne][colonne].fourmi->type==1 && Libre(plat, ligne, colonne, &i, &j)) {

    switch (code) {

    case 2:

      //On produit une reine.

      CreerReine(ant, color, i, j);

      plat->plateau[i][j].fourmi=ant;

      //~ plat->plateau[i][j].fourmi=&ant;

      break;

    case 3:

      //On produit une ouvriere.

      CreerOuvriere(ant, color, i, j);

      plat->plateau[i][j].fourmi=ant;

      break;

    case 4:

      //On produit un soldat.

      CreerSoldat(ant, color, i, j);

      plat->plateau[i][j].fourmi=ant;

      break;

    default:

      break;

    }

    //~ afficher_plateau(plat->plateau);

    //~ if (plat->plateau[i][j].fourmi->tp_prod==0){

    ant->prec=plat->plateau[ligne][colonne].fourmi;

    tmp=plat->plateau[ligne][colonne].fourmi->suiv;

    plat->plateau[ligne][colonne].fourmi->suiv=ant;

    ant->suiv=tmp;

//}

    return 1;

  }

  else {

    printf("Fourmiliere encerclee, impossible de creer un nouvel element\n");

    return 0;

  }

  free(tmp);

}

void init_monde (struct Monde* m,struct Fourmi* Fn, struct Fourmi* Fr, struct Fourmi* Or, struct Fourmi* On, struct Fourmi* Rn, struct Fourmi* Rr ) {
  int i, j;
  for (i=0; i<SIZE; i++) {
    for (j=0; j<SIZE; j++) {
      m->plateau[i][j].fourmi=NULL;
      //m->plateau[i][j].fourmilliere=NULL;
    }
  }
  CreerFourmiliere(Fr, 'r', 0,0);
  CreerFourmiliere(Fn, 'n', SIZE-1,SIZE-1);
  CreerOuvriere(Or, 'r',  0, 1);
  CreerOuvriere(On, 'n',  SIZE-1, SIZE-2);
  CreerReine(Rr, 'r', 1, 0);
  CreerReine(Rn, 'n', SIZE-2, SIZE-1);
  Fr->suiv=Or;
  Or->prec=Fr;
  Or->suiv=Rr;
  Rr->prec=Or;
  Fn->suiv=On;
  On->prec=Fn;
  On->suiv=Rn;
  Rn->prec=On;
  m->plateau[0][0]. fourmi=Fr;
  m->plateau[0][1].fourmi=Or;
  m->plateau[1][0].fourmi=Rr;
  m->plateau[SIZE-1][SIZE-1].fourmi=Fn;
  m->plateau[SIZE-1][SIZE-2].fourmi=On;
  m->plateau[SIZE-2][SIZE-1].fourmi=Rn;
  m->Frouge=Fr;
  m->Fnoir=Fn;
}

void ChangeReineFourmi(struct Monde* m, struct Fourmi* ant, int r2, int r3, char color) {
  struct Fourmi* tmpR= m->Frouge;
  struct Fourmi* tmpN= m->Fnoir;
  //struct Fourmi* tmp=malloc(sizeof(struct Fourmi));
  CreerFourmiliere(ant, color,r2,r3);
  ant->next=NULL;
  ant->prev=NULL;
  m->plateau[r2][r3].fourmi=ant;
  if (color=='r') {
    while(tmpR->next!=NULL) {
      tmpR=tmpR->next;
    }
    tmpR->next=ant;
    ant->prev=tmpR;
  }
  else {
    while(tmpN->next!=NULL) {
      tmpN=tmpN->next;
    }
    tmpN->next=ant;
    ant->prev=tmpN;
  }
}
int main (){
return 0;
}
