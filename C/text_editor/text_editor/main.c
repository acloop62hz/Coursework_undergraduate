#include "acllib.h"
#include <string.h>
#include <stdio.h>
char s[200]={'\0'};
int x=0,y=0;
float tx=0,ty=0;
void charListener(char key){
		if(x<0)x=0;if(tx<0)tx=0;
		if(key==13) {printf("%s\n",s);return ;}
		char dcun[200]={'\0'};
		if(x<strlen(s)){
			if(key==8){s[x-1]='\0';strcat(dcun,s+x);strcat(s,dcun);tx=tx-7;x--;}
			else if(key==46){strcat(dcun,s+x+1);s[x]='\0';strcat(s,dcun);}
			else{strcat(dcun,s+x);
			s[x]=key;s[x+1]='\0';
			strcat(s,dcun);tx=tx+7;x++;}
			}
		else if(x==strlen(s)){
		 {if(key==8){s[x-1]='\0';tx=tx-7;x--;}
		 else if(key==46); 
			else {s[x]=key;s[x+1]='\0';tx=7*strlen(s);x=strlen(s);}
			}
		}
		else{
			if(key==8){tx=tx-7;x--;}
		}
	
	beginPaint();
	clearDevice();//要放在这里！！ 
	paintText(0,0,s);
	endPaint();
	
	
}
	
void timeListener(int id){
	if(id==1){
	setCaretPos(tx,ty);
	showCaret();
	}
}

void keyboardListener(int key,int event){//注意来两次！ 
	if(event==0){
	if(key==37) {tx=tx-7;x=x-1;}
	if(key==39) {tx=tx+7;x=x+1;}
	if(key==46) charListener(46); 
	}
}


int Setup(){
	initWindow("Test",DEFAULT,DEFAULT,800,600);
	initConsole();

	//registerMouseEvent(mouseListener);
	setCaretSize(1,10);
	registerCharEvent(charListener);
	registerTimerEvent(timeListener);
	registerKeyboardEvent(keyboardListener);
	startTimer(1,300);

	return 0;
} 
