/* FILE NAME: RNDBASE.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Camera and double buf
 */
#include "rnd.h"

VOID VG6_RndInit( HWND hWnd )
{
  HDC hDC;
  VG6_hWndRnd = hWnd;
  hDC = GetDC(VG6_hWndRnd);
  VG6_hDCRndFrame = CreateCompatibleDC(hDC);
  ReleaseDC(VG6_hWndRnd, hDC);
}

VOID VG6_RndClose( VOID )
{
  DeleteObject(VG6_hBmRndFrame);
  DeleteDC(VG6_hDCRndFrame);
}

VOID VG6_RndResize( INT w, INT h )
{
   HDC hDC;

   if (VG6_hBmRndFrame != NULL)
     DeleteObject(VG6_hBmRndFrame);
   hDC = GetDC(VG6_hWndRnd);
   VG6_hBmRndFrame = CreateCompatibleBitmap(hDC, w, h);
   ReleaseDC(VG6_hWndRnd, hDC);
   SelectObject(VG6_hDCRndFrame, VG6_hBmRndFrame);
 
   VG6_RndFrameW = w;
   VG6_RndFrameH = h;

   VG6_RndProjSet();

}

VOID VG6_RndStart( VOID )
{
  SelectObject(VG6_hDCRndFrame, GetStockObject(DC_PEN));
  SelectObject(VG6_hDCRndFrame, GetStockObject(DC_BRUSH));
  SetDCPenColor(VG6_hDCRndFrame, RGB(255, 255, 255));
  SetDCBrushColor(VG6_hDCRndFrame, RGB(200, 200, 200));
  Rectangle(VG6_hDCRndFrame, 0, 0, VG6_RndFrameW, VG6_RndFrameH);
}

VOID VG6_RndEnd( VOID )
{
}

VOID VG6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, VG6_RndFrameW, VG6_RndFrameH, VG6_hDCRndFrame, 0, 0,
    SRCCOPY);
}  

VOID VG6_RndProjSet( VOID )
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = VG6_RndProjSize / 2;
  if (VG6_RndFrameW > VG6_RndFrameH) 
    ratio_x *= (DBL)VG6_RndFrameW / VG6_RndFrameH;
  else
    ratio_y *= (DBL)VG6_RndFrameH / VG6_RndFrameW;

  VG6_RndMatrProj = MatrViewFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
    VG6_RndProjDist, VG6_RndProjFarClip);
  VG6_RndMatrVP = MatrMulMatr(VG6_RndMatrView, VG6_RndMatrProj);
} 

VOID VG6_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  VG6_RndMatrView = MatrView(Loc, At, Up1);
  VG6_RndMatrVP = MatrMulMatr(VG6_RndMatrView, VG6_RndMatrProj);
}