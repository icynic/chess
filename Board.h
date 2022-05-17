#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;



struct Position {
	int c = 0;
	int r = 0;

	Position move(int pr, int pc) {
		if (r + pr <= 8 && r + pr >= 0 && c + pc <= 8 && c + pc >= 0) {
			return Position(r + pr, c + pc);
		}
		else {
			return Position();
		}

	}

	int move_r(int pr) {
		if (r + pr <= 8 && r + pr >= 0)
			return r + pr;
		return r;
	}
	int move_c(int pc) {
		if (c + pc <= 8 && c + pc >= 0)
			return c + pc;
		return c;
	}
	Position() = default;
	Position(int pr, int pc) {
		r = pr; c = pc;
	}
};




class Pieces {
public:
	string name = "      ";
	char type = ' ';
	bool moved = false;
	string side = " ";
	Position pst;
	bool side_set = false;

	void set(Position ppst, char ptype) {
		pst.c = ppst.c; pst.r = ppst.r;
		type = ptype;


		if (side_set == false) {
			side_set = true;
			if (ppst.r >= 7) {
				side = "up";
			}
			else if (ppst.r <= 2) {
				side = "down";
			}
		}

		switch (ptype) {
		case 'p':
			name = " Pawn ";
			break;
		case 'n':
			name = "Knight";
			break;
		case 'b':
			name = "Bishop";
			break;
		case 'r':
			name = " Rook ";
			break;
		case 'q':
			name = " Queen";
			break;
		case 'k':
			name = " King ";
			break;
		}
	}
	void clear() {
		name = "      ";
		type = ' ';
		moved = false;
		side = " ";
		side_set = false;
	}
	void swap_pst(Pieces& apiece) {
		Position temp = pst;
		pst = apiece.pst;
		apiece.pst = temp;
	}

	Pieces() = default;
};






class Board {
public:
	vector<string> board;

	map<int, int> true_row = { {1,17},{2,15},{3,13},{4,11},{5,9 },{6,7},{7,5},{8,3} };
	map<int, int> true_col = { {1,10}, {2,18}, {3,26}, {4,34}, {5,42}, {6,50}, {7,58}, {8,66} };

	vector<vector<Pieces>> vboard = vector<vector<Pieces>>(9, vector<Pieces>(9));



	void put(Pieces piece) {
		board[true_row[piece.pst.r]].replace(true_col[piece.pst.c], 6, piece.name);
	}



	Pieces& read(Position pst) {
		return vboard[pst.r][pst.c];
	}



	//initialize board
	Board() {

		board = {
	"┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐",
	"│      │   a  │   b  │   c  │   d  │   e  │   f  │   g  │   h  │      │",
	"├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤",
	"│   8  │      │      │      │      │      │      │      │      │   8  │",
	"├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤",
	"│   7  │      │      │      │      │      │      │      │      │   7  │",
	"├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤",
	"│   6  │      │      │      │      │      │      │      │      │   6  │",
	"├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤",
	"│   5  │      │      │      │      │      │      │      │      │   5  │",
	"├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤",
	"│   4  │      │      │      │      │      │      │      │      │   4  │",
	"├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤",
	"│   3  │      │      │      │      │      │      │      │      │   3  │",
	"├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤",
	"│   2  │      │      │      │      │      │      │      │      │   2  │",
	"├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤",
	"│   1  │      │      │      │      │      │      │      │      │   1  │",
	"├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤",
	"│      │   a  │   b  │   c  │   d  │   e  │   f  │   g  │   h  │      │",
	"└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘"
		};
		//put pieces on board(base on piece.pst, rather than the position in vboard)
		//white on down side
		Position ipst;
		vector<string> itype = { "rnbqkbnr","pppppppp","        " ,"        ","        ","        " , "pppppppp","rnbqkbnr" };
		for (int i = 1; i <= 8; i++) {
			ipst.r = i;
			for (int j = 1; j <= 8; j++) {
				ipst.c = j;
				vboard[i][j].set(ipst, itype[i - 1][j - 1]);
			}

		}
		refresh();

	}



	void print() {
		for (string i : board) {
			cout << i << endl;
		}
	}



