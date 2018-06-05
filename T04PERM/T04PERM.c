/* FILE NAME: T04PERM.C
 * PROGRAMMER: VG6
 * DATE: 05.06.2018
 * PURPOSE: Preparing for matrix
 */

#include <stdio.h>
#include <windows.h>

#define MAX 4
INT P[MAX], parity = 1;

/*Main numbers func */
VOID Store( VOID )
{
  INT i;
  FILE *F;

  F = fopen("PERM.txt", "a");

  if (F == NULL)
    return;

  for (i = 0; i < MAX; i++)
    fprintf(F, "%d", P[i]);
  fprintf(F, " ");
  fprintf(F, "%s", parity == 1 ? "Even" : "Odd");
  fprintf(F, "\n");
  fclose(F);
}

/*Swap func */
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
}

/* Sort func */
VOID Go( INT POS )
{
  INT i;

  if (POS == MAX)
  {
    Store();
    return;
  }
  else
  {
    for (i = POS; i < MAX; i++)
    {
      Swap(&P[POS], &P[i]);
      if (POS == 1)
         parity = parity;
      else
        parity = 1 - parity;
      Go(POS + 1);
      Swap(&P[POS], &P[i]);
    }
  }
}

VOID main( VOID )
{
  INT i;

  for (i = 0; i < MAX; i++)
    P[i] = i + 1; 

  Go(0);
}