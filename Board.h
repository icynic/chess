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
		pst = ppst;
		//pst.c = ppst.c; pst.r = ppst.r;
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
		map<char, string> name1 = { {'p'," PAWN "},{'n',"KNIGHT"},{'b',"BISHOP"},{'r'," ROOK "},{'q'," QUEEN"},{'k'," KING "} };
		if (side == "up")
			name = name1[ptype];
		map<char, string> name2 = { {'p'," pawn "},{'n',"knight"},{'b',"bishop"},{'r'," rook "},{'q'," queen"},{'k'," king "} };
		if (side == "down")
			name = name2[ptype];
	}
	void clear() {
		name = "      ";
		type = ' ';
		moved = false;
		side = " ";
		//side_set = false;
	}
	void swap_pst(Pieces& apiece) {
		Position temp = pst;
		pst = apiece.pst;
		apiece.pst = temp;
	}
	void asterisk(string option) {
		char last = ' ';
		if (option == "add") {
			last = name[5];
			name[5] = '*';
		}
		else if (option == "remove" && name[5] == '*') {
			name[5] = last;
		}
	}
	string enemy_side() {
		if (side == "up")
			return "down";
		else if (side == "down")
			return "up";
		else
			return " ";
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
	"\n┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐",
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
		sync();

	}



	void print() {
		for (string i : board) {
			cout << i << endl;
		}
	}



	void input1(string input_side) {


		string in;
		Position pst;
		cout << "Enter the position of a piece you want to move(" << input_side << "side)" << ": ";
		getline(cin, in);
		for (char i : in) {
			if (i == 'a' || i == 'b' || i == 'c' || i == 'd' || i == 'e' || i == 'f' || i == 'g' || i == 'h') {
				pst.c = int(i) - 96;
			}
			else if (i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6' || i == '7' || i == '8') {
				pst.r = int(i) - 48;
			}
		}
		if (pst.c != 0 && pst.r != 0 && read(pst).type != ' ') {
			if (read(pst).side == input_side) {
				//check possible move
				move_search(pst);
			}
			else {
				cout << "wrong side" << endl;
				input1(input_side);
			}



		}
		else {
			cout << "Invalid input, please try again" << endl;
			input1(input_side);
		}

	}

	//递归没有终点

	vector<Position> move_search(Position pself, int timek = 1) {
		Pieces& self = read(pself);
		vector<Position> pst_possible;
		string input_side = self.side;

		if (self.type == ' ')
			return pst_possible;



		Position pst1;

		int rlist_n[8] = { 2,2,-2,-2,-1,1,-1,1 };
		int clist_n[8] = { -1,1,-1,1,-2,-2,2,2 };
		switch (self.type) {
		case 'p':
			if (self.side == "down") {
				if (read(self.pst.move(1, 0)).type == ' ') {
					pst1 = self.pst.move(1, 0);
					pst_possible.push_back(pst1);
					if (self.moved == false) {

						pst1 = self.pst.move(2, 0);
						pst_possible.push_back(pst1);
					}
				}
				if (read(self.pst.move(1, 1)).enemy_side() == self.side) {
					pst1 = self.pst.move(1, 1);
					pst_possible.push_back(pst1);
				}
				if (read(self.pst.move(1, -1)).enemy_side() == self.side) {
					pst1 = self.pst.move(1, -1);
					pst_possible.push_back(pst1);
				}
			}
			else if (self.side == "up") {
				if (read(self.pst.move(-1, 0)).type == ' ') {
					pst1 = self.pst.move(-1, 0);
					pst_possible.push_back(pst1);
					if (self.moved == false) {

						pst1 = self.pst.move(-2, 0);
						pst_possible.push_back(pst1);
					}
				}
				if (read(self.pst.move(-1, 1)).enemy_side() == self.side) {
					pst1 = self.pst.move(-1, 1);
					pst_possible.push_back(pst1);
				}
				if (read(self.pst.move(-1, -1)).enemy_side() == self.side) {
					pst1 = self.pst.move(-1, -1);
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
			for (int i = 1; i < 8; i++) {
				pst1 = self.pst.move(i, 0);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
				pst1 = self.pst.move(0, i);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
				pst1 = self.pst.move(-i, 0);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
				pst1 = self.pst.move(0, -i);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}

			}


			break;
		case 'q':
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
				pst1 = self.pst.move(i, 0);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
				pst1 = self.pst.move(0, i);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
				pst1 = self.pst.move(-i, 0);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
				pst1 = self.pst.move(0, -i);
				if (pst1.c != 0 && pst1.r != 0) {
					pst_possible.push_back(pst1);
				}
			}

			break;
		case 'k':
			pst1 = self.pst.move(1, 1);
			if (pst1.c != 0 && pst1.r != 0) {
				pst_possible.push_back(pst1);
			}
			pst1 = self.pst.move(-1, -1);
			if (pst1.c != 0 && pst1.r != 0) {
				pst_possible.push_back(pst1);
			}
			pst1 = self.pst.move(1, -1);
			if (pst1.c != 0 && pst1.r != 0) {
				pst_possible.push_back(pst1);
			}
			pst1 = self.pst.move(-1, 1);
			if (pst1.c != 0 && pst1.r != 0) {
				pst_possible.push_back(pst1);
			}
			pst1 = self.pst.move(1, 0);
			if (pst1.c != 0 && pst1.r != 0) {
				pst_possible.push_back(pst1);
			}
			pst1 = self.pst.move(0, 1);
			if (pst1.c != 0 && pst1.r != 0) {
				pst_possible.push_back(pst1);
			}
			pst1 = self.pst.move(-1, 0);
			if (pst1.c != 0 && pst1.r != 0) {
				pst_possible.push_back(pst1);
			}
			pst1 = self.pst.move(0, -1);
			if (pst1.c != 0 && pst1.r != 0) {
				pst_possible.push_back(pst1);
			}


			break;
		}
		return remove_blocked(pst_possible, self,timek);
	}

	vector<Position> remove_blocked(vector<Position> pst_possible, Pieces& self,int timek) {
		Pieces apiece;
		//delete blocked move
		for (auto it = pst_possible.begin(); it != pst_possible.end(); ) {
			apiece = read(*it);
			bool have_erased = false;

			//vertival and horizontal				
			if (apiece.pst.c > self.pst.c && apiece.pst.r == self.pst.r) {
				for (int i = 1; i < apiece.pst.c - self.pst.c; i++) {
					if (read(self.pst.move(0, i)).type != ' ') {
						it = pst_possible.erase(it);
						have_erased = true;
						break;
					}
				}
				if (!have_erased)
					it++;
			}
			else if (apiece.pst.c < self.pst.c&& apiece.pst.r == self.pst.r) {
				for (int i = -1; i > apiece.pst.c - self.pst.c; i--) {
					if (read(self.pst.move(0, i)).type != ' ') {
						it = pst_possible.erase(it);
						have_erased = true;
						break;
					}
				}
				if (!have_erased)
					it++;
			}
			else if (apiece.pst.r > self.pst.r && apiece.pst.c == self.pst.c) {
				for (int i = 1; i < apiece.pst.r - self.pst.r; i++) {
					if (read(self.pst.move(i, 0)).type != ' ') {
						it = pst_possible.erase(it);
						have_erased = true;
						break;
					}
				}
				if (!have_erased)
					it++;
			}
			else if (apiece.pst.r < self.pst.r&& apiece.pst.c == self.pst.c) {
				for (int i = -1; i > apiece.pst.r - self.pst.r; i--) {
					if (read(self.pst.move(i, 0)).type != ' ') {
						it = pst_possible.erase(it);
						have_erased = true;
						break;
					}
				}
				if (!have_erased)
					it++;
			}




			//diagonal
			else if (abs(apiece.pst.r - self.pst.r) == abs(apiece.pst.c - self.pst.c)) {
				if (apiece.pst.c > self.pst.c && apiece.pst.r > self.pst.r) {
					for (int i = 1; i < apiece.pst.c - self.pst.c; i++) {
						if (read(self.pst.move(i, i)).type != ' ') {
							it = pst_possible.erase(it);
							have_erased = true;
							break;
						}
					}
					if (!have_erased)
						it++;
				}
				else if (apiece.pst.c < self.pst.c && apiece.pst.r < self.pst.r) {
					for (int i = -1; i > apiece.pst.c - self.pst.c; i--) {
						if (read(self.pst.move(i, i)).type != ' ') {
							it = pst_possible.erase(it);
							have_erased = true;
							break;
						}
					}
					if (!have_erased)
						it++;
				}
				else if (apiece.pst.r > self.pst.r && apiece.pst.c < self.pst.c) {
					for (int i = 1; i < apiece.pst.r - self.pst.r; i++) {
						if (read(self.pst.move(i, -i)).type != ' ') {
							it = pst_possible.erase(it);
							have_erased = true;
							break;
						}
					}
					if (!have_erased)
						it++;
				}
				else if (apiece.pst.r < self.pst.r && apiece.pst.c > self.pst.c) {
					for (int i = -1; i > apiece.pst.r - self.pst.r; i--) {
						if (read(self.pst.move(i, -i)).type != ' ') {
							it = pst_possible.erase(it);
							have_erased = true;
							break;
						}
					}
					if (!have_erased)
						it++;
				}
			}
			else {
				it++;
			}

		}
		return remove_check(pst_possible, self,timek);
	}

	//敌方queen的possible move 少了己方king ， 无法触发capture 为什么

	vector<Position> remove_check(vector<Position> pst_possible, Pieces& self, int timek) {
		Pieces apiece;
		for (auto it = pst_possible.begin(); it != pst_possible.end();) {
			apiece = read(*it);
			//delete ally
			bool find_king = false;
			Pieces save;
			if (apiece.side == self.side) {
				it = pst_possible.erase(it);

			}

			//可能是true
			else if (timek < 3) {//second_times == false

				apiece = vboard_swap(self.pst, apiece.pst);
				self.swap_pst(apiece);
				save = self;
				self.clear();


				//if (is_check(apiece.side)) {
				//	it = pst_possible.erase(it);
				//}
				//else {
					it++;
				//}
				self = save;
				self.swap_pst(apiece);
				vboard_swap(self.pst, apiece.pst);
			}
			else {
				it++;
			}
		}
		if (timek < 2) {
			if (pst_possible.size() != 0) {
				input2(pst_possible, self.pst);
			}
			else {
				cout << "No possible move, please try another piece" << endl;
				input1(self.side);
			}
		}
		return pst_possible;
	}


	bool is_check(string side) {
	//	int timek = 1;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				if (vboard[i][j].side != side && vboard[i][j].side != " ")
					for (Position epst : move_search(vboard[i][j].pst, 3))//true
						if (read(epst).type == 'k' && read(epst).side == side) {
							return true;
						}
		return false;
	}



	void input2(vector<Position> pst_possible, Position pst_self) {
		for (Position i : pst_possible) {
			read(i).asterisk("add");
		}
		sync();
		print();


		cout << "Enter a destination('*' means you can move to that block): ";
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


		for (Position i : pst_possible) {
			read(i).asterisk("remove");
		}


		//move
		for (Position apst : pst_possible) {
			if (apst.c == pst_destination.c && apst.r == pst_destination.r) {
				Pieces& self = read(pst_self);
				self.moved = true;
				Pieces& target = read(pst_destination);

				vboard_swap(self.pst, target.pst);
				self.swap_pst(target);
				self.clear();
				sync();
				print();

				//if enemy king is in ckeck
				if (is_check(target.enemy_side())) {
					for (int i = 1; i <= 8; i++)
						for (int j = 1; j <= 8; j++)
							if (vboard[i][j].type == 'k') {
								cout << "CHECK" << endl;
								if (move_search(vboard[i][j].pst, 2).size() == 0) {
									cout << "GAME OVER" << endl;
									cout << target.side << " win";
									exit(0);
								}
								return;
							}
				}
				return;
			}
		}
		cout << "Invalid position, please try again";
		input2(pst_possible, pst_self);

	}


	Pieces vboard_swap(Position p1, Position p2) {
		Pieces temp;
		temp = vboard[p1.r][p1.c];
		vboard[p1.r][p1.c] = vboard[p2.r][p2.c];
		vboard[p2.r][p2.c] = temp;
		return temp;
	}


	//synchronize vboard and true board
	void sync() {
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				put(vboard[i][j]);
			}
		}
	}
};

