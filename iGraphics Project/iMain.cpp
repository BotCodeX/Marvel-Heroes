#include "iGraphics.h"
#include "bitmap_loader.h"
#include "Menu.h"
#include "myheader.h"
#include "Variables.h"


//Structure for minions
typedef struct minions minions;

struct minions{
	int mini_x;
	int mini_y;
	int mini_num;
	bool mini_show;
};minions enemy[10];

char mins[10][30]={"1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp"};

//Setting up the initial values for the structure variables
void initialize(){
	
	int x=20;
	int y=100;

		for(int i=0;i<5;i++)
		{
			if(!enemy[i].mini_show){
				enemy[i].mini_show=true;
				enemy[i].mini_x=1600+x;
				enemy[i].mini_y=120+y;
				y+=90;
				x+=60;
			}
		}
}

//Setting up the changed numbers for the minions to initialize
void setVariables(){
	int x=20;
	int y=100;

	for(int i=0;i<5;i++)
	{
		 enemy[i].mini_x=1600+x;  
		 enemy[i].mini_y=120+y;
		 enemy[i].mini_num=rand()%5;
		 enemy[i].mini_show = true;
		 y+=90;
		 
		
	}
}

//This method controls Iron-Man's life states & also the collision logic in terms with minions
void showLife(){
	
	for(int i = 0; i<5; i++){
			if((imPos_y <= enemy[i].mini_y && imPos_y + 240 >= enemy[i].mini_y + 88) && imPos_x + 150 >= enemy[i].mini_x){
				enemy[i].mini_show=false;
				imLife -= 1;	
			}
		}

}

/*void showLife2(){
	/*if(wlAttack == true && imPos_y <= 200 && imPos_y >= 100)
		imLife -= 10;
	if(attack == true && imPos_y <= 200 && imPos_y >= 100)
		imLife -= 10;

}*/
void fal()
{
		modes =false;
		abouts = false;
		coms = false;
		highs =  false;
		plays = false;
}

//This method deals with the movement of minibots or minions
void miniMovement()
{
	for(int i=0;i<5;i++)
	{
		enemy[i].mini_x-=25;
		if(enemy[i].mini_x<=0)
		{
			enemy[i].mini_x=1600+rand()%200;
		}
		enemy[i].mini_num++;
		if(enemy[i].mini_num>=5)
		{
			enemy[i].mini_num=0;
		}
	}
	
}


//This method visualizes the minions/minibots. This method also calls miniMovement function to regenarate the minions again, using iSetTimer function
void miniShow(){
	if(miniFly)
		for(int i=0;i<5;i++)
		{
			if(enemy[i].mini_show)
			{
				iShowBMP2(enemy[i].mini_x,enemy[i].mini_y,mins[enemy[i].mini_num],0);
			}
			
		}
		iSetTimer(100, miniMovement); //mode need
		printf("modeState");
}

//This method stops the loading picture and initializes level1
void state1(){
	loadPic = false;
	//bgRotate = true;
	imStatic = true;
	miniFly = true;
	imStatus = true;
}	

//This method shows the loading game image before starting the game and also calls state1 function after 6 seconds
void loading_Game(){
	
	iSetTimer(2000, state1);
	
	if(loadPic){
		iShowImage(0, 0, 1600, 900, loadingGame);
	
		imStatic = false;
		imBlast = false;
		//bgRotate = false;
		miniFly = false;
		imStatus = false;
	}
	
}

/*//Changes the background
void change_background(){
	
	if(bgRotate){
	for(int i=0;i<2;i++)
	{
		background_x[i] -= 1; //left slide
		if(background_x[i]+1600<0) //left slide out of frame
			background_x[i] = background_x[(i+1)%2]+1600-2; 
	}
	}
		
}

//Rotates the background
void bgRotating(){
	if(bgRotate)
		for(int i=0;i<2;i++)
			iShowImage(background_x[i],0,1600,900,background[i]);
}
*/
//Initializes Iron-Man's normal position
void imStatic2(){
	imStatic = true;
}
//Uninitializes Iron-Man's blast position
void imBlast2(){
	imBlast = false;
}
//Uninitializes Iron-Man's Arc-blast position
void imArcBlast2(){
	imArcBlast = false;
}

