
#include "Board.h"

int main() {
	Board a;
	a.print();
	while (true) {
		vector<string> side_list = { "down","up"};
		for (string s : side_list) {
			a.input1(s);
			a.print();
		}
	}

	return 0;
}
