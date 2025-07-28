//============================================================================
// Name        : ABDUL MATEEN.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================
#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include <fstream>
using namespace std;
// seed the random numbers generator by current time (see the documentation of srand for further help)...
/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
/*
 * Main Canvas drawing function.
 * */
class startGame{
	public:
	int gameLevel;
	startGame(){
		gameLevel=2;
		loadLevel();
	}
	void loadLevel(){
		//boundary
		DrawLine(60,11,60,810,100,colors[WHITE]);
		DrawLine(59,12,1650,11,100,colors[WHITE]);
		DrawLine(60,810,1650,810,100,colors[WHITE]);
		DrawLine(1650,11,1650,810,100,colors[WHITE]);
	}
};
class paddle:public startGame{
	public:
	static int x1;
	static int wx1;
	static int x2;
	static int wx2;
	protected:
	static int paddlecolour;
	int level;
	public:
	paddle(){
		drawLowerPaddle();
		if(gameLevel==3){
			level=3;
			drawUpperPaddle();
		}
		else if(gameLevel==2){
			level=2;
		}
		else{
			level=1;
		}
	}
	void drawLowerPaddle(){
		if(x1+wx1>=1650){
			x1=1650-wx1;
		}
		else if(x1<=65){
			x1=65;
		}
		if(paddlecolour==0){
			DrawRectangle(x1,25,wx1,20,colors[LIME_GREEN]);
		}
		else if(paddlecolour==1){
			DrawRectangle(x1,25,wx1,20,colors[GREEN]);
		}
		else if(paddlecolour==2){
			DrawRectangle(x1,25,wx1,20,colors[DEEP_PINK]);
		}
		else if(paddlecolour==3){
			DrawRectangle(x1,25,wx1,20,colors[BLUE]);
		}
		else if(paddlecolour==4){
			DrawRectangle(x1,25,wx1,20,colors[RED]);
		}
		else if(paddlecolour==5){
			DrawRectangle(x1,25,wx1,20,colors[YELLOW]);
		}
	}
	void drawUpperPaddle(){
		if(x2+wx2>=1650){
			x2=1650-wx2;
		}
		else if(x2<=65){
			x2=65;
		}
		DrawRectangle(x2,770,wx2,40,colors[CHART_REUSE]);
	}
};
class ball:public startGame,public paddle{
	public:
	static int ballX[3],ballY[3];
	static int ballDirX[3],ballDirY[3];
	static int balls;
	static int color;
	ball(){
		drawBall();
		collision();
	}
	void drawBall(){
		if(color==0){
			for(int i=0;i<balls;i++){
				DrawCircle(ballX[i],ballY[i],20,colors[FIREBRICK]);
				ballY[i]+=ballDirY[i];
				ballX[i]+=ballDirX[i];
			}
		}
		else if(color==1){
			for(int i=0;i<balls;i++){
				DrawCircle(ballX[i],ballY[i],20,colors[GREEN]);
				ballY[i]+=ballDirY[i];
				ballX[i]+=ballDirX[i];
			}
		}
		else if(color==2){
			for(int i=0;i<balls;i++){
				DrawCircle(ballX[i],ballY[i],20,colors[DEEP_PINK]);
				ballY[i]+=ballDirY[i];
				ballX[i]+=ballDirX[i];
			}
		}
		else if(color==3){
			for(int i=0;i<balls;i++){
				DrawCircle(ballX[i],ballY[i],20,colors[BLUE]);
				ballY[i]+=ballDirY[i];
				ballX[i]+=ballDirX[i];
			}
		}
		else if(color==4){
			for(int i=0;i<balls;i++){
				DrawCircle(ballX[i],ballY[i],20,colors[RED]);
				ballY[i]+=ballDirY[i];
				ballX[i]+=ballDirX[i];
			}
		}
		else if(color==5){
			for(int i=0;i<balls;i++){
				DrawCircle(ballX[i],ballY[i],20,colors[YELLOW]);
				ballY[i]+=ballDirY[i];
				ballX[i]+=ballDirX[i];
			}
		}
		glutPostRedisplay();
	}
	void collision(){
		for(int i=0;i<balls;i++){
			if(ballX[i]<=65){
			ballDirX[i]=-ballDirX[i];
			}
			else if(ballX[i]>=1650){
				ballDirX[i]=-ballDirX[i];
			}
			else if(ballY[i]>=800){
				if(level==2 || level==1){
					ballDirY[i]=-ballDirY[i];
				}
			}
			else if(ballX[i]<=paddle::x1+paddle::wx1 && ballX[i]>=paddle::x1 && (ballY[i]<=50 && ballY[i]>=5)){
				ballDirY[i]=-ballDirY[i];
				if(color==1){
					paddle::paddlecolour=1;
				}
				else if(color==2){
					paddle::paddlecolour=2;
				}
				else if(color==3){
					paddle::paddlecolour=3;
				}
				else if(color==4){
					paddle::paddlecolour=4;
				}
				else if(color==5){
					paddle::paddlecolour=5;
				}
			}
			if(level==3){
				if(ballX[i]<=paddle::x2+wx2 && ballX[i]>=paddle::x2 && (ballY[i]<=810 && ballY[i]>=770)){
					ballDirY[i]=-ballDirY[i];
				}
			}
		}
	}
};
class brick:public startGame{
	public:
	int xarr[25][14];
	int xarrG[25][14];
	int yarrG[25][14];
	int xarrP[25][14];
	int yarrP[25][14];
	int xarrB[25][14];
	int yarrB[25][14];
	int xarrR[25][14];
	int yarrR[25][14];
	int xarrY[25][14];
	int yarrY[25][14];
	private:
	int pink[25][14];
	int blue[25][14];
	int red[25][14];
	int yellow[25][14];
	int random[25][14];
	public:
	bool greenF[25][14];
	bool pinkF[25][14];
	bool blueF[25][14];
	bool redF[25][14];
	bool yellowF[25][14];
	bool flag;
	int power;
	int power2;
	int score;
	protected:
	int brickwidth;
	int brickheight;
	static int lifes;
	bool gameOver;
	public:
	brick(){
		srand(time(0));
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				xarr[i][j]=1;
			}
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				xarrG[i][j]=1;
			}
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				pink[i][j]=2;
			}
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				blue[i][j]=3;
			}
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				red[i][j]=3;
			}
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				yellow[i][j]=2;
			}
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				random[i][j]=rand()%5+1;
			}
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				greenF[i][j]=false;
			}
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				pinkF[i][j]=false;
			}
		}
		for(int i=0;i<9;i++){
			for(int j=0;j<14;j++){
				blueF[i][j]=false;
			}
		}
		for(int i=0;i<9;i++){
			for(int j=0;j<14;j++){
				redF[i][j]=false;
			}
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<14;j++){
				yellowF[i][j]=false;
			}
		}
		if(gameLevel==1){
			brickheight=35;
			brickwidth=108;
		}
		else if(gameLevel==2){
			brickheight=20;
			brickwidth=100;
		}
		else{
			brickheight=35;
			brickwidth=100;
		}
		score=0;
		flag=false;
		power=5000;
		power2=5000;
	}
	//operator overloading(polymorphism)
	void operator ++(){
		score=score+1;
	}
	void drawBricks(int rows,int columns,int a){
		int brickX=300;
		int brickY=680;
		int xSpace=0;
		int ySpace=0;
		//drawing bricks for level 1
		if(gameLevel==1){
			int brickX=70;
			int brickY=760;
			int xSpace=0;
			int ySpace=0;
			for(int i=0;i<9;i++){
				for(int j=0;j<14;j++){
					if(xarr[i][j]>0){
						switch(random[i][j]){
							case 1:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[GREEN]);
							xarrG[i][j]=brickX+xSpace;
							yarrG[i][j]=brickY-ySpace;
							break;
							case 2:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[DEEP_PINK]);
							xarrP[i][j]=brickX+xSpace;
							yarrP[i][j]=brickY-ySpace;
							break;
							case 3:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[BLUE]);
							xarrB[i][j]=brickX+xSpace;
							yarrB[i][j]=brickY-ySpace;
							break;
							case 4:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[RED]);
							xarrR[i][j]=brickX+xSpace;
							yarrR[i][j]=brickY-ySpace;
							break;
							case 5:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[YELLOW]);
							xarrY[i][j]=brickX+xSpace;
							yarrY[i][j]=brickY-ySpace;
							break;
						}
						xarr[i][j]=brickX+xSpace;
					}
					xSpace+=brickwidth+4;
				}
				ySpace+=brickheight+4;
				xSpace=0;
			}
			string lifesText="LIVES:"+toString(lifes);
			DrawString(60,850,lifesText.c_str(),colors[WHITE]);
			string scoreText="SCORE:"+toString(score);
			DrawString(700,850,scoreText.c_str(),colors[WHITE]);
			string levelText="LEVEL:"+toString(gameLevel);
			DrawString(1400,850,levelText.c_str(),colors[WHITE]);
			DrawString(60,820,"ABDUL MATEEN",colors[LAWN_GREEN]);
			DrawString(1400,820,"23i-2511",colors[LAWN_GREEN]);
			DrawString(700,820,"PROGRESS:",colors[LAWN_GREEN]);
			DrawLine(830,825,1050,825,5,colors[WHITE]);
			DrawLine(830,825,830+score,825,4,colors[DARK_BLUE]);
		}
		//for level 2
		else if(gameLevel==2){
			int brickX=70;
			int brickY=770;
			int xSpace=0;
			int ySpace=0;
			int start=1;
			for(int i=0;i<25;i++){
				for(int j=0;j<5;j++){
					if(xarr[i][j]>0){
						switch(random[i][j]){
							case 1:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[GREEN]);
							xarrG[i][j]=brickX+xSpace;
							yarrG[i][j]=brickY-ySpace;
							break;
							case 2:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[DEEP_PINK]);
							xarrP[i][j]=brickX+xSpace;
							yarrP[i][j]=brickY-ySpace;
							break;
							case 3:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[BLUE]);
							xarrB[i][j]=brickX+xSpace;
							yarrB[i][j]=brickY-ySpace;
							break;
							case 4:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[RED]);
							xarrR[i][j]=brickX+xSpace;
							yarrR[i][j]=brickY-ySpace;
							break;
							case 5:
							DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[YELLOW]);
							xarrY[i][j]=brickX+xSpace;
							yarrY[i][j]=brickY-ySpace;
							break;
						}
						xarr[i][j]=brickX+xSpace;
					}
					xSpace+=brickwidth+4;
				}
				ySpace+=25;
				if(i>=4 && i<=13){
					xSpace=start*(104*5);
					if(i==8){
						start++;
					}
				}
				else if(i>=14){
					if(i==14 || i==19){
						start--;
					}
					xSpace=start*(104*5);
				}
				else{
					xSpace=0;
				}
			}
			string lifesText="LIVES:"+toString(lifes);
			DrawString(60,850,lifesText.c_str(),colors[WHITE]);
			string scoreText="SCORE:"+toString(score);
			DrawString(700,850,scoreText.c_str(),colors[WHITE]);
			string levelText="LEVEL:"+toString(gameLevel);
			DrawString(1400,850,levelText.c_str(),colors[WHITE]);
			DrawString(60,820,"ABDUL MATEEN",colors[LAWN_GREEN]);
			DrawString(1400,820,"23i-2511",colors[LAWN_GREEN]);
			DrawString(700,820,"PROGRESS:",colors[LAWN_GREEN]);
			DrawLine(830,825,1050,825,5,colors[WHITE]);
			DrawLine(830,825,830+score,825,4,colors[DARK_BLUE]);
		}
		//for level 3
		else if(gameLevel==3){
			if(a>12){
				return;
			}	
			else{
				if(a==1){
					printBricks(11,brickX,xSpace,brickY,ySpace,0,0);
				}
				else if(a==2){
					printBricks(5,brickX,xSpace,brickY,ySpace+35+4,1,0);
					printBricks(5,brickX,xSpace+(6*brickwidth+30),brickY,ySpace+35+4,1,6);
				}
				else if(a==3){
					printBricks(4,brickX,xSpace,brickY,ySpace+(2*35)+8,2,0);
					printBricks(4,brickX,xSpace+(7*brickwidth+35),brickY,ySpace+(2*35)+8,2,7);
				}
				else if(a==4){
					printBricks(3,brickX,xSpace,brickY,ySpace+(3*35)+12,3,0);
					printBricks(3,brickX,xSpace+(8*brickwidth+40),brickY,ySpace+(3*35)+12,3,8);
				}
				else if(a==5){
					printBricks(2,brickX,xSpace,brickY,ySpace+(4*35)+16,4,0);
					printBricks(2,brickX,xSpace+(9*brickwidth+45),brickY,ySpace+(4*35)+16,4,9);
				}
				else if(a==6){
					printBricks(1,brickX,xSpace,brickY,ySpace+(5*35)+20,5,0);
					printBricks(1,brickX,xSpace+(10*brickwidth+50),brickY,ySpace+(5*35)+20,5,10);
				}
				else if(a==7){
					printBricks(1,brickX,xSpace,brickY,ySpace+(6*35)+24,6,0);
					printBricks(1,brickX,xSpace+(10*brickwidth+50),brickY,ySpace+(6*35)+24,6,10);
				}
				else if(a==8){
					printBricks(2,brickX,xSpace,brickY,ySpace+(7*35)+28,7,0);
					printBricks(2,brickX,xSpace+(9*brickwidth+45),brickY,ySpace+(7*35)+28,7,9);
				}
				else if(a==9){
					printBricks(3,brickX,xSpace,brickY,ySpace+(8*35)+32,8,0);
					printBricks(3,brickX,xSpace+(8*brickwidth+40),brickY,ySpace+(8*35)+32,8,8);
				}
				else if(a==10){
					printBricks(4,brickX,xSpace,brickY,ySpace+(9*35)+36,9,0);
					printBricks(4,brickX,xSpace+(7*brickwidth+35),brickY,ySpace+(9*35)+36,9,7);
				}
				else if(a==11){
					printBricks(5,brickX,xSpace,brickY,ySpace+(10*35)+40,10,0);
					printBricks(5,brickX,xSpace+(6*brickwidth+30),brickY,ySpace+(10*35)+40,10,6);
				}
				else if(a==12){
					printBricks(11,brickX,xSpace,brickY,ySpace+(11*35)+44,11,0);
				}
			}
			string lifesText="LIVES:"+toString(lifes);
			DrawString(60,850,lifesText.c_str(),colors[WHITE]);
			string scoreText="SCORE:"+toString(score);
			DrawString(700,850,scoreText.c_str(),colors[WHITE]);
			string levelText="LEVEL:"+toString(gameLevel);
			DrawString(1400,850,levelText.c_str(),colors[WHITE]);
			DrawString(60,820,"ABDUL MATEEN",colors[LAWN_GREEN]);
			DrawString(1400,820,"23i-2511",colors[LAWN_GREEN]);
			DrawString(700,820,"PROGRESS:",colors[LAWN_GREEN]);
			DrawLine(830,825,1050,825,5,colors[WHITE]);
			DrawLine(830,825,830+score,825,4,colors[DARK_BLUE]);
			drawBricks(rows,columns,++a);
		}
	}
	//helper recursive function
	void printBricks(int x,int brickX,int xSpace,int brickY,int ySpace,int i,int j){
		if(x<=0){
			return;
		}
		else{
			if(xarr[i][j]>0){
				switch(random[i][j]){
				case 1:
				DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[GREEN]);
				xarrG[i][j]=brickX+xSpace;
				yarrG[i][j]=brickY-ySpace;
				break;
				case 2:
				DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[DEEP_PINK]);
				xarrP[i][j]=brickX+xSpace;
				yarrP[i][j]=brickY-ySpace;
				break;
				case 3:
				DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[BLUE]);
				xarrB[i][j]=brickX+xSpace;
				yarrB[i][j]=brickY-ySpace;
				break;
				case 4:
				DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[RED]);
				xarrR[i][j]=brickX+xSpace;
				yarrR[i][j]=brickY-ySpace;
				break;
				case 5:
				DrawRoundRect(brickX+xSpace,brickY-ySpace,brickwidth,brickheight,colors[YELLOW]);
				xarrY[i][j]=brickX+xSpace;
				yarrY[i][j]=brickY-ySpace;
				break;
				}
				xarr[i][j]=brickX+xSpace;
			}
			printBricks(--x,brickX,xSpace+brickwidth+5,brickY,ySpace,i,++j);
		}
	}
	void collision(){
		if(gameLevel==1){
			for(int a=0;a<ball::balls;a++){
				for(int i=0;i<9;i++){
					for(int j=0;j<14;j++){
						if((ball::ballX[a]==xarrG[i][j] && ball::ballY[a]<=yarrG[i][j]+brickheight && ball::ballY[a]>=yarrG[i][j]) || (ball::ballX[a]==xarrG[i][j]+brickwidth && ball::ballY[a]<=yarrG[i][j]+brickheight && ball::ballY[a]>=yarrG[i][j])){
							greenF[i][j]=true;
							ball::ballDirX[a]=-ball::ballDirX[a];
							xarr[i][j]=-90;
							xarrG[i][j]-=1700;
							ball::color=1;
							++*this;
						}
						else if((ball::ballX[a]==xarrP[i][j] && ball::ballY[a]<=yarrP[i][j]+brickheight && ball::ballY[a]>=yarrP[i][j]) || (ball::ballX[a]==xarrP[i][j]+brickwidth && ball::ballY[a]<=yarrP[i][j]+brickheight && ball::ballY[a]>=yarrP[i][j])){
							--pink[i][j];
							if(pink[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								pinkF[i][j]=true;
								xarr[i][j]=-90;
								xarrP[i][j]-=1700;
								ball::color=2;
								++*this;
							}
							else{
								ball::color=2;
								DrawRectangle(xarrP[i][j],yarrP[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if((ball::ballX[a]==xarrB[i][j]&& ball::ballY[a]<=yarrB[i][j]+brickheight && ball::ballY[a]>=yarrB[i][j]) || (ball::ballX[a]==xarrB[i][j]+brickwidth && ball::ballY[a]<=yarrB[i][j]+brickheight && ball::ballY[a]>=yarrB[i][j])){
							--blue[i][j];
							if(blue[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								blueF[i][j]=true;
								xarr[i][j]=-90;
								xarrB[i][j]-=1700;
								ball::color=3;
								++*this;
							}
							else{
								ball::color=3;
								DrawRectangle(xarrB[i][j],yarrB[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if((ball::ballX[a]==xarrR[i][j]&& ball::ballY[a]<=yarrR[i][j]+brickheight && ball::ballY[a]>=yarrR[i][j]) || (ball::ballX[a]==xarrR[i][j]+brickwidth && ball::ballY[a]<=yarrR[i][j]+brickheight && ball::ballY[a]>=yarrR[i][j])){
							--red[i][j];
							if(red[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								redF[i][j]=true;
								xarr[i][j]=-90;
								xarrR[i][j]-=1700;
								ball::color=4;
								++*this;
							}
							else{
								ball::color=4;
								DrawRectangle(xarrR[i][j],yarrR[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if((ball::ballX[a]==xarrY[i][j] && ball::ballY[a]<=yarrY[i][j]+brickheight && ball::ballY[a]>=yarrY[i][j]) || (ball::ballX[a]==xarrY[i][j]+brickwidth && ball::ballY[a]<=yarrY[i][j]+brickheight && ball::ballY[a]>=yarrY[i][j])){
							--yellow[i][j];
							if(yellow[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								yellowF[i][j]=true;
								xarr[i][j]=-90;
								xarrY[i][j]-=1700;
								ball::color=5;
								++*this;
							}
							else{
								ball::color=5;
								DrawRectangle(xarrY[i][j],yarrY[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if(ball::ballX[a]<=xarrG[i][j]+brickwidth && ball::ballX[a]>=xarrG[i][j] && ball::ballY[a]<=yarrG[i][j]+brickheight && ball::ballY[a]>=yarrG[i][j]){
							greenF[i][j]=true;
							ball::ballDirY[a]=-ball::ballDirY[a];
							xarr[i][j]=-90;
							xarrG[i][j]-=1700;
							ball::color=1;
							++*this;
						}
						else if(ball::ballX[a]<=xarrP[i][j]+brickwidth && ball::ballX[a]>=xarrP[i][j] && ball::ballY[a]<=yarrP[i][j]+brickheight && ball::ballY[a]>=yarrP[i][j]){
							--pink[i][j];
							if(pink[i][j]==0){
								pinkF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrP[i][j]-=1700;
								ball::color=2;
								++*this;
							}
							else{
								ball::color=2;
								DrawRectangle(xarrP[i][j],yarrP[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
						else if(ball::ballX[a]<=xarrB[i][j]+brickwidth && ball::ballX[a]>=xarrB[i][j] && ball::ballY[a]<=yarrB[i][j]+brickheight && ball::ballY[a]>=yarrB[i][j]){
							--blue[i][j];
							if(blue[i][j]==0){
								blueF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrB[i][j]-=1700;
								ball::color=3;
								++*this;
							}
							else{
								ball::color=3;
								DrawRectangle(xarrB[i][j],yarrB[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
						else if(ball::ballX[a]<=xarrR[i][j]+brickwidth && ball::ballX[a]>=xarrR[i][j] && ball::ballY[a]<=yarrR[i][j]+brickheight && ball::ballY[a]>=yarrR[i][j]){
							--red[i][j];
							if(red[i][j]==0){
								redF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrR[i][j]-=1700;
								ball::color=4;
								++*this;
							}
							else{
								ball::color=4;
								DrawRectangle(xarrR[i][j],yarrR[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
						else if(ball::ballX[a]<=xarrY[i][j]+brickwidth && ball::ballX[a]>=xarrY[i][j] && ball::ballY[a]<=yarrY[i][j]+brickheight && ball::ballY[a]>=yarrY[i][j]){
							--yellow[i][j];
							if(yellow[i][j]==0){
								yellowF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrY[i][j]-=1700;
								ball::color=5;
								++*this;
							}
							else{
								ball::color=5;
								DrawRectangle(xarrY[i][j],yarrY[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
					}
				}
			}
		}
		else if(gameLevel==2){
			for(int a=0;a<ball::balls;a++){
				for(int i=0;i<25;i++){
					for(int j=0;j<5;j++){
						if((ball::ballX[a]==xarrG[i][j] && ball::ballY[a]<=yarrG[i][j]+brickheight && ball::ballY[a]>=yarrG[i][j]) || (ball::ballX[a]==xarrG[i][j]+brickwidth && ball::ballY[a]<=yarrG[i][j]+brickheight && ball::ballY[a]>=yarrG[i][j])){
							greenF[i][j]=true;
							ball::ballDirX[a]=-ball::ballDirX[a];
							xarr[i][j]=-90;
							xarrG[i][j]-=1700;
							ball::color=1;
							++*this;
						}
						else if((ball::ballX[a]==xarrP[i][j] && ball::ballY[a]<=yarrP[i][j]+brickheight && ball::ballY[a]>=yarrP[i][j]) || (ball::ballX[a]==xarrP[i][j]+brickwidth && ball::ballY[a]<=yarrP[i][j]+brickheight && ball::ballY[a]>=yarrP[i][j])){
							--pink[i][j];
							if(pink[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								pinkF[i][j]=true;
								xarr[i][j]=-90;
								xarrP[i][j]-=1700;
								ball::color=2;
								++*this;
							}
							else{
								ball::color=2;
								DrawRectangle(xarrP[i][j],yarrP[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if((ball::ballX[a]==xarrB[i][j]&& ball::ballY[a]<=yarrB[i][j]+brickheight && ball::ballY[a]>=yarrB[i][j]) || (ball::ballX[a]==xarrB[i][j]+brickwidth && ball::ballY[a]<=yarrB[i][j]+brickheight && ball::ballY[a]>=yarrB[i][j])){
							--blue[i][j];
							if(blue[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								blueF[i][j]=true;
								xarr[i][j]=-90;
								xarrB[i][j]-=1700;
								ball::color=3;
								++*this;
							}
							else{
								ball::color=3;
								DrawRectangle(xarrB[i][j],yarrB[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if((ball::ballX[a]==xarrR[i][j]&& ball::ballY[a]<=yarrR[i][j]+brickheight && ball::ballY[a]>=yarrR[i][j]) || (ball::ballX[a]==xarrR[i][j]+brickwidth && ball::ballY[a]<=yarrR[i][j]+brickheight && ball::ballY[a]>=yarrR[i][j])){
							--red[i][j];
							if(red[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								redF[i][j]=true;
								xarr[i][j]=-90;
								xarrR[i][j]-=1700;
								ball::color=4;
								++*this;
							}
							else{
								ball::color=4;
								DrawRectangle(xarrR[i][j],yarrR[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if((ball::ballX[a]==xarrY[i][j] && ball::ballY[a]<=yarrY[i][j]+brickheight && ball::ballY[a]>=yarrY[i][j]) || (ball::ballX[a]==xarrY[i][j]+brickwidth && ball::ballY[a]<=yarrY[i][j]+brickheight && ball::ballY[a]>=yarrY[i][j])){
							--yellow[i][j];
							if(yellow[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								yellowF[i][j]=true;
								xarr[i][j]=-90;
								xarrY[i][j]-=1700;
								ball::color=5;
								++*this;
							}
							else{
								ball::color=5;
								DrawRectangle(xarrY[i][j],yarrY[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if(ball::ballX[a]<=xarrG[i][j]+brickwidth && ball::ballX[a]>=xarrG[i][j] && ball::ballY[a]<=yarrG[i][j]+brickheight && ball::ballY[a]>=yarrG[i][j]){
							greenF[i][j]=true;
							ball::ballDirY[a]=-ball::ballDirY[a];
							xarr[i][j]=-90;
							xarrG[i][j]-=1700;
							ball::color=1;
							++*this;
						}
						else if(ball::ballX[a]<=xarrP[i][j]+brickwidth && ball::ballX[a]>=xarrP[i][j] && ball::ballY[a]<=yarrP[i][j]+brickheight && ball::ballY[a]>=yarrP[i][j]){
							--pink[i][j];
							if(pink[i][j]==0){
								pinkF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrP[i][j]-=1700;
								ball::color=2;
								++*this;
							}
							else{
								ball::color=2;
								DrawRectangle(xarrP[i][j],yarrP[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
						else if(ball::ballX[a]<=xarrB[i][j]+brickwidth && ball::ballX[a]>=xarrB[i][j] && ball::ballY[a]<=yarrB[i][j]+brickheight && ball::ballY[a]>=yarrB[i][j]){
							--blue[i][j];
							if(blue[i][j]==0){
								blueF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrB[i][j]-=1700;
								ball::color=3;
								++*this;
							}
							else{
								ball::color=3;
								DrawRectangle(xarrB[i][j],yarrB[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
						else if(ball::ballX[a]<=xarrR[i][j]+brickwidth && ball::ballX[a]>=xarrR[i][j] && ball::ballY[a]<=yarrR[i][j]+brickheight && ball::ballY[a]>=yarrR[i][j]){
							--red[i][j];
							if(red[i][j]==0){
								redF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrR[i][j]-=1700;
								ball::color=4;
								++*this;
							}
							else{
								ball::color=4;
								DrawRectangle(xarrR[i][j],yarrR[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
						else if(ball::ballX[a]<=xarrY[i][j]+brickwidth && ball::ballX[a]>=xarrY[i][j] && ball::ballY[a]<=yarrY[i][j]+brickheight && ball::ballY[a]>=yarrY[i][j]){
							--yellow[i][j];
							if(yellow[i][j]==0){
								yellowF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrY[i][j]-=1700;
								ball::color=5;
								++*this;
							}
							else{
								ball::color=5;
								DrawRectangle(xarrY[i][j],yarrY[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
					}
				}
			}
		}
		else if(gameLevel==3){
			for(int a=0;a<ball::balls;a++){
				for(int i=0;i<12;i++){
					for(int j=0;j<11;j++){
						if((ball::ballX[a]==xarrG[i][j] && ball::ballY[a]<=yarrG[i][j]+brickheight && ball::ballY[a]>=yarrG[i][j]) || (ball::ballX[a]==xarrG[i][j]+brickwidth && ball::ballY[a]<=yarrG[i][j]+brickheight && ball::ballY[a]>=yarrG[i][j])){
							greenF[i][j]=true;
							ball::ballDirX[a]=-ball::ballDirX[a];
							xarr[i][j]=-90;
							xarrG[i][j]-=1700;
							ball::color=1;
							++*this;
						}
						else if((ball::ballX[a]==xarrP[i][j] && ball::ballY[a]<=yarrP[i][j]+brickheight && ball::ballY[a]>=yarrP[i][j]) || (ball::ballX[a]==xarrP[i][j]+brickwidth && ball::ballY[a]<=yarrP[i][j]+brickheight && ball::ballY[a]>=yarrP[i][j])){
							--pink[i][j];
							if(pink[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								pinkF[i][j]=true;
								xarr[i][j]=-90;
								xarrP[i][j]-=1700;
								ball::color=2;
								++*this;
							}
							else{
								ball::color=2;
								DrawRectangle(xarrP[i][j],yarrP[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if((ball::ballX[a]==xarrB[i][j]&& ball::ballY[a]<=yarrB[i][j]+brickheight && ball::ballY[a]>=yarrB[i][j]) || (ball::ballX[a]==xarrB[i][j]+brickwidth && ball::ballY[a]<=yarrB[i][j]+brickheight && ball::ballY[a]>=yarrB[i][j])){
							--blue[i][j];
							if(blue[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								blueF[i][j]=true;
								xarr[i][j]=-90;
								xarrB[i][j]-=1700;
								ball::color=3;
								++*this;
							}
							else{
								ball::color=3;
								DrawRectangle(xarrB[i][j],yarrB[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if((ball::ballX[a]==xarrR[i][j]&& ball::ballY[a]<=yarrR[i][j]+brickheight && ball::ballY[a]>=yarrR[i][j]) || (ball::ballX[a]==xarrR[i][j]+brickwidth && ball::ballY[a]<=yarrR[i][j]+brickheight && ball::ballY[a]>=yarrR[i][j])){
							--red[i][j];
							if(red[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								redF[i][j]=true;
								xarr[i][j]=-90;
								xarrR[i][j]-=1700;
								ball::color=4;
								++*this;
							}
							else{
								ball::color=4;
								DrawRectangle(xarrR[i][j],yarrR[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if((ball::ballX[a]==xarrY[i][j] && ball::ballY[a]<=yarrY[i][j]+brickheight && ball::ballY[a]>=yarrY[i][j]) || (ball::ballX[a]==xarrY[i][j]+brickwidth && ball::ballY[a]<=yarrY[i][j]+brickheight && ball::ballY[a]>=yarrY[i][j])){
							--yellow[i][j];
							if(yellow[i][j]==0){
								ball::ballDirX[a]=-ball::ballDirX[a];
								yellowF[i][j]=true;
								xarr[i][j]=-90;
								xarrY[i][j]-=1700;
								ball::color=5;
								++*this;
							}
							else{
								ball::color=5;
								DrawRectangle(xarrY[i][j],yarrY[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirX[a]=-ball::ballDirX[a];
							}
						}
						else if(ball::ballX[a]<=xarrG[i][j]+brickwidth && ball::ballX[a]>=xarrG[i][j] && ball::ballY[a]<=yarrG[i][j]+brickheight && ball::ballY[a]>=yarrG[i][j]){
							greenF[i][j]=true;
							ball::ballDirY[a]=-ball::ballDirY[a];
							xarr[i][j]=-90;
							xarrG[i][j]-=1700;
							ball::color=1;
							++*this;
						}
						else if(ball::ballX[a]<=xarrP[i][j]+brickwidth && ball::ballX[a]>=xarrP[i][j] && ball::ballY[a]<=yarrP[i][j]+brickheight && ball::ballY[a]>=yarrP[i][j]){
							--pink[i][j];
							if(pink[i][j]==0){
								pinkF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrP[i][j]-=1700;
								ball::color=2;
								++*this;
							}
							else{
								ball::color=2;
								DrawRectangle(xarrP[i][j],yarrP[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
						else if(ball::ballX[a]<=xarrB[i][j]+brickwidth && ball::ballX[a]>=xarrB[i][j] && ball::ballY[a]<=yarrB[i][j]+brickheight && ball::ballY[a]>=yarrB[i][j]){
							--blue[i][j];
							if(blue[i][j]==0){
								blueF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrB[i][j]-=1700;
								ball::color=3;
								++*this;
							}
							else{
								ball::color=3;
								DrawRectangle(xarrB[i][j],yarrB[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
						else if(ball::ballX[a]<=xarrR[i][j]+brickwidth && ball::ballX[a]>=xarrR[i][j] && ball::ballY[a]<=yarrR[i][j]+brickheight && ball::ballY[a]>=yarrR[i][j]){
							--red[i][j];
							if(red[i][j]==0){
								redF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrR[i][j]-=1700;
								ball::color=4;
								++*this;
							}
							else{
								ball::color=4;
								DrawRectangle(xarrR[i][j],yarrR[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
						else if(ball::ballX[a]<=xarrY[i][j]+brickwidth && ball::ballX[a]>=xarrY[i][j] && ball::ballY[a]<=yarrY[i][j]+brickheight && ball::ballY[a]>=yarrY[i][j]){
							--yellow[i][j];
							if(yellow[i][j]==0){
								yellowF[i][j]=true;
								ball::ballDirY[a]=-ball::ballDirY[a];
								xarr[i][j]=-90;
								xarrY[i][j]-=1700;
								ball::color=5;
								++*this;
							}
							else{
								ball::color=5;
								DrawRectangle(xarrY[i][j],yarrY[i][j],brickwidth,brickheight,colors[BLACK]);
								ball::ballDirY[a]=-ball::ballDirY[a];
							}
						}
					}
				}
			}
		}
	}
	void lives(){
		if(ball::ballY[0]<=1){
			--lifes;
			ball::ballX[0]=750;
			ball::ballY[0]=200;
			ball::ballDirY[0]=-ball::ballDirY[0];
		}
		if(gameLevel==3 && ball::ballY[0]>=810){
			--lifes;
			ball::ballX[0]=750;
			ball::ballY[0]=200;
		}
		if(lifes==0){
			gameOver=true;
		}
	}
	string toString(int score){
		string scoretext="";
		if(score==0){
			return "0";
		}
		while(score!=0){
			char c='0'+(score%10);
			scoretext=c+scoretext;
			score/=10;
		}
		return scoretext;
	}
	void filehandling(){
		if(gameOver){
			ofstream outFile("Score.txt");
			outFile<<"SCORE:"<<score<<endl;
			outFile.close();
			power=-9;
		}
	}
};
brick obj3;
class food:public paddle{
	public:
	food(){}
	void generateGreen(int x,int y,int i,int j){
		DrawTriangle(x,y,x+90,y,x+40,y+40,colors[GREEN]);
		if(x<=paddle::x1+paddle::wx1 && x>=paddle::x1 && (y<=54 && y>=52)){
			paddle::wx1*=2;
			paddle::wx2*=2;
			obj3.greenF[i][j]=false;
		}
		if(y<0){
			obj3.greenF[i][j]=false;
		}
	}
	void generatePink(int x,int y,int i,int j){
		DrawSquare(x,y,40,colors[DEEP_PINK]);
		if(x<=paddle::x1+paddle::wx1 && x>=paddle::x1 && (y<=54 && y>=52)){
			paddle::wx1/=2;
			paddle::wx2/=2;
			obj3.pinkF[i][j]=false;
		}
		if(y<0){
			obj3.pinkF[i][j]=false;
		}
	}
	void generateBlue(int x,int y,int i,int j){
		DrawCircle(x,y,20,colors[BLUE]);
		if(x<=paddle::x1+paddle::wx1 && x>=paddle::x1 && (y<=54 && y>=52)){
			for(int i=0;i<ball::balls;i++){
				if(ball::ballDirX[i]>0){
					ball::ballDirX[i]-=3;
				}
				else{
					ball::ballDirX[i]+=3;
				}
				if(ball::ballDirY[i]>0){
					ball::ballDirY[i]-=3;
				}
				else{
					ball::ballDirY[i]+=3;
				}
				obj3.flag=true;
				obj3.blueF[i][j]=false;
			}
		}
		if(y<0){
			obj3.blueF[i][j]=false;
		}
	}
	void generateRed(int x,int y,int i,int j){
		DrawRectangle(x,y,60,40,colors[RED]);
		if(x<=paddle::x1+paddle::wx1 && x>=paddle::x1 && (y<=54 && y>=52)){
			for(int i=0;i<ball::balls;i++){
				if(ball::ballDirX[i]>0){
					ball::ballDirX[i]+=3;
				}
				else{
					ball::ballDirX[i]-=3;
				}
				if(ball::ballDirY[i]>0){
					ball::ballDirY[i]+=3;
				}
				else{
					ball::ballDirY[i]-=3;
				}
				obj3.flag=true;
				obj3.redF[i][j]=false;
			}
		}
		if(y<0){
			obj3.redF[i][j]=false;
		}
	}
	void generateYellow(int x,int y,int i,int j){
		DrawSquare(x,y,40,colors[YELLOW]);
		if(x<=paddle::x1+paddle::wx1 && x>=paddle::x1 && (y<=54 && y>=52)){
			obj3.yellowF[i][j]=false;
			ball::balls=3;
		}
		if(y<0){
			obj3.yellowF[i][j]=false;
		}
	}
};
int paddle::x1=65;
int paddle::wx1=180;
int paddle::x2=65;
int paddle::wx2=100;
int ball::ballX[3]={750,850,950};
int ball::ballY[3]={100,150,100};
int ball::ballDirX[3]={5,5,5};
int ball::ballDirY[3]={5,5,5};
int brick::lifes=2;
int ball::balls=1;
int ball::color=0;
int paddle::paddlecolour=0;
void GameDisplay()/**/{
	glClearColor(0.2/*Red Component*/, 0.2,	//148.0/255/*Green Component*/,
			0.4/*Blue Component*/, 0.2 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	if(obj3.power!=-9){
		obj3.filehandling();
		startGame obj;
		paddle obj1;
		ball obj2;
		obj3.lives();
		obj3.drawBricks(12,11,1);
		obj3.collision();
		food obj4;
		if(obj.gameLevel==1){
			for(int i=0;i<9;i++){
				for(int j=0;j<14;j++){
					if(obj3.greenF[i][j]){
						obj4.generateGreen(obj3.xarrG[i][j]+1700,obj3.yarrG[i][j],i,j);
						obj3.yarrG[i][j]-=3;
					}
					if(obj3.pinkF[i][j]){
						obj4.generatePink(obj3.xarrP[i][j]+1700,obj3.yarrP[i][j],i,j);
						obj3.yarrP[i][j]-=3;
					}
					if(obj3.blueF[i][j]){
						obj4.generateBlue(obj3.xarrB[i][j]+1700,obj3.yarrB[i][j],i,j);
						obj3.yarrB[i][j]-=3;
					}
					if(obj3.redF[i][j]){
						obj4.generateRed(obj3.xarrR[i][j]+1700,obj3.yarrR[i][j],i,j);
						obj3.yarrR[i][j]-=3;
					}
					if(obj3.yellowF[i][j]){
						obj4.generateYellow(obj3.xarrY[i][j]+1700,obj3.yarrY[i][j],i,j);
						obj3.yarrY[i][j]-=3;
					}
				}
			}
		}
		else if(obj.gameLevel==2){
			for(int i=0;i<25;i++){
				for(int j=0;j<5;j++){
					if(obj3.greenF[i][j]){
						obj4.generateGreen(obj3.xarrG[i][j]+1700,obj3.yarrG[i][j],i,j);
						obj3.yarrG[i][j]-=3;
					}
					if(obj3.pinkF[i][j]){
						obj4.generatePink(obj3.xarrP[i][j]+1700,obj3.yarrP[i][j],i,j);
						obj3.yarrP[i][j]-=3;
					}
					if(obj3.blueF[i][j]){
						obj4.generateBlue(obj3.xarrB[i][j]+1700,obj3.yarrB[i][j],i,j);
						obj3.yarrB[i][j]-=3;
					}
					if(obj3.redF[i][j]){
						obj4.generateRed(obj3.xarrR[i][j]+1700,obj3.yarrR[i][j],i,j);
						obj3.yarrR[i][j]-=3;
					}
					if(obj3.yellowF[i][j]){
						obj4.generateYellow(obj3.xarrY[i][j]+1700,obj3.yarrY[i][j],i,j);
						obj3.yarrY[i][j]-=3;
					}
				}
			}
		}
		else if(obj.gameLevel==3){
			for(int i=0;i<12;i++){
				for(int j=0;j<11;j++){
					if(obj3.greenF[i][j]){
						obj4.generateGreen(obj3.xarrG[i][j]+1700,obj3.yarrG[i][j],i,j);
						obj3.yarrG[i][j]-=3;
					}
					if(obj3.pinkF[i][j]){
						obj4.generatePink(obj3.xarrP[i][j]+1700,obj3.yarrP[i][j],i,j);
						obj3.yarrP[i][j]-=3;
					}
					if(obj3.blueF[i][j]){
						obj4.generateBlue(obj3.xarrB[i][j]+1700,obj3.yarrB[i][j],i,j);
						obj3.yarrB[i][j]-=3;
					}
					if(obj3.redF[i][j]){
						obj4.generateRed(obj3.xarrR[i][j]+1700,obj3.yarrR[i][j],i,j);
						obj3.yarrR[i][j]-=3;
					}
					if(obj3.yellowF[i][j]){
						obj4.generateYellow(obj3.xarrY[i][j]+1700,obj3.yarrY[i][j],i,j);
						obj3.yarrY[i][j]-=3;
					}
				}
			}
		}
	}
	else{
		DrawString(700,500,"YOUR SCORE IS:"+to_string(obj3.score),colors[RED]);
	}
	glutSwapBuffers(); // do not modify this line..
}
void NonPrintableKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
	} else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	//glutPostRedisplay();
}
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	else if(key == 'w' || key == 'W'){
		paddle::x2-=25;
	}
	else if(key=='r' || key=='R'){
		paddle::x2+=25;
	}
	glutPostRedisplay();
}
void Timer(int m){
	// implement your functionality here
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0,Timer,0);
	if(obj3.flag){
		obj3.power-=1000;
		if(obj3.power<=0){
			for(int i=0;i<ball::balls;i++){
				if(ball::ballDirX[i]<0){
					ball::ballDirX[i]=-5;
					glutPostRedisplay();
				}
				else{
					ball::ballDirX[i]=5;
					glutPostRedisplay();
				}
				if(ball::ballDirY[i]<0){
					ball::ballDirY[i]=-5;
					glutPostRedisplay();
				}
				else{
					ball::ballDirY[i]=5;
					glutPostRedisplay();
				}
				obj3.flag=false;
				obj3.power=5000;
			}
		}
	}
	if(ball::balls==3){
		obj3.power2-=1000;
		if(obj3.power2<=0){
			ball::balls=1;
			obj3.power2=5000;
			ball::ballY[1]=150;
			ball::ballY[2]=100;
			ball::ballDirY[1]=-ball::ballDirY[1];
			ball::ballDirY[2]=-ball::ballDirY[2];
			glutPostRedisplay();
		}
	}
}
void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	static int prev=x;
	if(x>prev){
		paddle::x1+=10;
	}
	else if(x<prev){
		paddle::x1-=10;
	}
	prev=x;
	glutPostRedisplay();
}
void MouseClicked(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
int main(int argc, char*argv[]) {
	int width = 1700, height = 880; 
	// i have set my window size to be 800 x 600
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Arkadriod Brick Breaker Game"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */