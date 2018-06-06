/* FILE NAME: T04PERM.C
* PROGRAMMER: VG6
* DATE: 05.06.2018
* PURPOSE: Preparing for matrix
*/

#include <stdio.h>
#include <windows.h>

#define MAX 4
INT P[MAX];
BOOL parity = TRUE;

/*Main numbers func */
VOID Store(VOID)
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
VOID Swap(INT *A, INT *B)
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
}

/* Sort func */
VOID Go(INT POS)
{
  INT i, x;
  BOOL save_parity;

  if (POS == MAX)
  {
    Store();
    return;
  }
  else
  {
    Go(POS + 1);
    save_parity = parity;
    for (i = POS + 1; i < MAX; i++)
    {
      Swap(&P[POS], &P[i]);
      parity = !parity;
      Go(POS + 1);
    }
    x = P[POS];
    for (i = POS + 1; i < MAX; i++)
      P[i - 1] = P[i];
    P[MAX - 1] = x;
    parity = save_parity;
  }
}

VOID main(VOID)
{
  INT i;

  for (i = 0; i < MAX; i++)
    P[i] = i + 1;

  Go(0);
}