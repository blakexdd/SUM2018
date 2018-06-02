/* Gololobov Vladimir, 10-6, 01.06.2018 */
#include <windows.h>
#include <stdio.h>

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  INT i, l = 1, r = 100, m = (l + r) / 2, answer;
  CHAR Buf[100];

  MessageBox(NULL, "Загадайте число от 1 до 100", "Игра", MB_OK);

  while (l <= r)
  {
    sprintf(Buf, "Число больше, меньше или равно %i", m);
    answer = MessageBox(NULL, Buf, "Игра", MB_YESNOCANCEL);
    if (answer == IDYES)
    {
      l = m + 1;
      m = (l + r) / 2;
    }
    if (answer == IDNO)
    {
      r = m - 1;
      m = (l + r) / 2;
    }
    if (answer == IDCANCEL)
    {
      sprintf(Buf, "Ваше число %i", m);
      MessageBox(NULL, Buf, "Игра", MB_OK);
      break;
    }
  if (l == r)
  {
    sprintf(Buf, "Ваше число %i", l);
    MessageBox(NULL, Buf, "Игра", MB_OK);
    break;
  }
  }
  return 0;
}