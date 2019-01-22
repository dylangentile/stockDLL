#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

class Game
{
public:
	Game();
	~Game();
	void init(int x, int y, bool mode);
	bool buy(int which, int howmany);
	bool sell(int which, int howmany);
	void save();
	void cycle();

public:
	int numofStocks;
	int cash;
	int *values;
	int *newMods;
	int *own;

	bool saveMode; //true saves locally, false returns all of the values as a long string

};

Game::Game(){

}
Game::~Game(){

}

void
Game::init(int x, int y, bool mode){
	saveMode = mode;
	numofStocks = x;
	cash = y;
	values = new int[numofStocks];
	newMods = new int[numofStocks];
	own = new int[numofStocks];
	for (int i = 0; i < numofStocks; i++) {
		values[i] = rand() % 1000;
		newMods[i] = values[i];
		own[i] = 0;
	}
}
bool
Game::buy(int which, int howmany){
	if((values[which]*howmany) <= cash){
		cash -= values[which]*howmany;
		own[which] = howmany;
		return true;
	} 
	return false;
}
bool
Game::sell(int which, int howmany){
	if(own[which] >= howmany){
		cash += values[which]*howmany;
		own[which] -= howmany;
		return true;
	}
	return false;
}
void
Game::cycle(){
	for (int i = 0; i < numofStocks; i++) {
		int chance = rand() % 2;
		if (chance == 1) {
			newMods[i] = (rand() % 100)*(-1);
		}
		if (chance == 0) {
			newMods[i] = rand() % 100;
		}
	}

	for(int i = 0; i < numofStocks; i++){
		values[i] += newMods[i];
	}

}


void
Game::save() //format is How Many stocks  | how much cash |StockID:StockValue:HowManyIOwn| ie 8|1000|0:769:0|1:765:0|2:212:0|3:973:0|4:165:0|5:824:0|6:249:0|7:208:0|E
{
	cout << numofStocks << "|" << cash << "|";
	for(int i = 0; i < numofStocks; i++){
		cout << i << ":" << values[i] << ":" << own[i] << "|";
	}
	cout << "E\n";
}


void 
noGui(Game *mygame){
	while(true){
		string input;
		cin >> input;
		if(input == "qds" || input == "q"){
			break;
		}
		if(input == "qs"){
		  mygame->save();
			break;
		}
		while(true){
			if(input == "d"){
				mygame->cycle();
				break;
			}
			int idtobuy = input[0] - '0';
			int howmany = input[2] - '0';
			if (input[3] == '-' && input[1] == ':') {
				//selling function
				if(!mygame->sell(idtobuy, howmany))
				{
					cout << "!";
				}
				
			}
			else if (input[1] == ':') {
				if(!mygame->buy(idtobuy, howmany)){
					cout << "!";
				}
			}
			else {
				cout << "!";
			}

		}
	}
}

void
Game::interpret(string data) //string format is: Declarinput(!) How Many stocks | how much cash |StockID:StockValue:HowManyIOwn| ... |Transactions(T)|StockID:HowManyIwant|...      ie !8|1000|0:769:0|1:765:0|2:212:0|3:973:0|4:165:0|5:824:0|6:249:0|7:208:0|T|1|0:1|E
{  //it doesn't matter if the actions in the string are legal. It's all the job of this program to determine that and tell php/jQuery

	if (data[0] == "!") {
		string stockNumTmp;
		while (data[i] != "|") {

		}
	}
	
}



string retplumin(int x) {
  string str;
  stringstream ss;
  ss << x;
  str = ss.str();
  if (x < 0) {
    return str;
	}
	if (x > 0) {
	  return "+" + str;

	}
	if (x == 0) {
		return "0";
	}
	return "0";
}



void withUI(Game *mygame){
cout << "Welcome to stock game!\n";
cout << "CASH: $" << mygame->cash << "\n";
while (true) {
		string input;
		
		cout << "GlarCorp\tMixeCorp\tSnowCorp\tJoesCorp\n0:$" << mygame->values[0] << "\t\t$1:" << mygame->values[1] << "\t\t$2:" << mygame->values[2] << "\t\t$3:" << mygame->values[3] << "\n";
		cout << "MarkCorp\tJohnCorp\tListCorp\tCodeCorp\n4:$" << mygame->values[4] << "\t\t$5:" << mygame->values[5] << "\t\t$6:" << mygame->values[6] << "\t\t$7:" << mygame->values[7] << "\n\n\n";
		
		while (true) {
			cout << "\tCASH: $" << mygame->cash << "\n";
			cin >> input;
			if (input == "d") {
				break;
			}

			int idtobuy = input[0] - '0';
			int howmany = input[2] - '0';

			//cout << idtobuy;
			//cout << howmany;
			
			if (input[3] == '-' && input[1] == ':') {
				//selling function
				if(mygame->sell(idtobuy, howmany))
				{
					cout << "\nTransaction Completed\n";
				} 
				else
				{
					cout << "\nYour transaction was somehow invalid?\n";
				}
				
			}
			else if (input[1] == ':') {
				if(mygame->buy(idtobuy, howmany)){
					cout << "\nTransaction Completed\n";
				} else{
					cout << "\nYour transaction was somehow invalid?\n";
				}
			}
			else {
				cout << "\nImproper Formatting!!\n";
			}
			
		}

		mygame->cycle();
		
		for (int i = 0; i < mygame->numofStocks; i++) {
			cout << i << ":" << retplumin(mygame->newMods[i]) << "\t";
		}
		cout << '\n';
		cin >> input;
		
		cout << "\n\n";
		cout << "CASH: $" << mygame->cash << "\nWorth: ";
		int wt = 0;
		for (int i = 0; i < mygame->numofStocks; i++) {
			wt += mygame->values[i] * mygame->own[i];
			cout << i << ':' << mygame->own[i] << " + ";
		}
		cout << "0 = $" << wt << "\n";
	}
}


#include <cstring>

int main(int argc, char const *argv[])
{
	bool api = false;
	bool gui = true;
	srand(time(NULL));
	if(argc == 2){
		if(strcmp(argv[0], "ng"))
		{
			gui = false;
		}
	}
	
	Game *thegame = new Game;
	thegame->init(8,1000,false);
	if(argc == 2){
		if(strcmp(argv[0], "ioi"))
		{
			thegame->save();
		}
	}

	if (argc == 3) {
		if (strcmp(argv[0], "i")) {
			string data = argv[0];
			if (data[0] == "!") {
				//thegame->interpret(data);
			}
		}
	}


	if (!api) {
		if (gui) {
			withUI(thegame);
		}
		else {
			noGui(thegame);
		}
	}
	return 0;
}
