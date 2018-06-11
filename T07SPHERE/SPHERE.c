/* FILE NAME: T07SPHERE.C
 * PROGRAMMER: VG6
 * DATE: 06.06.2018
 * PURPOSE: For 3d graphics in the furute
 */
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>


#define WND_CLASS_NAME "My window class"

#define N 8
#define M 15
typedef DOUBLE DBL;
#define PI       3.14159265358979323846

typedef struct
{
  DBL X, Y, Z; 
} VEC;

static VEC G[N][M];

VEC VecSet(DBL X, DBL Y, DBL Z)
{
  VEC r = { X, Y, Z };
    return r;
}

VEC VecRotateZ(VEC V, DBL AngeInDegree)
{
  DBL a = AngeInDegree * PI / 180, si = sin(a), co = cos(a);

  return VecSet(V.X * co - V.Y * si, V.X * si + V.Y * co, V.Z);
}

VEC VecRotateY(VEC V, DBL AngeInDegree)
{
  DBL a = AngeInDegree * PI / 180, si = sin(a), co = cos(a);

  return VecSet(V.Z * si + V.X * co, V.Y, V.Z * co - V.X * si);
} 

VOID SphereEval(VOID)
{
  INT i, j;
  DBL t = clock() / (DBL)CLOCKS_PER_SEC;

  for (i = 0; i < N; i++)
  {
    DBL theta = i * PI / (N - 0), sit = sin(theta), cot = cos(theta);
    for (j = 0; j < M; j++)
    {
      DBL phy = j * 2 * PI / (M - 1), sip = sin(phy), cop = cos(phy);
      G[i][j] = VecSet(sip * sit, cot, cop * sit);
    }
  }
}

VOID SphereDraw(HDC hDC, INT X0, INT Y0, INT R)
{
  INT i, j;
  DBL t = clock() / (DBL)CLOCKS_PER_SEC;
  static POINT P[N][M];

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      VEC r = VecRotateY(VecRotateZ(G[i][j], 60 * t), 30 * t);

      P[i][j].x = (INT)(X0 + R * r.X);
      P[i][j].y = (INT)(Y0 - R * r.Y);

      SelectObject(hDC, GetStockObject(DC_PEN));
      SetDCPenColor(hDC, RGB(255, 0, 0));
      SetPixel(hDC, P[i][j].x, P[i][j].y, RGB(255, 0, 0));
    }  

  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(200, 200, 200)); 

  for (i = 1; i < N - 1; i++)
  {
    for (j = 0; j < M - 1; j++)
    {
      POINT pnts[4];

      pnts[0] = P[i][j];
      pnts[1] = P[i][j + 1];
      pnts[2] = P[i + 1][j + 1];
      pnts[3] = P[i + 1][j];

      if ((pnts[0].x - pnts[1].x) * (pnts[0].y + pnts[1].y) +
          (pnts[1].x - pnts[2].x) * (pnts[1].y + pnts[2].y) +
          (pnts[2].x - pnts[3].x) * (pnts[2].y + pnts[3].y) +
          (pnts[3].x - pnts[0].x) * (pnts[3].y + pnts[0].y) < 0)
        Polygon(hDC, pnts, 4);
    }      
  }
  SelectObject(hDC, GetStockObject(NULL_BRUSH));
  SetDCPenColor(hDC, RGB(0, 0, 0));

  for (i = 1; i < N - 1; i++)
  {
    for (j = 0; j < M - 1; j++)
    {
      POINT pnts[4];

      pnts[0] = P[i][j];
      pnts[1] = P[i][j + 1];
      pnts[2] = P[i + 1][j + 1];
      pnts[3] = P[i + 1][j];

      if ((pnts[0].x - pnts[1].x) * (pnts[0].y + pnts[1].y) +
          (pnts[1].x - pnts[2].x) * (pnts[1].y + pnts[2].y) +
          (pnts[2].x - pnts[3].x) * (pnts[2].y + pnts[3].y) +
          (pnts[3].x - pnts[0].x) * (pnts[3].y + pnts[0].y) > 0)
      {
        SelectObject(hDC, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hDC, RGB(255, 0, 0));
        Polygon(hDC, pnts, 4);
      }
    }
  }
/*

    for (i = 0; i < N; i++)
    {
      MoveToEx(hDC, P[i][0].x, P[i][0].y, NULL);
      SetDCPenColor(hDC, RGB(255, 0, 0));
      for (j = 1; j < M; j++)
        LineTo(hDC, P[i][j].x, P[i][j].y);
    }
    for (j = 0; j < M - 1; j++)
    {
      MoveToEx(hDC, P[0][j].x, P[0][j].y, NULL);
      SetDCPenColor(hDC, RGB(255, 0, 0));
      for (i = 1; i < N; i++)
        LineTo(hDC, P[i][j].x, P[i][j].y);
    }     */
}


LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg,
                              WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd)
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Eror register window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  }

  hWnd =
    CreateWindow(WND_CLASS_NAME,
    "SPHERE",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);

  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);
  SetFocus(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);

  return 1;
}
 
LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  static HBITMAP hBmFrame;
  static HDC hMemDCFrame;
  static INT W, H;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 47, 3, NULL);
    hDC = GetDC(hWnd);
    hMemDCFrame = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);

    SphereEval();
    return 0;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);

    if (hBmFrame != NULL)
      DeleteObject(hBmFrame);

    hDC = GetDC(hWnd);
    hBmFrame = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);

    SelectObject(hMemDCFrame, hBmFrame);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_TIMER:

    SelectObject(hMemDCFrame, GetStockObject(DC_PEN));
    SelectObject(hMemDCFrame, GetStockObject(DC_BRUSH));
    SetDCPenColor(hMemDCFrame, RGB(0, 0, 0));
    SetDCBrushColor(hMemDCFrame, RGB(255, 255, 255));

    Rectangle(hMemDCFrame, 0, 0, W, H);

    SphereEval();
    SphereDraw(hMemDCFrame, W / 2, H / 2, 400);

    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    BitBlt(hDC, 0, 0, W, H, hMemDCFrame, 0, 0, SRCCOPY);

    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    DeleteObject(hBmFrame);
    DeleteDC(hMemDCFrame);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}