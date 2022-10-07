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

/**
 *  @struct stucture process
 *  @author William Meunier<meunierwil@cy-tech.fr>
 *  @version 0.1
 *  @date Wed 05 Oct 2022 12:23
 *
 *
 *  @param[in]
 *
 */
typedef struct process
{
    char nom[20];
    int TpsExe;
    int TpsArr;
    int TpsFin;
    int TpsSej;
    int TpsAtt;
    int status;    //  0:sleeping, n:running(n: running time), -1: ended 
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
    for (int i = 0; i < nbp; i++)
    {   
        int min_i = i;
        for(int j= i; j < nbp; j++)
        {
            if (proc[j].TpsArr < proc[min_i].TpsArr)
            {
                min_i = j;
            }
        }
        permut = proc[min_i];
        proc[min_i] = proc[i];
        proc[i] = permut;

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
    // int TpsFin, TpsSej, TpsAtt;
    // TpsFin = 0;
    // TpsSej = 0;
    // TpsAtt = 0;

    // for (i = 0; i < nbp; i++)
    // {
    //     TpsFin = TpsFin + proc[i].TpsExe;
    //     TpsSej = TpsFin - proc[i].TpsArr;
    //     TpsAtt = TpsSej - proc[i].TpsExe;

    //     proc[i].TpsFin = TpsFin;
    //     proc[i].TpsSej = TpsSej;
    //     proc[i].TpsAtt = TpsAtt;
    // }
    // R�alise le tri PRIO non préemptive

    int nbp_end = 0;
    int curent_tps = 0;
    int index_curent_running = -1;
    int index_last_in = -1;


    process permut;

    while(nbp_end != nbp)
    {   
        if (index_last_in == -1 && proc[0].TpsArr >= curent_tps)
        {   
            curent_tps++;
            continue;
        }else
        {   
            int temp=0;
            for (int i = nbp-1; i > index_last_in; i--)  // à faire mieux (pas opti + pas beau)
            {
                if (proc[i].TpsArr < curent_tps){
                    temp++;
                }
            }
            index_last_in+=temp; 
            
        } 

        for (int i=0; i<=index_last_in; i++)
        {
            if (proc[i].status == -1)
            {
                continue;
            }

            if()
        }
        
        if (index_last_in != nbp-1 && proc[index_last_in+1].TpsArr == curent_tps) 
        {
            index_last_in++;
        }
        curent_tps++;
    }


    // for (i = 0; i < nbp; i++)
    // {
    //     for (j = i; j < nbp; j++)
    //     {
    //         if (proc[i].priorite < proc[j].priorite  &&  )
    //         {
    //             if (1 || proc[i].TpsSej == proc[j].TpsSej)
    //             {
    //                 permut = proc[i];
    //                 proc[i] = proc[j];
    //                 proc[j] = permut;


    //             }
    //         }
    //     }
    // }

    // Afficher l'enchainement des processus
    for (int i = 0; i < nbp; i++)
    {
        for (int j = 0; j < proc[i].TpsExe; j++)
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
    printf("Processus\t TpsExe\t TpsArr\t TpsSej\t TpsAtt\t priorité\n");
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
    proc[0].TpsExe = 10;
    proc[0].TpsArr = 2;
    proc[0].priorite = 3;
    proc[0].status = 0;
    strcpy(proc[1].nom, "B");
    proc[1].TpsExe = 6;
    proc[1].TpsArr = 0;
    proc[1].priorite = 5;
    proc[0].status = 0;
    strcpy(proc[2].nom, "C");
    proc[2].TpsExe = 2;
    proc[2].TpsArr = 5;
    proc[2].priorite = 2;
    proc[0].status = 0;
    strcpy(proc[3].nom, "D");
    proc[3].TpsExe = 4;
    proc[3].TpsArr = 5;
    proc[3].priorite = 1;
    proc[0].status = 0;
    strcpy(proc[4].nom, "E");
    proc[4].TpsExe = 8;
    proc[4].TpsArr = 3;
    proc[4].priorite = 4;
    proc[0].status = 0;
    // Afficher l'ordonnancement appilqu�
    printf("Ordonnancement PRIO  :\n");
    printf("*********************\n");
    // Appel de PRIO
    prio(proc, nbp);
    ORDO(proc, nbp);

    return (0);
}
