#pragma once
#include <string>

class Stock {
public:
	Stock();
	~Stock();
	void change();

public:
	int value, mod, own;
	std::string name;



};

