#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>

int kingkon1_xy[2],kingkon2_xy[2];
int bar1[4],bar2[4],bar3[4],bar4[4],bar5[4],bar6[4],bar7[4],bar8[4];

static int get_code( void ) { 
  int ch=getch(); // data input on keyboard
  if (ch==0||ch==224) // 224 is a ASCII 
  	ch=256+getch();
  return ch;
}

int toString(char a[]) {
  int c,sign,offset,n;
  if(a[0]=='-'){
  	sign=-1;
  }
  if(sign==-1) {
    offset=1;
  }
  else {
   offset=0;
  }
  for(c=offset;a[c]!='\0';c++) {
    n=n*10+a[c]-'0';
  }
  if(sign==-1) {
    n=-n;
  }
  return n;
}
  
main() {  // Synchronize function
   int gd=DETECT,gm;
   initgraph(&gd,&gm,"C:\\TC\\BGI"); //Use BGI in folder Turbo C++
   setbkcolor(9); // Set Color LIGHTBLUE
   loadstart(); // Firts Fucntion Load Game
   menu(); // Fucntion Menu 
   getch();
   closegraph(); // Out of the graphics
   return 0;
}

loadstart(){
   int font=3;
   int x=getmaxx()/2;
   int y=getmaxy()/2;
   settextstyle(font,HORIZ_DIR,1);setcolor(15);
   outtextxy(x-200,y,"WELCOME TO THE GAME GORILLA By Nitas Srisanoi");
   delay(2000);
   cleardevice();
   outtextxy(x-25,y,"START");
   delay(500); // delay 0.5 sec for load ... 
   outtextxy(x+25,y,"."); 
   delay(500);
   outtextxy(x+30,y,".");
   delay(500);
   outtextxy(x+35,y,".");
   delay(500);
   cleardevice();
   return 0;
}
   
menu(){ // Menu
   int menu_sel=0;
   int sound_random=100;
   int sound_delay=200;
   int ch,x,y,font=3,menu=1;
   x=getmaxx()/2;
   y=getmaxy()/2;
   while(menu_sel<=0){
     sound(10*random(sound_random));
     delay(sound_delay);
     nosound();
     switch(menu){ // Check data menu
       case 1: cleardevice(); // Clear data
       settextstyle(font, HORIZ_DIR, 1);setcolor(15);
       outtextxy(x-50,(y/2)+75,"GAME KINGKONG"); // Display on screen
       outtextxy(x-80,(y/2)+100,"[---->START GAME<----]");
       outtextxy(x-80,(y/2)+115,"      OPTION     ");
       outtextxy(x-80,(y/2)+130,"      EXIT  GAME    "); 
	   break;
	   
       case 2: cleardevice();
       settextstyle(font, HORIZ_DIR, 1);setcolor(15);
       outtextxy(x-50,(y/2)+75,"GAME KINGKONG"); // Display on screen
       outtextxy(x-80,(y/2)+100,"      START GAME    ");
       outtextxy(x-80,(y/2)+115,"[---->OPTION<----]");
       outtextxy(x-80,(y/2)+130,"      EXIT  GAME    "); 
	   break;
	   
       case 3:cleardevice();
       settextstyle(font, HORIZ_DIR, 1);setcolor(15);
       outtextxy(x-50,(y/2)+75,"GAME KINGKONG"); // Display on screen
       outtextxy(x-80,(y/2)+100,"     START GAME    ");
       outtextxy(x-80,(y/2)+115,"     OPTION      ");
       outtextxy(x-80,(y/2)+130,"[---->EXIT  GAME<----]"); 
	   break;
	}
      if(kbhit()){
      ch = get_code();
      switch(ch){
      case 328:switch(menu) {
	        case 1:menu=2;
			break;
			case 2:menu=3;
			break;
			case 3:menu=1;
			break;
	  } 
	  break;
	  
      case 336:switch(menu) {
	       case 1:menu=2;
		   break;
		   case 2:menu=3;
		   break;
		   case 3:menu=1;
		   break;
	  }
	  break;
	  
      case 27:exit(0);break;
      case 13:switch(menu){
	      case 1:background();
	      gorilla(kingkon1_xy[0],kingkon1_xy[1],1);
	      gorilla(kingkon2_xy[0],kingkon2_xy[1],1);
	      play();
	      setcolor(8);break;
	      case 2:printf("Coming soon!!!!");break;
	      case 3:exit(0);
		  break;
	  }
	  break;
	  }
     } 
   }
   return 0;
}
   
