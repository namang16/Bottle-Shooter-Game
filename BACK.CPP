#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

void day()
{
  setbkcolor(CYAN);
  circle(90, 60, 50);
  setfillstyle(SOLID_FILL, YELLOW);
  floodfill(105, 105, WHITE);
  ellipse(200, 40, 60, 240, 10, 15);
  ellipse(225, 30, 345, 165, 20, 15);
  ellipse(265, 36, 340, 160, 20, 15);
  ellipse(268, 50, 230, 50, 20, 10);
  ellipse(225, 53, 163, 340, 33, 17);
  ellipse(305, 33, 20, 182, 21, 19);
  ellipse(325, 41, 290, 100, 21, 15);
  ellipse(299, 52, 228, 20, 33, 11);
  setfillstyle(SOLID_FILL, LIGHTGRAY);
  floodfill(225, 50, WHITE);
  floodfill(300, 50, WHITE);
  ellipse(440, 40, 60, 240, 10, 15);
  ellipse(465, 30, 345, 165, 20, 15);
  ellipse(502, 37, 340, 160, 20, 15);
  ellipse(508, 52, 230, 50, 20, 10);
  ellipse(466, 54, 163, 340, 31, 15);
  floodfill(470, 45, WHITE);
  line(0, 430, 640, 430);
  setfillstyle(SOLID_FILL, GREEN);
  floodfill(10, 440, WHITE);
  setfillstyle(SOLID_FILL, LIGHTGREEN);
  bar(10, 445, 110, 465);
  bar(120, 445, 230, 465);
  setcolor(GREEN);
  settextstyle(1, 0, 1);
  outtextxy(11, 445, "SCORE: ");
  outtextxy(121, 445, "BULLETS: ");
}

void night()
{
  int i, x, y;
  setbkcolor(BLACK);
  setfillstyle(SOLID_FILL, WHITE);
  arc(70, 70, 67, 294, 50);
  arc(110, 70, 113, 246, 50);
  floodfill(25, 80, WHITE);
  line(0, 430, 640, 430);
  setfillstyle(SOLID_FILL, BROWN);
  floodfill(10, 440, WHITE);
  for(i = 1; i<=100; i++)
  {
    x = rand()%getmaxx();
    y = rand()%getmaxy();
    if(y<=430)
      putpixel(x, y, 15);
  }
  line(0, 430, 640, 430);
  setfillstyle(SOLID_FILL, DARKGRAY);
  floodfill(400, 440, WHITE);
  setfillstyle(SOLID_FILL, LIGHTGRAY);
  bar(10, 445, 110, 465);
  bar(120, 445, 230, 465);
  setcolor(DARKGRAY);
  settextstyle(1, 0, 1);
  outtextxy(11, 445, "SCORE: ");
  outtextxy(121, 445, "BULLETS: ");
}

void draw_shooter()
{
  int points[] = {250, 430, 280, 410, 300, 410, 300, 370, 330, 370, 330, 410, 350, 410, 380, 430, 250, 430};
  setfillstyle(SOLID_FILL, BLUE);
  fillpoly(9, points);
}

void draw_bottle()
{
  int points[] = {315, 113, 315, 118, 310, 128, 310, 178, 330, 178, 330, 128, 325, 118, 325, 113, 315, 113};
  setcolor(RED);
  setfillstyle(SOLID_FILL, LIGHTRED);
  fillpoly(9, points);
  rectangle(315, 170, 325, 150);
  setfillstyle(SOLID_FILL, RED);
  floodfill(320, 165, RED);
}

void draw_bullet()
{
  int points[] = {320, 205, 315, 212, 315, 238, 325, 238, 325, 212, 320, 205};
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, LIGHTGRAY);
  fillpoly(6, points);
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
  int gd = DETECT, gm, back;
  initgraph ( &gd, &gm, "C:\\TC\\BGI" ) ;
  randomize();
  back = random(100);
  if(back%2 == 0)
    {
      day();
      setfillstyle(SOLID_FILL, LIGHTGREEN);
    }
  else
    {
      night();
      setfillstyle(SOLID_FILL, LIGHTGRAY);
    }
  setcolor(WHITE);
  draw_shooter();
  setfillstyle(SOLID_FILL, MAGENTA);
  bar(0, 180, 640, 185);
  draw_bottle();
  getch();
  closegraph();
  return 0;
}