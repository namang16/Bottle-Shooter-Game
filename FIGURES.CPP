#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

void draw_bottle()
{
  int points[] = {315, 185, 315, 190, 310, 200, 310, 250, 330, 250, 330, 200, 325, 190, 325, 185, 315, 185};
  setcolor(GREEN);
  setfillstyle(SOLID_FILL, LIGHTGREEN);
  fillpoly(9, points);
  rectangle(315, 212, 325, 238);
  setfillstyle(SOLID_FILL, GREEN);
  floodfill(320, 225, GREEN);
}

void draw_bullet()
{
  int points[] = {320, 205, 315, 212, 315, 238, 325, 238, 325, 212, 320, 205};
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, LIGHTGRAY);
  fillpoly(6, points);
}

void draw_shooter()
{
  int points[] = {250, 460, 280, 440, 300, 440, 300, 400, 330, 400, 330, 440, 350, 440, 380, 460, 250, 460};
  setfillstyle(SOLID_FILL, WHITE);
  fillpoly(9, points);
}

void draw_burst(int x, int y)
{
  setlinestyle(0,0,1);
  line (x - 16, y - 12, x - 10, y - 2);
  line (x - 10, y - 2, x - 16, y);
  line (x - 16, y, x - 10, y + 2);
  line (x - 10, y + 2, x - 16, y + 12);

  line (x - 16, y + 12, x - 6, y + 2);
  line (x - 6, y + 2, x, y + 12);
  line (x, y + 12, x + 6, y + 2);
  line (x + 6, y + 2, x + 16, y + 12);

  line (x - 16, y - 12, x - 6, y - 2);
  line (x - 6, y - 2, x, y - 12);
  line (x, y - 12, x + 6, y - 2);
  line (x + 6, y - 2, x + 16, y - 12);

  line (x + 16, y - 12, x + 10, y - 2);
  line (x + 10, y - 2, x + 16, y);
  line (x + 16, y, x + 10, y + 2);
  line (x + 10, y + 2, x + 16, y + 12);

  setfillstyle(SOLID_FILL, YELLOW);
  floodfill(x, y, RED);
}

int main()
{
int gd = DETECT, gm;
initgraph ( &gd, &gm, "C:\\TC\\BGI" ) ;
draw_bottle();
getch();
cleardevice();
setbkcolor(WHITE);
draw_bullet();
getch();
cleardevice();
setbkcolor(BLACK);
draw_shooter();
getch();
cleardevice();
setbkcolor(WHITE);
setcolor(RED);
draw_burst(320, 240);
getch();
cleardevice();
closegraph();
return 0;
}