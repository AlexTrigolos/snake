#pragma once
#include <iostream>
#include "Object.h"
#include "Snake.h"

using namespace std;

class Apple{
	public:
	int x, y;
	Apple(int h, int w){
		x = w;
		y = h;
	}
	
	void new_apple(int w, int h, Snake snake){
		while(snake.check_snake_position(x, y) != 0){
			x = rand() % w + 1, y = rand() % h + 1;
		}
	}
	
	bool check_apple(int a, int b){
		if(a == x && b == y){
			return true;
		}else{
			return false;
		}
	}
};