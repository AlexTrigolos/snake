#pragma once
#include <iostream>
#include <vector>
#include "Object.h"

using namespace std;

class Snake{
	public:
	int size = 3;
	vector<Object> snake_body;
	char direction = 'l';
	Snake(int h, int w){
		snake_body.push_back(Object(w / 2, h / 2));
		snake_body.push_back(Object(w / 2 + 1, h / 2));
		snake_body.push_back(Object(w / 2 + 2, h / 2));
	}
	
	int check_snake_position(int a, int b){
		for(int i = 0; i < snake_body.size(); i++){
			if(snake_body[i].x == b && snake_body[i].y == a){
				if(i == 0){
					return 1;
				}else if(i >= size){
					return 0;
				}else if(snake_body[i - 1].x == snake_body[i + 1].x){
					return 4;
				}else if(snake_body[i - 1].y == snake_body[i + 1].y){
					return 3;
				}else if((snake_body[i - 1].y == snake_body[i + 1].y + 1 && snake_body[i - 1].x + 1 == snake_body[i + 1].x && snake_body[i + 1].x == snake_body[i].x) || (snake_body[i - 1].y == snake_body[i + 1].y - 1 && snake_body[i - 1].x - 1 == snake_body[i + 1].x && snake_body[i - 1].x == snake_body[i].x)){
					return 5;//нижнправ
				}else if((snake_body[i - 1].y == snake_body[i + 1].y - 1 && snake_body[i - 1].x - 1 == snake_body[i + 1].x && snake_body[i - 1].y == snake_body[i].y) || (snake_body[i - 1].y == snake_body[i + 1].y + 1 && snake_body[i - 1].x + 1 == snake_body[i + 1].x && snake_body[i + 1].y == snake_body[i].y)){
					return 6;//верхлев
				}else if((snake_body[i - 1].y == snake_body[i + 1].y - 1 && snake_body[i - 1].x + 1 == snake_body[i + 1].x && snake_body[i + 1].y == snake_body[i].y) || (snake_body[i - 1].y == snake_body[i + 1].y + 1 && snake_body[i - 1].x - 1 == snake_body[i + 1].x && snake_body[i - 1].y == snake_body[i].y)){
					return 7;//нижнлев
				}else if((snake_body[i - 1].y == snake_body[i + 1].y - 1 && snake_body[i - 1].x + 1 == snake_body[i + 1].x && snake_body[i - 1].y == snake_body[i].y) || (snake_body[i - 1].y == snake_body[i + 1].y + 1 && snake_body[i - 1].x - 1 == snake_body[i + 1].x && snake_body[i + 1].y == snake_body[i].y)){
					return 2;//верхправ
				}
			}
		}
		return 0;
	}
};