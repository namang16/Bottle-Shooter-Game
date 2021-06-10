#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>

union REGS in, out;

int callmouse();
int mousehide();
void mouseposi(int* , int* , int* );
void restrictmouseptr(int , int , int , int );
int testkeys();

void start_game();
void init_game();
void end_game();
void exit_game();

void homescreen();
void front();
void load();
void instruct();

void game_won();
void game_lost();

void draw_button();
void draw_buttons1();
void draw_buttons2();
void draw_buttons3();

void draw_bullet();
void draw_bottle();
void draw_shooter();
void draw_burst(int, int);

void day();
void night();

void bottle_move(int *x);
void bullet_move(int, int *y);
void shooter_move(int*, int);

int f_bottle = 0, f_bullet = 0, f_shooter = 1;
int score = 0, bullets = 10, count_bottle = 0, back = 0;
char score_ch[5], bullets_ch[5];

void *bottle, *bullet, *burst, *shooter;

void main()
{
  int gd = DETECT, gm;
  int i = 10, j = 30, key, x = 310, x_s = 250, s_m = 0, s = 300;
  int x_mouse, y_mouse, cl_mouse;
  randomize();
  initgraph(&gd,&gm,"C:\\TC\\BGI");
  cleardevice();
  init_game();
  homescreen();

  callmouse();
  restrictmouseptr(0, 430, 640, 480);

  while(f_bottle == 1)
  {
    mouseposi(&x_mouse, &y_mouse, &cl_mouse);
    if(cl_mouse == 1)
    {
      if((x_mouse>480 && x_mouse<550) && (y_mouse>440 && y_mouse<460))
      {
	mousehide();
	cleardevice();
	load();
	homescreen();
	i = 10;
	j = 30;
	x = 310;
	x_s = 250;
	s_m = 0;
	s = 300;
	f_shooter = 1;
	f_bullet = 0;
	callmouse();
	restrictmouseptr(0, 430, 640, 480);
      }
      else if((x_mouse>370 && x_mouse<470) && (y_mouse>440 && y_mouse<460))
      {
	mousehide();
	cleardevice();
	load();
	start_game();
	i = 10;
	j = 30;
	x = 310;
	x_s = 250;
	s_m = 0;
	s = 300;
	f_shooter = 1;
	f_bullet = 0;
	callmouse();
	restrictmouseptr(0, 430, 640, 480);
      }
      else if((x_mouse>560 && x_mouse<630) && (y_mouse>440 && y_mouse<460))
      {
	mousehide();
	cleardevice();
	exit_game();
      }
    }

    bottle_move(&i);
    if( kbhit() )
    {
      key = testkeys();
      if( key == 32)
      {
	f_bullet = 1;
	f_shooter = 0;
      }
      if( key == 27 )
	f_bottle = 0;
      if( key == 75 && f_shooter == 1)
      {
	if(x_s > 100)
	{
	  s_m = -1;
	  shooter_move(&x_s, s_m);
	  x -= 20;
	  s -= 20;
	  s_m = 0;
	}
      }
      if( key == 77 && f_shooter == 1)
      {
	if(x_s < 400)
	{
	  s_m = 1;
	  shooter_move(&x_s, s_m);
	  x += 20;
	  s += 20;
	  s_m = 0;
	}
      }
    }
    if(f_bullet == 1)
      bullet_move(x, &j);
    if(i>= s && i<= s+40 && j>=195 && j<=230)
    {
      putimage(i-10, j-70, burst, COPY_PUT);
      setfillstyle(SOLID_FILL, MAGENTA);
      bar(0, 180, 640, 185);
      sound(500);
      delay(300);
      nosound();
      putimage(i-10, j-70, burst, XOR_PUT);
      f_bullet = 0;
      f_shooter = 1;
      bullets--;
      score+=20;
      j = 30;
      if(count_bottle % 2 == 0)
      {
	i = 620;
	count_bottle++;
      }
      else
      {
	i = 10;
	count_bottle++;
      }

      itoa(score, score_ch, 10);
      itoa(bullets, bullets_ch, 10);
      if(back%2 == 0)
      {
	setfillstyle(SOLID_FILL, LIGHTGREEN);
	bar(10, 445, 110, 465);
	bar(120, 445, 230, 465);
	setcolor(GREEN);
	settextstyle(1, 0, 1);
	outtextxy(11, 445, "SCORE: ");
	outtextxy(80, 445, score_ch);
	outtextxy(121, 445, "BULLETS: ");
	outtextxy(205, 445, bullets_ch);
      }
      else
      {
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(10, 445, 110, 465);
	bar(120, 445, 230, 465);
	setcolor(DARKGRAY);
	settextstyle(1, 0, 1);
	outtextxy(11, 445, "SCORE: ");
	outtextxy(80, 445, score_ch);
	outtextxy(121, 445, "BULLETS: ");
	outtextxy(205, 445, bullets_ch);
      }
    }
    if(j>240)
    {
      f_bullet = 0;
      f_shooter = 1;
      bullets--;
      j = 30;
      itoa(bullets, bullets_ch, 10);
      if(back%2 == 0)
      {
	setfillstyle(SOLID_FILL, LIGHTGREEN);
	bar(120, 445, 230, 465);
	setcolor(GREEN);
	settextstyle(1, 0, 1);
	outtextxy(121, 445, "BULLETS: ");
	outtextxy(205, 445, bullets_ch);
      }
      else
      {
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(120, 445, 230, 465);
	setcolor(DARKGRAY);
	settextstyle(1, 0, 1);
	outtextxy(121, 445, "BULLETS: ");
	outtextxy(205, 445, bullets_ch);
      }
    }
    if(score == 120 || bullets == 0)
    {
      delay(200);
      mousehide();
      end_game();
      i = 10;
      j = 30;
      x = 310;
      x_s = 250;
      s_m = 0;
      s = 300;
      f_shooter = 1;
      f_bullet = 0;
      callmouse();
      restrictmouseptr(0, 430, 640, 480);
    }
    key = 0;
    setfillstyle(SOLID_FILL, MAGENTA);
    bar(0, 180, 640, 185);
  }
  getch();
  closegraph();
}

