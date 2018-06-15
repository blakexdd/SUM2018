/* FILE NAME: CTRLL.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */

#include "unit.h"

typedef struct tagvg6UNIT_CTRL
{
  UNIT_BASE_FIELDS;
  VEC CameraX;
  VEC CameraY;
} vg6UNIT_CTRL;

static VOID VG6_UnitInit( vg6UNIT_CTRL *Uni, vg6ANIM *Ani )
{
 // Uni->Camera = VecSet(8, 8, 8);

}

static VOID VG6_UnitResponse( vg6UNIT_CTRL *Uni, vg6ANIM *Ani )
{
  Uni->CameraX.X = 8;
  Uni->CameraX.Y = 3;
  Uni->CameraX.Z = 8;

  Uni->CameraX =
    OneAxisTransform(Uni->CameraX.X,
     MatrRotateY(30 * Ani->GlobalDeltaTime * (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT])));
  /*Uni->CameraY =
    VectorTransform(Uni->CameraY,
     MatrRotateZ(Ani->GlobalDeltaTime * 30 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));*/
}

static VOID VG6_UnitRender( vg6UNIT_CTRL *Uni, vg6ANIM *Ani )
{
  static CHAR Buf[1024];

  VG6_RndCamSet(Uni->CameraX, VecSet(0, 0, 0), VecSet(0, 1, 0));
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
