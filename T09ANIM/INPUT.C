/* FILE NAME: INPUT.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */

#include "unit.h"

VOID VG6_AnimInputInit( VOID )
{
   INT i;
   GetKeyboardState(VG6_Anim.Keys);
   for (i = 0; i < 256; i++)
   {
     VG6_Anim.Keys[i] >>= 7;
     VG6_Anim.KeysClick[i] = VG6_Anim.Keys[i] && !VG6_Anim.KeysOld[i];
   }
   memcpy(VG6_Anim.KeysOld, VG6_Anim.Keys, 256);
    /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          VG6_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          VG6_Anim.JButClick[i] = VG6_Anim.JBut[i] && !VG6_Anim.JButOld[i];
          VG6_Anim.JButOld[i] = VG6_Anim.JBut[i];
        }

        /* Axes */
        VG6_Anim.JX = VG6_GET_JOYSTICK_AXIS(X);
        VG6_Anim.JY = VG6_GET_JOYSTICK_AXIS(Y);
        VG6_Anim.JZ = VG6_GET_JOYSTICK_AXIS(Z);
        VG6_Anim.JR = VG6_GET_JOYSTICK_AXIS(R);

        /* Point of view */
        VG6_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }


}

18.3. Input system

    


18.3.1. Keyboard

Асинхронный ввод!!!

  BYTE Keys[256];      -- состояние клавиш на текущем кадре
  BYTE KeysOld[256];   -- состояние клавиш на прошлом кадре
  BYTE KeysClick[256]; -- признаки однократного нажатия клавиш

Получение текущего состояния клавиатуры (и кнопок мыши)
  GetKeyboardState(Keys);

Keys[i] – старший бит 1, если i-я кнопка нажата

Типовая обработка:
  GetKeyboardState(Keys);
  for (i = 0; i < 256; i++)
  {
    Keys[i] >>= 7;
    KeysClick[i] = Keys[i] && !KeysOld[i];   <- Отслеживание однократного нажатия
  }
  memcpy(KeysOld, Keys, 256);

Номера в массиве Keys[...]:
специальные клавиши:

VK_ESCAPE VK_INSERT VK_LEFT VK_NEXT VK_PRIOR VK_F1 ... VK_LBUTTON VK_RBUTTON VK_MBUTTON
                                                                    (мыша)
обычные клавиши:
'A', 'B' ... 'Z', '0', '1', ... , '9'

Пример использования – движение Loc у камеры от стрелок (вперед-назад):

UnitResponse:
  /* Uni->CamLoc += Uni->CamDir * Speed * dt */
  Uni->CamLoc =
    VecAddVec(Uni->CamLoc,
      VecMulNum(Uni->CamDir, Ani->DeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DNOW])));

18.3.2. Mouse


пользовательские переменные

  INT Mx, My, Mz, Mdx, Mdy, Mdz;

получение X и Y:

  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  /* приращение координат на экране */
  Mdx = pt.x - Mx;
  Mdy = pt.y - My;
  /* абсолютные значения */
  Mx = pt.x;
  My = pt.y;

Кнопки - buttons - в обработке клавиатуры (из Keys/KeysClick)

опрос колеса (mouse wheel)

глобальная переменная:
INT VG4_MouseWheel;

case WM_MOUSEWHEEL:
  VG4_MouseWheel += (SHORT)HIWORD(wParam);
  return 0;


получение Z:
  Mdz = VG4_MouseWheel;
  Mz += VG4_MouseWheel;
  VG4_MouseWheel = 0;

Пример использования – кручение Loc у камеры относительно Y:

UnitResponse:
  /* Uni->CamLoc ->rotateY(Mx * DeltaTime * AngleSpeed)*/
  Uni->CamLoc =
    PointTransform(Uni->CamLoc,
      MatrRotateY(Ani->DeltaTime * Uni->AngleSpeed * Ani->Mdx));


18.3.3.Joystick
 

доп библиотеки (windows multimedia library):
#include <mmsystem.h> (после windows.h)

+ подключаем библиотеку: /* winmm.lib */
#pragma comment(lib, "winmm")

пользовательские переменные

  BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button state */
  INT JPov;                               /* Joystick point-of-view control [-1,0..7] */
  FLT
    JX, JY, JZ, JR;                       /* Joystick axes */

опрос:
  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          JBut[i] = (ji.dwButtons >> i) & 1;
          JButClick[i] = JBut[i] && !JButOld[i];
          JButOld[i] = JBut[i];
        }

        /* Axes */
        JX = VG4_GET_JOYSTIC_AXIS(X);
        JY = VG4_GET_JOYSTIC_AXIS(Y);
        JZ = VG4_GET_JOYSTIC_AXIS(Z);
        JR = VG4_GET_JOYSTIC_AXIS(R);

        /* Point of view */
        JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }

!!!
Оси:
  jc:
    jc.wXmin jc.wXmax ... Y ... Z ... R ... U
  ji:
    ji.dwXpos ... Y ...

общая формула (для X):
   2.0 * (ji.dwXpos - jc.wXmin) / (jc.wXmax - jc.wXmin) - 1

общий макрос для всех осей:

#define VG4_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos – jc.w ## A ## min) / (jc.w ## A ## max – jc.w ## A ## min) - 1)


 \ANIM\INPUT.C --> VG4_AnimKeyboardResponse();
                  VG4_AnimMouseResponse();
                  VG4_AnimJoystickResponse();
