/* FILE NAME: Main.c
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Checking VEC.h file
 */

#include "rnd/rnd.h"
#include "unit.h"

#define N 8
#define M 18

#define WND_CLASS_NAME "My window class"


LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error", "ERROR", MB_OK);
    return 0;
  }
  hWnd =
    CreateWindow(WND_CLASS_NAME,
    "Oniame",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);

  ShowWindow(hWnd, SW_SHOWMAXIMIZED);
  UpdateWindow(hWnd);

    VG6_AnimUnitAdd(VG6_UnitCreateCow());
    VG6_AnimUnitAdd(VG6_AnimUnitCtrl());

  while (1)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
    {
      VG6_AnimRender();
      VG6_AnimCopyFrame(VG6_Anim.hDC);
    }
  return 1;
} 

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;

  switch (Msg)
  {
  case WM_CREATE:
    VG6_AnimInit(hWnd);
    SetTimer(hWnd, 47, 3, NULL);
    return 0;
  case WM_SIZE:
    VG6_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_TIMER:
    VG6_AnimRender();
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
  hDC = BeginPaint(hWnd, &ps);
  VG6_AnimCopyFrame(hDC);
  EndPaint(hWnd, &ps);
  return 0;
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure?", "Quit", MB_YESNO | MB_DEFBUTTON2 | MB_ICONINFORMATION) == IDYES)
      SendMessage(hWnd, WM_DESTROY, 0, 0);
    return 0;
  case WM_DESTROY:
    VG6_AnimClose();
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);

} 