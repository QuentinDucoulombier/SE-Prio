#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process
{
  char nom[20];
  int TpsExe;
  int TpsArr;
  int TpsFin;
  int TpsSej;
  int TpsAtt;
} process;

//////////////////////////////////////////////////////////////////////////
// Fonction  : FIFO                                                     //
// Acces     : Public                                                   //
// But       : Tri des processus en fonction du TpsArr                  //
//                                                                      //
// Arguments                                                            //
// - IN      : neant                                                    //
// - IN/OUT  : neant                                                    //
// - OUT     : neant                                                    //
// Retour    : neant                                                    //
//                                                                      //
// Historique                       Date        Version  par            //
// Création de la fonction FIFO     10/09/2022  1.0.01   Alain          //
//////////////////////////////////////////////////////////////////////////

void FIFO(process* proc , int nbp)
{
  // Tri des processus en fonction tu TpsArr (Temps Arrivée)

  /* A Faire :
     Développer ici code pour le FIFO
  */

}

//////////////////////////////////////////////////////////////////////////
// Fonction  : SJF                                                      //
// Acces     : Public                                                   //
// But       : Tri des processus en fonction du TpsExe                  //
//                                                                      //
// Arguments                                                            //
// - IN      : neant                                                    //
// - IN/OUT  : neant                                                    //
// - OUT     : neant                                                    //
// Retour    : neant                                                    //
//                                                                      //
// Historique                       Date        Version  par            //
// Création de la fonction SJF      10/09/2022  1.0.01   Alain          //
//////////////////////////////////////////////////////////////////////////

void SJF(process* proc , int nbp)
{
  // Utilise le FIFO pour ordonner les processus
  FIFO(proc,nbp);
  // Calcul du TpsFin, TpsSej et TpsAtt
  int TpsFin,TpsSej,TpsAtt;
  TpsFin=0;
  TpsSej=0;
  TpsAtt=0;
  int i;
  for(i=0;i<nbp;i++)
  { TpsFin = TpsFin + proc[i].TpsExe;
    TpsSej = TpsFin - proc[i].TpsArr;
    TpsAtt = TpsSej - proc[i].TpsExe;

    proc[i].TpsFin = TpsFin;
    proc[i].TpsSej = TpsSej;
    proc[i].TpsAtt = TpsAtt;
  }
  // Réalise le tri Shortest Job First

  /* A Faire :
     Développer ici code pour le SJF
  */

  // Afficher l'enchainement des processus
  for(i=0;i<nbp;i++)
  { for(j=0;j<proc[i].TpsExe;j++)
    { printf("%s ",proc[i].nom);
    }
  }
  printf("\n\n");
}

//////////////////////////////////////////////////////////////////////////
// Fonction  : ORDO                                                     //
// Acces     : Public                                                   //
// But       : Calcul et affiche le TpsSej et TpsAtt                    //
//                                                                      //
// Arguments                                                            //
// - IN      : neant                                                    //
// - IN/OUT  : neant                                                    //
// - OUT     : neant                                                    //
// Retour    : neant                                                    //
//                                                                      //
// Historique                       Date        Version  par            //
// Création de la fonction ORDO     10/09/2022  1.0.01   Alain          //
//////////////////////////////////////////////////////////////////////////

void ORDO(process* proc , int nbp)
{
  // Calcul du TpsFin, TpsSej, TotSej et TpsAtt, TotAtt
  int TpsFin,TpsSej,TotSej,TpsAtt,TotAtt;
  TpsFin=0;
  TpsSej=0;
  TotSej=0;
  TpsAtt=0;
  TotAtt=0;
  int i;
  for(i=0;i<nbp;i++)
  { TpsFin = TpsFin + proc[i].TpsExe;
    TpsSej = TpsFin - proc[i].TpsArr;
    TpsAtt = TpsSej - proc[i].TpsExe;

    TotSej = TotSej + TpsSej;
    TotAtt = TotAtt + TpsAtt;

    proc[i].TpsFin = TpsFin;
    proc[i].TpsSej = TpsSej;
    proc[i].TpsAtt = TpsAtt;
  }
  // Afficher le Temps d'execution et le Temps d'arrivee et de chaque processus
  printf("Processus\t TpsExe\t TpsArr\t TpsSej\t TpsAtt\n");
  for (i=0;i<nbp;i++)
  { printf("%s\t\t %d\t %d\t %d\t %d\n",proc[i].nom,proc[i].TpsExe,proc[i].TpsArr,proc[i].TpsSej,proc[i].TpsAtt);
  }
  printf("\n");
  // afficher les temps moyen de sejour et d'attente
  float TpsSejMoy,TpsAttMoy;
  TpsSejMoy=(float)TotSej/nbp;
  TpsAttMoy=(float)TotAtt/nbp;
  printf("le temps moyen de sejour est = %f\n",TpsSejMoy);
  printf("le temps moyen d'attente est = %f\n",TpsAttMoy);
}

//////////////////////////////////////////////////////////////////////////
// Programme : 01-SJF.c                                                 //
// Acces     : SE                                                       //
// But       : Ordonnancement SJF (Shortest Job First)                  //
//                                                                      //
// Arguments                                                            //
// - IN      : neant                                                    //
// - IN/OUT  : neant                                                    //
// - OUT     : neant                                                    //
// Retour    : neant                                                    //
//                                                                      //
// Historique                       Date        Version  par            //
// Création de 01-SJF.c             10/09/2022  1.0.00   Alain          //
//////////////////////////////////////////////////////////////////////////

void main()
{
  // Creation de cinq processus
  int nbp = 5;
  process* proc;
  proc=(process *)malloc(sizeof(process)*nbp);
  // Initialisation des données
  strcpy(proc[0].nom,"A");
  proc[0].TpsExe=3;
  proc[0].TpsArr=0;
  strcpy(proc[1].nom,"B");
  proc[1].TpsExe=6;
  proc[1].TpsArr=1;
  strcpy(proc[2].nom,"C");
  proc[2].TpsExe=4;
  proc[2].TpsArr=4;
  strcpy(proc[3].nom,"D");
  proc[3].TpsExe=2;
  proc[3].TpsArr=6;
  strcpy(proc[4].nom,"E");
  proc[4].TpsExe=1;
  proc[4].TpsArr=7;
  // Afficher l'ordonnancement appilqué
  printf("Ordonnancement SJF  :\n");
  printf("*********************\n");
  // Appel du SJF
  SJF(proc,nbp);
  ORDO(proc,nbp);
}