//This method is Iron-Mans whole appearance in the game-play. Also shows Iron-Man's life status and points 
void imEntrance(){
	
	if(imStatic){
		iShowBMP2(imPos_x, imPos_y, "1e.bmp", 0);	
	}
	
	if(imBlast){
		iShowBMP2(imPos_x, imPos_y, "1d.bmp", 0);
		iShowBMP2(imPos_x + 240, imPos_y + 157, "1o.bmp",0);
	}
	
	if(imArcBlast){
		iShowBMP2(imPos_x, imPos_y, "1i.bmp", 0);
		iShowBMP2(imPos_x + 91, imPos_y + 179-12, "blast2.bmp",0);
	}

	iSetTimer(400, imStatic2);
	iSetTimer(400, imArcBlast2);
	iSetTimer(400, imBlast2);
	

	if(imStatus){
		iText(700, 800, imScore_c, GLUT_BITMAP_TIMES_ROMAN_24);
		//iText(40, 800, imLife_c, GLUT_BITMAP_TIMES_ROMAN_24);
		//sprintf(imLife_c,"Life: %d", imLife);
		sprintf(imScore_c,"Score: %d", imScore);
		iText(40,800,TimeValueStr,GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(TimeValueStr,"Time Left: %d s",Time);
	}
}

//Sets all variables to false and returns to gameState 5
void imDead(){
	if(Time ==  0){
		//iSetTimer(5000, genDeadPic);
		iDelay(3);
		loadPic = false;
		imStatic = false;
		imBlast = false;
		//bgRotate = false;
		miniFly = false;
		imStatus = false;
		Time=30;
		gameState = 5;
		
	}
}

void TimeCount(){
	Time--;         //TIME
}

//Brings back Whiplashes initial position
void back(){
	wlShow = true;
	wlAttack = false;
}


//changes the level when minibots are defeated
void levelChange(){
	//if(imScore >= 300)
		gameState = 7;
	
}

void highScoreLogic()
{
	if (imfinal > HighScore)
	{
		HighScore = imfinal;
		FILE *HighScoreLogic;
		HighScoreLogic = fopen("highscore.txt", "w");
		fprintf(HighScoreLogic, "%d", HighScore);
		fclose(HighScoreLogic);
	}
}

void highScoreShow()
{
	iShowBMP(0, 0, "HighScoreBackground.bmp");

	FILE *HighScoreShow;
	HighScoreShow = fopen("highscore.txt", "r");
	fscanf(HighScoreShow, "%d", &HighScore);
	sprintf(HighScoreValue, "High Score: %d", HighScore);

	iText(1200, 450, HighScoreValue, GLUT_BITMAP_TIMES_ROMAN_24);

}


void iDraw()
{
	iClear();

	if(gameState == 0 && pic == true)
	{
		iShowImage(0,0,1600,900,background[bgn]);
	}
	if(gameState !=0)
	{
		pic=false;
	}
	if(gameState ==0)
	{
		pic=true;
	}

	//iPauseTimer();
	if(gameState == -1)
	{
		iShowImage(0, 0, 1600, 900, menuPage);
		imScore = 0;
		//applyButtons();
		Time=30;
	}
	
	if(gameState == 2)
		
		iShowImage(0, 0, 1600, 900, Instructions);
	
	if(gameState == 3)
		
		iShowImage(0, 0, 1600, 900, aboutUs);
	
	if(gameState == 4)
	
		exit(0);
	
	if(gameState == 5){
		
		iShowImage(0, 0, 1600, 900, imDeadPic);
		//iText(600, 400, "%s");
		imLife = 300;
		imfinal=imScore;
		Time=15;
		
	}

	if(gameState == 0){
		
		imDead();
		loading_Game();
		//bgRotate = true;
		//bgRotating();
	    imEntrance();
		miniShow();
		showLife();

		
	}

	/* if parameter (time) for minishow function is passed...
	
	if(gameState == 0){
		
		imDead();
		loading_Game();
		//bgRotate = true;
		bgRotating();
	    imEntrance();

		if( modeState == 1 )// for Easy Mode
		{
			time = 100;
			miniShow(time);
		}

		if( modeState == 2 )// for Medium Mode
		{
			time = 75;
			miniShow(time);
		}


		if( modeState == 3 )// for Hard Mode
		{
			time = 50;
			miniShow(time);
		}

		showLife();

		
	}*/

	/*if(gameState == 6){
		
		iPauseTimer(m);
		//bgRotate = false;
		iShowImage(0, 0, 1600, 900, levelbg);
		imEntrance();
		showLife2();
		
		
	}*/

	if(gameState == 1)
		{ 
			 highScoreLogic();
			 highScoreShow();

		}
	if (gameState == 8)
	{
		iShowBMP(0,0 ,"game8.bmp");
	}

	// For Mode Option, shows mode window , written in iDraw...

	if(gameState == 8 && level == true)
	{
	
		iShowImage(0, 0, 1600, 900, lev );
		/*iShowBMP( 436, 432 ,"Easy.bmp" );
		iShowBMP( 436 , 358 , "Med.bmp");
		iShowBMP( 436 ,284 ,"Hard.bmp" );*/
	
	}

	//iPassiveMouse operation


	if (plays == true)
		iShowBMP(126, 477, "Plays.bmp");
	if (highs == true)
		iShowBMP(126, 346-74, "Highs.bmp");
	if (abouts == true)
		iShowBMP(126, 164-98, "Abouts.bmp");
	if (coms == true)
		iShowBMP(126, 252-81, "Coms.bmp");
	if (modes == true)
		iShowBMP(126, 435-60, "Modes.bmp");

	
}



void iPassiveMouse(int mx, int my)
{
	mposx = mx;
	mposy = my;
	printf("%d,%d\n",mx,my);
	if(gameState == -1)
	{
	if(mx >= 120 && mx <= 426  && my >= 435 && my <= 501)//modes
	{
		modes = true;
		abouts = false;
		coms = false;
		highs = false;
		plays = false;
	}
	else if(mx >= 120 && mx <= 426  && my >= 164 && my <= 228)//about
	{
		modes = false;
		abouts = true;
		coms = false;
		highs = false;
		plays = false;
	}
	else if(mx >= 120 && mx <= 426  && my >= 252 && my <= 316)//command
	{
		modes = false;
		abouts = false;
		coms = true;
		highs = false;
		plays = false;
	}
	else if(mx >= 120 && mx <= 426  && my >=346 && my <= 410)//high score
	{
		modes =false;
		abouts = false;
		coms = false;
		highs =  true;
		plays = false;
	}
	else if(mx >= 120 && mx <= 426  && my >= 524 && my <= 590)//play
	{
		modes =false;
		abouts = false;
		coms = false;
		highs =  false;
		plays = true;
	} 
	else
	{
		fal();
	} 
	}
	if(gameState != -1)
	{
		fal();
	}

}
/*
 function iMouseMove() is called when the user presses and drags the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouseMove(int mx, int my)
{
	mposx = mx;
	mposy = my;
}

/*
 function iMouse() is called when the user presses/releases the mouse.
 (mx, my) is the position where the mouse pointer is.
 */


void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gameState == -1)
		{
			if(mx >= 1412 && mx <= 1481  && my >= 143 && my <= 202)
			gameState = 4;//exit
		if(mx >= 120 && mx <= 426  && my >= 164 && my <= 228)
			gameState = 3;//about
		if(mx >= 120 && mx <= 426  && my >= 252 && my <= 316)
			gameState = 2;//command
		if(mx >= 120 && mx <= 426  && my >=346 && my <= 410)
			gameState = 1; //high score
		if(mx >= 120 && mx <= 426  && my >= 524 && my <= 590){
			gameState = 0; //play
		
			iSetTimer(3000, imEntrance);
			iSetTimer(5000,initialize);
			
			loading_Game();
			setVariables();
			//iSetTimer(30000, levelChange);

			/* iMouse conditions for mode option*/
		}
	}
		if(mx >= 120 && mx <= 426  && my >= 435 && my <= 501)
			{
			printf("before oooooooooooooo\n");
			gameState = 8;
			level =true;
			printf("oooooooooooooo\n");
			}
		if(gameState == 8 )
		{
			if(mx >= 30 && mx <= 423 && my >= 494  && my <= 700 ) 
			{
				bgn=0;
				
			}

			if(mx >= 488 && mx <= 881 && my >= 495 && my <= 700 ) 
			{
				bgn=1;
				
			}

			if(mx >= 30 && mx <= 423 && my >= 182 && my <= 388 )
			{
				bgn=2;
				
			}// For Ha
			if(mx >= 490 && mx <= 884 && my >= 183 && my <= 387 )
			{
				bgn=3;
				
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

/*
 function iKeyboard() is called whenever the user hits a key in keyboard.
 key- holds the ASCII value of the key pressed.
 */
void iKeyboard(unsigned char key)
{
	if (key == 'q')
	{
		exit(0);
	}

	//place your codes for other keys here
	if ( key == '\b'){
		gameState = -1;
		imLife = 30000;
		imScore = 0;
	}
	if ( key == 'm')
	{
		if(music == true)
			music=false;
		else if(music == false)
			music = true;
	}

	if(key == 'p')
	{
		iPauseTimer(0);
	}
	if(key == 'r')
	{
		iResumeTimer(0);
	}


	if ( key == 's'){
		imStatic = false;
		imBlast = true;
		imArcBlast = false;
		

		if(((imPos_y + 140 >= enemy[0].mini_y && imPos_y + 140 <= enemy[0].mini_y+88) || (imPos_y + 172 >= enemy[0].mini_y && imPos_y + 172 <= enemy[0].mini_y+88)) && (imPos_x + 1440 >= enemy[0].mini_x))
		{
			enemy[0].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 140 >= enemy[1].mini_y && imPos_y + 140 <= enemy[1].mini_y+88) || (imPos_y + 172 >= enemy[1].mini_y && imPos_y + 172 <= enemy[1].mini_y+88)) && (imPos_x + 1440 >= enemy[1].mini_x))
		{
			enemy[1].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 140 >= enemy[2].mini_y && imPos_y + 140 <= enemy[2].mini_y+88) || (imPos_y + 172 >= enemy[2].mini_y && imPos_y + 172 <= enemy[2].mini_y+88)) && (imPos_x + 1440 >= enemy[2].mini_x))
		{
			enemy[2].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 140 >= enemy[3].mini_y && imPos_y + 140 <= enemy[3].mini_y+88) || (imPos_y + 172 >= enemy[3].mini_y && imPos_y + 172 <= enemy[3].mini_y+88)) && (imPos_x + 1440 >= enemy[3].mini_x))
		{
			enemy[3].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 140 >= enemy[4].mini_y && imPos_y + 140 <= enemy[4].mini_y+88) || (imPos_y + 172 >= enemy[4].mini_y && imPos_y + 172 <= enemy[4].mini_y+88)) && (imPos_x + 1440 >= enemy[4].mini_x))
		{
			enemy[4].mini_show=false;
			imScore += 10;
		}
		
		
		if(((imPos_y + 140 >= wl_Y && imPos_y + 140 <= wl_Y+224) || (imPos_y + 172 >= wl_Y && imPos_y + 172 <= wl_Y+224)) && (imPos_x + 1200 >= wl_X))
		{
			
			wlLife -= 10;
			imScore += 10;
		}
		if(((imPos_y + 140 >= wl_Y && imPos_y + 140 <= wl_Y+224) || (imPos_y + 172 >= wl_Y && imPos_y + 172 <= wl_Y+224)) && (imPos_x + 1200 >= wl_X))
		{
			
			//lokiLife -= 10;
			imScore += 10;
		}

	}

		//iSetTimer(5000,initialize);
		
		if ( key == 'd'){
		imStatic = false;
		imBlast = false;
		imArcBlast = true;
		

		if(((imPos_y + 170 >= enemy[0].mini_y && imPos_y + 170 <= enemy[0].mini_y+88) || (imPos_y + 240 >= enemy[0].mini_y && imPos_y + 240 <= enemy[0].mini_y+88)) && (imPos_x + 1440 >= enemy[0].mini_x))
		{
			enemy[0].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 170 >= enemy[1].mini_y && imPos_y + 170 <= enemy[1].mini_y+88) || (imPos_y + 240 >= enemy[1].mini_y && imPos_y + 240 <= enemy[1].mini_y+88)) && (imPos_x + 1440 >= enemy[1].mini_x))
		{
			enemy[1].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 170 >= enemy[2].mini_y && imPos_y + 170 <= enemy[2].mini_y+88) || (imPos_y + 240 >= enemy[2].mini_y && imPos_y + 240 <= enemy[2].mini_y+88)) && (imPos_x + 1440 >= enemy[2].mini_x))
		{
			enemy[2].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 170 >= enemy[3].mini_y && imPos_y + 170 <= enemy[3].mini_y+88) || (imPos_y + 240 >= enemy[3].mini_y && imPos_y + 240 <= enemy[3].mini_y+88)) && (imPos_x + 1440 >= enemy[3].mini_x))
		{
			enemy[3].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 170 >= enemy[4].mini_y && imPos_y + 170 <= enemy[4].mini_y+88) || (imPos_y + 240 >= enemy[4].mini_y && imPos_y + 240 <= enemy[4].mini_y+88)) && (imPos_x + 1440 >= enemy[4].mini_x))
		{
			enemy[4].mini_show=false;
			imScore += 10;
		}
			
	}
}


