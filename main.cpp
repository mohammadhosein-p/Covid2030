#include <iostream>
#include <cmath>
#include <windows.h>
#include <time.h>
#include <cstring>
using namespace std;
int temp=0;
int maxBullet = 3;
int range=5;
int kill=0;
int tir=3;
int kheshab=0;
int health=3 ;
int credit=0;
int game_round=0;
int final_level=3;
int vaccineCollected = 0;
char order[1];
int arr[15][15] = {0}; 
bool is_sound_on = false;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Clear_scr() {
#if defined_WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux_) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif

}

void green() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}
void red() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}
void yellow() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
}
void cyan() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void magenta() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
}
void blue() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}
void blue_bold() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

}
void green_bold() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

}
void red_bold() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

}
void magenta_bold() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

}
void yellow_bold() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void cyan_bold() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void reset_color() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

void main_menu();
void start();
void print_health_status();
void print_ammo_status();
void print_play_ground();
void player_function(char);
void shot(char);
void zombi_Movment();
void death();
void check_bullet(char);
void upgrade(char);
void reload(char);
void levelFinish();


int main() {
	int zombieMoveCounter = 0;
	srand(time(0));

	red();
	cout << " ######   #######  ##     ## #### ########      #######    #####     #######    #####\n";
	cout << "##    ## ##     ## ##     ##  ##  ##     ##    ##     ##  ##    ##  ##     ##  ##    ##\n";
	cout << "##       ##     ## ##     ##  ##  ##     ##           ## ##      ##        ## ##      ##\n";
	cout << "##       ##     ## ##     ##  ##  ##     ##     #######  ##      ##  #######  ##      ## \n";
	cout << "##       ##     ##  ##    ##  ##  ##     ##    ##        ##      ##        ## ##      ##    \n";
	cout << "##    ## ##     ##   ##  ##   ##  ##     ##    ##         ##    ##  ##     ##  ##    ##  \n";
	cout << " ######   #######     ###    #### ########     ########    #####     #######    #####\n";
	reset_color();

	cout << "Welcome to Covid 2030 game!\n";

	main_menu();
	system("cls");
	start();
	print_play_ground();

	while(true) {
		cin >> order;
		game_round++;
		zombieMoveCounter++;
		player_function(order[0]);
		check_bullet(order[0]);
		reload(order[0]);
		upgrade(order[0]);
		levelFinish();
		if (order[0] == 'e' or order[0] == 'E')
			main_menu();
		if (zombieMoveCounter % 2 ==0)
			zombi_Movment();
		death();
		system("cls");
		print_play_ground();
	}

}










void main_menu() {
	cout << "1 - New Game\t2 - Settings\t3 - Credits\t4 - Help\t5 - Exit\n";
	cin >> order[0];
	system("cls");
	switch (order[0]) {
		case '1': // NEW GAME
			system("cls");
			break;

		case '2': // SETTINGS
			cout << "Final level is: " << final_level << endl;
			if (is_sound_on == false) {
				cout << "Sound is mute!\nDo you want to unmute the sound? (y : YES | n : NO)\n";
				cin >> order[0];
				system("cls");
				if (order[0] == 'n') {
					return main_menu();
				} else if (order[0] == 'y') {
					is_sound_on = true;
					return main_menu();
				} else {
					return main_menu();
				}
			} else if (is_sound_on == true) {
				cout << "Sound is not mute!!\nDo you want to mute the sound? (y : YES | n : NO)\n";
				cin >> order[0];
				system("cls");
				if (order[0] == 'n') {
					return main_menu();
				} else if (order[0] == 'y') {
					is_sound_on = false;
					return main_menu();
				} else {
					return main_menu();
				}
			}

			break;

		case '3': // CREDITS
			yellow();
			cout << "Amirreza Samari kalaj\nMohammadhossein Paakdaman\nMohammadmahdi Sharifi pour\n";
			reset_color();
			Sleep(2000);
			system("cls");
			return main_menu();
			break;

		case '4': // HELP
			blue();
			cout << "HELP\n";
			reset_color();
			return main_menu();
			break;

		case '5': // EXIT
			cout << "Are you sure you want to exit the game? (y : YES | n : NO)\n";
			cin >> order[0];
			system("cls");
			if (order[0] == 'y') {
				cout << "Good Bye!";
				exit(0);
			}

			if (order[0] == 'n') {
				return main_menu();
			}

			break;

		default: // Invalid input
			return main_menu();
			break;

	}
	return;
}

