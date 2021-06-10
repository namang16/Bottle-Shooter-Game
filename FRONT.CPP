#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

union REGS in, out;

int callmouse()
{
  in.x.ax = 1;
  int86(0x33, &in, &out);
  return 1;
}

int mousehide()
{
  in.x.ax = 2;
  int86(0x33, &in, &out);
  return 1;
}

void mouseposi(int &xpos, int &ypos, int &click)
{
  in.x.ax = 3;
  int86(0x33, &in, &out);
  click = out.x.bx;
  xpos = out.x.cx;
  ypos = out.x.dx;
}


void restrictmouseptr(int x1, int y1, int x2, int y2)
{
  in.x.ax = 7;
  in.x.cx = x1;
  in.x.dx = x2;
  int86(0x33, &in, &out);
  in.x.ax = 8;
  in.x.cx = y1;
  in.x.dx = y2;
  int86(0x33, &in, &out);
}



void front()
{
  int x, y, xx, yy, count = 0, i = 0;
  x = getmaxx();
  y = getmaxy();
  while(count<=50)
  {
    i++;
    count++;
    setfillstyle(1, random(i));
    circle(xx = random(x), yy = random(y), random(30));
    floodfill(xx, yy, getmaxcolor());
  }
  setfillstyle(1, CYAN);
  bar(160, 100, 460, 300);
  settextstyle(10,0,5);
  setcolor(4);
  outtextxy(190,100,"BOTTLE");
  outtextxy(170,170,"SHOOTER");
  setlinestyle(3, 1, 3);
  line(178, 187, 438, 187);
  line(168, 257, 456, 257);
}

void draw_buttons()
{
  setfillstyle(SOLID_FILL, LIGHTGRAY);
  bar(280, 340, 350, 360);
  bar(230, 370, 400, 390);
  bar(280, 400, 350, 420);
  setcolor(4);
  settextstyle(1, 0, 1);
  outtextxy(293, 338, "PLAY");
  outtextxy(253, 368, "INSTRUCTIONS");
  outtextxy(293, 398, "EXIT");
}

int main()
{
int x, y, cl;
int gd = DETECT, gm;
initgraph ( &gd, &gm, "C:\\TC\\BGI" ) ;
front();
draw_buttons();
callmouse();
restrictmouseptr(0, 0, 640, 480);
do
{
  mouseposi(x, y, cl);
  if((x>280 && x<350) && (y>340 && y<360) && cl == 1)
  {
    mousehide();
    cleardevice();
    outtextxy(100, 100, "PLAY");
    break;
  }
  else if((x>230 && x<400) && (y>370 && y<390) && cl == 1)
  {
    mousehide();
    cleardevice();
    outtextxy(100, 100, "INSTRUCTIONS");
    break;
  }
  else if((x>280 && x<350) && (y>400 && y<420) && cl == 1)
  {
    mousehide();
    cleardevice();
    outtextxy(100, 300, "THANKS FOR PLAYING");
    delay(1000);
    exit(0);
  }

}while(!kbhit());
getch();
mousehide();
getch();
closegraph();
return 0;
}