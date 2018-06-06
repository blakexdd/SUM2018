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

VOID Detg ( VOID );

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

  fprintf(F, "%lf", Detg());
  fclose(F);
}

DOUBLE Detg( VOID )
{
  INT i, j;
  DOUBLE kaef, det = 0;

  for (i = 1; i < N; i++)
    for (j = i + 1; j < N; j++)
    {
    kaef = A[i][j] / A[i][i];
    A[i][j] = A[i + 1][j] - A[i][j] * kaef;
    }
    det *= A[i][i];

    return det;
}

VOID main( VOID )
{

  LoadMatrix("IN1.TXT");
  Store();
}