	void input1() {
		string in;
		Position pst;
		cout << "Enter the position of a piece you want to move: ";
		getline(cin, in);
		for (char i : in) {
			if (i == 'a' || i == 'b' || i == 'c' || i == 'd' || i == 'e' || i == 'f' || i == 'g' || i == 'h') {
				pst.c = int(i) - 96;
			}
			else if (i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6' || i == '7' || i == '8') {
				pst.r = int(i) - 48;
			}
		}
		if (pst.c != 0 && pst.r != 0) {
			//check possible move
			move_search(pst);

		}
		else {
			cout << "Invalid input, please try again" << endl;
			input1();
		}
	}



	vector<Position> move_search(Position pself, bool second_times = false) {
		Pieces& self = read(pself);
		if (self.type == ' ')
			cerr << "error: search blank" << endl;

		vector<Position> pst_possible;
		Position pst1;

		int rlist_n[8] = { 2,2,-2,-2,-1,1,-1,1 };
		int clist_n[8] = { -1,1,-1,1,-2,-2,2,2 };
		switch (self.type) {
		case 'p':

			if (self.side == "down") {

				pst1 = self.pst.move(1, 0);
				pst_possible.push_back(pst1);
				if (self.moved == false) {

					pst1 = self.pst.move(2, 0);
					pst_possible.push_back(pst1);
				}
			}
			else if (self.side == "up") {

				pst1 = self.pst.move(-1, 0);
				pst_possible.push_back(pst1);
				if (self.moved == false) {

					pst1 = self.pst.move(-2, 0);
					pst_possible.push_back(pst1);
				}
			}
			break;
		case 'n':

			for (int i = 0; i < 8; i++) {
				pst1 = self.pst.move(rlist_n[i], clist_n[i]);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
			}

			break;
		case 'b':
			for (int i = 1; i < 8; i++) {
				pst1 = self.pst.move(i, i);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
				pst1 = self.pst.move(-i, -i);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
				pst1 = self.pst.move(i, -i);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
				pst1 = self.pst.move(-i, i);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
			}

			break;
		case 'r':

			break;
		case 'q':

			break;
		case 'k':

			break;
		}

		Pieces apiece;
		//delete blocked move
		for (auto it = pst_possible.begin(); it != pst_possible.end(); it++) {
			apiece = read(*it);
			//if (true) {//(apiece.side != " ")
				//vertival and horizontal				
			if (apiece.pst.c > self.pst.c && apiece.pst.r == self.pst.r) {
				for (int i = 1; i < apiece.pst.c - self.pst.c; i++) {
					if (read(self.pst.move(0, i)).type != ' ') {
						if (pst_possible.size() != 1) {
							it = pst_possible.erase(it) - 1;
						}
						else {
							it = pst_possible.erase(it);
						}
						break;
					}
				}
			}
			else if (apiece.pst.c < self.pst.c&& apiece.pst.r == self.pst.r) {
				for (int i = -1; i > apiece.pst.c - self.pst.c; i--) {
					if (read(self.pst.move(0, i)).type != ' ') {
						if (pst_possible.size() != 1) {
							it = pst_possible.erase(it) - 1;
						}
						else {
							it = pst_possible.erase(it);
						}
						break;
					}
				}
			}
			else if (apiece.pst.r > self.pst.r && apiece.pst.c == self.pst.c) {
				for (int i = 1; i < apiece.pst.r - self.pst.r; i++) {
					if (read(self.pst.move(i, 0)).type != ' ') {
						if (pst_possible.size() != 1) {
							it = pst_possible.erase(it) - 1;
						}
						else {
							it = pst_possible.erase(it);
						}
						break;
					}
				}
			}
			else if (apiece.pst.r < self.pst.r&& apiece.pst.c == self.pst.c) {
				for (int i = -1; i > apiece.pst.r - self.pst.r; i--) {
					if (read(self.pst.move(i, 0)).type != ' ') {
						if (pst_possible.size() != 1) {
							it = pst_possible.erase(it) - 1;
						}
						else {
							it = pst_possible.erase(it);
						}
						break;
					}
				}
			}

			//diagonal
			else if (abs(apiece.pst.r - self.pst.r) == abs(apiece.pst.c - self.pst.c)) {
				if (apiece.pst.c > self.pst.c && apiece.pst.r > self.pst.r) {
					for (int i = 1; i < apiece.pst.c - self.pst.c; i++) {
						if (read(self.pst.move(i, i)).type != ' ') {
							if (pst_possible.size() != 1) {
								it = pst_possible.erase(it) - 1;
							}
							else {
								it = pst_possible.erase(it);
							}
							break;
						}
					}
				}
				else if (apiece.pst.c < self.pst.c && apiece.pst.r < self.pst.r) {
					for (int i = -1; i > apiece.pst.c - self.pst.c; i--) {
						if (read(self.pst.move(i, i)).type != ' ') {
							if (pst_possible.size() != 1) {
								it = pst_possible.erase(it) - 1;
							}
							else {
								it = pst_possible.erase(it);
							}
							break;
						}
					}
				}
				else if (apiece.pst.r > self.pst.r && apiece.pst.c < self.pst.c) {
					for (int i = 1; i < apiece.pst.r - self.pst.r; i++) {
						if (read(self.pst.move(i, -i)).type != ' ') {
							if (pst_possible.size() != 1) {
								it = pst_possible.erase(it) - 1;
							}
							else {
								it = pst_possible.erase(it);
							}
							break;
						}
					}
				}
				else if (apiece.pst.r < self.pst.r && apiece.pst.c > self.pst.c) {
					for (int i = -1; i > apiece.pst.r - self.pst.r; i--) {
						if (read(self.pst.move(i, -i)).type != ' ') {
							if (pst_possible.size() != 1) {
								it = pst_possible.erase(it) - 1;
							}
							else {
								it = pst_possible.erase(it);
							}
							//!!!让迭代器-1可能会出错
							//! 
							//! 
							break;
						}
					}
				}
			}



		}

		for (auto it = pst_possible.begin(); it != pst_possible.end();) {
			apiece = read(*it);
			//delete ally
			if (apiece.side == self.side) {
				it = pst_possible.erase(it);

			}
			/*
			//check examine(enemy pieces)
			else if (second_times == false) {
				for (int i = 1; i <= 8; i++)
					for (int j = 1; j <= 8; j++)
						if (vboard[i][j].side != self.side && vboard[i][j].side != " ")
							for (Position epst : move_search(vboard[i][j].pst, true))
								if (read(epst).name == " king " && read(epst).side == self.side) {
									it = pst_possible.erase(it) - 1;
									break;
								}
				it++;
			}
			*/

			else {
				it++;
			}
		}
		if (second_times == false) {
			if (pst_possible.size() != 0) {
				input2(pst_possible, self.pst);
			}
			else {
				cout << "No possible move, please try again" << endl;
				input1();
			}
		}
		return pst_possible;
	}

