#include "analyse_syntaxique.h"
#include <stdio.h>


void analyser(char *fichier)
{
  demarrer(fichier);
  Etat_Automate_Ana etat = C_INIT;

  int err=0;

  err = Rec_eag();
  if (lexeme_courant().nature!=FIN_SEQUENCE)
    err=1;
  printf("Err final = %d\n",err);
  if (err == 0)

    printf("Expression correcte ..\n");

  else
    printf("Expression incorrecte !! ..\n");
}
/*------------------------------------ récursive functions ------------------------------------------*/
/****************************************************************************************************/
int Rec_eag()
{
  printf("inside eag : \n");
  int err = Rec_seq_terme();
  printf("inside eag after seq_terme:err = %d \n",err);
  if (err==1)
    return 1;
  else
    return 0;
}
/********/
int Rec_seq_terme()
{
  printf("inside seq_terme : \n");
  
  int err = Rec_terme();
  printf("inside seq_terme after terme :err=%d \n",err);
  if (err == 1)
  {
    printf("Erreur in Rec_terme: \n");
    return 1;
  }
  err = Rec_suite_seq_terme();
  printf("inside seq_terme after suite_seq_terme : err=%d\n",err);
  if (err == 1)
  {
    printf("Erreur in Rec_suite_seq_terme : \n");
    return 1;
  }
  return 0;
}
/********/
int Rec_suite_seq_terme()
{
  printf("inside suite_seq_terme : \n");
  
  int err = Rec_op1();
  printf("inside suite_seq_terme after OP1: err=%d\n",err);
  if (err != 1)
  {
    err = Rec_terme();
    printf("inside suite_seq_terme after terme:err=%d \n",err);
    if (err == 1)
    {
      printf("Erreur in Rec_terme l,53 : \n");
      return 1;
    }

    err = Rec_suite_seq_terme();
    printf("inside suite_seq_terme after suite_seq_terme :err=%d \n",err);
    if (err == 1)
    {
      printf("Erreur in Rec_suite_seq_terme l,60 : \n");
      return 1;
    }
    return 0;
  }
  printf("J'ai lu epsilone : \n");
  // return 0;
}
/********/
int Rec_terme(){
  printf("inside terme : \n");
  int err = Rec_seq_facteur();
  printf("inside terme after seq_facteur :err= %d \n",err);
  if(err==1)
    return 1;
  else
    return 0;
}
/********/
int Rec_seq_facteur()
{
  printf("inside seq_facteur : \n");
  int err;
  err = Rec_facteur();
  printf("inside seq_facteur after facteur:err= %d \n",err);

  if (err == 1)
  {
    printf("Erreur in Rec_facteur l,83 : \n");
    return err;
  }
  err = Rec_suite_seq_facteur();
  printf("inside seq_facteur after suite_seq_facteur: err=%d \n",err);
  if (err == 1)
  {
    printf("Erreur in Rec_suite_seq_facteur l,90 : \n");
    return 1;
  }
  return 0;
}
/********/
int Rec_suite_seq_facteur()
{
  printf("inside suite_seq_facteur : \n");
  int err;
  err = Rec_op2();
  printf("inside suite_seq_facteur after OP2:err=%d\n",err);
  if (err != 1)
  {
    err = Rec_facteur();
    printf("inside suite_seq_facteur after facteur :err=%d\n",err);
    if (err == 1)
    {
      printf("Erreur in Rec_facteur in suite_seq_facteur : \n");
      return 1;
    }

    err = Rec_suite_seq_facteur();
    printf("inside suite_seq_facteur after_suite_seq_facteur :err=%d \n",err);
    if (err ==1)
    {
      printf("Erreur in Rec_suite_seq_facteur l,115 : \n");
      return 1;
    }
    return 0;
  }
  printf("j'ai lu epsilone\n");
  //  else
  //     return 1;
}
/********/

int Rec_facteur()
{
  
  printf("inside Facteur : \n");
  afficher(lexeme_courant());
  printf("\n");
  switch (lexeme_courant().nature)
  {
  case ENTIER:
    avancer();
    printf("Sortie case entier\n");

    break;
  case PARO:

    avancer();

    int err = Rec_eag();
    printf("inside Facteur after eag :err=%d \n",err);
    if (err == 1)
    {
      printf("Erreur in Rec_eag l,144 : \n");
      return 1;
    }

    if (lexeme_courant().nature == PARF)
    {
      avancer();
      // return 0;
    }

    else{
      printf("Error from not PARF\n");
      return 1;
    }
    break;
  // case FIN_SEQUENCE:
  //   return 0;
  //   break;
  default:
    printf("error from default\n");
    return 1;
    break;
  }
}
/********/
int Rec_op1()
{
  printf("inside OP1 : \n");
  afficher(lexeme_courant());
  printf("\n");
  switch (lexeme_courant().nature)
  {
  case PLUS:
  case MOINS:
    avancer();
    // return 0;
    break;

  default:
    return 1;
    break;
  }
}
/********/
int Rec_op2()
{
  printf("inside OP2 : \n");
  afficher(lexeme_courant());
  printf("\n");
  switch (lexeme_courant().nature)
  {
  case MUL:
  case DIV:
    avancer();
    // return 0;
    break;

  default:
    return 1;
    break;
  }
}