void start() {
	for (int i = 1; i<14; i++)
		for (int j=1; j<14; j++)
			arr[i][j] = 0;
	arr[0][0] = 1; arr[14][14]=2; // player num = 1 or 6, destination num = 2
	for (int index = 0; index<final_level; index++) { //select zambie location
		int i = rand()%12+3, j = rand()%12+3;
		if (arr[i][j] == 0)
			arr[i][j] = 5; //zambie num = 5
		else
			index--;
	}
	for (int index=0 ; index<final_level ; index++) { //select vaccine location
		int i = rand()%15, j = rand()%15;
		if (arr[i][j] == 0)
			arr[i][j] = 4; //vaccine num = 4
		else 
			index--;
	}
	for (int index = 0 ; index<(final_level+1)/2; index++) {
		int i = rand()%15, j = rand()%15;
		if (arr[i][j] == 0)
			arr[i][j] = 3; //ammo num = 3
		else 
			index--;
	}
}


void print_health_status(int number_of_health) {
	cout << "Health: [ ";
	for(int i=0; i< number_of_health ; i++) {
		cout << "| ";
	}
	cout << "]\t";
}

void print_ammo_status(int num_tir, int num_kheshab) {
	cout << "Ammo: " << num_tir << "/" << num_kheshab << "\t";
}

