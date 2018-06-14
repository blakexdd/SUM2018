/* FILE NAME: U_COW.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */
#include <time.h>
#include "unit.h"

typedef struct tagvg6ANIM_Cow
{
  UNIT_BASE_FIELDS;
  VEC Pos;
  vg6PRIM COW;
} vg6UNIT_Cow;

static VOID VG6_UnitInit( vg6UNIT_Cow *Uni, vg6ANIM *Ani )
{
  VG6_RndPrimLoad(&Uni->COW, "avent.obj");
  Uni->Pos = VecSet(0, 1, 0);
}

static VOID VG6_UnitClose( vg6UNIT_Cow *Uni, vg6ANIM *Ani )
{
  VG6_RndPrimFree(&Uni->COW);
}

static VOID VG6_UnitResponse( vg6UNIT_Cow *Uni, vg6ANIM *Ani )
{
  
}

static VOID VG6_UnitRender( vg6UNIT_Cow *Uni, vg6ANIM *Ani )
{
  VG6_RndCamSet(Uni->Camera, VecSet(0, 2, -5), VecSet(0, -1, 0));
  glEnable(GL_POLYGON_SMOOTH);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  VG6_RndPrimDraw(&Uni->COW, MatrRotateY((FLT)clock() / 100));
}

vg6UNIT * VG6_UnitCreateCow( VOID )
{
  vg6UNIT_Cow *Uni;

  if ((Uni = (vg6UNIT_Cow *)VG6_AnimUnitCreate(sizeof(vg6UNIT_Cow))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->VG6_UnitInit = (VOID *)VG6_UnitInit;
  Uni->VG6_UnitResponse = (VOID *)VG6_UnitResponse;
  Uni->VG6_UnitRender = (VOID *)VG6_UnitRender;
  return (vg6UNIT *)Uni;
}
