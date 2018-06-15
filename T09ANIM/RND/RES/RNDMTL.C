/* FILE NAME   : RNDMTL.C
 * PURPOSE     : WinAPI animation system.
 *               Rendering system implementation module.
 *               Materials handle.
 * PROGRAMMER  : Vitaly A. Galinsky.
 * LAST UPDATE : 11.06.2018.
 * NOTE        : Module prefix 'VG4'.
 */

#include "../../anim.h"

/* Array of materials */
vg6MATERIAL VG6_RndMaterials[VG6_MAX_MATERIALS];
/* Materials array store size */
INT VG6_RndMaterialsSize;

/* Material storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG6_RndMtlInit( VOID )
{
  vg6MATERIAL defm =
  {
    "Default material",
    0
  };

  VG6_RndMaterialsSize = 0;
  VG6_RndMtlAdd(&defm);
} /* End of 'VG6_RndMtlInit' function */

/* Add material to stock function.
 * ARGUMENTS:
 *   - pointer to material data:
 *       vg4MATERIAL *Mtl;
 * RETURNS:
 *   (INT) 
 ew material stock number.
 */
INT VG6_RndMtlAdd( vg6MATERIAL *Mtl )
{
  if (VG6_RndMaterialsSize >= VG6_MAX_MATERIALS)
    return 0;
  VG6_RndMaterials[VG6_RndMaterialsSize] = *Mtl;
  return VG6_RndMaterialsSize++;
} /* End of 'VG6_RndMtlAdd' function */

/* Apply material before rendering function.
 * ARGUMENTS:
 *   - material number in materials storage array:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) applyed material shader program Id.
 */
INT VG6_RndMtlApply( INT MtlNo )
{
  INT prg, loc;
  vg6MATERIAL *mtl;

  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= VG6_RndMaterialsSize)
    MtlNo = 0;
  mtl = &VG6_RndMaterials[MtlNo];

  /* Set program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= VG6_RndShadersSize)
    prg = 0;
  else
    prg = VG6_RndShaders[prg].ProgId;

  glUseProgram(prg);
  if ((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, VG6_Anim.Time);

  return prg;
} /* End of 'VG6_RndMtlApply' function */

/* END OF 'RNDMTL.C' FILE */
