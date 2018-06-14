/* FILE NAME: TIMER.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */

#include "unit.h"


static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID VG6_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  VG6_Anim.IsPause = FALSE;
  VG6_Anim.FPS = 30.0;
  PauseTime = 0;
}

VOID VG6_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  VG6_Anim.GlobalTime = (FLT)(t.QuadPart - StartTime) / TimePerSec;
  VG6_Anim.GlobalDeltaTime = (FLT)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (VG6_Anim.IsPause)
  {
    VG6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    VG6_Anim.DeltaTime = VG6_Anim.GlobalDeltaTime;
    VG6_Anim.Time = (FLT)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    VG6_Anim.FPS = FrameCounter * TimePerSec / (FLT)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}