play(){ // play game
int x = getmaxx();
int key_esc;
int user_play = 1;
int overgame = 0;
int win =0;
int angle = 0;
int velocity = 0;
setcolor(8);
outtextxy(x-620,10,"Player 1");
outtextxy(x-80,10,"Player 2");
while(overgame == 0) {
   if(user_play == 1) {
     angle = checkkeyboard_angle(1);
     velocity = checkkeyboard_velocity(1);
     gorilla(kingkon1_xy[0],kingkon1_xy[1],3,0,500);
     user_play = 2;
     win = start_game(angle,velocity,1);
   }
   
   else {
     angle = checkkeyboard_angle(2);
     velocity = checkkeyboard_velocity(2);
     gorilla(kingkon2_xy[0],kingkon2_xy[1],4,0,500);
     user_play = 1;
     win = start_game(angle,velocity,2);
   }
   
  if(win == 10 || win == 20) {
         overgame = 1;
         cleardevice();
         setcolor(8);
         if(win == 10) {
	       outtextxy(300,200,"Player 1 win !!!");
		 }
	       
	 	 else {
		   outtextxy(300,200,"Player 2 win !!!");
		 }
		 getch();
   }
 }
 return 0;
}

start_game(int angle , int velocity , int play) {
int loop_start = 0;
int loop_user;
int status_win = 0;
int banana_x , banana_y;
int status_banana =0;
int g = 100;
float t,a_rad,x=0,y=0;
a_rad=angle*3.141592/180;
while(loop_start == 0){
 if(play == 1){
    banana_x = kingkon1_xy[0]-20 ;
    banana_y = kingkon1_xy[1];
    for(t=0;banana_y<=480 && banana_x<=640 && banana_x>=0;t=t+.01) {
	  x=(velocity*(cos(a_rad))*t);
	  y=(velocity*(sin(a_rad))*t)-(0.5*g*t*t);
	  
      if(status_banana == 0) {
	    banana_y -= y;
	    banana_x += x;
	    
        if(banana_x >= bar1[0] && banana_x <= bar1[1] && banana_y >= bar1[2]){
	       gorilla(banana_x,banana_y,7);banana_y = 490;
		}
        else if(banana_x >= bar2[0] && banana_x <= bar2[1] && banana_y >= bar2[2]){
		    gorilla(banana_x,banana_y,7);banana_y = 490;
		}
        else if(banana_x >= bar3[0] && banana_x <= bar3[1] && banana_y >= bar3[2]){
	        gorilla(banana_x,banana_y,7);banana_y = 490;
		}
        else if(banana_x >= bar4[0] && banana_x <= bar4[1] && banana_y >= bar4[2]){
	        gorilla(banana_x,banana_y,7);banana_y = 490;
		}
        else if(banana_x >= bar5[0] && banana_x <= bar5[1] && banana_y >= bar5[2]){
	        gorilla(banana_x,banana_y,7);banana_y = 490;
		}
        else if(banana_x >= bar6[0] && banana_x <= bar6[1] && banana_y >= bar6[2]){
	        gorilla(banana_x,banana_y,7);banana_y = 490;
		}
        else if(banana_x >= bar7[0] && banana_x <= bar7[1] && banana_y >= bar7[2]){
	        gorilla(banana_x,banana_y,7);banana_y = 490;
		}
        else if(banana_x >= bar8[0] && banana_x <= bar8[1] && banana_y >= bar8[2]){
	        gorilla(banana_x,banana_y,7);
	        banana_y = 490;
		}
        else if(banana_x >= bar8[0] && banana_x <= bar8[1] && banana_y >= bar8[2]-40){
			gorilla(banana_x,banana_y,8);banana_y = 490;status_win = 10;}
			gorilla(banana_x,banana_y,5,0,100);
			gorilla(kingkon1_xy[0],kingkon1_xy[1],1);
			status_banana = 1;
		}
		
		else{
			banana_y -= y;
			banana_x += x;
			gorilla(banana_x,banana_y,6,0,100);
			gorilla(kingkon1_xy[0],kingkon1_xy[1],1);
			status_banana = 0;
		}
    }
    
    loop_start = 1;
    setcolor(8);
	}
	else {
      banana_x = kingkon2_xy[0]+20 ;
      banana_y = kingkon2_xy[1];
      
      for(t=0;banana_y<=480 && banana_x<=640 && banana_x>=0;t=t+.01) {
	      x=(velocity*(cos(a_rad))*t);
	      y=(velocity*(sin(a_rad))*t)-(0.5*g*t*t);
	      
          if(status_banana == 0) {
	         banana_y -= y;
	         banana_x -= x;
	         
             if(banana_x >= bar1[0] && banana_x <= bar1[1] && banana_y >= bar1[2]) {
	                  gorilla(banana_x,banana_y,7);banana_y = 490;
			 }
             else if(banana_x >= bar2[0] && banana_x <= bar2[1] && banana_y >= bar2[2]) {
	                  gorilla(banana_x,banana_y,7);banana_y = 490;
			 }
             else if(banana_x >= bar3[0] && banana_x <= bar3[1] && banana_y >= bar3[2]) {
	                  gorilla(banana_x,banana_y,7);
	                  banana_y = 490;
			 }
             else if(banana_x >= bar4[0] && banana_x <= bar4[1] && banana_y >= bar4[2]) {
	                  gorilla(banana_x,banana_y,7);banana_y = 490;
			 }
             else if(banana_x >= bar5[0] && banana_x <= bar5[1] && banana_y >= bar5[2]) {
	                  gorilla(banana_x,banana_y,7);banana_y = 490;
			 }
             else if(banana_x >= bar6[0] && banana_x <= bar6[1] && banana_y >= bar6[2]) {
	                  gorilla(banana_x,banana_y,7);banana_y = 490;
			 }
             else if(banana_x >= bar7[0] && banana_x <= bar7[1] && banana_y >= bar7[2]) {
	                  gorilla(banana_x,banana_y,7);banana_y = 490;
			 }
             else if(banana_x >= bar8[0] && banana_x <= bar8[1] && banana_y >= bar8[2]) {
	                  gorilla(banana_x,banana_y,7);banana_y = 490;
			 }
             else if(banana_x >= bar1[0] && banana_x <= bar1[1] && banana_y >= bar1[2] -40) {
	                  gorilla(banana_x,banana_y,8);banana_y = 490;status_win = 20;}
	                  gorilla(banana_x,banana_y,5,0,100);
	                  gorilla(kingkon2_xy[0],kingkon2_xy[1],1);
	                  status_banana = 1;
			 }
             else {
	                  banana_y -= y;
	                  banana_x -= x;
	                  gorilla(banana_x,banana_y,6,0,100);
	                  gorilla(kingkon2_xy[0],kingkon2_xy[1],1);
	                  status_banana = 0;
			 }
        }
       loop_start = 1; //exit
       setcolor(8);
     }// play user
  }
 return status_win;
}

