/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Primitives
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../anim.h"


/* Create primitive by vertex and index sizes function.
 * ARGUMENTS:
 *   - primitive to create:
 *       vg6PRIM *Pr;
 *   - primitive type:
 *       vg6PRIM_TYPE Type;
 *   - vertex array:
 *       vg6VERTEX *V;
 *   - vertex array size:
 *       INT NoofV;
 *   - index array:
 *       INT *I;
 *   - index array size:
 *       INT NoofI;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL VG6_RndPrimCreate( vg6PRIM *Pr, vg6PRIM_TYPE Type, vg6VERTEX *V, INT NoofV, INT *I, INT NoofI )
{
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(vg6PRIM));

  glGenBuffers(1, &Pr->VBuf);
  glGenVertexArrays(1, &Pr->VA);

  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vg6VERTEX) * NoofV, V, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(vg6VERTEX), (VOID *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(vg6VERTEX), (VOID *)sizeof(VEC));
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(vg6VERTEX), (VOID *)(sizeof(VEC) + sizeof(VEC2)));
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(vg6VERTEX), (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  glBindVertexArray(0);

  if (NoofI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);
    Pr->NumOfI = NoofI;
  }
  else
    Pr->NumOfI = NoofV;

  Pr->Type = Type;

  /* Set default transform (identity) */
  Pr->Trans = MatrIdentity();

  return TRUE;
} /* End of 'VG6_RndPrimCreate' function */

/* Free primitive function.
 * ARGUMENTS:
 *   - primitive to free up:
 *       vg6PRIM *Pr;
 * RETURNS: None.
 */
VOID VG6_RndPrimFree( vg6PRIM *Pr )
{
  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);

  if (Pr->IBuf != 0)
    glDeleteBuffers(1, &Pr->IBuf);

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(vg6PRIM));
} /* End of 'VG6_RndPrimFree' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive to draw:
 *       vg6PRIM *Pr;
 *   - world transformation matrix:
 *       MATR World
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
VOID VG6_RndPrimDraw( vg6PRIM *Pr, MATR World )
{
  INT gl_prim_type;
  MATR M = MatrMulMatr(MatrMulMatr(Pr->Trans, World), VG6_RndMatrVP);

  /* Set transform matrix */
  glLoadMatrixf(M.M[0]);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  gl_prim_type = Pr->Type == VG6_RND_PRIM_TRIMESH ? GL_TRIANGLES : GL_TRIANGLE_STRIP;
  /* gl_prim_type = GL_POINTS; */

  glPointSize(3);

  glBindVertexArray(Pr->VA);
  if (Pr->IBuf == 0)
    glDrawArrays(gl_prim_type, 0, Pr->NumOfI);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(gl_prim_type, Pr->NumOfI, GL_UNSIGNED_INT, NULL);
  }
  glBindVertexArray(0);
} /* End of 'VG6_RndPrimDraw' function */

/* Load primitive from "*.OBJ" file function.
 * ARGUMENTS:
 *   - primitive to be load to:
 *       vg6PRIM *Pr;
 *   - filename to load from:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL VG6_RndPrimLoad( vg6PRIM *Pr, CHAR *FileName )
{
  INT nv, nf, size;
  vg6VERTEX *V;
  INT *I;
  FILE *F;
  CHAR Buf[1000];

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(vg6PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertex and facet quantity */
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf += 3;

  /* Calculate memory size for primitive data */
  size = sizeof(vg6VERTEX) * nv + sizeof(INT) * nf;

  /* Allocate memory */
  V = malloc(size);
  if (V == NULL)
  {
    fclose(F);
    return FALSE;
  }

  /* Fill all allocated memory by 0 */
  memset(V, 0, size);
  I = (INT *)(V + nv);

  /* Load primitive data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      FLT x, y, z;

      sscanf(Buf + 2, "%f%f%f", &x, &y, &z);
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
      I[nf++] = n1 - 1;
      I[nf++] = n2 - 1;
      I[nf++] = n3 - 1;
    }
  fclose(F);

  /* Create primitive */
  VG6_RndPrimCreate(Pr, VG6_RND_PRIM_TRIMESH, V, nv, I, nf);
  free(V);
  return TRUE;
} /* End of 'VG6_RndPrimLoad' function */

