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
  VG6_RndPrimLoad(&Uni->COW, "Avent.obj");
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
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  VG6_RndPrimDraw(&Uni->COW, MatrRotateY((FLT)clock() / 10));
}

vg6UNIT * VG6_UnitCreateCow( VOID )
{
  vg6UNIT_Cow *Uni;

  if ((Uni = (vg6UNIT_Cow *)VG6_AnimUnitCreate(sizeof(vg6UNIT_Cow))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)VG6_UnitInit;
  Uni->Response = (VOID *)VG6_UnitResponse;
  Uni->Render = (VOID *)VG6_UnitRender;
  Uni->Close = (VOID *)VG6_UnitClose;
  return (vg6UNIT *)Uni;
}
