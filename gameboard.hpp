#ifndef GAMEBOARD_HPP		// Sentinel (Wächter), verhindert das
#define GAMEBOARD_HPP		// Mehrfachladen der Headerdatei! 

#include <string>
#include <ncurses.h>
#include <vector>
#include <memory>
#include <fstream> 
using namespace std;

class Point {
	public:
		int x;
		int y;
};

class Gameboard{
	private:
		WINDOW *wnd;
		WINDOW *stw;
		Point max;
		Point player;
		Point status = {0,0};
		char prestau = ' ';
		char irestau = ' ';
		WINDOW *loadGameboard(int, int, char **argv);
		WINDOW *loadStatus(int, int);
		vector<Point> goals;
	public:
		Gameboard(int, int,char **argv);
		virtual ~Gameboard();
		virtual WINDOW *getWindowHandle();
		virtual WINDOW *getStatusWindowHandle();
		Point getPlayer();
		void movePlayer(Point);
		char getItem(Point pt);
		void moveItem(Point from, Point to);
		void displayGoals();
		void displayStatus();
		bool areGoalsComplete();

};


#endif
