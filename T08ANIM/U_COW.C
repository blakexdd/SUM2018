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
  VG6_RndPrimLoad(&Uni->COW, "cow.object");
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
  VG6_RndCamSet(VecSet(0, 0, 0), VecSet(0, 30, -30), VecSet(0, -1, 0));
  VG6_RndPrimDraw(&Uni->COW, MatrRotateY(clock() / 100.0));
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
