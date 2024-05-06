#pragma once
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <iostream>
#include <ncurses.h>
//#include "/public/colors.h"
//#include "/public/read.h"

using namespace std;
 //#include "/public/colors.h"
  //#include "/public/read.h"


class Map{
vector<vector<char>> map;
default_random_engine gen;
public:
//getter and setters
char getcord (int p,int h){
	return map.at(h).at(p);
}
	void setcord (int h, int p, char f)
{	if(f == 'M' or f == '#' or f == '~' or f == '.' or f == '$')  {
	map.at(p).at(h) = f;
	return;
	}	else 
	return;
}




static const char HERO  = 'H';
static const char MONSTER = 'M';
static const char WALL = '#';
static const char WATER = '~';
static const char OPEN = '.';
static const char TREASURE = '$';
static const char TREE = 'T';
static const char PORTAL = '@';
static const size_t SIZE = 100;
static const size_t DISPLAY = 45;
void init_map() {
	uniform_int_distribution<int> d100(1,100);
map.clear();
map.resize(SIZE);
for(auto &v : map) v.resize(SIZE,'.');
for(size_t i= 0;i<SIZE;i++){
	  for(size_t j= 0;j<SIZE;j++){
	if(i == 0 or j ==0 or i == SIZE-1 or j == SIZE-1)
		map.at(i).at(j) = WALL;
	else if(i == SIZE/2 and j== SIZE/2)
		map.at(i).at(j) = HERO;
	else{
		if(d100(gen) <=5) {
		map.at(i).at(j) = MONSTER;
	}	else if(d100(gen) <=3) {
          map.at(i).at(j) = TREASURE;
	}	else  if(d100(gen) <=10) {
          map.at(i).at(j) =WALL ;
	}   else  if(d100(gen) <=10) {
            map.at(i).at(j) =TREE ;
      } 	else  if(d100(gen) <=3) {
          map.at(i).at(j) = WATER;
	}	else  if(d100(gen) <=40) {
        if ( map.at(i-1).at(j) == WATER or map.at(i+1).at(j) == WATER or map.at(i).at(j-1) == WATER or map.at(i).at(j+1) == WATER )
					map.at(i).at(j) = WATER;
				}
			}
		}
	}
}

void draw(int x, int y, int world) {
		if(world>2)world=2;
int start_x = x-DISPLAY/2;
  int end_x = x+DISPLAY/2;
  int start_y = y-DISPLAY/2;
  int end_y = y+DISPLAY/2;

if(start_x<0){
	end_x = end_x - start_x;
	start_x=0;
}if(end_x>SIZE-1){
	start_x = start_x - (end_x - (SIZE-1));
	end_x = SIZE-1;
}if(start_y<0){
	end_y=end_y - start_y;
	start_y =0;
}
if(end_y > SIZE-1) {
	start_y = start_y - (end_y - (SIZE-1));
	end_y = SIZE-1;
}

for(size_t i= start_y;i<=end_y;i++) {
	for(size_t j= start_x;j<=end_x;j++) {
	if(i==y && j == x){
		attron(A_UNDERLINE | A_BOLD);
		mvaddch(i-start_y,j-start_x,'H');
		attroff(A_UNDERLINE | A_BOLD);
	} else {
		int color = 1;
		 
		if(map.at(i).at(j) == WALL){
		color = 5+(world*10);
				}	else   if(map.at(i).at(j) == WATER){
          color = 4+(world*10);
				}	else  if(map.at(i).at(j) == HERO){
          color = 3+(world*10);
				}	else    if(map.at(i).at(j) == TREASURE){
          color = 2+(world*10);
				}	else   if(map.at(i).at(j) == MONSTER){
   	     color = 1+(world*10);

				}	else   if(map.at(i).at(j) == TREE){
          color = 6;
				}	else	if(map.at(i).at(j) == OPEN)
            color = 7+(world*10);
		  else    if(map.at(i).at(j) == PORTAL)
          color = 9;

			
		
					attron(COLOR_PAIR(color));
					mvaddch(i-start_y,j-start_x,map.at(i).at(j));
					attroff(COLOR_PAIR(color));
		}
}
}
}
Map(){
init_map();
}


};


















