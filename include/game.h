#pragma once
#include "stock.h"

class Game {
public:
	Game();
	~Game();
	void init(int stocks, int money);
	bool sell(int which, int howmany);
	bool buy(int which, int howmany);
	void cycle();
	bool turn();
	void print();

public:
	int cash;
	int stockMax;
	Stock *stockArray;


private:

};