int callmouse()			//call mouse pointer
{
  in.x.ax = 1;
  int86(0x33, &in, &out);
  return 1;
}

int mousehide()                 //hide mouse pointer
{
  in.x.ax = 2;
  int86(0x33, &in, &out);
  return 1;
}

void mouseposi(int *xpos, int *ypos, int *click)
{
  in.x.ax = 3;
  int86(0x33, &in, &out);
  *click = out.x.bx;            //return left click, right click or no click
  *xpos = out.x.cx;             //return x position of mouse pointer
  *ypos = out.x.dx;             //return y position of mouse pointer
}

void restrictmouseptr(int x1, int y1, int x2, int y2)
{
  in.x.ax = 7;                  //restrict x coordinate of mouse pointer
  in.x.cx = x1;
  in.x.dx = x2;
  int86(0x33, &in, &out);
  in.x.ax = 8;                  //restrict y coordinate of mouse pointer
  in.x.cx = y1;
  in.x.dx = y2;
  int86(0x33, &in, &out);
}

int testkeys()
{
  in.h.ah = 0 ;
  int86 (0x16, &in, &out) ;
  if ( out.h.al )                 //if ascii code is not 0
    return ( out.h.al ) ;      	 //return ascii code
  else
    return ( out.h.ah ) ;       //return scan code
}

void start_game()
{
  cleardevice();
  back = random(100);
  score = 0;
  bullets = 10;

  if(back%2 == 0)
    day();
  else
    night();

  setfillstyle(SOLID_FILL, MAGENTA);
  bar(0, 180, 640, 185);

  putimage(250, 370, shooter, COPY_PUT);

  draw_buttons2();
}

void init_game()
{
  int area;
  cleardevice();

  draw_bottle();
  area = imagesize(310,185,330,250);
  bottle = malloc(area);
  getimage(310,190,330,255, bottle);
  putimage(310,190, bottle, XOR_PUT);

  draw_bullet();
  area = imagesize(315,205,325,238);
  bullet = malloc(area);
  getimage(315,205,325,238, bullet);
  putimage(315,205, bullet, XOR_PUT);

  draw_burst(200, 300);
  area = imagesize(200-16,300-12,200+16,300+12);
  burst = malloc(area);
  getimage(200-16,300-12,200+16,300+12,burst);
  putimage(200-16,300-12,burst,XOR_PUT);

  draw_shooter();
  area = imagesize(250,400,380,460);
  shooter = malloc(area);
  getimage(250,370,380,430, shooter);
  putimage(250,370,shooter,XOR_PUT);
  cleardevice();

  if (bottle == NULL || burst == NULL || shooter == NULL || bullet == NULL)
  {
    closegraph();
    printf( "Insufficient memory... Press any key " );
    getch();
    exit(0);
  }
}

