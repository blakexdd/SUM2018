/* FILE NAME: T05DET.C
* PROGRAMMER: VG6
* DATE: 05.06.2018
* PURPOSE: Det of matrix
*/

#include <stdio.h>
#include <windows.h>

#define MAX 5
INT P[MAX], parity = 1, N = 0;
DOUBLE A[MAX][MAX], det = 0;

/*Load matrix func */
BOOL LoadMatrix(CHAR *FileName)
{
  FILE *F;
  INT i, j;

  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fscanf(F, "%d", &N);

  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
}

/*Output matrix and det */
VOID Store(VOID)
{
  INT i, j;
  FILE *F;

  F = fopen("PERM.txt", "a");

  if (F == NULL)
    return;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
      fprintf(F, "%10.3lf", A[i][j]);
    fprintf(F, "\n");
  }
  fprintf(F, "%10.3lf", det);
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
VOID Go( INT POS )
{
  INT i;
  
  if (POS == N)
  {
    DOUBLE prod = 1;

    for (i = 0; i < N; i++)
        prod *= A[i][P[i]];
    det += (parity * 2 - 1) * prod;
    return;
  }
  else
  {
    for (i = POS; i < N; i++)
    {
      Swap(&P[POS], &P[i]);
      parity = !parity;
      Go(POS + 1);
      Swap(&P[POS], &P[i]);
      parity = !parity;
    }
  }
}

VOID main(VOID)
{
  INT i;

  for (i = 0; i < MAX; i++)
    P[i] = i;

  LoadMatrix("IN1.txt");
  Go(0);
  Store();
}