void print_play_ground() {
	cout << "Level: " << final_level << "\tVaccine: " << vaccineCollected << "\tCredit: " << credit << "\tRound: " << game_round << endl;
	print_health_status(health);
	print_ammo_status(tir, kheshab);
	cout << "Kill: " << kill << endl;

	cout << "-----------------" << endl;
	for (int i = 1; i <= 15; i++) {
		cout << "|";
		for (int j = 2; j <= 16; j++) {
			if (arr[i-1][j-2]==0)
				cout << " ";
			if (arr[i-1][j-2]==1||arr[i-1][j-2]==6) {
				green();
				cout << "P";
			}
			if (arr[i-1][j-2]==2){
				cyan();
				cout << "D";
			}
			if (arr[i-1][j-2]==5||arr[i-1][j-2]>6){
				magenta();
				cout << "z";
			}	
			if (arr[i-1][j-2]==4) {
				yellow();
				cout << "V";
			}
			if (arr[i-1][j-2]==3){
				blue_bold();
				cout << "A";
			}
			reset_color();
		}

		cout << "|" << endl;
	}
	cout << "-----------------" << endl;
}
void player_function(char x)
{
	int i,j;
	for(int s=0;s<15;s++)
		   for(int z=0;z<15;z++)
		   	if(arr[s][z]==1||arr[s][z]==6)
		   	{
		   		i=s;
		   		j=z;
			}
	if(x=='w'||x=='W')
	{
		if(i-1>-1)
		{
	     	if(arr[i-1][j]==4)
		    {
			   vaccineCollected++;
			   credit += final_level + 1;
			   arr[i-1][j]=1;
		    }
		    else if(arr[i-1][j]==3)
		    {
			   kheshab++;
			   arr[i-1][j]=1;
	     	}
		    else if(arr[i-1][j]==5)
		    {
		    	arr[i-1][j]=6;
			}
			else if(arr[i-1][j]==0)
		    {
		    	arr[i-1][j]=1;
			}
			arr[i][j]--;
	   }
	}
	else if(x=='s'||x=='S')
	{
		if(i+1<15)
		{
		    if(arr[i+1][j]==4)
		    {
			   vaccineCollected++;
			   credit += final_level + 1;
			   arr[i+1][j]=1;
		    }
		    else if(arr[i+1][j]==3)
		    {
			   kheshab++;
			   arr[i+1][j]=1;
	     	}
		    else if(arr[i+1][j]==5)
		    {
		    	arr[i+1][j]=6;
			}
			else if(arr[i+1][j]==0)
		    {
		    	arr[i+1][j]=1;
			}
			else if (arr[i+1][j]==2)
			{
				arr[i+1][j]=1;
			}
			arr[i][j]--;
	   }
	}
	else if(x=='d'||x=='D')
	{
		if(j+1<15)
		{
		   if(arr[i][j+1]==4)
		    {
			   vaccineCollected++;
			   credit += final_level + 1;
			   arr[i][j+1]=1;
		    }
		    else if(arr[i][j+1]==3)
		    {
			   kheshab++;
			   arr[i][j+1]=1;
	     	}
		    else if(arr[i][j+1]==5)
		    {
		    	arr[i][j+1]=6;
			}
			else if(arr[i][j+1]==0)
		    {
		    	arr[i][j+1]=1;
			}
			else if(arr[i][j+1]==2)
		    {
		    	arr[i][j+1]=1;
			}
			arr[i][j]--;
	    }
	}
	else if(x=='a'||x=='A')
	{
	   if(j-1>-1)
	    {
		   if(arr[i][j-1]==4)
		    {
			   vaccineCollected++;
			   credit += final_level + 1;
			   arr[i][j-1]=1;
		    }
		    else if(arr[i][j-1]==3)
		    {
			   kheshab++;
			   arr[i][j-1]=1;
	     	}
		    else if(arr[i][j-1]==5)
		    {
		    	arr[i][j-1]=6;
			}
			else if(arr[i][j-1]==0)
		    {
		    	arr[i][j-1]=1;
			}
			arr[i][j]--;
		}
			
	}
	if(arr[14][14]==0)
	arr[14][14]=2;
}
void shot(char x)
{
	for(int i=0;i<15;i++)
	  for(int j=0;j<15;j++)
	    if(arr[i][j]==1||arr[i][j]==6)
	    {
	    	if(x=='f'||x=='F')
	    	{
	    		for(int s=j;s>max(j-range,0);s--)
	    		   if(arr[i][s]==5||arr[i][s]>=6)
	    		   {
	    		   	  arr[i][s]-=5;
	    		   	  cout<<"eival";
	    		   	  credit+=final_level+1;
	    		   	  kill++;
	    		   	  break;
				   }
			}
			else if(x=='h'||x=='H')
	    	{
	    		for(int s=j;s<min(j+range,15);s++)
	    		   if(arr[i][s]==5||arr[i][s]>6)
	    		   {
	    		   	  arr[i][s]-=5;
	    		   	  cout<<"eival";
	    		   	  credit+=final_level+1;
	    		   	  kill++;
	    		   	  break;
				   }
			}
			else if(x=='t'||x=='T')
	    	{
	    		for(int s=i;s>max(0,i-range);s--)
	    		   if(arr[s][j]==5||arr[s][j]>6)
	    		   {
	    		   	  arr[s][j]-=5;
	    		   	  cout<<"eival";
	    		   	  credit+=final_level+1;
	    		   	  kill++;
	    		   	  break;
				   }
			}
			else if(x=='g'||x=='G')
	    	{
	    		for(int s=i;s<min(15,i+range);s++)
	    		   if(arr[s][j]==5||arr[s][j]>6)
	    		   {
	    		   	  arr[s][j]-=5;
	    		   	  cout<<"eival";
	    		   	  credit+=final_level+1;
	    		   	  kill++;
	    		   	  break;
				   }
			}
		}
}
void zombi_Movment()
{
		int i,j,x;
	for(int s=0;s<15;s++)
	   for(int z=0;z<15;z++)
		   	if(arr[s][z]==1||arr[s][z]==6)
		   	{
		   		i=s;
		   		j=z;
			}
	for(int g=0;g<15;g++)
	   for(int u=0;u<15;u++)
	     if(arr[g][u]==5||arr[g][u]>6)
		 {
		    if(g!=i||u!=j)
		    {
		 	if(u<j)
			{
				x=arr[g][u+1];
				arr[g][u+1]=-arr[g][u+1]-5;
			}
			else if(u>j)
			{
				x=arr[g][u-1];
				arr[g][u-1]=-arr[g][u-1]-5;
			}	
		 	else if(u==j)
		 	{
		 		if(g<i)
		 	    {
		 	      x=arr[g+1][u];
		 	      arr[g+1][u]=-arr[g+1][u]-5;
			    }
		 	    else if(g>i)
		 	    {
		 	     x=arr[g-1][u];
			     arr[g-1][u]=-arr[g-1][u]-5;
			    }
			}
			arr[g][u]-=5;
		   }
		 /* else
	       {
	    	arr[g][u]=6;
		   }*/
	    }
	for(int c=0;c<15;c++)
	   for(int d=0;d<15;d++)
	     if(arr[c][d]==-5||arr[c][d]==-8||arr[c][d]==-9||arr[c][d]==-6||arr[c][d]==-10)
	     {   
	         temp=arr[c][d];
	     	 arr[c][d]=abs(temp);
		 }	
}
void death()
{
	for(int i=0;i<15;i++)
	  for(int j=0;j<15;j++)
	    if(arr[i][j]==1||arr[i][j]==6)
	    {
        	for(int s=max(0,i-1);s<min(i+2,15);s++)
	          for(int z=max(j-1,0);z<min(j+2,15);z++)
	            if(arr[s][z]==5||arr[s][z]>6)
	              {
	     	        health--;
		          }
	    }
}
void check_bullet(char x)
{
	if(x=='f'||x=='F'||x=='g'||x=='G'||x=='h'||x=='H'||x=='t'||x=='T')
	{
		if(tir>0)
		shot(order[0]);
		else if(tir==0)
		cout<<"No charged ammo!";
		tir--;
		if(tir==-1)
		tir++;
	}
}