checkkeyboard_velocity(int player){ //Get data velocity form player
    int x=getmaxx();
    int y=getmaxy();
    char key[200]="";
    int length,loop,velocity;
    if(player==1) {
	   setcolor(15);outtextxy(x-620,55,"Velocity:");
	}
    else {
	   setcolor(15);outtextxy(x-120,55,"Velocity:");
	}
    while(player<=2) {
      if(kbhit) {
		if(player==1) {
		    gotoxy(12,5);
		    scanf("%s",&key);
		    gotoxy(12,4-5);
		}
	    else {
		    gotoxy(75,5);
	        scanf("%s",&key);
	        gotoxy(75,4-5);
		}
    length=strlen(key);
    
	for(loop=0;loop<length;loop++){
		if(isdigit(key[loop])){
	   		velocity=toString(key);
	   		
	   		if(velocity<=5000&&velocity>=0) {
	   			if(player==1) {
					setfillstyle(1,0);
					bar(x-650,y-450,x,90);
					player=4;
				}
				else{
					setfillstyle(1,0);
		     		bar(x-150,y-450,x,90);
					player = 4;
				}
	    	}
			else { 
				if(player==1){
					setfillstyle(1,0);
			    	bar(x-540,y-400,x,50);
				}
		 		else{
				 	setfillstyle(1,0);
		      		ar(x-40,y-400,x,50);
				}
	    	}
	    }
		else{ 
			if(player==1){
				setfillstyle(1,0);
				bar(x-540,y-400,x,50);
			}
	    	else{
				setfillstyle(1,0);
				bar(x-40,y-400,x,50);
			}
       	}
      }
    }
  }
  return velocity;
}

checkkeyboard_angle(int player) { //Get data angle form player
     int x=getmaxx();
     int y=getmaxy();
     char key[200]="";
     int angle,length,loop;
     if(player==1) {
	 	setcolor(15);
		 outtextxy(x-620,40,"Angle:"); // Display on screen
	 }
     else {
	    setcolor(15);
		outtextxy(x-120,40,"Angle:"); // Display on screen
	 }
     while(player<=2) {
        if(kbhit){
			if(player==1) {
			  	gotoxy(10,4);
		      	scanf("%s",&key);
		      	gotoxy(10,4);
			}
			else {
				gotoxy(72,4);
	     		scanf("%s",&key);
	     		gotoxy(72,4);
			}
		length=strlen(key);
		
		for(loop=0;loop<length;loop++) {
			if(isdigit(key[loop])) {
	   			angle=toString(key);
	   			
	    		if(angle<=90&&angle>=0) {
	      			player=4;
				}
	    		else {
					if(player==1){
						setfillstyle(15,0);
						bar(x-560,y-450,x,50);}
	    				else {
						setfillstyle(15,0);
		 				bar(x-63,y-450,x,50);
						}
	   			}
	   		}
			else {
				if(player==1){
					setfillstyle(15,0);
					bar(x-560,y-450,x,50);
				}
	   			else{setfillstyle(15,0);
					bar(x-63,y-450,x,50);
				}
       		}
      	}
    }
  }
  return angle;
}