	void input2(vector<Position> pst_possible, Position pst_self) {
		for (Position i : pst_possible) {
			cout << "you can move to: " << endl;
			cout << i.r << " row, " << i.c << " col" << endl;
		}

		cout << "Enter a destination: ";
		string in;
		Position pst_destination;
		getline(cin, in);
		for (char i : in) {
			if (i == 'a' || i == 'b' || i == 'c' || i == 'd' || i == 'e' || i == 'f' || i == 'g' || i == 'h') {
				pst_destination.c = int(i) - 96;
			}
			else if (i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6' || i == '7' || i == '8') {
				pst_destination.r = int(i) - 48;
			}
		}

		//move
		for (Position apst : pst_possible) {
			if (apst.c == pst_destination.c && apst.r == pst_destination.r) {
				Pieces& self = read(pst_self);
				self.moved = true;
				Pieces& target = read(pst_destination);
				

				//vboard[target.pst.r][target.pst.c]=vboard[self.pst.r][self.pst.c];
				vboard_swap(self.pst,target.pst);
				self.swap_pst(target);
				self.clear();
				refresh();
				print();

				
				
				return;
			}
		}
		cout << "Invalid position, please try again";
		input2(pst_possible, pst_self);

	}


	void vboard_swap(Position p1, Position p2) {
		Pieces temp;
		temp = vboard[p1.r][p1.c];
		vboard[p1.r][p1.c] = vboard[p2.r][p2.c];
		vboard[p2.r][p2.c] = temp;
	}


	//synchronize vboard and true board
	void refresh() {
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				put(vboard[i][j]);
			}
		}
	}
};

