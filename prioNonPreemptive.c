/** @file prio.c
 *  @author William Meunier<meunierwil@cy-tech.fr>
 *  @version 0.1
 *  @date Wed 05 Oct 2022 12:01
 *
 *  @brief projet SE
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////

typedef struct process
{
    char nom[20];
    int TpsExe;
    int TpsArr;
    int TpsFin;
    int TpsSej;
    int TpsAtt;
    int priorite;
} process;

/**
 *  @fn void FIFO (process *proc, int nbp)
 *  @author William Meunier<meunierwil@cy-tech.fr>
 *  @version 0.1
 *  @date Wed 05 Oct 2022 12:23
 *
 *  @brief Ordonne les proc en FIFO
 *
 *  @param[in]
 *
 */
void FIFO(process *proc, int nbp)
{
    process permut;
    int i;
    for (i = 0; i < nbp - 1; i++)
    {
        if (proc[i + 1].TpsArr < proc[i].TpsArr)
        {
            permut = proc[i];
            proc[i] = proc[i + 1];
            proc[i + 1] = permut;
        }
    }
}

/**
 *  @fn void prio (process *proc, int nbp)
 *  @author William Meunier<meunierwil@cy-tech.fr>
 *  @version 0.1
 *  @date Wed 05 Oct 2022 12:06
 *
 *  @brief
 *
 *  @param[in]
 *
 */
void prio(process *proc, int nbp)
{
    // Utilise le FIFO pour ordonner les processus
    FIFO(proc, nbp);
    // Calcul du TpsFin, TpsSej et TpsAtt
    int TpsFin, TpsSej, TpsAtt;
    TpsFin = 0;
    TpsSej = 0;
    TpsAtt = 0;
    int i;
    int j;
    for (i = 0; i < nbp; i++)
    {
        TpsFin = TpsFin + proc[i].TpsExe;
        TpsSej = TpsFin - proc[i].TpsArr;
        TpsAtt = TpsSej - proc[i].TpsExe;

        proc[i].TpsFin = TpsFin;
        proc[i].TpsSej = TpsSej;
        proc[i].TpsAtt = TpsAtt;
    }
    // R�alise le tri PRIO non préemptive

    process permut;
    for (i = 0; i < nbp; i++)
    {
        for (j = 0; j < nbp; j++)
        {
            if (proc[i].TpsSej == proc[j].TpsSej)
            {
                if (proc[i].priorite < proc[j].priorite)
                {
                    permut = proc[i];
                    proc[i] = proc[j];
                    proc[j] = permut;
                }
            }
        }
    }

    // Afficher l'enchainement des processus
    for (i = 0; i < nbp; i++)
    {
        for (j = 0; j < proc[i].TpsExe; j++)
        {
            printf("%s ", proc[i].nom);
        }
    }
    printf("\n\n");
}
/**
 *  @fn void ORDO (process *proc, int nbp)
 *  @author William Meunier<meunierwil@cy-tech.fr>
 *  @version 0.1
 *  @date Wed 05 Oct 2022 12:15
 *
 *  @brief Calcul temps : Fin, Sej, Att et total : Fin, Sej, Att
 *
 *  @param[in]
 *
 */

void ORDO(process *proc, int nbp)
{
    // Calcul du TpsFin, TpsSej, TotSej et TpsAtt, TotAtt
    int TpsFin, TpsSej, TotSej, TpsAtt, TotAtt;
    TpsFin = 0;
    TpsSej = 0;
    TotSej = 0;
    TpsAtt = 0;
    TotAtt = 0;
    int i;
    for (i = 0; i < nbp; i++)
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
    // Afficher le Temps d'execution et le Temps d'arrivee et de chaque processus
    printf("Processus\t TpsExe\t TpsArr\t TpsSej\t TpsAtt\n priorité\n");
    for (i = 0; i < nbp; i++)
    {
        printf("%s\t\t %d\t %d\t %d\t %d\t %d\n", proc[i].nom, proc[i].TpsExe, proc[i].TpsArr, proc[i].TpsSej, proc[i].TpsAtt, proc[i].priorite);
    }
    printf("\n");
    // afficher les temps moyen de sejour et d'attente
    float TpsSejMoy, TpsAttMoy;
    TpsSejMoy = (float)TotSej / nbp;
    TpsAttMoy = (float)TotAtt / nbp;
    printf("le temps moyen de sejour est = %f\n", TpsSejMoy);
    printf("le temps moyen d'attente est = %f\n", TpsAttMoy);
}

/////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn int main (int argc, char const *argv[])
 *  @author William Meunier<meunierwil@cy-tech.fr>
 *  @version 0.1
 *  @date Wed 05 Oct 2022 12:04
 *
 *  @brief Fonction Principale
 *
 *  @param[in] argc Nombre d'arguments
 *  @param[in] *argv[] Tableau d'arguments
 *  @return EXIT_SUCCESS : le programme doit se terminer normalement
 *
 */
int main()
{

    // Creation de cinq processus
    int nbp = 5;
    process *proc;
    proc = (process *)malloc(sizeof(process) * nbp);
    // Initialisation des donn�es
    strcpy(proc[0].nom, "A");
    proc[0].TpsExe = 3;
    proc[0].TpsArr = 0;
    proc[0].priorite = 3;
    strcpy(proc[1].nom, "B");
    proc[1].TpsExe = 6;
    proc[1].TpsArr = 1;
    proc[1].priorite = 2;
    strcpy(proc[2].nom, "C");
    proc[2].TpsExe = 4;
    proc[2].TpsArr = 4;
    proc[2].priorite = 5;
    strcpy(proc[3].nom, "D");
    proc[3].TpsExe = 2;
    proc[3].TpsArr = 6;
    proc[3].priorite = 4;
    strcpy(proc[4].nom, "E");
    proc[4].TpsExe = 1;
    proc[4].TpsArr = 7;
    proc[4].priorite = 1;
    // Afficher l'ordonnancement appilqu�
    printf("Ordonnancement PRIO  :\n");
    printf("*********************\n");
    // Appel de PRIO
    prio(proc, nbp);
    ORDO(proc, nbp);

    return (0);
}
