#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <MMSystem.h>
#include <math.h>
#include <stdbool.h>
#include "wtypes.h"
#define Pi 3.14159265
using namespace std;

int main()
{
	RECT desktop;
	const HWND hdesktop = GetDesktopWindow();
	GetWindowRect(hdesktop,&desktop);
	int horizontal = desktop.right;
	int vertical = desktop.bottom;
    srand(time(0));
    int plyLocLft=0,plyLocTop=vertical/2+50,plyLocRght=12,plyLocBtm=vertical/2-50;
    int aiLocLft=horizontal-15,aiLocTop=vertical/2+50,aiLocRght=horizontal,aiLocBtm=vertical/2-50;
    int player2;
    printf("1.vs ai\n2.vs player2\n");
    scanf("%d",&player2);

    float ballx=horizontal/2-5,bally=vertical/2;
    int speed,ballspeed,SekmeOrani;
    printf("\nHareket hizi seciniz(onerilen=9)\n");
    scanf("%d",&speed);
    printf("\ntop hizini seciniz(onerilen=13)\n");
    scanf("%d",&ballspeed);
    printf("\nTopun koselere carpma sonucu hizlanma orani(onerilen=10)\n");
    scanf("%d",&SekmeOrani);
    int oldballspeed=ballspeed;
    bool won_round=false;
    int aci=270;
START:
    closegraph();
    initwindow(1707,960,"");

    setfillstyle(SOLID_FILL,WHITE);
    circle(ballx,bally,6);
    floodfill(ballx,bally,WHITE);
    settextstyle(0,0,15);
    outtextxy(horizontal/2-250,100,"Press SPACE To Start");
    bar(plyLocLft,plyLocTop,plyLocRght,plyLocBtm);
    bar(aiLocLft,aiLocTop,aiLocRght,aiLocBtm);
    int plyScore=0,aiScore=0;
    char plyscore[3];
    char aiscore[3];
    float plyLoc=(plyLocBtm+plyLocTop)/2;
    float aiLoc=(aiLocBtm+aiLocTop)/2;
    while(1)
    {
        if(GetAsyncKeyState(VK_SPACE))
            break;
    }


    int page=0;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        ballx=horizontal/2-5;
        bally=vertical/2;
        if(won_round==0)
        {
            aci=45+(rand()%90);
        }
        else
        {
            aci=225+(rand()%90);
        }
        sprintf(aiscore,"%d",aiScore);
        sprintf(plyscore,"%d",plyScore);
        while(1)
        {
            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();


            outtextxy(horizontal/2-200,100,plyscore);
            outtextxy(1000,100,aiscore);
            bar(plyLocLft,plyLocTop,plyLocRght,plyLocBtm);
            bar(aiLocLft,aiLocTop,aiLocRght,aiLocBtm);
            circle(ballx,bally,6);
            floodfill(ballx,bally,WHITE);

            if(GetAsyncKeyState('W')&&plyLocBtm>0)
            {
                plyLocTop-=speed;
                plyLocBtm-=speed;
                plyLoc-=speed;
            }
            if(GetAsyncKeyState('S')&&plyLocTop<vertical)
            {
                plyLocTop+=speed;
                plyLocBtm+=speed;
                plyLoc+=speed;
            }
            if(GetAsyncKeyState(VK_BACK))
                break;
            ballx+=(int)(sin(aci*(Pi/180))*ballspeed);
            bally+=(int)(cos(aci*(Pi/180))*ballspeed*-1);
            if(ballx+40<=0)
            {
                aiScore++;
                won_round=false;
                break;
            }
            if(ballx-40>=horizontal)
            {
                won_round=true;
                plyScore++;
                break;
            }
            if(bally-6<=0||bally+6>=vertical)
            {
                if(aci<180)
                    aci=180-aci;
                else
                {
                    aci=540-aci;
                }
            }

            if(player2==1)
            {
                if((bally>=(aiLocBtm+aiLocTop)/2)&&aiLocTop<vertical)
                {
                    aiLocBtm+=speed;
                    aiLocTop+=speed;
                    aiLoc+=speed;
                }
                if((bally<(aiLocBtm+aiLocTop)/2)&&aiLocBtm>0)
                {
                    aiLocBtm-=speed;
                    aiLocTop-=speed;
                    aiLoc-=speed;
                }
            }
            if(player2==2)
            {
                if(GetAsyncKeyState(VK_DOWN)&&aiLocTop<vertical)
                {
                    aiLocBtm+=speed;
                    aiLocTop+=speed;
                    aiLoc+=speed;
                }
                if(GetAsyncKeyState(VK_UP)&&aiLocBtm>0)
                {
                    aiLocBtm-=speed;
                    aiLocTop-=speed;
                    aiLoc-=speed;
                }

            }
            if((plyLocBtm<bally)&&(plyLocTop>bally)&&(ballx<=plyLocRght))
            {
                aci=(int)(((1.0-((2.0*(plyLoc-bally))/100.0))*45.0)+45.0);
                ballspeed=((sqrt(pow((bally-plyLoc),2)))*SekmeOrani)/50+oldballspeed;
                printf("%d\n",aci);
            }
            if((aiLocBtm<bally)&&(aiLocTop>bally)&&(ballx>=aiLocLft))
            {
                aci=(int)(((1.0-((2.0*(aiLoc-bally))/100.0))*45.0)+225.0);
                ballspeed=((sqrt(pow((bally-aiLoc),2)))*SekmeOrani)/50+oldballspeed;
            }

            page=1-page;
            delay(5);
        }
        while(1)
        {

            cleardevice();

            ballspeed=oldballspeed;
            //outtextxy(1366/2-250,100,"test");
            if(won_round==0&&player2==1&&aiScore<10&&plyScore<10)
            {
                cleardevice();
                outtextxy(horizontal/2-250,100,"AI Scored");
                delay(500);
                break;
            }
            if(won_round==0&&player2==2&&aiScore<10&&plyScore<10)
            {
                cleardevice();
                outtextxy(horizontal/2-250,100,"Player 2 Scored");
                delay(500);
                break;

            }
            if(won_round==1&&plyScore<10&&aiScore<10)
            {
                cleardevice();
                outtextxy(horizontal/2-250,100,"Player 1 Scored");
                delay(500);
                break;

            }

            if(aiScore>=10)
            {
                while(1)
                {
                    setactivepage(page);
                    setvisualpage(1-page);
                    cleardevice();
                    outtextxy(horizontal/2-250,100,"YOU LOST");
                    outtextxy(horizontal/2-250,400,"PRESS 'R' TO REPLAY");
                    outtextxy(horizontal/2-250,600,"PRESS ESC TO EXIT");
                    if(GetAsyncKeyState('R'))
                        goto START;
                    if(GetAsyncKeyState(VK_ESCAPE))
                    {
                        goto END;
                    }

                    page=1-page;
                }

            }
            if(plyScore>=10)
            {
                while(1)
                {
                    setactivepage(page);
                    setvisualpage(1-page);
                    cleardevice();
                    outtextxy(horizontal/2-250,100,"YOU WON");
                    outtextxy(horizontal/2-250,400,"PRESS 'R' TO REPLAY");
                    outtextxy(horizontal/2-250,600,"PRESS ESC TO EXIT");
                    if(GetAsyncKeyState('R'))
                        goto START;
                    if(GetAsyncKeyState(VK_ESCAPE))
                    {
                        goto END;
                    }
                    page=1-page;
                }

            }

        }

    }

END:
    closegraph();
    printf("%s\n",aiscore);

    printf("%s\n",plyscore);
    printf("%d %d",plyLocBtm,plyLocTop);




    return 0;
}
