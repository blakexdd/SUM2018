/* FILE NAME: CTRLL.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */

#include "unit.h"

typedef struct tagvg6UNIT_Ctrl
{
  UNIT_BASE_FIELDS;
}vg6UNIT_Ctrl;

static VOID VG6_CtrlResponse( vg6UNIT_Ctrl *Uni, vg6ANIM *Ani )
{

}

static VOID VG6_UnitRenderCtrl( vg6UNIT_Ctrl *Uni, vg6ANIM *Ani )
{
  static CHAR Buf[1024];

  sprintf(Buf, "FPS %.2f", VG6_Anim.FPS);
  SetWindowText(VG6_Anim.hWnd, Buf);
}

vg6UNIT * VG6_AnimUnitCtrl( VOID )
{
  vg6UNIT_Ctrl *Uni;

  if ((Uni = (vg6UNIT_Ctrl *)VG6_AnimUnitCreate(sizeof(vg6UNIT_Ctrl))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->VG6_UnitResponse  = (VOID *)VG6_CtrlResponse;
  Uni->VG6_UnitRender = (VOID *)VG6_UnitRenderCtrl;
  return (vg6UNIT *)Uni;
}  