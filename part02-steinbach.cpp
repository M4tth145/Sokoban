#include <string.h>
#include <unistd.h>
#include <iostream>
#include <ncurses.h>

using namespace std;

#define WAIT_TICK 10000

WINDOW *win1;
WINDOW *win2;
WINDOW *win3;

int main()
{
  char a[25], b[25], c[25];

  cout << "Satz 1: ";
  cin.getline(a, 25);
  cout <<"\nSatz 2: ";
  cin.getline(b, 25);
  cout << "\nSatz 3: ";
  cin.getline(c, 25);

  initscr(); //NCurses: Bildschirm initialisieren
  cbreak();  //NCurses: Strg+C zum Abbrechen einschalten
  noecho();  //NCurses: Zeichen-Echo ausschalten
  clear();   //NCurses: Bildschirm löschen
  refresh(); //NCurses: Bildschirm neu zeichnen

  curs_set(0);

  win1 = newwin( 3, 50, 1, 1);
  win2 = newwin(3 , 50, 5, 1);
  win3 = newwin(3 , 50, 9, 1);

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_RED);
  init_pair(3, COLOR_YELLOW, COLOR_GREEN);
  init_pair(4, COLOR_WHITE, COLOR_BLUE);

  bkgd(COLOR_PAIR(1)); //Vordergrund/Hintergrundfarben des Fensters
  wbkgd(win1, COLOR_PAIR(2));
  wbkgd(win2, COLOR_PAIR(3));
  wbkgd(win3, COLOR_PAIR(4));

  mvwprintw (win1, 1, 1, a);
  mvwprintw (win2, 1, 1, b);
  mvwprintw (win3, 1, 1, c);

  refresh();
  wrefresh(win1);
  wrefresh(win2);
  wrefresh(win3);

  while(true);

  return 0;


  //init();
  //run();
  //close();
}