void upgrade(char x) {
	if (x == 'u' or x == 'U') {
		while (true) {
			system("cls");
			cout << "0 - Return to the game" << endl;
			cout << "1 - Upgrade capacity of magazine: 1 Bullet (max is 7 Bullets, now is " << maxBullet << ") , credit required : " << final_level * maxBullet << endl;
			cout << "2 - Upgrade range of shotgun : 1 times the size of the person himself (maximum is 10 times, now is " << range << "), credit required : " << final_level + range << endl;
			cout << "3 - get an additional health (maximum is 5 healths, now is " << health << "), credit required: " << (final_level + 1) * health << endl;
			char ch;
			cin >> ch;
			if (ch == '0' or ch == '1' or ch == '2' or ch == '3') {
				system("cls");
				if (ch == '0')
					return;
				
				else if (ch == '1') {
					if (maxBullet == 7) 
						cout << endl << "The selected item is maximum.";
					else if (credit < maxBullet * final_level) 
						cout << endl << "Unfortunately, your credit is not enough to get this item. Please gain " << maxBullet * final_level - credit <<" more credit by playing.";
					else {
						credit -= maxBullet * final_level; maxBullet ++;
						cout  << endl << "Upgrade done successfully." << endl << "Your magazine capacity is now " << maxBullet << " .";
					}
				}
				
				else if (ch == '2') {
					if (range == 10)
						cout << endl << "The selected item is maximum.";
					else if (credit < range + final_level)
						cout << endl << "Unfortunately, your credit is not enough to get this item. Please gain " << range + final_level - credit << " more credit by playing.";
					else {
						credit -= range + final_level; range ++;
						cout << endl << "Upgrade done successfully.Your shotgun range is now " << range << " .";
					}
				}

				else if (ch == '3') {
					if (health == 5) 
						cout << "The selected item is maximum.";
					else if (credit < (final_level + 1) * health)
						cout << "Unfortunately, your credit is not enough to get this item. Please gain " << (final_level+1) * health - credit << " more credit by playing.";
					else {
						credit -= (final_level+1) * health ; health++;
						cout << "Additional health received successfully.Your health is now " << health << " .";
					}
				}
				
			}
		}
	}
}

void reload(char x) {
	if (x == 'r' or x == 'R') {
		game_round--;
		system("cls");
		if (kheshab == 0) 
			cout << "No Ammo!";
		else if (tir == maxBullet)
			cout << "The gun is already Charged";
		else {
			tir++; kheshab--;
			cout << "Reloaded!";
		}
	}
}

void levelFinish() {
	if (arr[14][14] == 1) {
		if (vaccineCollected == final_level) {
			final_level++;
			vaccineCollected = 0;
			game_round=0;
			start();
		}
	}
}
