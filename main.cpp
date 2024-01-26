#include <iostream>
#include <cmath>
#include <windows.h>
#include <time.h>
#include <cstring>
#include <fstream>
using namespace std;
int saveVariable=0; // x=1 -> save , x=2 -> load
int difficulty=2;
int temp=0;
int maxBullet = 3;
int kill_counter=0;
int Zombi_print=0;
int range=5;
int kill=0;
int tir=3;
int kheshab=0;
int health=3 ;
int credit=0;
int game_round=0;
int level_finish = 15;
int final_level=1;
int vaccineCollected = 0;
int zombieMoveCounter = 0;
char order[1];
int arr[15][15] = {0};
int back_up[15][15]={0};
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
void ingame_menu();
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
void Accident();
void save();
void exit();
void startingMenu();


int main() {
	srand(time(0));
	startingMenu();

	while(true) {
		cin >> order[0];
		game_round++;
		player_function(order[0]);
		check_bullet(order[0]);
		reload(order[0]);
		upgrade(order[0]);
		levelFinish();
		zombi_Movment();
		death();
		Accident();
		exit();
		ingame_menu();
        system("cls");
		print_play_ground();
	}
}










void main_menu() {
	cout << "0 - Load Game\t1 - New Game\t2 - Settings\t3 - Credits\t4 - Help\t5 - Exit\n";
	cin >> order[0];
	system("cls");
	switch (order[0]) {
		case '0' :
			saveVariable=2;
			save();
			if(saveVariable == 3) {
				system("cls");
				main_menu();
				return;
			}
			print_play_ground();
			break;
		case '1': // NEW GAME
			final_level = 1;
			credit = 0 ;
			game_round=0;
			kill = 0;
			vaccineCollected = 0;
			tir=3;
			kheshab=0;
			health=3 ;
			maxBullet = 3;
			range=5;
			start();
			system("cls");
			break;

		case '2': // SETTINGS
			cout << "Final level is: " << level_finish << endl <<"Difficulty of game is: " << difficulty <<endl;
			cout << "1 - select difficulty\n2 - Sound settings\n3 - Final level settings\n4 - Back to menu\n"; 
			cin >> order[0];
			system("cls");
			if(order[0]=='1') {
				while(true) {
					cout << "current difficulty: " << difficulty << "\n0 - exit\n1 - easy\n2 - medium\n3 - hard\n";
					int x;
					cin >> x;
					system("cls");
					if (x==1 or x==2 or x==3)
						difficulty = x;
					else if(x==0) {
						main_menu();
						break;
					}
				}
			}
			if (order[0] == '2'){
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
		}
		else if (order[0] == '3'){
			cout << "Choose final level :\n1 - 5 Levels (easy mode)\n2 - 10 Levels (medium mode)\n3 - 15 Levels (hard mode)\n4 - 20 Levels (pro mode)\n";
			cin >> order[0];
			system("cls");
			if (order[0] == '1'){
			level_finish = 5;
			cout << "Final level changed to 5\n";
			Sleep(1500);
			system("cls");
			main_menu();
			}
			else if (order[0] == '2'){
			level_finish = 10;
			cout << "Final level changed to 10\n";
			Sleep(1500);
			system("cls");
			main_menu();
			}
			else if (order[0] == '3'){
			level_finish = 15;
			cout << "Final level changed to 15\n";
			Sleep(1500);
			system("cls");
			main_menu();
			}
			else if (order[0] == '4'){
			level_finish = 20;
			cout << "Final level changed to 20\n";
			Sleep(1500);
			system("cls");
			main_menu();
			}
			
		}
		else if (order[0] == '4')
		main_menu();

			break;

		case '3': // CREDITS
			yellow();
			cout <<"Amirreza Samari kalaj\nMohammadhossein Paakdaman\nMohammadmahdi Sharifi pour\n";
			reset_color();
			Sleep(2000);
			system("cls");
			return main_menu();
			break;

		case '4': // HELP
			yellow();
			cout << "Welcome to COVID 2030 game\n\n";
			cyan();
			cout << "Objective:\nYour job is to collect all of Vaccines(V) and reach to Destination(D) in each level to can save the planet from Zombies\nIn this path Zombies(Z) can damage you so you can use your shotgun and kill them before!\n\n";
			cout << "Controls:\n- Move Up: W\n- Move Down: S\n- Move Left: A\n- Move Right: D\n- Shooting upwards: T\n- Shooting down: G\n- Shooting to the right: H\n- Shooting to the left: F\n\n";
			cout << "Scoring:\nYou can collect Credits by killing Zombies or going to next level and use those credits to update yourself.\n\n";  
			cout << "Levels:\nYou can collect all of the Vaccines and Save the planet in 20 levels.\n\n";
			cout << "Tips:\nYou can reload your ammo by pressing R.\nYour gun have a range that is by default 5 but you can update it.\nPress U to inter to update menu.\nPress E to exit game.\nPress M to inter to menu.\n\n"; 
			yellow();
			cout <<"Have fun playing COVID 2030!\nRemember we counted on you to save the planet.\n\n";
			reset_color();
			getchar();
			return main_menu();
			break;

		case '5': // EXIT
			cout << "Are you sure you want to exit the game? (y : YES | n : NO)\n";
			cin >> order[0];
			system("cls");
			if (order[0] == 'y') {
				cout << "Good Bye!";
				Sleep(2500);
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

void ingame_menu() {
	if (order[0] == 'm' or order[0]=='M') {
		system("cls");
		cout << "0 - Return to game\t1 - New Game\t2 - Settings\t3 - Exit\n";
		cin >> order[0];
		system("cls");
		if ( order[0] != '0' && order[0]!= '1' && order[0]!= '2' && order[0]!='3') {
			while (true) {
				cout << "Please just enter the numbers in the menu:\n";
				cin >> order[0];
				system("cls");
				if (order[0] == '0' || order[0]== '1' || order[0]== '2' || order[0]=='3' )
					break;
			}
		}
		switch (order[0]) {
			case '0': //return
				game_round--;
				system("cls");
				break;

			case '1': // NEW GAME
				final_level = 1;
				credit = 0 ;
				game_round = 0;
				kill = 0;
				vaccineCollected = 0;
				tir=3;
				kheshab=0;
				health=3 ;
				maxBullet = 3;
				range=5;
				start();
				system("cls");
				break;

			case '2':

		cout << "Final level is: " << level_finish << endl <<"Difficulty of game is: " << difficulty <<endl;
				cout << "1 - Sound settings\n2 - Back to menu\n"; 
				cin >> order[0];
				system("cls");
				if (order[0] == '1'){
				if (is_sound_on == false) {
					cout << "Sound is mute!\nDo you want to unmute the sound? (y : YES | n : NO)\n";
					cin >> order[0];
					system("cls");
					if (order[0] == 'n') {
						order[0]='m';
						return ingame_menu();
					} else if (order[0] == 'y') {
						is_sound_on = true;
						order[0]='m';
						return ingame_menu();
					} else {
						order[0]='m';
						return ingame_menu();
					}
				} else if (is_sound_on == true) {
					cout << "Sound is not mute!!\nDo you want to mute the sound? (y : YES | n : NO)\n";
					cin >> order[0];
					system("cls");
					if (order[0] == 'n') {
						order[0]='m';
						return ingame_menu();
					} else if (order[0] == 'y') {
						is_sound_on = false;
						order[0]='m';
						return ingame_menu();
					} else {
						order[0]='m';
						return ingame_menu();
					}
				}
			}
			else if (order[0] == '2'){
				order[0]='m';
		return ingame_menu();
		}
			else {
				order[0]='m';
		return ingame_menu();

}
				break;

			case '3':
			while(true) {
				cout << "Do you want to save your game? (y : YES | n : NO)" << endl;
				cin >> order[0];
				system("cls");
				if (order[0] == 'y' or order[0]=='Y') {
					saveVariable=1;
					save();
					cout << "Saved succefully!";
					Sleep(1000);
					system("cls");
					main_menu();
					break;
				}
				else if (order[0] == 'n' or order[0]=='N'){
				cout << "Are you sure you want to exit the current game without saving? (y : YES | n : NO)\n";
				cin >> order[0];
				system("cls");
				if (order[0] == 'y' or order[0]=='Y') {
					main_menu();
					break;
				}
				else if (order[0] == 'n' or order[0]=='N') {
					order[0]='m';
					ingame_menu();
					break;
				}
				system("cls"); 
					break;
				}
				else {
					system("cls");
					cout << "Invalid input!";
					Sleep(1000);
					
				}
				system("cls");
			}	
	}
}
}

void start() {
	for (int i = 0; i<=14; i++)
		for (int j=0; j<=14; j++)
		{
			arr[i][j] = 0;
			back_up[i][j] = 0;
		}
	arr[0][0] = 1;
	arr[14][14]=2; // player num = 1 or 6, destination num = 2
	for (int index = 0; index<final_level; index++) { //select zambie location
		int i = rand()%15, j = rand()%15;
		if(i>=0 && i<3 && j>=0 && j<3)
			index--;
		else if (arr[i][j] == 0)
			arr[i][j] = 5; //zambie num = 5
		else
			index--;
	}
	for (int index=0 ; index<final_level ; index++) { //select vaccine location
		int i = rand()%15, j = rand()%15;
		if (arr[i][j] == 0)
		{
			arr[i][j] = 4; //vaccine num = 4
			back_up[i][j]=4;
		}
		else
			index--;
	}
	for (int index = 0 ; index<(final_level+1)/2; index++) {
		int i = rand()%15, j = rand()%15;
		if (arr[i][j] == 0)
		{
			arr[i][j] = 3; //ammo num = 3
			back_up[i][j]=3;
		}
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
			if (arr[i-1][j-2]==2) {
				cyan();
				cout << "D";
			}
			if (arr[i-1][j-2]==5||arr[i-1][j-2]==5) {
				magenta();
				cout << "Z";
			}
			if (arr[i-1][j-2]==4) {
				yellow();
				cout << "V";
			}
			if (arr[i-1][j-2]==3) {
				blue_bold();
				cout << "A";
			}
			reset_color();
		}

		cout << "|" << endl;
	}
	cout << "-----------------" << endl;
}
void player_function(char x) {
	int i,j;
	for(int s=0; s<15; s++)
		for(int z=0; z<15; z++)
			if(arr[s][z]==1||arr[s][z]==6) {
				i=s;
				j=z;
			}
	if(x=='w'||x=='W') {
		if(i-1>-1) {
			if(arr[i-1][j]==4) {
				vaccineCollected++;
				credit += final_level + 1;
				arr[i-1][j]=1;
				back_up[i-1][j]=0;
				system("cls");
				cout << "Vaccine collected!"<<endl<<final_level + 1<<" credit gained!";
		    	Sleep(1000);
			} else if(arr[i-1][j]==3) {
				kheshab++;
				arr[i-1][j]=1;
				system("cls");
				cout << "Ammo collected!";
		    	Sleep(1000);
				back_up[i-1][j]=0;
			} else if(arr[i-1][j]==5) {
				arr[i-1][j]=6;
			} else if(arr[i-1][j]==0) {
				arr[i-1][j]=1;
			}
			arr[i][j]--;
		}
	} else if(x=='s'||x=='S') {
		if(i+1<15) {
			if(arr[i+1][j]==4) {
				vaccineCollected++;
				credit += final_level + 1;
				arr[i+1][j]=1;
				back_up[i+1][j]=0;
				system("cls");
				cout << "Vaccine collected!"<<endl<<final_level + 1<<" credit gained!";
		    	Sleep(1000);
			} else if(arr[i+1][j]==3) {
				kheshab+=1;
				arr[i+1][j]=1;
				back_up[i+1][j]=0;
				system("cls");
				cout << "Ammo collected!";
		    	Sleep(1000);
			} else if(arr[i+1][j]==5) {
				arr[i+1][j]=6;
			} else if(arr[i+1][j]==0) {
				arr[i+1][j]=1;
			} else if (arr[i+1][j]==2) {
				arr[i+1][j]=1;
			}
			arr[i][j]--;
		}
	} else if(x=='d'||x=='D') {
		if(j+1<15) {
			if(arr[i][j+1]==4) {
				vaccineCollected++;
				credit += final_level + 1;
				arr[i][j+1]=1;
				back_up[i][j+1]=0;
				system("cls");
				cout << "Vaccine collected!"<<endl<<final_level + 1<<" credit gained!";
		    	Sleep(1000);
			} else if(arr[i][j+1]==3) {
				kheshab+=1;
				arr[i][j+1]=1;
				back_up[i][j+1]=0;
				system("cls");
				cout << "Ammo collected!";
		    	Sleep(1000);
			} else if(arr[i][j+1]==5) {
				arr[i][j+1]=6;
			} else if(arr[i][j+1]==0) {
				arr[i][j+1]=1;
			} else if(arr[i][j+1]==2) {
				arr[i][j+1]=1;
			}
			arr[i][j]--;
		}
	} else if(x=='a'||x=='A') {
		if(j-1>-1) {
			if(arr[i][j-1]==4) {
				vaccineCollected++;
				credit += final_level + 1;
				arr[i][j-1]=1;
				back_up[i][j-1]=0;
				system("cls");
				cout << "Vaccine collected!"<<endl<<final_level + 1<<" credit gained!";
		    	Sleep(1000);
			} else if(arr[i][j-1]==3) {
				kheshab+=1;
				arr[i][j-1]=1;
				back_up[i][j-1]=0;
				system("cls");
				cout << "Ammo collected!";
		    	Sleep(1000);
			} else if(arr[i][j-1]==5) {
				arr[i][j-1]=6;
			} else if(arr[i][j-1]==0) {
				arr[i][j-1]=1;
			}
			arr[i][j]--;
		}

	}
	if(arr[14][14]==0)
		arr[14][14]=2;
}
void shot(char x) {
	kill_counter=0;
	for(int i=0; i<15; i++)
		for(int j=0; j<15; j++)
			if(arr[i][j]==1||arr[i][j]==6) {
				if(x=='f'||x=='F') {
					for(int s=j; s>max(j-range,0); s--)
						if(arr[i][s]==5) {
							kill_counter++;
							arr[i][s]-=5;
							credit+=final_level+1;
							kill++;
							break;
						}
				} else if(x=='h'||x=='H') {
					for(int s=j; s<min(j+range,15); s++)
						if(arr[i][s]==5) {
							kill_counter++;
							arr[i][s]-=5;
							credit+=final_level+1;
							kill++;
							break;
						}
				} else if(x=='t'||x=='T') {
					for(int s=i; s>max(0,i-range); s--)
						if(arr[s][j]==5) {
							kill_counter++;
							arr[s][j]-=5;
							credit+=final_level+1;
							kill++;
							break;
						}
				} else if(x=='g'||x=='G') {
					for(int s=i; s<min(15,i+range); s++)
						if(arr[s][j]==5) {
							kill_counter++;
							arr[s][j]-=5;
							credit+=final_level+1;
							kill++;
							break;
						}
				}
			}
			if(kill_counter==0)
			{
				system("cls");
				cout << "Zombie is not in range! come closer";
		    	Sleep(1000);
			}
			else
			{
			  system("cls");
			  cyan();	
			  Zombi_print=kill%14-1;
			  if(Zombi_print==0)
			     cout<<"First Blood";
			  else if(Zombi_print==1)
			     cout<<"Double Kill";
			  else if(Zombi_print==2&&final_level%2==1)
			     cout<<"Hattrick";
			  else if(Zombi_print==2&&final_level%2==0)
			     cout<<"Triple Kill";
			  else if(Zombi_print==3)
			     cout<<"Team killer";
			  else if(Zombi_print==4)
			     cout<<"Headshot";
			  else if(Zombi_print==5)
			     cout<<"Rampage";
			  else if(Zombi_print==6)
			     cout<<"Killing Spree";
			  else if(Zombi_print==7)
			     cout<<"Unstoppable";
			  else if(Zombi_print==8)
			     cout<<"Monster Kill";
			  else if(Zombi_print==9)
			     cout<<"Muiti Kill";
			  else if(Zombi_print==10)
			     cout<<"Ludicrous Kill";
			  else if(Zombi_print==11)
			     cout<<"Uitra Kill";
			  else if(Zombi_print==12)
			     cout<<"Dominating";
			  else if(Zombi_print==13)
			     cout<<"Godlike";
			      reset_color();
			     cout <<endl <<final_level + 1  <<" credit gained!";
			  Sleep(1000);
			 
			}
}
void zombi_Movment()
{
	zombieMoveCounter++;
	if(difficulty==3 or (zombieMoveCounter%2==0 && difficulty==2) or (zombieMoveCounter%3==0 && difficulty==1))
  {
	int i,j,x;
	for(int s=0;s<15;s++)
	   for(int z=0;z<15;z++)
		   	if(arr[s][z]==1)
		   	{
		   		i=s;
		   		j=z;
			}
	for(int g=0;g<15;g++)
	   for(int u=0;u<15;u++)
	     if(arr[g][u]==5)
		 {
		 	arr[g][u]-=5;
		 	if(u<j)
		 	{
		 	   if(arr[g][u+1]==1||arr[g][u+1]==6)
		 	   {
		 	   	arr[g][u+1]=6;
			   }
			   else
		 	   arr[g][u+1]=30;
			}
		 	else if(u>j)
		 	{
		 		if(arr[g][u-1]==1||arr[g][u-1]==6)
		 	   {
		 	   	arr[g][u-1]=6;
			   }
			   else
			   arr[g][u-1]=30;
			}
		 	else if(u==j)
		 	{
		 		if(g<i)
				 {
				 	 if(arr[g+1][u]==1||arr[g+1][u]==6)
		 	         {
		 	   	       arr[g+1][u]=6;
			         }
			         else
				 	   arr[g+1][u]=30;
				 }
				 else if(g>i)
				 {
				 	 if(arr[g-1][u]==1||arr[g-1][u]==6)
		 	        {
		 	   	      arr[g-1][u]=6;
			        }
			        else
				 	  arr[g-1][u]=30;
			     }	
			}
		 }	
	for(int c=0;c<15;c++)
	   for(int d=0;d<15;d++)
	     if(arr[c][d]==30)
		    arr[c][d]=5;
  }
}
void death() {
	for(int i=0; i<15; i++)
		for(int j=0; j<15; j++)
			if(arr[i][j]==1||arr[i][j]==6) {
				for(int s=max(0,i-1); s<min(i+2,15); s++)
					for(int z=max(j-1,0); z<min(j+2,15); z++)
						if(arr[s][z]==5||arr[s][z]==6) {
							health--;
							if (health > 0) {
								system("cls");
								red();
								cout << "The zombie is eating you! You lost one of your healths!";
								reset_color();
								Sleep(2500);
							} else if ( health <= 0) {
								system("cls");
								red();
								cout << "You Died!\n";
								reset_color();
								cout << "You Lose! Would you like to try again? (y : Yes | n : No)\n";
								cin >> order[0];
								if ( order[0] == 'n') {
									system("cls");
									main_menu();
								} else if (order[0] == 'y') {
									system("cls");
									cout << "The game will restart in 5 seconds...";
									Sleep(5000);
									final_level = 1;
									credit = 0 ;
									game_round = 0;
									kill = 0;
									vaccineCollected = 0;
									tir=3;
									kheshab=0;
									health=3 ;
									maxBullet = 3;
									range=5;
									start();

								}

							}

						}
			}
}
void check_bullet(char x) {
	if(x=='f'||x=='F'||x=='g'||x=='G'||x=='h'||x=='H'||x=='t'||x=='T') {
		if(tir>0){
			shot(order[0]);
			tir--;
		}
		else if(tir==0){
			system("cls");
			cout<<"No charged ammo!";
			Sleep(1500);
		}
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
						cout  << "The selected item is maximum.";
					else if (credit < maxBullet * final_level)
						cout << "Unfortunately, your credit is not enough to get this item. Please gain " << maxBullet * final_level - credit <<" more credit by playing.";
					else {
						credit -= maxBullet * final_level;
						maxBullet ++;
						cout << "Upgrade done successfully." << endl << "Your magazine capacity is now " << maxBullet << " .";
					}
				}

				else if (ch == '2') {
					if (range == 10)
						cout  << "The selected item is maximum.";
					else if (credit < range + final_level)
						cout << "Unfortunately, your credit is not enough to get this item. Please gain " << range + final_level - credit << " more credit by playing.";
					else {
						credit -= range + final_level;
						range ++;
						cout << "Upgrade done successfully.Your shotgun range is now " << range << " .";
					}
				}

				else if (ch == '3') {
					if (health == 5)
						cout << "The selected item is maximum.";
					else if (credit < (final_level + 1) * health)
						cout << "Unfortunately, your credit is not enough to get this item. Please gain " << (final_level+1) * health - credit << " more credit by playing.";
					else {
						credit -= (final_level+1) * health ;
						health++;
						cout << "Additional health received successfully.Your health is now " << health << " .";
					}
				}
				Sleep(3500);
				

			}
		}
	}
}

