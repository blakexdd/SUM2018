/* FILENAME: T02EYES2.C
 * PROGRAMMER: VG6
 * DATE: 01.06.2018
 */

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WND_CLASS_NAME "My window class"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }
  hWnd =
    CreateWindow(WND_CLASS_NAME,
    "EYE",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);
  
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

VOID  DrawEye( HDC hDc, INT X, INT Y, INT R, INT R1, INT mx, INT my )
{
  INT dx = mx - X, dy = my - Y, sx, sy;
  DOUBLE len = sqrt(dx * dx + dy * dy),
    t = (R - R1) / len;

  SelectObject(hDc, GetStockObject(DC_PEN));
  SelectObject(hDc, GetStockObject(DC_BRUSH));
  SetDCPenColor(hDc, RGB(255, 0, 0));
  SetDCBrushColor(hDc, RGB(255, 255, 255));
  Ellipse(hDc, X - R, Y - R, X + R, Y + R);

  if (len < R - R1)
    sx = mx, sy = my;
  else
  {
    sx = (INT)(X + dx * t), sy = (INT)(Y + dy * t);
    t = (R - R1) / len;
  }
  SelectObject(hDc, GetStockObject(DC_PEN));
  SelectObject(hDc, GetStockObject(DC_BRUSH));
  SetDCPenColor(hDc, RGB(0, 0, 0));
  SetDCBrushColor(hDc, RGB(0, 0, 0));
  Ellipse(hDc, sx - R1, sy - R1, sx + R1, sy + R1);

}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDc;
  POINT pt;
  RECT rc;
  PAINTSTRUCT ps;
  static INT W, H;
  static HDC hMemDC;
  static HBITMAP hBm;
  INT i, j;
  
  switch (Msg)
  {
  case WM_CREATE:
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);
    SetTimer(hWnd, 47, 30, NULL);
    return 0;
  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);

    hBm = CreateCompatibleBitmap(hMemDC, W, H);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_TIMER:
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(0, 128, 0));
    Rectangle(hMemDC, 0, 0, W, H);

    for (i = 0; i <= 5000; i += 200)
      for (j = 0; j <= 1000; j += 200)
         DrawEye(hMemDC, 100 + i, 100 + j, 78, 30, pt.x, pt.y);

    InvalidateRect(hWnd, NULL, FALSE);

    return 0;
  case WM_CLOSE:
    if(MessageBox(hWnd, "Do you want to close the window?", "Exit", MB_YESNO == IDYES))
      SendMessage(hWnd, WM_DESTROY, 0, 0);
  case WM_PAINT:
    hDc = BeginPaint(hWnd, &ps);
    BitBlt(hDc, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}