/**
 * @file PRIO.c
 * @author Faucher Noé (fauchernoe@cy-tech.fr)
 * @author Ducoulombier Quentin (ducoulombi@cy-tech.fr)
 * @author William Maunier (meunierwil@cy-tech.fr)
 * @author Furger Achille (furgerachi@cy-tech.fr)
 * @brief Algorithme d'ordonnancement par priorité
 * @version 0.1
 * @date 19-10-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STR "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"

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
    char nom;
    int TpsExe;
    int TpsArr;
    int TpsFin;
    int TpsSej;
    int TpsAtt;
    int status;    //  0:sleeping, n:running(n: running time), -1: ended 
    int priorite;
} process;


/** 
 * @fn void process_construct(char* fnom, int fTpsExe, int fTpsArr, int fpriorite, process *proc, int i)
 * @author Quentin Ducoulombier (ducoulombi@cy-tech.fr)
 * @version 0.1
 * @date 2022-10-19
 * 
 * @brief Fonction qui permet de construire les "process"
 * 
 * @param fnom 
 * @param fTpsExe 
 * @param fTpsArr 
 * @param fpriorite 
 * @param proc 
 * @param i 
 */
void process_construct(char fnom, int fTpsExe, int fTpsArr, int fpriorite, process *proc, int i)
{
  proc[i].nom = fnom;
  proc[i].TpsExe = fTpsExe;
  proc[i].TpsArr = fTpsArr;
  proc[i].priorite = fpriorite;
  proc[i].status = 0;
}



/**
 *  @fn void tri_en_temps_arriver (process *proc, int nbp)
 *  @author Faucher Noé <fauchernoe@cy-tech.fr>
 *  @version 2.0
 *  @date Wed 05 Oct 2022 12:23
 *
 *  @brief tri les processus selon le temps d'arriver
 *
 *  @param[in]
 *
 */
void tri_en_temps_arriver(process *proc, int nbp)
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
 * @fn void echange(process *proc, int i, int j)
 * @author Faucher Noé (fauchernoe@cy-tech.fr)
 * @version 0.1
 * @date 26-10-2022
 * @brief 
 * 
 * @param proc 
 * @param i 
 * @param j 
 */
void echange(process *proc, int i, int j) {

    process temp = proc[i];

    proc[i]=proc[j];
    proc[j]=temp;
}


/** 
 * @fn void affich_stat_ORDO(process *proc, int nbp)
 * @author Faucher Noé (fauchernoe@cy-tech.fr)
 * @version 0.1
 * @date 26-10-2022
 * @brief 
 * 
 * @param proc 
 * @param nbp 
 */
void affich_stat_ORDO(process *proc, int nbp)
{
    // Calcul du TpsFin, TpsSej, TotSej et TpsAtt, TotAtt
    int TotAtt,TotSej = 0;
    for (int i = 0; i < nbp; i++)
    {
        proc[i].TpsSej = proc[i].TpsFin - proc[i].TpsArr;
        proc[i].TpsAtt = proc[i].TpsSej - proc[i].TpsExe;

        TotSej = TotSej + proc[i].TpsSej;
        TotAtt = TotAtt + proc[i].TpsAtt;
    }
    // Afficher le Temps d'execution et le Temps d'arrivee et de chaque processus
    printf("Processus\t TpsExe\t TpsArr\t TpsFin\t TpsSej\t TpsAtt\t priorité\n");
    for (int i = 0; i < nbp; i++)
    {
        printf("%c\t\t %d\t %d\t %d\t %d\t %d\t %d\n", proc[i].nom, proc[i].TpsExe, proc[i].TpsArr, proc[i].TpsFin, proc[i].TpsSej, proc[i].TpsAtt, proc[i].priorite);
    }
    printf("\n");

    // afficher les temps moyen de sejour et d'attente
    float TpsSejMoy, TpsAttMoy;
    TpsSejMoy = (float)TotSej / nbp;
    TpsAttMoy = (float)TotAtt / nbp;
    printf("le temps moyen de sejour est = %f\n", TpsSejMoy);
    printf("le temps moyen d'attente est = %f\n", TpsAttMoy);
}



/** @fn void PRIO(process *proc, int nbp, int preemptif)
 * @author Faucher Noé (fauchernoe@cy-tech.fr)
 * @version 0.1
 * @date 26-10-2022
 * @brief 
 * 
 * @param proc 
 * @param nbp 
 * @param preemptif 
 */