void reload(char x) {
	if (x == 'r' or x == 'R') {
		game_round--;
		system("cls");
		if (kheshab == 0){
			cout << "No Ammo!";
			Sleep(1000);
		}
		else if (tir == maxBullet){
			cout << "The gun is already Charged";
			Sleep(1000);
		}
		else {
			tir = maxBullet;
			kheshab--;
			cout << "Reloaded!";
			Sleep(1000);
		}
	}
}

void levelFinish() {
	if (arr[14][14] == 1) {
		kill=0;
		game_round=0;
		if (vaccineCollected == final_level && final_level == level_finish) {
			system("cls");
			green();
			cout << "Congratulations! You have successfully collected all the vaccines!\nNow it is time to return to the Earth\nGood Bye!\n";
			Sleep(3000);
			system("cls");
			reset_color();
			main_menu();
		} else if (vaccineCollected == final_level) {
			system("cls");
			final_level++;
			vaccineCollected = 0;
			game_round=0;
			green();
			cout << "You Won! You have reached level " << final_level;
			Sleep(2500);
			reset_color();
			start();
		} else {
			system("cls");
			red();
			cout << "First get all the vaccines.";
			Sleep(2500);
			reset_color();

		}
	}
}
void Accident()
{
	for(int i=0;i<15;i++)
	   for(int j=0;j<15;j++)
	   if(back_up[i][j]==3&&arr[i][j]==0)
	   {
	   	arr[i][j]=back_up[i][j];
	   }
	   else if(back_up[i][j]==4&&arr[i][j]==0)
	   {
	   	arr[i][j]=back_up[i][j];
	   }
}

