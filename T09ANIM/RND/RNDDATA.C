/* FILE NAME: RNDDATA.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Global variables
 */
#include "../anim.h"

FLT
  VG6_RndProjSize = 0.1,  /* Project plane fit square */
  VG6_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  VG6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  VG6_RndMatrView, /* View coordinate system matrix */
  VG6_RndMatrProj, /* Projection coordinate system matrix */
  VG6_RndMatrVP;   /* Stored (View * Proj) matrix */