background(){ // Background Game
   int y_bar=getmaxy();
   float x_bar=(getmaxx()/8);
   int loop_bar=0,bar_type,bar_top[8];
   cleardevice();
   randomize();
    while(loop_bar<=8) {
	   bar_top[loop_bar]=rand()%250+200;
	   bar_type=rand()%13+1;
	   if(bar_type==3||bar_type==4||bar_type==8||bar_type==10||bar_type==11){
	    setfillstyle(bar_type,8);
	    switch(loop_bar){
           case 0:bar1[0]=loop_bar*x_bar+8;
                  bar1[1]=(loop_bar*x_bar)+x_bar;
                  bar1[2]=bar_top[loop_bar];
				  break;
           case 1:bar2[0]=loop_bar*x_bar+8;
                  bar2[1]=(loop_bar*x_bar)+x_bar;
                  bar2[2]=bar_top[loop_bar];
				  break;
           case 2:bar3[0]=loop_bar*x_bar+8;
                  bar3[1]=(loop_bar*x_bar)+x_bar;
                  bar3[2]=bar_top[loop_bar];
				  break;
           case 3:bar4[0]= loop_bar*x_bar+8;
                  bar4[1]=(loop_bar*x_bar)+x_bar;
                  bar4[2]=bar_top[loop_bar];
				  break;
           case 4:bar5[0]=loop_bar*x_bar+8;
                  bar5[1]=(loop_bar*x_bar)+x_bar;
                  bar5[2]=bar_top[loop_bar];
				  break;
           case 5:bar6[0]=loop_bar*x_bar+8;
                  bar6[1]=(loop_bar*x_bar)+x_bar;
                  bar6[2]=bar_top[loop_bar];
				  break;
           case 6:bar7[0]=loop_bar*x_bar+8;
                  bar7[1]=(loop_bar*x_bar)+x_bar;
                  bar7[2]=bar_top[loop_bar];
				  break;
           case 7:bar8[0]=loop_bar*x_bar+8;
                  bar8[1]=(loop_bar*x_bar)+x_bar;
                  bar8[2]=bar_top[loop_bar];
				  break;
		}
	    bar3d(loop_bar*x_bar+8,y_bar,(loop_bar*x_bar)+x_bar,bar_top[loop_bar],1,0);
	    
	    if(loop_bar==0){kingkon1_xy[0]=(loop_bar*x_bar+8)+(x_bar/2);
	      		    kingkon1_xy[1]=bar_top[loop_bar]-40;
		}
	    if(loop_bar==7){kingkon2_xy[0]=(loop_bar*x_bar+8)+(x_bar/2);
	      		    kingkon2_xy[1]=bar_top[loop_bar]-40;}loop_bar++;
		}
    }
	return 0;
}

