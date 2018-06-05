/* FILE NAME: T06DETG.c
 * PROGRAMMER: VG6
 * DATE: 05.06.2018
 * PURPOSE: Det by the Gauss method
 */

#include <stdio.h>
#include <windows.h>

#define MAX 5
INT P[MAX], parity = 1, N;
DOUBLE A[MAX][MAX], det = 0.0;

/*Load matrix func */
BOOL LoadMatrix( CHAR *FileName )
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
    for(j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
}

/*Main numbers func */
VOID Store( VOID )
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

  fprintf(F, "%lf", det);
  fclose(F);
}

VOID Detg ( VOID )
{
  INT coef, i, k;

  for (k = i + 1; k < N; k++)
  {
    coef = A[k][i] / A[i][i];
    for (p = i; p < N; p++)
      A[k][p] -= A[i][p] * coef;
  }
}

VOID main( VOID )
{
  INT i;

  LoadMatrix("IN1.TXT");

  Store();
}