void end_game()
{
  if (score == 120)
  {
    cleardevice();
    game_won();
    return;
  }
  else if (bullets == 0)
  {
    cleardevice();
    game_lost();
    return;
  }
}

void exit_game()
{
  mousehide();
  cleardevice();
  settextstyle(1, 0, 5);
  setbkcolor(YELLOW);
  setcolor(RED);
  outtextxy(250, 180, "THANKS");
  outtextxy(280, 220, "FOR");
  outtextxy(240, 260, "PLAYING");
  delay(2000);
  free(shooter);
  free(burst);
  free(bullet);
  free(bottle);
  exit(0);
}

void homescreen()
{
  int x_mouse, y_mouse, cl_mouse = 0;
  cleardevice();
  front();
  draw_buttons1();
  callmouse();
  restrictmouseptr(0, 0, getmaxx(), getmaxy());
  while(1)
  {
    mouseposi(&x_mouse, &y_mouse, &cl_mouse);
    if((x_mouse>280 && x_mouse<350) && (y_mouse>340 && y_mouse<360) && cl_mouse == 1)
    {
      mousehide();
      cleardevice();
      load();
      start_game();
      f_bottle = 1;
      break;
    }
    else if((x_mouse>230 && x_mouse<400) && (y_mouse>370 && y_mouse<390) && cl_mouse == 1)
    {
      mousehide();
      cleardevice();
      instruct();
      start_game();
      f_bottle = 1;
      break;
    }
    else if((x_mouse>280 && x_mouse<350) && (y_mouse>400 && y_mouse<420) && cl_mouse == 1)
    {
      mousehide();
      cleardevice();
      exit_game();
    }
  }
}

void front()
{
  setbkcolor(LIGHTCYAN);
  int x, y, xx, yy, count = 0, i = 16;
  x = getmaxx();
  y = getmaxy();
  setcolor(WHITE);
  while(count<=100)
  {
    count++;
    setfillstyle(1, random(i));
    circle(xx = random(x), yy = random(y), random(30));
    floodfill(xx, yy, getmaxcolor());
  }
  setfillstyle(9, YELLOW);
  bar(160, 100, 460, 300);
  settextstyle(1,0,7);
  setcolor(4);
  outtextxy(195,105,"BOTTLE");
  outtextxy(175,175,"SHOOTER");
  line(178, 177, 438, 177);
  line(168, 257, 456, 257);
}

void load()
{
  cleardevice();
  int x, y, c = 150, i, e;
  x = getmaxx()/2;
  y = getmaxy()/2;
  setbkcolor(BLACK);
  setcolor(CYAN);
  for(e = 0; e<15; e++)
  {
    for(i = 50; i<100; i++)
    {
      settextstyle(SMALL_FONT, HORIZ_DIR, 10);
      outtextxy(x, y, "Loading...");
      circle(x, y, i);
      circle(x, y, c);
      c--;
      cleardevice();
    }
  }
}

void instruct()
{
  int x, y, cl;
  cleardevice();
  rectangle(1,1,638,478);
  settextstyle(3,0,1);
  setusercharsize(50,30,50,30);
  outtextxy(150,10,"INSTRUCTIONS");
  setbkcolor(YELLOW);
  settextstyle(6,0,3);
  outtextxy(10, 90, "1. This is a SINGLE PLAYER GAME.");
  outtextxy(10, 130, "2. You can move the SHOOTER RIGHT and LEFT with the help of");
  outtextxy(50, 150, "ARROW KEYS.");
  outtextxy(10, 190, "3. Press SPACEBAR to shoot the BULLET.");
  outtextxy(10, 230, "4. You score 20 POINTS every time you shoot the BOTTLE.");
  outtextxy(10, 270, "5. You have got 10 BULLETS. ");
  outtextxy(10, 310, "6. You WIN the game if you score more than 120 POINTS. ");
  draw_button();
  callmouse();
  restrictmouseptr(0, 0, getmaxx(), getmaxy());
  while(1)
  {
    mouseposi(&x, &y, &cl);
    if((x>480 && x<550) && (y>440 && y<460) && cl == 1)
    {
      mousehide();
      cleardevice();
      load();
      return;
    }
  }
}

