/* FILE NAME: CTRLL.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */

#include "unit.h"

typedef struct tagvg6UNIT_CTRL
{
  UNIT_BASE_FIELDS;
  VEC Camera;
} vg6UNIT_CTRL;

static VOID VG6_UnitInit( vg6UNIT_CTRL *Uni, vg6ANIM *Ani )
{
  Uni->Camera = VecSet(8, 8, 8);
  VG6_RndCamSet(Uni->Camera, VecSet(0, 2, -5), VecSet(0, -1, 0));
}

static VOID VG6_UnitResponse( vg6UNIT_CTRL *Uni, vg6ANIM *Ani )
{
  Uni->Camera = VectorTransform(Uni->Camera, MatrRotateY((Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * Ani->DeltaTime * 30));
  VG6_RndCamSet(Uni->Camera, VecSet(0, 2, -5), VecSet(0, -1, 0));
}

static VOID VG6_UnitRender( vg6UNIT_CTRL *Uni, vg6ANIM *Ani )
{
  static CHAR Buf[1024];

  sprintf(Buf, "FPS %.2f", VG6_Anim.FPS);
  SetWindowText(VG6_Anim.hWnd, Buf);
}

vg6UNIT * VG6_AnimUnitCtrl( VOID )
{
  vg6UNIT_CTRL *Uni;

  if ((Uni = (vg6UNIT_CTRL *)VG6_AnimUnitCreate(sizeof(vg6UNIT_CTRL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init  = (VOID *)VG6_UnitInit;
  Uni->Response  = (VOID *)VG6_UnitResponse;
  Uni->Render = (VOID *)VG6_UnitRender;
  return (vg6UNIT *)Uni;
}
