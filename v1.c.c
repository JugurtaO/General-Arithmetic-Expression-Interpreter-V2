#include "analyse_syntaxique.h"
#include <stdio.h>

void analyser(char *fichier)
{
  demarrer(fichier);
  Etat_Automate_Ana etat = C_INIT;
  Lexeme Lex;

  int err;
  Lex = lexeme_courant();
  
  err = Rec_eag(Lex);

  if (err != 1)

    printf("Expression correcte ..\n");

  else
    printf("Expression incorrecte !! ..\n");
}
/*------------------------------------ récursive functions ------------------------------------------*/
/****************************************************************************************************/
int Rec_eag(Lexeme Lex)
{
  int err = Rec_seq_terme(Lex);

  return err;
}
/********/
int Rec_seq_terme(Lexeme Lex)
{
  
  int err;
  err = Rec_terme(Lex);
  if (err == 1)
    return 1;
  Lex = lexeme_courant();
  
  err = Rec_suite_seq_terme(Lex);
  if (err == 1)
    return 1;
  return 0;
}
/********/
int Rec_suite_seq_terme(Lexeme Lex)
{
  int err;
  err = Rec_op1(Lex);
  afficher(Lex);
  printf("\n");
  if (err == 0)
  {

    Lex = lexeme_courant();
    // afficher(Lex);
    printf("\n");
    err = Rec_terme(Lex);
    if (err == 1)
      return 1;

    Lex = lexeme_courant();

    err = Rec_suite_seq_terme(Lex);
    if (err == 1)
      return 1;
    return 0;
  }
  return 0;
}
/********/
int Rec_terme(Lexeme Lex)
{
  int err = Rec_seq_facteur(Lex);
  // afficher(Lex);
  printf("\n");
  return err;
}
/********/
int Rec_seq_facteur(Lexeme Lex)
{
  int err;
  err = Rec_facteur(Lex);
  // afficher(Lex);
  printf("\n");
  if (err == 1)
    return 1;
  Lex = lexeme_courant();
  // afficher(Lex);
  printf("\n");
  err = Rec_suite_seq_facteur(Lex);
  if (err == 1)
    return 1;
  return 0;
}
/********/
int Rec_suite_seq_facteur(Lexeme Lex)
{
  int err;
  err = Rec_op2(Lex);


  if (err == 0)
  {
    Lex = lexeme_courant();
    // afficher(Lex);
  printf("\n");
    err = Rec_facteur(Lex);
    if (err == 1)
      return 1;

    Lex = lexeme_courant();
    // afficher(Lex);
  printf("\n");
    err = Rec_suite_seq_facteur(Lex);
    if (err == 1)
      return 1;

    return 0;
  }
  // else
  //   return 0;

  
}
/********/

int Rec_facteur(Lexeme Lex)
{
  int err;
   afficher(Lex);
  printf("\n");
  switch (Lex.nature)
  {
  case ENTIER:
    avancer();
    return 0;

    break;
  case PARO:

    avancer();
    Lex = lexeme_courant();
   
    err = Rec_eag(Lex);
    if (err == 1)
      return 1;
      
    Lex = lexeme_courant();
    afficher(Lex);
  printf("\n");
    if (Lex.nature = PARF)
    {
      avancer();
      return 0;
    }

    else
      return 1;

    break;
  default:
    return 1;
    break;
  }
}
/********/
int Rec_op1(Lexeme Lex)
{
  afficher(Lex);
  printf("\n");
  switch (Lex.nature)
  {
  case PLUS:
  case MOINS:
    avancer();
    return 0; 
    break;

  default:
    return 1;
    break;
  }
}
/********/
int Rec_op2(Lexeme Lex)
{
  afficher(Lex);
  printf("\n");
  switch (Lex.nature)
  {
  case MUL:
    avancer();
    return 0;
    break;

  default:
    return 1;
    break;
  }
}
