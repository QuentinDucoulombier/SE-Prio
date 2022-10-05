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
  // Tri des processus en fonction tu TpsArr

  /* A Faire :
     Développer ici code pour le FIFO
  */

}

//////////////////////////////////////////////////////////////////////////
// Fonction  : SRT                                                      //
// Acces     : Public                                                   //
// But       : Tri des processus en fonction du SRT                     //
//                                                                      //
// Arguments                                                            //
// - IN      : neant                                                    //
// - IN/OUT  : neant                                                    //
// - OUT     : neant                                                    //
// Retour    : neant                                                    //
//                                                                      //
// Historique                       Date        Version  par            //
// Création de la fonction SRT      10/09/2022  1.0.01   Alain          //
//////////////////////////////////////////////////////////////////////////

void SRT(process* proc, int nbp)
{
  // Utilise le FIFO pour ordonner les processus
  FIFO(proc,nbp);
  // Calcul du TotExe & TpsFin
  int TotExe,TpsFin;
  TotExe=0;
  TpsFin=0;
  int i;
  for(i=0;i<nbp;i++)
  { TotExe = TotExe + proc[i].TpsExe;
    TpsFin = proc[i].TpsExe;
    proc[i].TpsFin = TpsFin;
  }
  // Tri des processus en fonction tu TpsExe
  process permut;
  int current;
  current = 0;
  int j;
  for(i=0;i<nbp;i++)
  { for(j=i+1;j<nbp;j++)
    { if (proc[i].TpsExe > proc[j].TpsExe)
      { permut=proc[i];
        proc[i]=proc[j];
        proc[j]=permut;
        current = j;
//	printf("SRT : %s permute avec %s\n",proc[i].nom,proc[j].nom);
      }
    }
  }
  // Mise en attente

  /* A Faire */

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

void ORDO(process* proc, int nbp)
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
  {
    TpsFin = TpsFin + proc[i].TpsExe;
    TpsSej = TpsFin - proc[i].TpsArr;
    TpsAtt = TpsSej - proc[i].TpsExe;

    TotSej = TotSej + TpsSej;
    TotAtt = TotAtt + TpsAtt;

    proc[i].TpsFin = TpsFin;
    proc[i].TpsSej = TpsSej;
    proc[i].TpsAtt = TpsAtt;
  }
  float TpsSejMoy,TpsAttMoy;
  TpsSejMoy=(float)TotSej/nbp;
  TpsAttMoy=(float)TotAtt/nbp;

  // Afficher le Temps d'execution et le Temps d'arrivee et de chaque processus
  printf("Processus\t TpsExe\t TpsArr\t TpsSej\t TpsAtt\n");
  for (i=0;i<nbp;i++)
  { printf("%s\t\t %d\t %d\t %d\t %d\n",proc[i].nom,proc[i].TpsExe,proc[i].TpsArr,proc[i].TpsSej,proc[i].TpsAtt);
  }
  printf("\n");

  // afficher les temps moyen de sejour et d'attente
  printf("le temps moyen de sejour est = %f\n",TpsSejMoy);
  printf("le temps moyen d'attente est = %f\n",TpsAttMoy);
}

//////////////////////////////////////////////////////////////////////////
// Programme : 03-SRT.c                                                 //
// Acces     : SE                                                       //
// But       : Ordonnancement FIFO ou FCFS                              //
//                                                                      //
// Arguments                                                            //
// - IN      : neant                                                    //
// - IN/OUT  : neant                                                    //
// - OUT     : neant                                                    //
// Retour    : neant                                                    //
//                                                                      //
// Historique                       Date        Version  par            //
// Création de 03-SRT.c             10/09/2022  1.0.00   Alain          //
//////////////////////////////////////////////////////////////////////////

void main()
{
  int nbp = 5;
  process* proc;
  proc=(process *)malloc(sizeof(process)*nbp);

  // Appel du SRT
  printf("Ordonnancement SRT  :\n");
  printf("*********************\n");
  nbp = 2;
  strcpy(proc[0].nom,"A");
  proc[0].TpsExe=10;
  proc[0].TpsArr=0;
  strcpy(proc[1].nom,"B");
  proc[1].TpsExe=4;
  proc[1].TpsArr=2;

/*
  strcpy(proc[2].nom,"C");
  proc[2].TpsExe=2;
  proc[2].TpsArr=8;
*/

  SRT(proc,nbp);

}