void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)//for exit
	{
		exit(0);
	}

	//place your codes for other keys here
	if (key == GLUT_KEY_UP){ 
		imPos_y += 10;
		if(imPos_y >= 500)
			imPos_y -= 10;
	}
	if (key == GLUT_KEY_DOWN){
		imPos_y -= 10;
		if(imPos_y <= 120)
			imPos_y += 10;
	}
}

int main()
{
	//place your own initialization codes here.

	
	int sum = 0.111*ScH;
	for(int i=4; i>=0; i--)
	{
		bCordinate[i].x = 0.04375*ScW;
		bCordinate[i].y = sum;
		sum += 0.1333*ScH;
	}

	int m = iSetTimer(100 , miniMovement);
	iSetTimer(1000, TimeCount);

	if(music)
		PlaySound("mcu2015.wav" , NULL , SND_LOOP | SND_ASYNC);

	
	
	iInitialize(ScW, ScH, "MARVEL HEROES");
	Instructions = iLoadImage("ins.bmp");
	aboutUs = iLoadImage("Credits.png");
	menuPage = iLoadImage("MenuBG.bmp");
	levelbg = iLoadImage("bg2.bmp");
	
	//iSetTimer(2,change_background);
	dx = 5;
	dy = 7;

	pic_x = 0;
	pic_y = 0;
	
	loadingGame = iLoadImage("loadingGame.png");
	imDeadPic = iLoadImage("imDead2.png");

	background[0] = iLoadImage("bg4.bmp");
	background[1] = iLoadImage("bg2.bmp");
	background[2] = iLoadImage("bg3.bmp");
	background[3] = iLoadImage("bg1.bmp");
	lev = iLoadImage("game8.bmp");
	
	iStart(); // it will start drawing
	

	return 0;
}

