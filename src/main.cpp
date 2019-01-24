#include "game.h"


#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void gameHandler(Game *thegame) {
	while (true) {
		thegame->print();
		
		
		bool x = thegame->turn();

		if (!x) {
			cout << "Thanks for playing...\n";
			break;
		}
		else {
			thegame->cycle();
		}
	}



}



int main(int argc, char const *argv[]) {


	srand(time(NULL));
	Game *thegame = new Game;
	thegame->init(8, 1000);

	gameHandler(thegame);

	return 0;
}