void PRIO(process *proc, int nbp, int preemptif) {
    
    // Tri les processus par temps arriver
    tri_en_temps_arriver(proc, nbp);

    
    int nbp_end = 0;
    int curent_tps = 0;
    int index_curent_running = -1;
    int index_last_in = -1;


    while(nbp_end != nbp)
    {   
        // Verification et mise à jour d'arriver de process
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

        // Choisir le nouveau process
        if (preemptif || index_curent_running == -1)
        {

            int min_prio_index = nbp_end;
            for (int i=nbp_end; i<=index_last_in; i++)
            {
                if (proc[i].priorite < proc[min_prio_index].priorite ) 
                {
                    min_prio_index = i;
                }
            }

            if (index_curent_running != -1)
            {
                echange(proc,min_prio_index,index_curent_running);

            }else
            {
                echange(proc,min_prio_index,nbp_end);
                index_curent_running=nbp_end;
            }
        }




        // Maj du statut de process
        if (proc[index_curent_running].status == -1)
        {
            curent_tps++;
            continue;
        }

        if (proc[index_curent_running].status == proc[index_curent_running].TpsExe)
        {
            nbp_end++;
            proc[index_curent_running].status = -1;
            proc[index_curent_running].TpsFin = curent_tps-nbp_end;
            index_curent_running = -1; 
            curent_tps++;
            continue;
        }
        
        proc[index_curent_running].status++;  
        
        

        if (index_last_in != nbp-1 && proc[index_last_in+1].TpsArr == curent_tps) 
        {
            index_last_in++;
        }
        
        
        //affich_proc(proc,nbp);

        printf("%c ",proc[index_curent_running].nom);
        curent_tps++;
    }


    //affich_proc(proc,nbp);

    printf("\n");

}



/** 
 * @fn int alea(int lower, int upper)
 * @author FURGER Achille (furgerachi@cy-tech.fr)
 * @version 0.1
 * @date 25-10-2022
 * 
 * @brief Fonction qui génère un entier aléatoire entre deux bornes
 * 
 * @param lower 
 * @param upper 
 * @return int 
 */
int alea(int lower, int upper) {
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

/** 
 * @fn process *exempleCours(int nbp) 
 * @author FURGER Achille (furgerachi@cy-tech.fr)
 * @version 0.1
 * @date 25-10-2022
 * 
 * @brief Fonction qui teste avec les résultats du cours
 * 
 * @param nbp 
 * @return process* 
 */
process *exempleCours(int nbp) 
{
    // Creation de cinq processus
    process *proc;
    proc = (process *)malloc(sizeof(process) * nbp);
    
    // Initialisation des donn�es
    process_construct('A',10,2,3,proc,0);
    process_construct('B',6,0,5,proc,1);
    process_construct('C',2,5,2,proc,2);
    process_construct('D',4,5,1,proc,3);
    process_construct('E',8,3,4,proc,4);

    return proc;
}

/** @fn process *test1(int nbp) 
 * @author FURGER Achille (furgerachi@cy-tech.fr)
 * @version 0.1
 * @date 25-10-2022
 * 
 * @brief Fonction qui teste un cas plus ou moins extrèmes
 * 
 * @param nbp 
 * @return process* 
 */
process *test(int nbp) 
{
    // Création des processus
    process *proc;
    proc = (process *)malloc(sizeof(process) * nbp);


    srand(time(NULL));
    //char* str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    for (int i = 0; i < nbp; i++)
    {
        process_construct(STR[i], alea(1,20), (i==0)? i:alea(0,40), alea(1,10), proc, i);
    }
    return proc;
}


/**
 * @fn int main(int argc, char const *argv[]) 
 * @author Faucher Noé (fauchernoe@cy-tech.fr)
 * @version 0.1
 * @date 26-10-2022
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[]) {

    if (argc != 2 ) 
    {
        printf("Pas assez d'argument ou trop (il en faut 1)\n");
        return 1;
    }
/*
    // Creation de cinq processus
    int nbp = 5;
    process *proc;
    proc = (process *)malloc(sizeof(process) * nbp);
    
    // Initialisation des donn�es
    process_construct("A",10,2,3,proc,0);
    process_construct("B",6,0,5,proc,1);
    process_construct("C",2,5,2,proc,2);
    process_construct("D",4,5,1,proc,3);
    process_construct("E",8,3,4,proc,4);
*/
    /*Ordonnement exemple cours*/
    int nbp = 5;
    process *proc = exempleCours(nbp);

    /*Ordonnement test*/
    /*int nbp = 10;
    process *proc = test(nbp);*/


    // Afficher l'ordonnancement appilqu�
    int preemptif = atoi(argv[1]);
    printf("Ordonnancement PRIO %s",(preemptif)?"préemptif":"non préemtif");
    printf(" :\n*********************\n");

    // Appel de PRIO
    PRIO(proc, nbp,preemptif);
    affich_stat_ORDO(proc, nbp);

    free(proc);
    return 0;
}