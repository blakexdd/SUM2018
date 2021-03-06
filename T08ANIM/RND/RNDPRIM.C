/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Primitives
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../anim.h"

BOOL VG6_RndPrimCreate( vg6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(vg6PRIM));

  size = sizeof(vg6VERTEX) * NoofV + sizeof(INT) * NoofI * 3;

  /* Allocate memory */
  Pr->V = malloc(size);
  if (Pr->V == NULL)
    return FALSE;

  /* Fill all allocated memory by 0 */
  memset(Pr->V, 0, size);

  Pr->I = (INT *)(Pr->V + NoofV);

  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();

  return TRUE;
} /* End of 'VG6_RndPrimCreate' function */

VOID VG6_RndPrimFree( vg6PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(vg6PRIM));
} /* End of 'VG6_RndPrimFree' function */

VOID VG6_RndPrimDraw( vg6PRIM *Pr, MATR World )
{
  INT i;
  POINT *pnts; 
  MATR M = MatrMulMatr(MatrMulMatr(Pr->Trans, World), VG6_RndMatrVP);

  /* Allocate memory for projections */
  pnts = malloc(sizeof(POINT) * Pr->NumOfV);
  if (pnts == NULL)
    return;

  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr4x4(Pr->V[i].P, M);

    pnts[i].x = (INT)((p.X + 1) * VG6_Anim.W / 2);
    pnts [i].y = (INT)((-p.Y + 1) * VG6_Anim.H / 2);
  }

  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    POINT p[3];


    p[0] = pnts[Pr->I[i]];
    p[1] = pnts[Pr->I[i + 1]];
    p[2] = pnts[Pr->I[i + 2]];
    Polygon(VG6_Anim.hDC, p, 3);
  }

  free(pnts);
} /* End of 'VG6_RndPrimDraw' function */

BOOL VG6_RndPrimLoad( vg6PRIM *Pr, CHAR *FileName )
{
  INT nv, nf;
  FILE *F;
  CHAR Buf[1000];

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(vg6PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertex and facet quantity */
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf += 3;
  }

  if (!VG6_RndPrimCreate(Pr, nv, nf))
  {
    fclose(F);
    return FALSE;
  }

  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
      Pr->I[nf++] = n1 - 1;
      Pr->I[nf++] = n2 - 1;
      Pr->I[nf++] = n3 - 1;
    }
  }
  fclose(F);
  return TRUE;
}
