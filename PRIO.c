#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct process {
  char nom[20];
  int Priorite;
  int TpsExe;
  int TpsArr;
  int TpsFin;
  int TpsSej;
  int TpsAtt;
} process;

void PRIO(process *proc, int preemptif) {

}

int main() {
    int nbp = 5;
    process *proc;
    proc= (process *) malloc(nbp * sizeof(*proc));
    // Initialisation des donn�es
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
   


    return 0;
}