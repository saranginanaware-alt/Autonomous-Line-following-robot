#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>

#define N 9

int px[N]={80,180,180,300,420,420,520,520,590};
int py[N]={390,390,280,280,280,150,150,350,350};

void drawGraphBackground()
{
 int x,y;

 setcolor(DARKGRAY);
 for(x=50;x<=630;x+=40)
     line(x,75,x,445);
 for(y=75;y<=445;y+=40)
     line(50,y,630,y);

 setcolor(LIGHTGRAY);
 line(50,445,635,445);
 line(50,70,50,445);

 setcolor(CYAN);
 outtextxy(625,450,"X");
 outtextxy(35,65,"Y");

 setcolor(DARKGRAY);
 for(x=90;x<=610;x+=80)
     line(x,441,x,449);
 for(y=115;y<=435;y+=80)
     line(46,y,54,y);
}

void drawEnvironment()
{
 int i;
 cleardevice();

 drawGraphBackground();

 setcolor(CYAN);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(55,15,"AUTONOMOUS LINE FOLLOWING ROBOT");

 settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
 setcolor(LIGHTGRAY);
 outtextxy(95,45,"DUAL IR SENSOR NAVIGATION - GRAPH VIEW");

 setcolor(DARKGRAY);
 rectangle(55,90,125,145);
 rectangle(225,90,295,145);
 rectangle(330,90,400,145);
 rectangle(470,205,610,260);

 setcolor(YELLOW);
 outtextxy(63,110,"SHELF A");
 outtextxy(233,110,"SHELF B");
 outtextxy(338,110,"SHELF C");
 outtextxy(490,225,"STORAGE");

 setcolor(WHITE);
 setlinestyle(SOLID_LINE,0,THICK_WIDTH);
 for(i=0;i<N-1;i++)
     line(px[i],py[i],px[i+1],py[i+1]);
 setlinestyle(SOLID_LINE,0,1);

 for(i=0;i<N;i++)
 {
     setcolor(LIGHTCYAN);
     circle(px[i],py[i],3);
 }

 setcolor(GREEN);
 rectangle(55,365,105,415);
 outtextxy(55,420,"START");

 setcolor(LIGHTRED);
 rectangle(565,325,615,375);
 outtextxy(555,380,"FINISH");
}

void drawRobot(int x,int y)
{
 setcolor(YELLOW);
 setfillstyle(SOLID_FILL,YELLOW);
 bar(x-13,y-10,x+13,y+10);
 setcolor(WHITE);
 rectangle(x-13,y-10,x+13,y+10);

 setfillstyle(SOLID_FILL,LIGHTGRAY);
 bar(x-17,y-8,x-13,y+8);
 bar(x+13,y-8,x+17,y+8);

 setcolor(LIGHTCYAN);
 setfillstyle(SOLID_FILL,LIGHTCYAN);
 fillellipse(x-6,y+12,3,3);
 fillellipse(x+6,y+12,3,3);

 setcolor(BLACK);
 outtextxy(x-4,y-4,"R");
}

void drawDashboard(int leftIR,int rightIR,int motor,int completed)
{
 setfillstyle(SOLID_FILL,BLUE);
 bar(455,290,635,455);
 setcolor(WHITE);
 rectangle(455,290,635,455);

 outtextxy(470,305,"ROBOT CONTROL");

 if(leftIR==0) outtextxy(470,335,"LEFT IR : BLACK");
 else outtextxy(470,335,"LEFT IR : WHITE");

 if(rightIR==0) outtextxy(470,355,"RIGHT IR: BLACK");
 else outtextxy(470,355,"RIGHT IR: WHITE");

 if(motor==0) outtextxy(470,380,"MOTOR: FORWARD");
 else if(motor==1) outtextxy(470,380,"MOTOR: LEFT");
 else if(motor==2) outtextxy(470,380,"MOTOR: RIGHT");
 else outtextxy(470,380,"MOTOR: STOP");

 if(completed) outtextxy(470,410,"STATUS: COMPLETED");
 else outtextxy(470,410,"STATUS: AUTONOMOUS");

 outtextxy(470,435,"P=PAUSE ESC=EXIT");
}

int main()
{
 int gd=DETECT,gm;
 int i,j,x,y,leftIR,rightIR,motor,key;
 int completed=0;
 float t;

 initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

 for(i=0;i<N-1;i++)
 {
  for(j=0;j<=25;j++)
  {
   t=j/25.0;
   x=px[i]+(int)((px[i+1]-px[i])*t);
   y=py[i]+(int)((py[i+1]-py[i])*t);

   if(i==1 || i==4 || i==6)
   {
    leftIR=0; rightIR=1; motor=1;
   }
   else if(i==2 || i==5)
   {
    leftIR=1; rightIR=0; motor=2;
   }
   else
   {
    leftIR=0; rightIR=0; motor=0;
   }

   if(i==N-2 && j==25) completed=1;

   drawEnvironment();
   drawRobot(x,y);
   drawDashboard(leftIR,rightIR,motor,completed);

   if(kbhit())
   {
    key=getch();
    if(key==27)
    {
     closegraph();
     return 0;
    }
    if(key=='p' || key=='P')
    {
     setcolor(YELLOW);
     outtextxy(250,55,"PAUSED - PRESS ANY KEY");
     getch();
    }
   }
   delay(65);
  }
 }

 setcolor(GREEN);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(150,485,"AUTONOMOUS RUN COMPLETED!");

 getch();
 closegraph();
 return 0;
}
