#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
union REGS in,out;

int callmouse()
{
  in.x.ax = 1;
  int86(51, &in, &out);
  return 1;
}


void mouseposi(int &xpos, int &ypos, int &click)
{
  in.x.ax = 3;
  int86(51, &in, &out);
  click = out.x.bx;
  xpos = out.x.cx;
  ypos = out.x.dx;
}

int mousehide()
{
  in.x.ax = 2;
  int86(51, &in, &out);
  return 1;
}

void setposi(int &xpos, int &ypos)
{
  in.x.ax = 4;
  in.x.cx = xpos;
  in.x.dx = ypos;
  int86(51, &in, &out);
}

void restrictmouseptr(int x1, int y1, int x2, int y2)
{
  in.x.ax = 7;
  in.x.cx = x1;
  in.x.dx = x2;
  int86(51, &in, &out);
  in.x.ax = 8;
  in.x.cx = y1;
  in.x.dx = y2;
  int86(51, &in, &out);
}

int main()
{
int gd = DETECT, gm;
initgraph ( &gd, &gm, "C:\\TC\\BGI" ) ;
int x, y, cl, a = 120, b =420;
setposi(a, b);
callmouse();
rectangle(100, 100, 550, 400);
restrictmouseptr(100, 100, 550, 400);
do
{
  mouseposi(x, y, cl);
  gotoxy(10, 9);
  printf("\n\tMouse Position is %d, %d", x, y);
  printf("\n\tClick: %d", cl);
  printf("\n\tPress any key to hide the mouse");
}while(!kbhit());
getch();
mousehide();
printf("\n\tPress any key to exit");
getch();
closegraph();
return 0;
}