void game_won()
{
  int x, y, color, xx, yy, cl, i;
  while(!kbhit())
  {
    x = 320 - random(40) + 150;
    y = random(100) + 300;
    color = random(7) + 9;
    setcolor(10);
    setbkcolor(BLACK);
    settextstyle(4,0,8);
    callmouse();
    restrictmouseptr(0, 0, 639, 479);
    outtextxy(getmaxx()/2-230,getmaxy()/2-60,"YOU WON");
    draw_buttons3();
    mouseposi(&xx, &yy, &cl);
    if(cl == 1)
    {
      if((xx>270 && xx<360) && (yy>340 && yy<360))
      {
	mousehide();
	cleardevice();
	bullets = 10;
	score = 0;
	load();
	start_game();
	return;
      }
      else if((xx>280 && xx<350) && (yy>370 && yy<390))
      {
	mousehide();
	cleardevice();
	exit_game();
      }
    }
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
    delay(1000);
    cleardevice();
    mousehide();
  }
  if(kbhit())
    exit_game();
}

void game_lost()
{
  int xx, yy, cl, i;
  setcolor(10);
  setbkcolor(BLACK);
  settextstyle(4,0,8);
  callmouse();
  outtextxy(getmaxx()/2-230,getmaxy()/2-60,"YOU LOST");
  draw_buttons3();
  restrictmouseptr(0, 0, 639, 479);
  while(1)
  {
    mouseposi(&xx, &yy, &cl);
    if(cl == 1)
    {
      if((xx>270 && xx<360) && (yy>340 && yy<360))
      {
	mousehide();
	cleardevice();
	bullets = 10;
	score = 0;
	load();
	start_game();
	return;
      }
      else if((xx>280 && xx<350) && (yy>370 && yy<390))
      {
	mousehide();
	cleardevice();
	exit_game();
      }
    }
  }
}

void draw_button()
{
  setfillstyle(SOLID_FILL, LIGHTMAGENTA);
  bar(480, 440, 550, 460);
  setcolor(RED);
  settextstyle(1, 0, 1);
  outtextxy(493, 438, "PLAY");
}

void draw_buttons1()
{
  setfillstyle(SOLID_FILL, LIGHTMAGENTA);
  bar(280, 340, 350, 360);
  bar(230, 370, 400, 390);
  bar(280, 400, 350, 420);
  setcolor(RED);
  settextstyle(1, 0, 1);
  outtextxy(293, 338, "PLAY");
  outtextxy(253, 368, "INSTRUCTIONS");
  outtextxy(293, 398, "EXIT");
}

void draw_buttons2()
{
  setfillstyle(SOLID_FILL, LIGHTMAGENTA);
  bar(480, 440, 550, 460);
  bar(370, 440, 470, 460);
  bar(560, 440, 630, 460);
  setcolor(RED);
  settextstyle(1, 0, 1);
  outtextxy(493, 438, "HOME");
  outtextxy(383, 438, "RESTART");
  outtextxy(573, 438, "EXIT");
}

void draw_buttons3()
{
  setfillstyle(SOLID_FILL, LIGHTMAGENTA);
  bar(270, 340, 360, 360);
  bar(280, 370, 350, 390);
  setcolor(RED);
  settextstyle(1, 0, 1);
  outtextxy(283, 338, "REPLAY");
  outtextxy(293, 368, "EXIT");
}

void draw_bullet()
{
  int points[] = {320, 205, 315, 212, 315, 238, 325, 238, 325, 212, 320, 205};
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, LIGHTGRAY);
  fillpoly(6, points);
}

void draw_bottle()
{
  int points[] = {315, 190, 315, 195, 310, 205, 310, 255, 330, 255, 330, 205, 325, 195, 325, 190, 315, 190};
  setcolor(RED);
  setfillstyle(SOLID_FILL, LIGHTRED);
  fillpoly(9, points);
  rectangle(315, 212, 325, 238);
  setfillstyle(SOLID_FILL, RED);
  floodfill(320, 225, RED);
}

