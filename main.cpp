
#include <iostream>
#include <cstdlib>     // srand, rand 
#include <ctime>       // time 
#include <string>
using namespace std;

string retPlusMinus(int x) {
	if (x > 0) {
		return "+";// + tostring(x);
	}
	else {
		return x;
	}
}


int main(int argc, char **argv[])
{
	int stockMax = 8;
	int *values = new int[stockMax];
	int *newMods = new int[stockMax];
	srand(time(NULL));
	for (int i = 0; i < stockMax; i++) {
		values[i] = rand() % 1000;
		newMods[i] = values[i];
	}
	cout << "\nWelcome to stock game!\n";

	while (true) {
		char input;
		cout << "GlarCorp\tMixeCorp\tSnowCorp\tJoesCorp\n0:$" << values[0] << "\t\t$1:" << values[1] << "\t\t$2:" << values[2] << "\t\t$3:" << values[3] << "\n";
		cout << "MarkCorp\tJohnCorp\tListCorp\tCodeCorp\n4:$" << values[4] << "\t\t$5:" << values[5] << "\t\t$6:" << values[6] << "\t\t$7:" << values[7] << "\n\n\n";
		cin >> input;

		for (int i = 0; i < stockMax; i++) {
			int chance = rand() % 2;
			if (chance == 1) {
				newMods[i] = (rand() % 100)*(-1);
			}
			if (chance == 0) {
				newMods[i] = rand() % 100;
			}
		}
		cout << "0:$+" << newMods[0] << "\t1:$+" << newMods[1] << "\t2:$+" << newMods[2] << "\t3:$+" << newMods[3] << "\t4:$+" << newMods[4] << "\t5:$+" << newMods[5] << "\t6:$+" << newMods[6] << "\t7:$+" << newMods[7] << "\n\n\n";
		cin >> input;
		for (int i = 0; i < stockMax; i++) {
			values[i] += newMods[i];
		}
	}
	return 0;


}



