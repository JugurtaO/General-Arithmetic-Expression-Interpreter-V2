#include "analyse_lexicale.h"
#include "lecture_caracteres.h"
#include <stdio.h>
#define MAX_SIZE 100
typedef enum {C_INIT, C_ENTIER, C_FIN, C_PARO,C_PARF,C_ERROR, C_OPARATEUR} Etat_Automate_Ana ;



int Rec_eag();
int Rec_seq_terme();
int Rec_suite_seq_terme();
int Rec_terme();
int Rec_suite_seq_facteur();
int Rec_seq_facteur();
int Rec_facteur();
int Rec_op1();
int Rec_op2();

void analyser(char *fichier);
