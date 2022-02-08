#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define SIZE 8
#define GOLD 50

//Ouverture fermeture de fichier, chargement de la sauvegarde !!

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

int main () {
  int a, b,tour, gold1, gold2, prod, ligned, colonned, i, j, h;
  int choix=0;
  char saisie[256];
  struct Monde m;
  struct Fourmi Fn;
  struct Fourmi Fr;
  struct Fourmi Or;
  struct Fourmi On;
  struct Fourmi Rn;
  struct Fourmi Rr;
  struct Fourmi* rouge=malloc(sizeof(struct Fourmi));
  struct Fourmi* rouge2=malloc(sizeof(struct Fourmi));
  struct Fourmi* noir=malloc(sizeof(struct Fourmi));
  struct Fourmi* noir2=malloc(sizeof(struct Fourmi));
  gold1=gold2=GOLD;
  tour=1;
  init_monde(&m, &Fn, &Fr, &Or, &On, &Rn, &Rr);
  while (choix!=4) {
    i=0;
    j=0;
    h=0;
    rouge=m.Frouge;
    rouge2=m.Frouge;
    noir=m.Fnoir;
    noir2=m.Fnoir;
    while(h==0) {
      printf("\t     TOUR n°%d\n", tour);
      afficher_plateau(m.plateau);
      //c'est le 1er joueur qui joue
      printf("\n     JOUEUR 1 (Fourmis Rouges)\n");
      printf("           Argent : %d", gold1);
      printf("\nChoisissez l'action\n1: Jouer\n2: Passer tour\n3: Sauvegarder\n4: Quitter\n");
      choix=(int) lireLong();
      if (choix>=1 && choix<=4 && choix!=0) { //// Secure
        h=1;
        if (choix==1) { //on joue
          while (rouge2!=NULL) {
            while (rouge!=NULL) {
              if (rouge->type==1) { //On joue une fourmilliere
                if (!rouge->typeF && !rouge->tp_prod) {
                  while (i==0) {
                    printf("Actions pour la fourmiliere en %d %d\n1:Produire\n2:Ne rien faire\n", rouge->pos[0], rouge->pos[1]);
                    choix=(int) lireLong();
                    if ((choix==1 || choix==2) && choix!=0) { //// Secure
                      i=1;
                      if (choix==1) {
                        while (j==0) {
                          printf("Que voulez-vous produire?\n1:Une Reine(Prend 6 tours et 20 pieces)\n2:Une Ouvriere(Prend 2 tours et 1 pieces)\n3:Un Soldat(Prend 4 tours et 5 pieces)\n");
                          prod=(int) lireLong();
                          if ((prod>=1 && prod<=3) && choix!=0) { //// Secure
                            j=1;
                            switch(prod) {
                            case 1://Reine
                              if (gold1>=20) {
                                rouge->tp_prod=5;
                                rouge->typeF=2;
                                gold1=gold1-20;
                              }
                              else {
                                printf("Il vous manque %d pieces\n", 60-gold1);
                                printf("Que voulez-vous produire?\n1:Une Reine(Prend 6 tours et 20 pieces)\n2:Une Ouvriere(Prend 2 tours et 1 pieces)\n3:Un Soldat(Prend 4 tours et 5 pieces)\n");
                              }
                              break;
                            case 2://Ouvriere
                              if (gold1>=1) {
                                rouge->tp_prod=1;
                                rouge->typeF=3;
                                gold1=gold1-1;
                              }
                              else {
                                printf("Il vous manque %d pieces\n", 1-gold1);
                                printf("Que voulez-vous produire?\n1:Une Reine(Prend 6 tours et 20 pieces)\n2:Une Ouvriere(Prend 2 tours et 1 pieces)\n3:Un Soldat(Prend 4 tours et 5 pieces)\n");
                                if (scanf("%d", &prod)!=-1);
                              }
                              break;
                            case 3://Soldat
                              if (gold1>=5) {
                                rouge->tp_prod=3;
                                rouge->typeF=4;
                                gold1=gold1-5;
                              }
                              else {
                                printf("Il vous manque %d pieces\n", 5-gold1);
                                printf("Que voulez-vous produire?\n1:Une Reine(Prend 6 tours et 20 pieces)\n2:Une Ouvriere(Prend 2 tours et 1 piece)\n3:Un Soldat(Prend 4 tours et 5 pieces)\n");
                                if (scanf("%d", &prod)!=-1);
                              }
                              break;
                            default:
                              break;
                            }
                          }
                          else {
                            printf(" !! Saisie Incorrecte recommencez !!\n");
                          }
                        }
                        j=0;
                      }
                      else {
                        i=1;
                      }
                    }
                  }
                  i=0;
                }

                else {
                  if(!rouge->tp_prod) {
                    struct Fourmi* tmpr=malloc(sizeof(struct Fourmi));
                    produire_agent(&m, rouge->pos[0], rouge->pos[1], rouge->typeF, 'r', tmpr);
                    afficher_plateau(m.plateau);
                    rouge->typeF=0;
                    rouge=rouge->suiv;
                  }
                  else {
                    rouge->tp_prod--;
                    printf("Il reste %d tours\n", rouge->tp_prod);
                  }
                }
              }
              else {
                if (rouge->type==2) { //On joue une Reine
                  while (i==0) {
                    printf("^^^^\n");
                    if (rouge->pos[0]==rouge->dest[0] && rouge->pos[1]==rouge->dest[1]) {
                      printf("Actions pour la Reine en %d %d\n-bouger\n-immobiliser(Ne rien faire)\n-detruire\n-transformer(Effet immediat et prend 30 pieces) \n", rouge->pos[0], rouge->pos[1]);
                      lire(saisie, 256);
                      if (!strcmp(saisie, "transformer")) {
                        if (gold1>=30) {
                          struct Fourmi* tmpF=malloc(sizeof (struct Fourmi));
                          int r2=rouge->pos[0];
                          int r3= rouge->pos[1];
                          ordre_fourmi(&m, "detruire", rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                          ChangeReineFourmi(&m,tmpF,r2,r3, 'r');
                          i=1;
                        }
                        else {
                          printf("\nIl vous manque %d pieces\n", 30-gold1);
                          i=0;
                        }
                      }
                      if (!strcmp("bouger", saisie)) {
                        i=1;
                        printf("Entrez la ligne et la colonne de la destination\n");
                        ligned=(int) lireLong();
                        colonned=(int) lireLong();
                        if (0<=ligned && ligned<SIZE && 0<=colonned && colonned<SIZE) {
                          rouge->dest[0]=ligned;
                          rouge->dest[1]=colonned;
                          ordre_fourmi(&m, "bouger", rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                        }
                        else {
                          printf("Deplacement impossible reessayez\n");
                          i=0;
                        }
                      }
                      else {
                        if (!strcmp("detruire", saisie) || !strcmp("immobiliser", saisie)) {
                          ordre_fourmi(&m, saisie, rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                          i=1;
                        }
                      }
                    }
                    else {
                      ordre_fourmi(&m, "bouger", rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                      i=1;
                    }
                  }
                  i=0;
                }
                else {
                  if (rouge->type==3) { //On joue une Ouvriere
                    if (rouge->immo==1) {
                      gold1++;
                    }
                    else {
                      while (i==0) {
                        if (rouge->pos[0]==rouge->dest[0] && rouge->pos[1]==rouge->dest[1]) {
                          printf("Actions pour l'Ouvriere en %d %d\n-bouger\n-immobiliser(Ne rien faire)\n-detruire\n", rouge->pos[0], rouge->pos[1]);
                          lire(saisie, 256);
                          if (!strcmp("bouger", saisie)) {
                            i=1;
                            printf("Entrez la ligne et la colonne de la destination\n");
                            ligned=(int) lireLong();
                            colonned=(int) lireLong();
                            if (0<=ligned && ligned<SIZE && 0<=colonned && colonned<SIZE) {
                              rouge->dest[0]=ligned;
                              rouge->dest[1]=colonned;
                              ordre_fourmi(&m, "bouger", rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                              printf("^^\n");
                            }
                            else {
                              printf("Deplacement impossible reessayez\n");
                              i=0;
                            }
                          }
                          else {
                            if (!strcmp("detruire", saisie) || !strcmp("immobiliser", saisie)) {
                              ordre_fourmi(&m, saisie, rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                              i=1;
                            }
                          }
                        }
                        else {
                          ordre_fourmi(&m, "bouger", rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                          i=1;
                        }
                      }
                      i=0;
                    }
                  }
                  else {
                    if (rouge->type==4) { //On joue un Soldat
                      while (i==0) {
                        printf("%d %d %d %d\n",rouge->pos[0], rouge->dest[0], rouge->pos[1], rouge->dest[1] );
                        if (rouge->pos[0]==rouge->dest[0] && rouge->pos[1]==rouge->dest[1]) {
                          printf("Actions pour le Soldat en %d %d\n-bouger\n-immobiliser(Ne rien faire)\n-detruire\n", rouge->pos[0], rouge->pos[1]);
                          lire(saisie, 256);
                          if (!strcmp("bouger", saisie)) {
                            printf("Entrez la ligne et la colonne de la destination\n");
                            ligned=(int) lireLong();
                            colonned=(int) lireLong();
                            if (0<=ligned && ligned<SIZE && 0<=colonned && colonned<SIZE) {
                              rouge->dest[0]=ligned;
                              rouge->dest[1]=colonned;
                              ordre_fourmi(&m, "bouger", rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                            }
                            else {
                              printf("Deplacement impossible reessayez\n");
                              i=0;
                            }
                          }
                          else {
                            if (!strcmp("detruire", saisie) || !strcmp("immobiliser", saisie)) {
                              ordre_fourmi(&m, saisie, rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                              i=1;
                            }
                          }
                        }
                        else {
                          ordre_fourmi(&m, "bouger", rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                          i=1;
                        }
                      }
                      i=0;
                    }
                  }
                }
              }
              rouge=rouge->suiv;
            }
            rouge2=rouge2->next;
            rouge=rouge2;
          }
        }

        else {
          if (choix==2) {
            while(rouge2!=NULL) {
              while (rouge!=NULL) {
                if (rouge->type==1) {
                  if(rouge->typeF!=0 && rouge->tp_prod!=0) {
                    rouge->tp_prod--;
                  }
                  else {
                    if(rouge->typeF!=0 && rouge->tp_prod==0) {
                      struct Fourmi* tmpr=malloc(sizeof(struct Fourmi));
                      produire_agent(&m, rouge->pos[0], rouge->pos[1], rouge->typeF, 'r', tmpr);
                      rouge->typeF=0;
                    }
                  }
                }
                else {
                  if (rouge->type==3 && rouge->immo==1) {
                    gold1++;
                  }
                  else {
                    if (rouge->dest[0]!=rouge->pos[0] || rouge->dest[1]!=rouge->pos[1]) {
                      ordre_fourmi(&m, "bouger", rouge->pos[0], rouge->pos[1], rouge->dest[0], rouge->dest[1], &a, &b);
                    }
                  }
                }
                rouge=rouge->suiv;
                //~ rouge=NULL;
              }
              rouge2=rouge2->next;
              rouge=rouge2;
            }
          }
        }
      } else {
        printf(" !!Erreur de saisie recommencez!!\n");
        h=0;
      }
    }
    h=0;

    if (choix==4) {
      break;
    }
    h=0;
    j=0;
    i=0;
//////////////////////////////////////////////////////////////////////////////////////////c'est le 2eme joueur qui joue
    while(h==0) {
      printf("\t     TOUR n°%d\n", tour);
      afficher_plateau(m.plateau);
      //c'est le 1er joueur qui joue
      printf("\n     JOUEUR 2 (Fourmis Noires)\n");
      printf("           Argent : %d", gold2);
      printf("\nChoisissez l'action\n1: Jouer\n2: Passer tour\n3: Sauvegarder\n4: Quitter\n");
      choix=(int) lireLong();
      if (choix>=1 && choix<=4 && choix!=0) { //// Secure
        h=1;
        if (choix==1) { //on joue
          while (noir2!=NULL) {
            while (noir!=NULL) {
              if (noir->type==1) { //On joue une fourmilliere
                if (!noir->typeF && !noir->tp_prod) {
                  while (i==0) {
                    printf("Actions pour la fourmiliere en %d %d\n1:Produire\n2:Ne rien faire\n", noir->pos[0], noir->pos[1]);
                    choix=(int) lireLong();
                    if ((choix==1 || choix==2) && choix!=0) { //// Secure
                      i=1;
                      if (choix==1) {
                        while (j==0) {
                          printf("Que voulez-vous produire?\n1:Une Reine(Prend 6 tours et 20 pieces)\n2:Une Ouvriere(Prend 2 tours et 1 pieces)\n3:Un Soldat(Prend 4 tours et 5 pieces)\n");
                          prod=(int) lireLong();
                          if ((prod>=1 && prod<=3) && choix!=0) { //// Secure
                            j=1;
                            switch(prod) {
                            case 1://Reine
                              if (gold2>=20) {
                                noir->tp_prod=5;
                                noir->typeF=2;
                                gold2=gold2-20;
                              }
                              else {
                                printf("Il vous manque %d pieces\n", 60-gold2);
                                printf("Que voulez-vous produire?\n1:Une Reine(Prend 6 tours et 20 pieces)\n2:Une Ouvriere(Prend 2 tours et 1 pieces)\n3:Un Soldat(Prend 4 tours et 5 pieces)\n");
                              }
                              break;
                            case 2://Ouvriere
                              if (gold2>=1) {
                                noir->tp_prod=1;
                                noir->typeF=3;
                                gold2=gold2-1;
                              }
                              else {
                                printf("Il vous manque %d pieces\n", 1-gold2);
                                printf("Que voulez-vous produire?\n1:Une Reine(Prend 6 tours et 20 pieces)\n2:Une Ouvriere(Prend 2 tours et 1 pieces)\n3:Un Soldat(Prend 4 tours et 5 pieces)\n");
                                if (scanf("%d", &prod)!=-1);
                              }
                              break;
                            case 3://Soldat
                              if (gold2>=5) {
                                noir->tp_prod=3;
                                noir->typeF=4;
                                gold2=gold2-5;
                              }
                              else {
                                printf("Il vous manque %d pieces\n", 5-gold2);
                                printf("Que voulez-vous produire?\n1:Une Reine(Prend 6 tours et 20 pieces)\n2:Une Ouvriere(Prend 2 tours et 1 piece)\n3:Un Soldat(Prend 4 tours et 5 pieces)\n");
                                if (scanf("%d", &prod)!=-1);
                              }
                              break;
                            default:
                              break;
                            }
                          }
                          else {
                            printf(" !! Saisie Incorrecte recommencez !!\n");
                          }
                        }
                        j=0;
                      }
                      else {
                        i=1;
                      }
                    }
                  }
                  i=0;
                }

                else {
                  if(!noir->tp_prod) {
                    struct Fourmi* tmpr=malloc(sizeof(struct Fourmi));
                    produire_agent(&m, noir->pos[0], noir->pos[1], noir->typeF, 'n', tmpr);
                    afficher_plateau(m.plateau);
                    noir->typeF=0;
                    noir=noir->suiv;
                  }
                  else {
                    noir->tp_prod--;
                    printf("Il reste %d tours\n", noir->tp_prod);
                  }
                }
              }
              else {
                if (noir->type==2) { //On joue une Reine
                  while (i==0) {

                    if (noir->pos[0]==noir->dest[0] && noir->pos[1]==noir->dest[1]) {
                      printf("^^^^\n");
                      printf("Actions pour la Reine en %d %d\n-bouger\n-immobiliser(Ne rien faire)\n-detruire\n-transformer(Effet immediat et prend 30 pieces) \n", noir->pos[0], noir->pos[1]);
                      lire(saisie, 256);
                      if (!strcmp(saisie, "Transformer")) {
                        if (gold1>=30) {
                          struct Fourmi* tmpF=malloc(sizeof (struct Fourmi));
                          int r2=noir->pos[0];
                          int r3= noir->pos[1];
                          ordre_fourmi(&m, "detruire", noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                          ChangeReineFourmi(&m,tmpF,r2,r3, 'n');
                          i=1;
                        }
                        else {
                          printf("\nIl vous manque %d pieces\n", 30-gold1);
                          i=0;
                        }
                      }
                      if (!strcmp("bouger", saisie)) {
                        i=1;
                        printf("Entrez la ligne et la colonne de la destination\n");
                        ligned=(int) lireLong();
                        colonned=(int) lireLong();
                        if (0<=ligned && ligned<SIZE && 0<=colonned && colonned<SIZE) {
                          noir->dest[0]=ligned;
                          noir->dest[1]=colonned;
                          ordre_fourmi(&m, "bouger", noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                        }
                        else {
                          printf("Deplacement impossible reessayez\n");
                          i=0;
                        }
                      }
                      else {
                        if (!strcmp("detruire", saisie) || !strcmp("immobiliser", saisie)) {
                          ordre_fourmi(&m, saisie, noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                          i=1;
                        }
                      }
                    }
                    else {
                      ordre_fourmi(&m, "bouger", noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                      i=1;
                    }
                  }
                  i=0;
                }
                else {
                  if (noir->type==3) { //On joue une Ouvriere
                    if (noir->immo==1) {
                      gold1++;
                    }
                    else {
                      while (i==0) {
                        if (noir->pos[0]==noir->dest[0] && noir->pos[1]==noir->dest[1]) {
                          printf("Actions pour l'Ouvriere en %d %d\n-bouger\n-immobiliser(Ne rien faire)\n-detruire\n", noir->pos[0], noir->pos[1]);
                          lire(saisie, 256);
                          if (!strcmp("bouger", saisie)) {
                            i=1;
                            printf("Entrez la ligne et la colonne de la destination\n");
                            ligned=(int) lireLong();
                            colonned=(int) lireLong();
                            if (0<=ligned && ligned<SIZE && 0<=colonned && colonned<SIZE) {
                              noir->dest[0]=ligned;
                              noir->dest[1]=colonned;
                              ordre_fourmi(&m, "bouger", noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                              printf("^^\n");
                            }
                            else {
                              printf("Deplacement impossible reessayez\n");
                              i=0;
                            }
                          }
                          else {
                            if (!strcmp("detruire", saisie) || !strcmp("immobiliser", saisie)) {
                              ordre_fourmi(&m, saisie, noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                              i=1;
                            }
                          }
                        }
                        else {
                          ordre_fourmi(&m, "bouger", noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                          i=1;
                        }
                      }
                      i=0;
                    }
                  }
                  else {
                    if (noir->type==4) { //On joue un Soldat
                      while (i==0) {
                        if (noir->pos[0]==noir->dest[0] && noir->pos[1]==noir->dest[1]) {
                          printf("Actions pour le Soldat en %d %d\n-bouger\n-immobiliser(Ne rien faire)\n-detruire\n", noir->pos[0], noir->pos[1]);
                          lire(saisie, 256);
                          if (!strcmp("bouger", saisie)) {
                            printf("Entrez la ligne et la colonne de la destination\n");
                            ligned=(int) lireLong();
                            colonned=(int) lireLong();
                            if (0<=ligned && ligned<SIZE && 0<=colonned && colonned<SIZE) {
                              noir->dest[0]=ligned;
                              noir->dest[1]=colonned;
                              ordre_fourmi(&m, "bouger", noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                            }
                            else {
                              printf("Deplacement impossible reessayez\n");
                              i=0;
                            }
                          }
                          else {
                            if (!strcmp("detruire", saisie) || !strcmp("immobiliser", saisie)) {
                              ordre_fourmi(&m, saisie, noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                              i=1;
                            }
                          }
                        }
                        else {
                          ordre_fourmi(&m, "bouger", noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                          i=1;
                        }
                      }
                      i=0;
                    }
                  }
                }
              }
              noir=noir->suiv;
            }
            noir2=noir2->next;
            noir=noir2;
          }
        }

        else {
          if (choix==2) {
            while(noir2!=NULL) {
              while (noir!=NULL) {
                if (noir->type==1) {
                  if(noir->typeF!=0 && noir->tp_prod!=0) {
                    noir->tp_prod--;
                  }
                  else {
                    if(noir->typeF!=0 && noir->tp_prod==0) {
                      struct Fourmi* tmpr=malloc(sizeof(struct Fourmi));
                      produire_agent(&m, noir->pos[0], noir->pos[1], noir->typeF, 'n', tmpr);
                      noir->typeF=0;
                    }
                  }
                }
                else {
                  if (noir->type==3 && noir->immo==1) {
                    gold1++;
                  }
                  else {
                    if (noir->dest[0]!=noir->pos[0] || noir->dest[1]!=noir->pos[1]) {
                      ordre_fourmi(&m, "bouger", noir->pos[0], noir->pos[1], noir->dest[0], noir->dest[1], &a, &b);
                    }
                  }
                }
                noir=noir->suiv;
              }
              noir2=noir2->next;
              noir=noir2;
            }
          }
        }
      } else {
        printf(" !!Erreur de saisie recommencez!!\n");
        h=0;
      }
    }
    tour++;
  }
  return 0;
}

