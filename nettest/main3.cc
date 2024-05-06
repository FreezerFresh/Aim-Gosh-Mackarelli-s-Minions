#include "map.h"
#include <unistd.h>
#include <CircSLelement.h>
#include <iostream>
//#include "classes.h"
#include "Turns.cc"
#include "/public/read.h"
using namespace std;

const int MAX_FPS = 60;
const unsigned int TIMEOUT = 10;
const int UP = 65;
const int DOWN = 66;
const int RIGHT = 67;
const int LEFT =68;

void turn_on_ncurses() {
	initscr();
	start_color();
init_pair(1,COLOR_WHITE,COLOR_BLACK);
 init_pair(2,COLOR_CYAN,COLOR_BLACK);
 init_pair(3,COLOR_GREEN,COLOR_BLACK);
 init_pair(4,COLOR_YELLOW,COLOR_BLACK);
 init_pair(5,COLOR_RED,COLOR_BLACK);
 init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
 init_pair(7,COLOR_GREEN,COLOR_BLACK);
 init_pair(9,COLOR_MAGENTA,COLOR_CYAN);

  init_pair(11,COLOR_WHITE,COLOR_BLACK);
   init_pair(12,COLOR_CYAN,COLOR_BLACK);
   init_pair(13,COLOR_GREEN,COLOR_BLACK);
   init_pair(14,COLOR_YELLOW,COLOR_BLACK);
   init_pair(15,COLOR_RED,COLOR_BLACK);
   init_pair(16,COLOR_MAGENTA,COLOR_BLACK);
   init_pair(17,COLOR_GREEN,COLOR_BLACK);


clear();
noecho();
cbreak();
timeout(TIMEOUT);
} 
void turn_off_ncurses() {
	clear();
	endwin();
	if (system("clear")){}
}
/*
void combat() {     
  Bridges bridges (2, "esprezzo", "928790560549"); // im using my code since im bridge guy

      CircSLelement<Heroes>* heroesList = nullptr;
      //Classes stats: class name(speed, x_cord, y_cord, max_health, curr_health, defense, mag_defense, attack, mag_attack, exp, level, input)
      Goblin doger(10, 0, 0, 100, 100, 10, 5, 15, 3, 1, "l", 0);
      Mage goge(10, 0, 0, 100, 100, 10, 5, 15, 3, 0, "k", 0);

      auto *e11 = new CircSLelement<Heroes>(doger,"dog");

      auto *e12 = new CircSLelement<Heroes>(goge,"dog");

e11->setNext(e12);
      e12->setNext(e11);

      sortHeroesBySpeed(heroesList);
      heroesList = e11;

      cout << TotalHealth(heroesList) << endl;
   //   fight(doger,goge);
      cout<< goge.getcurr_health()<<endl;

      CircSLelement<Heroes>* enemiesList = nullptr;

      Goblin der(10, 0, 0, 100, 100, 10, 5, 15, 3, 1, "l", 0);
      Mage goe(10, 0, 0, 100, 100, 10, 5, 15, 3, 0, "k", 0);

      auto *e21 = new CircSLelement<Heroes>(doger,"dg");

      auto *e22 = new CircSLelement<Heroes>(goge,"og");
      e21 ->setNext(e22);
      e22 ->setNext(e21);


      sortHeroesBySpeed(enemiesList);
          enemiesList = e21;

      CircSLelement<Heroes>* combinedList =mergeLists(enemiesList,heroesList);
      sortHeroesBySpeed(combinedList);
      //bridges.setDataStructure(combinedList);
              //bridges.visualize();
  goe.action();

      delete e12;
      delete e11;
      delete e21;
      delete e22;

}


*/

int main() {


	turn_on_ncurses();
 Map map;
int x = Map::SIZE / 2, y = Map::SIZE /2;
	int old_x = -1, old_y = -1;
	map.setcord(2,(Map::SIZE/2)-1,'@');
	map.setcord(2,(Map::SIZE/2),'@');
	int level=0;
while (true) {
	int ch = getch();
	if(ch == 'q' || ch == 'Q') break;
 else if (ch==RIGHT) {
x++;
if(x>=Map::SIZE) x = Map::SIZE -1;
}else if (ch == LEFT) {
x--;
if(x<0)x=0;
} else if (ch == UP){
y--;
if(y>=Map::SIZE) y=Map::SIZE -1;
}else if(ch == DOWN){
			y++;
			if(y>=Map::SIZE) y = Map::SIZE -1;
}else if (ch ==ERR) {
;
}
if(x!= old_x or y!=old_y) {

if(map.getcord(x,y) == Map::TREASURE) {
				map.setcord(x,y,Map::OPEN);
			//	money++;
			}else if (map.getcord(x,y) ==Map::WALL or Map::TREE) {
				x= old_x;
				y= old_y;
			}else if (map.getcord(x,y) == Map::MONSTER) {
				turn_off_ncurses();
			//	combat();
				turn_on_ncurses();
				map.setcord(x,y,Map::OPEN);
			}else if (map.getcord(x,y) == Map::PORTAL) {
                
			level++;
			  map.setcord(x,y,Map::OPEN);
	
			}
map.draw(x,y,level);
mvprintw(Map::DISPLAY+1,0,"X: %i Y: %i\n",x,y);
//put stats here on the side of the game
 mvprintw(0,Map::DISPLAY+1,"Party info\n");
			
refresh();
}
old_x = x;
old_y=y;
usleep(1'000'000/MAX_FPS);
}
turn_off_ncurses();
	return 0;

}
