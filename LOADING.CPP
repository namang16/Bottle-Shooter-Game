#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

void load1()
{
  int i = 0;
  setbkcolor(BLUE);
  settextstyle(2, 0, 7);
  outtextxy(200, 100, "Press Any Key to Start Loading...");
  rectangle(150, 250, 540, 300);
  getch();
  setcolor(4);
  //settextstyle(11, 0, 30);
  //outtextxy(180, 200, "Don't Press Any Key Otherwise Cancel It");
  setcolor(GREEN);
  while(i<=390)
  {
    if(i<=390)
    {
      delay(20);
      rectangle(150 + i, 250, 540, 300);
      i++;
    }
    if(i==390)
    {
    cleardevice();
    setbkcolor(CYAN);
    setcolor(14);
    settextstyle(4, 0, 6);
    outtextxy(100, 100, "LET'S PLAY");
    getch();
    }
  }
}

void load2()
{
  int x, y;
  x = getmaxx()/2;
  y = getmaxy()/2;
  setbkcolor(BLACK);
  setcolor(CYAN);
  int c = 150;
  for(int e = 0; e<15; e++)
  {
    for(int i = 50; i<100; i++)
    {
      settextstyle(SMALL_FONT, HORIZ_DIR, 10);
      outtextxy(x, y, "Loading...");
      circle(x, y, i);
      circle(x, y, c);
      c--;
      cleardevice();
    }
  }
      setcolor(6);
      settextstyle(SMALL_FONT, HORIZ_DIR, 10);
      settextjustify(x, y);
      outtextxy(x-70, y-60, "LET'S PLAY!");
      delay(150);
}

int main()
{
int gd = DETECT, gm;
initgraph ( &gd, &gm, "C:\\TC\\BGI" ) ;
load2();
getch();
closegraph();
return 0;
}