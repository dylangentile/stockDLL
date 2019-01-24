#include <cstdlib>
#include <iostream>
#include <sstream>
#include "game.h"


using namespace std;


Game::Game() {

}


Game::~Game() {



}

void
Game::init(int stocks, int money) {
	cash = money;
	stockMax = stocks;
	stockArray = new Stock[stockMax];
	for (int i = 0; i < stockMax; i++) {
		stockArray[i].value = rand() % 1000;
		stockArray[i].mod = 0;
		stockArray[i].own = 0;
	}

}


void
Game::print() {
	cout << "CASH: $" << cash << "\n\n";
	for (int i = 0; i < stockMax; i++) {
		cout << i << ":$" << stockArray[i].value << "(+$"<< stockArray[i].mod << ")\t";
		if ((i + 1) % 4 == 0) {
			cout << "\n";
		}
	}

	cout << "Yourmove:\n";
}


bool
Game::buy(int which, int howmany) {
	int val = stockArray[which].value;
	if (cash >= val * howmany) {
		cash -= val * howmany;
		stockArray[which].own += howmany;
		return true;
	}
	return false;
}

bool
Game::sell(int which, int howmany) {
	int val = stockArray[which].value;
	int on = stockArray[which].own;
	if (on >= howmany) {
		cash += val * howmany;
		stockArray[which].own -= howmany;
		return true;
	}
	return false;
}

void
Game::cycle() {
	int pos;
	for (int i = 0; i < stockMax; i++) {
		pos = rand() % 2;
		if (pos == 1) {
			stockArray[i].mod = rand() % 100;
		}
		else {
			stockArray[i].mod = (rand() % 100) * (-1);
		}
	}

	for (int i = 0; i < stockMax; i++) {
		stockArray[i].change();
	}
	cout << "\n\n";
}

bool
Game::turn() {
	bool ret = true;
	while (true) {
		cout << "CASH: $" << cash << "\n";		
		cout << "!;";
		string input;
		cin >> input;

		
		if (input == "nw") {
			int networth = cash;
			cout << "\n";
			for (int i = 0; i < stockMax; i++) {
				cout << i << ":" << stockArray[i].own << " + ";
				networth += stockArray[i].value * stockArray[i].own;
			}
			cout << "CASH = " << networth << "\n!;";
			cin >> input;
		}


		if (input == "d") {
			break;
		}
		if (input == "q") {
			ret = false;
			break;
		}

		int len = input.length();
		int colonPos = -1;
		for (int i = 0; i < len; i++) {
			if (input[i] == ':') {
				colonPos = i;
				break;
			}
		}
		if (colonPos == -1) {
			return false;
		}
		string idToBuyStr = "", howmanyStr = "";
		int idToBuy, howmany;
		bool dobuy = true;

		for (int i = 0; i < colonPos; i++) {
			idToBuyStr += input[i];
		}

		for (int i = colonPos + 1; i < len; i++) {
			if (input[i] == '-') {
				dobuy = false;
			}
			else {
				howmanyStr += input[i];
			}
		}


		{
			stringstream ss;
			ss << howmanyStr;
			ss >> howmany;
		}
		{
			stringstream ss;
			ss << idToBuyStr;
			ss >> idToBuy;
		}

		bool ret = true;
		if (dobuy) {
			if (!buy(idToBuy, howmany)) {
				cout << "You don't have the cash...\n";
			}
			else {
				cout << "Transaction Completed\n";
			}
		}
		else {
			if (!sell(idToBuy, howmany)) {
				cout << "You don't own that...\n";
			}
			else {
				cout << "Transaction Completed\n";
			}
		}
	}
	return ret;
}