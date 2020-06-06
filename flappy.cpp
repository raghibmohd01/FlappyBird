#include<iostream>
#include<graphics.h>
#include<time.h>
#include<stdio.h>

int score=0;
bool live=true;

class Pole;
void start();
class Player;
class Bird
{
    int bird_x,bird_y;


public:
    Bird()
    {
        bird_x=100;
        bird_y=300;
    }
    void draw()
    {

    setcolor(WHITE);
    circle(bird_x+6,bird_y,4);
    circle(bird_x,bird_y,10);

     setfillstyle(1,YELLOW);
    floodfill(bird_x,bird_y,WHITE);
    line(bird_x-5,bird_y+5,bird_x-15,bird_y+5);
    bird_y+=7;
    }
    void fly()
    {
      if(kbhit())
       {
        int ch=getch();
             if(bird_y>30)
                bird_y-=35;   //height of jump
                //printf("\a");
       }
       if(bird_y>getmaxy())             //if bird goes down move back it to middle
             bird_y=getmaxy()/2;
    }
   friend bool logic(Bird,Pole);
};

class Pole
{

    int width;
    int pole_x,pole_y;
    int gap;  //vertical gap between upper pol and downward pol
public:
    Pole()
    {
      width=40;
      pole_x=400,pole_y=300;
      gap=75;
    }
   void  get_pole_x_y()
    {
        srand(time(0));
      pole_x=rand()%getmaxx()+300;    //generates new poles coordinates
       srand(time(0));
       pole_y=rand()%150+100;

    }
    void draw()
    {

        setcolor(3);
        rectangle(pole_x,0,pole_x+width,pole_y);      //first pole rectangle point x-left, bottom corner
        setfillstyle(4,3);
        floodfill(pole_x+3,pole_y-2,3);
        rectangle(pole_x,pole_y+gap,pole_x+width,pole_y+getmaxy());  //second pole point x--left , pole-y+gap corner
        floodfill(pole_x+3,pole_y+gap+3,3);

        pole_x-=18;
        if(pole_x<0)
           get_pole_x_y();
    }
   friend bool logic(Bird,Pole);
};

class Player
{
public:
    int score;
//    string name;

public:
          Player()
          {
              score=0;
          }
          void print_score()
          {
            char str[100];
            sprintf(str,"Score: %d",score);
            outtextxy(getmaxx()-100, 10,str);
          }

           void score_up()
          {
              score=score+5;
          }
       friend bool logic(Bird,Pole);

};

bool logic(Bird bb,Pole pp)
{
           char ch;

           //plyr.print_score();
           if(bb.bird_x>=pp.pole_x+5&&bb.bird_x<=pp.pole_x+pp.width)
         if(bb.bird_y<pp.pole_y+5||bb.bird_y>pp.pole_y+pp.gap)
         {
              outtextxy(pp.pole_x,pp.pole_y+10,"Game Over");
              getch();
              cleardevice();
              outtextxy(getmaxx()/2,getmaxy()/2,"Play again  y/n");
              ch=getch();
              if(ch=='y')
              {
                  live=true;
                  start();
              }
              else
               live=false;


         }
         else{
               return true;

         }
      return false;
}

void start()
{
     Bird brd;
     Pole pol;
     Player plyr;

    int gd=0,gm;
    initgraph(&gd,&gm,"");
    initwindow(400,400,"MR_Flappy_Bird",300,30);

     setbkcolor(1);
     cleardevice();

    while(live==true)
    {
       plyr.print_score();
       pol.draw();
       brd.draw();
       brd.fly();
       if(logic(brd,pol))
       {
           plyr.score_up();
       }
         delay(90);
    cleardevice();

    }

    getch();

    closegraph();
}
int main()
{
  start();

}



