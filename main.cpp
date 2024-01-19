#include <iostream>
#include <cmath>
#include <windows.h>
#include <time.h>
#include <cstring>
using namespace std;
int kill=0;
int tir=3;
int kheshab=0;
int health=3 ;
int vaccine=0;
int credit=0;
int game_round=0;
int final_level=4;
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

	/*while(true) {
		cin >> order;
		zombieMoveCounter++;
		shot(order[0]);
		player_function(order[0]);
		if (zombieMoveCounter % 2 ==0)
			zombi_movment();
		death();
	}*/

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
			//sleep(2);
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
	arr[0][0] = 1; arr[14][14]=2; // player num = 1, destination num = 2
	for (int index = 0; index<final_level; index++) { //select zambie location
		int i = rand()%12+3, j = rand()%12+3;
		cout << i << j;
		if (arr[i][j] == 0)
			arr[i][j] = 3; //zambie num = 3
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
			arr[i][j] = 5; //ammo num = 5
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
	cout << "Level: " << final_level << "\tVaccine: " << vaccine << "\tCredit: " << credit << "\tRound: " << game_round << endl;
	print_health_status(health);
	print_ammo_status(tir, kheshab);
	cout << "Kill: " << kill << endl;

	cout << "-----------------" << endl;
	for (int i = 1; i <= 15; i++) {
		cout << "|";
		for (int j = 2; j <= 16; j++) {
			if (arr[i-1][j-2]==0)
				cout << " ";
			if (arr[i-1][j-2]==1) {
				green();
				cout << "P";
			}
			if (arr[i-1][j-2]==2){
				cyan();
				cout << "D";
			}
			if (arr[i-1][j-2]==3){
				magenta();
				cout << "z";
			}	
			if (arr[i-1][j-2]==4) {
				yellow();
				cout << "V";
			}
			if (arr[i-1][j-2]==5){
				blue_bold();
				cout << "A";
			}
			reset_color();
		}

		cout << "|" << endl;
	}
	cout << "-----------------" << endl;
}