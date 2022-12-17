#include <string>
#include <unistd.h>
#include <memory>
#include <ncurses.h>
#include <vector>
#include <fstream> 
#include <iostream>

#include "gameboard.hpp"

#define WAIT_TICK 10000

using namespace std;


WINDOW *wnd;
WINDOW *stw;
shared_ptr<Gameboard> gb;					//Smart-Pointer auf das Gameboard-Objekt

int init(char **argv) {
	
	Point move;
	gb = make_shared<Gameboard>(0, 0, argv);		// Erstellen eines Gameboard-Objekt
	wnd = gb->getWindowHandle();
	stw = gb->getStatusWindowHandle();				// Holen des Ncurses-Handler
	wrefresh(wnd);
	wrefresh(stw);
	
	return 0;											// Rückgabe immer 0
}
void run() {
	Point itemBox;
	char ch;
	Point move;

	bool exit_requested = false;

	while(!exit_requested) {
	  int in_char = wgetch(wnd);
	  bool win = gb->areGoalsComplete();
	  if(win == true){
		  exit_requested = true;
	  }
	  switch(in_char) {
	    case 'q':   //quit game
	      exit_requested = true;
	      break;
	    case KEY_UP:   //up
	    case 'w':
			move=gb->getPlayer();
			move.y -= 1;
			ch=gb->getItem(move);
			if('$' == ch){
				itemBox = move;
				itemBox.y -= 1;
				gb->moveItem(move,itemBox);
			}
			gb->movePlayer(move);
			gb->displayGoals();
			gb->displayStatus();
	      break;
	    case KEY_DOWN:  //down
	    case 's':
			move=gb->getPlayer();
			move.y += 1;
			ch=gb->getItem(move);
			if('$' == ch){
				itemBox = move;
				itemBox.y += 1;
				gb->moveItem(move,itemBox);
			}
			gb->movePlayer(move);
			gb->displayGoals();
			gb->displayStatus();
	      break;
	    case KEY_LEFT:   //left
	    case 'a':
			move=gb->getPlayer();
			move.x -= 1;
			ch=gb->getItem(move);
			if('$' == ch){
				itemBox = move;
				itemBox.x -= 1;
				gb->moveItem(move,itemBox);
			}
			gb->movePlayer(move);
			gb->displayGoals();
			gb->displayStatus();
	      break;
	    case KEY_RIGHT:
	    case 'd':
			move=gb->getPlayer();
			move.x += 1;
			ch=gb->getItem(move);
			if('$' == ch){
				itemBox = move;
				itemBox.x += 1;
				gb->moveItem(move,itemBox);
			}
			gb->movePlayer(move);
			gb->displayGoals();
			gb->displayStatus();
	      break;
	    default:
	      break;
	}
	usleep(WAIT_TICK);  // 10ms
    wrefresh(wnd);
	wrefresh(stw);
	
   }
}
void close() {
	endwin();
}
int main (int argc, char **argv)  {
	if (argc == 2){
		init(argv);
		run();
		close();
	} else {
		cout << "Syntax Error. Parameter Falsch." << endl;
		endwin();
	}
	
}