void draw_shooter()
{
  setcolor(BLUE);
  int points[] = {250, 430, 280, 410, 300, 410, 300, 370, 330, 370, 330, 410, 350, 410, 380, 430, 250, 430};
  setfillstyle(SOLID_FILL, BLUE);
  fillpoly(9, points);
}

void draw_burst (int x, int y)
{
  setlinestyle(0,0,1);
  setcolor(RED);
  line ( x - 16, y - 12, x - 10, y - 2 );
  line ( x - 10, y - 2, x - 16, y );
  line ( x - 16, y, x - 10, y + 2 );
  line ( x - 10, y + 2, x - 16, y + 12 );
  line ( x - 16, y + 12, x - 6, y + 2 );
  line ( x - 6, y + 2, x, y + 12 );
  line ( x, y + 12, x + 6, y + 2 );
  line ( x + 6, y + 2, x + 16, y + 12 );
  line ( x - 16, y - 12, x - 6, y - 2 );
  line ( x - 6, y - 2, x, y - 12 );
  line ( x, y - 12, x + 6, y - 2 );
  line ( x + 6, y - 2, x + 16, y - 12 );
  line ( x + 16, y - 12, x + 10, y - 2 );
  line ( x + 10, y - 2, x + 16, y );
  line ( x + 16, y, x + 10, y + 2 );
  line ( x + 10, y + 2, x + 16, y + 12 );
  setfillstyle(SOLID_FILL, YELLOW);
  floodfill(x, y, RED);
}

void day()
{
  setbkcolor(CYAN);
  setcolor(WHITE);
  circle(90, 60, 48);
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
  setcolor(CYAN);
  line(0, 430, 640, 430);
  setcolor(GREEN);
  settextstyle(1, 0, 1);
  outtextxy(11, 445, "SCORE: ");
  outtextxy(121, 445, "BULLETS: ");
  itoa(score, score_ch, 10);
  itoa(bullets, bullets_ch, 10);
  outtextxy(80, 445, score_ch);
  outtextxy(205, 445, bullets_ch);
}

void night()
{
  int i, x, y;
  setbkcolor(BLACK);
  setcolor(WHITE);
  setfillstyle(SOLID_FILL, WHITE);
  arc(60, 50, 71, 290, 30);
  arc(80, 50, 113, 246, 32);
  floodfill(35, 50, WHITE);
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
  setcolor(BLACK);
  line(0, 430, 640, 430);
  setfillstyle(SOLID_FILL, LIGHTGRAY);
  bar(10, 445, 110, 465);
  bar(120, 445, 230, 465);
  setcolor(DARKGRAY);
  settextstyle(1, 0, 1);
  outtextxy(11, 445, "SCORE: ");
  outtextxy(121, 445, "BULLETS: ");
  itoa(score, score_ch, 10);
  itoa(bullets, bullets_ch, 10);
  outtextxy(80, 445, score_ch);
  outtextxy(205, 445, bullets_ch);
}

void bottle_move(int *x)
{
  if(count_bottle % 2 == 0)
  {
    putimage(*x, 112, bottle, COPY_PUT);
    delay(40);
    putimage(*x, 112, bottle, XOR_PUT);
    *x += 10;
  }
  else
  {
    putimage(*x, 112, bottle, COPY_PUT);
    delay(40);
    putimage(*x, 112, bottle, XOR_PUT);
    *x -= 10;
  }

  if(count_bottle % 2 == 0)
  {
    if(*x > 610)
    {
      *x = 620;
      count_bottle++;
    }
  }
  else
  {
    if(*x < 10)
    {
      *x = 10;
      count_bottle++;
    }
  }
}

void bullet_move(int x, int *y)
{
  putimage(x,360 - *y, bullet, COPY_PUT);
  delay(10);
  putimage(x,360 - *y, bullet, XOR_PUT);
  *y += 15;
}

void shooter_move(int *x, int l_r)
{
  if(l_r == -1)
  {
    putimage(*x, 370, shooter, XOR_PUT);
    *x -=20;
    putimage(*x, 370, shooter, COPY_PUT);
  }
  else if(l_r == 1)
  {
    putimage(*x, 370, shooter, XOR_PUT);
    *x +=20;
    putimage(*x, 370, shooter, COPY_PUT);
  }
}