gorilla(int x,int y,int type,int number,int time) { // Animation gorilla
   int loop=1;
   switch(type) {
    case 1:
		setbkcolor(9);
		setcolor(15);
		setfillstyle(1,9);
		sector(x-4,y+26,0,360,5,5);
		sector(x+4,y+26,0,360,5,5);
		sector(x-6,y+30,0,360,5,5);
		sector(x+6,y+30,0,360,5,5);
		sector(x-7,y+35,0,360,5,5);
		sector(x+7,y+35,0,360,5,5);
		setcolor(15);
		setfillstyle(1,9);
		sector(x-10,y+12,0,360,4,4);
		sector(x+10,y+12,0,360,4,4);
		sector(x-15,y+16,0,360,4,4);
		sector(x+15,y+16,0,360,4,4);
		sector(x-20,y+22,0,360,5,5);
		sector(x+20,y+22,0,360,5,5);
		setcolor(15);
		setfillstyle(1,9);
		sector(x,y+15,0,360,10,13);
		setcolor(15);
		setfillstyle(1,9);
		sector(x,y+17,0,360,4,4);
		sector(x-3,y+12,0,360,2,2);
		sector(x+3,y+12,0,360,2,2);
		setcolor(15);
		circle(x,y,8);
		setfillstyle(1,8);
		sector(x,y+3,0,360,7,4);
		setcolor(15);
		ellipse(x,y+3,180,360,4,2);
		setcolor(8);
		sector(x-3,y-1,0,360,3,3);
		sector(x+3,y-1,0,360,3,3);
		setcolor(15);
		circle(x-3,y-1,1);
		circle(x+3,y-1,1);
	break;
    case 2:
	 while(loop <= number) {
		delay(time);
		setcolor(0);
		setfillstyle(1,9);
		sector(x-10,y+12,0,360,4,4);
		sector(x+10,y+12,0,360,4,4);
		sector(x-15,y+16,0,360,4,4);
		sector(x+15,y+16,0,360,4,4);
		sector(x-20,y+22,0,360,5,5);
		sector(x+20,y+22,0,360,5,5);
		setcolor(0);
		setfillstyle(1,9);
		sector(x-10,y+12,0,360,4,4);
		sector(x+10,y+12,0,360,4,4);
		sector(x-15,y+8,0,360,4,4);
		sector(x+15,y+8,0,360,4,4);
		sector(x-20,y+2,0,360,5,5);
		sector(x+20,y+2,0,360,5,5);
		delay(time);
		setcolor(0);
		setfillstyle(1,9);
		sector(x-10,y+12,0,360,4,4);
		sector(x+10,y+12,0,360,4,4);
		sector(x-15,y+8,0,360,4,4);
		sector(x+15,y+8,0,360,4,4);
		sector(x-20,y+2,0,360,5,5);
		sector(x+20,y+2,0,360,5,5);
		setcolor(0);
		setfillstyle(1,9);
		sector(x-10,y+12,0,360,4,4);
		sector(x+10,y+12,0,360,4,4);
		sector(x-15,y+16,0,360,4,4);
		sector(x+15,y+16,0,360,4,4);
		sector(x-20,y+22,0,360,5,5);
		sector(x+20,y+22,0,360,5,5);
		loop++;
	}
	break;
    case 3:
		setcolor(0);
		setfillstyle(1,9);
		sector(x-10,y+12,0,360,4,4);
		sector(x-15,y+16,0,360,4,4);
		sector(x-20,y+22,0,360,5,5);
		setcolor(0);
		setfillstyle(1,9);
		sector(x-10,y+12,0,360,4,4);
		sector(x-15,y+8,0,360,4,4);
		sector(x-20,y+2,0,360,5,5);
		delay(time);
		setcolor(0);
		setfillstyle(1,9);
		sector(x-10,y+12,0,360,4,4);
		sector(x-15,y+8,0,360,4,4);
		sector(x-20,y+2,0,360,5,5);
		setcolor(0);
		setfillstyle(1,9);
		sector(x-10,y+12,0,360,4,4);
		sector(x-15,y+16,0,360,4,4);
		sector(x-20,y+22,0,360,5,5);
	break;
    case 4:
		setcolor(0);
		setfillstyle(1,9);
		sector(x+10,y+12,0,360,4,4);
		sector(x+15,y+16,0,360,4,4);
		sector(x+20,y+22,0,360,5,5);
		setcolor(0);
		setfillstyle(1,9);
		sector(x+10,y+12,0,360,4,4);
		sector(x+15,y+8,0,360,4,4);
		sector(x+20,y+2,0,360,5,5);
		delay(time);
		setcolor(0);
		setfillstyle(1,9);
		sector(x+10,y+12,0,360,4,4);
		sector(x+15,y+8,0,360,4,4);
		sector(x+20,y+2,0,360,5,5);
		setcolor(0);
		setfillstyle(1,9);
		sector(x+10,y+12,0,360,4,4);
		sector(x+15,y+16,0,360,4,4);
		sector(x+20,y+22,0,360,5,5);
	break;
    case 5:
		setfillstyle(1,9);
		setcolor(0);
		sector(x,y,0,360,5,2);
		delay(time);
		setfillstyle(1,9);
		setcolor(0);
		sector(x,y,0,360,5,2);
	break;
	case 6:
		setfillstyle(1,8);
		setcolor(0);
		sector(x,y,0,360,2,5);
		delay(time);
		setfillstyle(1,9);
		setcolor(0);
		sector(x,y,0,360,2,5);
	break;
	case 7:
		setfillstyle(1,9);
		setcolor(8);
		sector(x,y,0,360,10,10);
	break;
	case 8:
		setfillstyle(1,9);
		setcolor(0);
		sector(x,y,0,360,40,40);
		delay(2000);break;
	}
  return 0;
}

