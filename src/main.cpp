#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

string retplumin(int x) {
	if (x < 0) {
		return to_string(x);
	}
	if (x > 0) {
		return "+" + to_string(x);

	}
	if (x == 0) {
		return "0";
	}
	return "0";
}


int main(int argc, char const *argv[])
{
	
	int stockMax = 8;
	double cash = 1000;
	int *values = new int[stockMax];
	int *newMods = new int[stockMax];
	int *own = new int[stockMax];
	srand(time(NULL));
	for (int i = 0; i < stockMax; i++) {
		values[i] = rand() % 1000;
		newMods[i] = values[i];
		own[i] = 0;
	}
	cout << "\nWelcome to stock game!\n";
	cout << "CASH: $" << cash << "\n";

	while (true) {
		string input;
		
		cout << "GlarCorp\tMixeCorp\tSnowCorp\tJoesCorp\n0:$" << values[0] << "\t\t$1:" << values[1] << "\t\t$2:" << values[2] << "\t\t$3:" << values[3] << "\n";
		cout << "MarkCorp\tJohnCorp\tListCorp\tCodeCorp\n4:$" << values[4] << "\t\t$5:" << values[5] << "\t\t$6:" << values[6] << "\t\t$7:" << values[7] << "\n\n\n";
		
		while (true) {
			cout << "\tCASH: $" << cash << "\n";
			cin >> input;
			if (input == "d") {
				break;
			}

			int idtobuy = input[0] - '0';
			int howmany = input[2] - '0';

			//cout << idtobuy;
			//cout << howmany;
			
			if (input[3] == '-') {
				//selling function
				if (own[idtobuy] >= howmany) {
					own[idtobuy] -= howmany;
					cash += values[idtobuy] * howmany;
				}
			}
			else if (input[1] == ':') {
				//buying function
				if (idtobuy >= 0 && idtobuy <= 8) {
					int cost = values[idtobuy] * (howmany);
					if ((double)cost < cash) {
						own[idtobuy] += howmany;
						cash = cash - cost;
						cout << "\nTransaction Completed. Type 'd' to move to the next day.\nNext Transaction:";
					}
					else {
						cout << "\nYou're too poor!\n";
					}

				}
				else {
					cout << "\nWhat you're trying to buy doesn't exist!\n";
				}
			}
			else {
				cout << "\nImproper Formatting!!\n";
			}
			
		}

		for (int i = 0; i < stockMax; i++) {
			int chance = rand() % 2;
			if (chance == 1) {
				newMods[i] = (rand() % 100)*(-1);
			}
			if (chance == 0) {
				newMods[i] = rand() % 100;
			}
		}
		for (int i = 0; i < stockMax; i++) {
			cout << i << ":" << retplumin(newMods[i]) << "\t";
		}
		cout << '\n';
		cin >> input;
		for (int i = 0; i < stockMax; i++) {
			values[i] += newMods[i];
		}
		cout << "\n\n";
		cout << "CASH: $" << cash << "\nWorth: ";
		int wt = 0;
		for (int i = 0; i < stockMax; i++) {
			wt += values[i] * own[i];
			cout << i << ':' << own[i] << " + ";
		}
		cout << "0 = $" << wt << "\n";
	}
	return 0;
}