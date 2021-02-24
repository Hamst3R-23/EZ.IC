#include <ncurses.h>

int main(){
	int ch;
	int k;
	int mas1[4][2] = {3,3,2,3,1,3,0,3};
	char mas2[] = {'+','*','*','*'};
	initscr();
	keypad(stdscr,TRUE);
	for(int i=0; i<4; i++)
		mvaddch(mas1[i][0],mas1[i][1],mas2[i]);	
	
	refresh();
	while ((ch=getch())!='q'){
		clear();
		if (ch == KEY_UP){
			for(k=3; k>0; k--){
				mas1[k][0] = mas1[k-1][0];
				mas1[k][1] = mas1[k-1][1];
			}
			mas1[0][0]--;
			for(int k=0; k<4; k++)
				mvaddch(mas1[k][0],mas1[k][1],mas2[k]);		
		}
		if (ch == KEY_DOWN){
			for(k=3; k>0; k--){
				mas1[k][0] = mas1[k-1][0];
				mas1[k][1] = mas1[k-1][1];
			}
			mas1[0][0]++;
			for(int k=0; k<4; k++)
				mvaddch(mas1[k][0],mas1[k][1],mas2[k]);				
		}
		if (ch == KEY_RIGHT){
			for(k=3; k>0; k--){
				mas1[k][0] = mas1[k-1][0];
				mas1[k][1] = mas1[k-1][1];
			}
			mas1[k][1]++;
			for(int k=0; k<4; k++)
				mvaddch(mas1[k][0],mas1[k][1],mas2[k]);					
		}
		if (ch == KEY_LEFT){
			for(k=3; k>0; k--){
				mas1[k][0] = mas1[k-1][0];
				mas1[k][1] = mas1[k-1][1];
			}
			mas1[k][1]--;
			for(int k=0; k<4; k++)
				mvaddch(mas1[k][0],mas1[k][1],mas2[k]);	
		}
		refresh();
	}
	endwin();
	return 0;
}