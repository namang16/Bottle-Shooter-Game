#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

void firework(int maxx)
{
  int x, y, color, i;
  while(!kbhit())
  {
    x = maxx/2 - random(40) + 150;
    y = random(100) + 300;
    color = random(7) + 9;
    setcolor(10);
    settextstyle(4,0,8);
    //setusercharsize(120,50,120,40);
    outtextxy(getmaxx()/2-230,getmaxy()/2-60,"YOU WON");
    for(i = 0; i<100; i++)
    {
      putpixel(x + i, y + random(4) + 10, color);
      putpixel(x + i, y - i/3 + random(4) + 10, color);
      putpixel(x + i/2, y - i/2 + random(4) + 10, color);
      putpixel(x + i/2, y + i/2 + random(4) + 10, color);
      putpixel(x + i, y + i/4 + random(4) + 10, color);
      delay(5);
    }
   x = x - 350; y = random(60) + 100;

    for(i = 0; i<100; i++)
    {
      putpixel(x + random(4), y - i, color - 3);
      putpixel(x + 2 * i/3 + random(4), y - 2 * i/3, color - 3);
      putpixel(x - 2 * i/3 + random(4), y - 2 * i/3, color - 3);
      putpixel(x - i/3 + random(4), y - i, color - 3);
      putpixel(x - i + random(4), y - i/10, color - 3);
      delay(3);
    }
    x = x + 350; y = 100;

    for(i = 0; i<100; i++)
    {
      putpixel(x + i/3 + random(4), y + i/2, color - 2);
      putpixel(x + 10 + i/2 + random(4), y - 10 + i/6, color - 2);
      putpixel(x + 10 + i/2 + random(4), y - 10 - i/2, color - 2);
      putpixel(x - i/3 + random(4), y - 10 - i/2, color - 2);
      putpixel(x - 10 - i/3 + random(4), y - 10 + i/2, color - 2);
      putpixel(x - 10 - i + random(4), y - 20 - i/2, color - 2);
      putpixel(x + 10 + i + random(4), y - 10 - i/2, color - 2);
      putpixel(x + 10 + random(4), y - 10 - i, color - 2);
      putpixel(x + i/10 + random(4), y + 10 + i/2, color - 2);
      putpixel(x - 10 - i/2 + random(4), y - 10 + i/20, color - 2);
      delay(5);
    }
    x = x - 350; y = 400;

    for(i = 0; i < 150; i++)
    {
      putpixel(x - i/2 + random(i), y - i/2 + random(i), color+1);
      putpixel(x + 2 - i/2 + random(i), y + 2 - i/2 + random(i), color+1);
      delay(3);
    }
    delay(50);
    cleardevice();
  }
}

void main()
{
int gd = DETECT, gm, maxx;
randomize();
initgraph ( &gd, &gm, "C:\\TC\\BGI" ) ;
maxx = getmaxx();
firework(maxx);
}
