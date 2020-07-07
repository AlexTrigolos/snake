#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Apple.h"
#include "Snake.h"
#include <locale.h>
#include <ctime>

using namespace std;

int width = 10, height = 10;
Snake snake(height, width);////////////
Apple apple(rand() % width + 1, rand() % height + 1);////////////
bool is_game_stopped = false;//////////
bool is_won = false;
string action;
int speed = 300;
int change_speed = 5;

bool All_check(int x, int y){
	if(snake.check_snake_position(y, x) != 0){
		is_game_stopped = true;
		return 0;
	}else if(x == 0 || x == width + 1 || y == 0 || y == height + 1){
		is_game_stopped = true;
		return 0;
	}else{
		return 1;
	}
}

void move_snake(){
	if(snake.direction == 'l' && snake.snake_body[0].x - 1 == apple.y && snake.snake_body[0].y == apple.x){
		snake.snake_body.insert(snake.snake_body.begin(), Object(snake.snake_body[0].x - 1, snake.snake_body[0].y));
		apple.new_apple(width, height, snake);
		snake.size++;
		speed -= change_speed;
	}else if(snake.direction == 'r' && snake.snake_body[0].x + 1 == apple.y && snake.snake_body[0].y == apple.x){
		snake.snake_body.insert(snake.snake_body.begin(), Object(snake.snake_body[0].x + 1, snake.snake_body[0].y));
		apple.new_apple(width, height, snake);
		snake.size++;
		speed -= change_speed;
	}else if(snake.direction == 'd' && snake.snake_body[0].x == apple.y && snake.snake_body[0].y + 1 == apple.x){
		snake.snake_body.insert(snake.snake_body.begin(), Object(snake.snake_body[0].x, snake.snake_body[0].y + 1));
		apple.new_apple(width, height, snake);
		snake.size++;
		speed -= change_speed;
	}else if(snake.direction == 'u' && snake.snake_body[0].x == apple.y && snake.snake_body[0].y - 1 == apple.x){
		snake.snake_body.insert(snake.snake_body.begin(), Object(snake.snake_body[0].x, snake.snake_body[0].y - 1));
		apple.new_apple(width, height, snake);
		snake.size++;
		speed -= change_speed;
	}else{
		if(snake.direction == 'l' && All_check(snake.snake_body[0].x - 1, snake.snake_body[0].y)){
			snake.snake_body.insert(snake.snake_body.begin(), Object(snake.snake_body[0].x - 1, snake.snake_body[0].y));
		}else if(snake.direction == 'r' && All_check(snake.snake_body[0].x + 1, snake.snake_body[0].y)){
			snake.snake_body.insert(snake.snake_body.begin(), Object(snake.snake_body[0].x + 1, snake.snake_body[0].y));
		}else if(snake.direction == 'd' && All_check(snake.snake_body[0].x, snake.snake_body[0].y + 1)){
			snake.snake_body.insert(snake.snake_body.begin(), Object(snake.snake_body[0].x, snake.snake_body[0].y + 1));
		}else if(snake.direction == 'u' && All_check(snake.snake_body[0].x, snake.snake_body[0].y - 1)){
			snake.snake_body.insert(snake.snake_body.begin(), Object(snake.snake_body[0].x, snake.snake_body[0].y - 1));
		}
		snake.snake_body.pop_back();
	}
	if(snake.size == 25){
		is_won = true;
	}
}

void draw(){
	int i, j, a, b;
	for(i = 0; i < width + 2; i++){
		cout << "#";
	}
	cout << endl;
	for(i = 1; i < height + 1; i++){
		for(j = 0; j < width + 2; j++){
			b = false;
			if(j != 0 && j != width + 1){
				if((a = snake.check_snake_position(i, j)) == 0 && (b = apple.check_apple(i, j)) == false){
					cout << static_cast<char>(249);
				}else if(b == true){
					cout << static_cast<char>(253);
				}else if(a == 1){
					cout << 'O';
				}else if(a == 2){
					cout << static_cast<char>(187);
				}else if(a == 3){
					cout << static_cast<char>(205);
				}else if(a == 4){
					cout << static_cast<char>(186);
				}else if(a == 5){
					cout << static_cast<char>(188);
				}else if(a == 6){
					cout << static_cast<char>(201);
				}else if(a == 7){
					cout << static_cast<char>(200);
				}
			}else{
				cout << "#";
			}
		}
		cout << endl;
	}
	for(i = 0; i < width + 2; i++){
		cout << "#";
	}
	cout << endl;
}

void restart(){
	snake = Snake(height, width);////////////
	apple = Apple(rand() % width + 1, rand() % height + 1);////////////
	is_game_stopped = false;//////////
	is_won = false;
	speed = 300;
}

bool ask();

void main_func(){
	srand(time(0));
	int k1, k2, k3 = 0;
    while(k3 < 2000000){
		k3++;
		system("cls");
		if(is_game_stopped == false && is_won == false){
			draw();
			Sleep(speed);
			if(_kbhit()){
				k1 = _getch();
				if (k1 == 0xE0 || k1 == 0x00){
					k2 = _getch();
					switch(k2){
					case 0x4B:
						if(snake.direction != 'r'){
							snake.direction = 'l';
						}
						break;
					case 0x50:
						if(snake.direction != 'u'){
							snake.direction = 'd';
						}
						break;
					case 0x4D:
						if(snake.direction != 'l'){
							snake.direction = 'r';
						}
						break;
					case 0x48:
						if(snake.direction != 'd'){
							snake.direction = 'u';
						}
						break;
					}
				}else if(k1 == 27){
					break;
				}
			}
			move_snake();
			continue;
		}else if(is_game_stopped == true){
			cout << "LOOOOSEEEEEER" << endl;
		}else if(is_won == true){
			cout << "WOOOOOOOOON" << endl;
		}
		if(ask() == false){
			k3 = 2000000;
		}else{
			k3 = 0;
		}
    }
}

bool ask(){
	cout << "One more time? (y/n)" << endl;
	cin >> action;
	if(action != "y" && action != "n"){
		cout << "I can't understand." << endl;
		ask();
	}
	if(action == "y"){
		restart();
		return true;
	}else{
		system("cls");
		cout << "See you later.\n";
		return false;
	}
}

void menu(){
	string a;
	cout << "1. EASY" << endl;
	cout << "2. MEDIUM" << endl;
	cout << "3. HARD" << endl;
	cin >> a;
	while(a.size() > 1 || a[0] != 49 && a[0] != 50 && a[0] != 51){
		cout << "ERROR" << endl; 
		cin >> a;
	}
	if(a[0] == 49){
		change_speed = 7;
	}else if(a[0] == 50){
		change_speed = 11;
	}else if(a[0] == 51){
		change_speed = 16;
	}
}

int main(){
	menu();
	cout << "READY" << endl;
	Sleep(1000);
	cout << "GO" << endl;
	Sleep(500);
	main_func();
	return 0;
}