void save() {
	if (saveVariable == 1) { //save
		ofstream s("save.txt", ios::out);
		s << final_level << endl << kill_counter << endl << health << endl << tir << endl << kheshab << endl << credit << endl;
		s << range << endl <<  maxBullet << endl << vaccineCollected << endl << difficulty << endl;
		for (int i=0 ; i<15 ; i++)
			for (int j=0 ; j<15 ; j++) 
				s << arr[i][j] << endl << back_up[i][j] << endl;
		s.close();
	}
	else if (saveVariable == 2) { //load
		ifstream l("save.txt" , ios::in);
		if (!l) {
			system("cls");
			cout << "failed to load!";
			saveVariable = 3;
			Sleep(1500);
			return;
		}
		l >> final_level >> kill_counter >> health >> tir >> kheshab >> credit >> range >> maxBullet >> vaccineCollected >> difficulty;
		for (int i=0 ; i<15 ; i++) 
			for (int j=0 ; j<15 ; j++)
				l >> arr[i][j] >> back_up[i][j];
		l.close();
	}
}

void exit() {
	if (order[0]=='e' or order[0]=='E') {
		system("cls");
		while(true) {
			cout << "Do you want to save your game? (y : YES | n : NO)" << endl;
			cin >> order[0];
			system("cls");
			if (order[0] == 'y' or order[0]=='Y') {
				saveVariable=1;
				save();
				cout << "Saved succefully!";
					Sleep(1000);
					system("cls");
				main_menu();
				break;
			}
			else if (order[0] == 'n' or order[0]=='N') {
				cout << "Are you sure you want to exit the current game without saving? (y : YES | n : NO)\n";
				cin >> order[0];
				system("cls");
				if (order[0] == 'y' or order[0]=='Y') {
					main_menu();
					break;
				}
				else if (order[0] == 'n' or order[0]=='N') {
					
					return;
				}
			}
			else {
				cout << "Invalid input!";
				Sleep(1000);
				system("cls");
			}
		}
	}
}

void startingMenu() {
	red();
	cout << " ######   #######  ##     ## #### ########      #######    #####     #######    #####\n";
	cout << "##    ## ##     ## ##     ##  ##  ##     ##    ##     ##  ##    ##  ##     ##  ##    ##\n";
	cout << "##       ##     ## ##     ##  ##  ##     ##           ## ##      ##        ## ##      ##\n";
	cout << "##       ##     ## ##     ##  ##  ##     ##     #######  ##      ##  #######  ##      ##\n";
	cout << "##       ##     ##  ##    ##  ##  ##     ##    ##        ##      ##        ## ##      ##\n";
	cout << "##    ## ##     ##   ##  ##   ##  ##     ##    ##         ##    ##  ##     ##  ##    ##\n";
	cout << " ######   #######     ###    #### ########     ########    #####     #######    #####\n";
	reset_color();

	cout << "Welcome to Covid 2030 game!\n";

	main_menu();
	system("cls");
	print_play_ground();
}