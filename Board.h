#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;


class Timer {
	time_t start_time = 0;
	time_t sum = 0;
	bool is_started = false;
public:
	//start the timer
	void start() {
		start_time = time(0);
	}
	//pause the timer and record the time
	void pause() {
		sum += difftime(time(0), start_time);
	}
	//get total time
	long get() {
		return sum;
	}
	Timer() = default;
};



struct Position {
	int c = 0;
	int r = 0;

	//only return legal move
	Position move(int pr, int pc) {
		if (r + pr <= 8 && r + pr >= 0 && c + pc <= 8 && c + pc >= 0)
			return Position(r + pr, c + pc);
		else
			return Position();
	}
	bool is_empty() {
		if (c != 0 && r != 0)
			return false;
		else
			return true;
	}

	Position(int pr, int pc) {
		r = pr; c = pc;
	}
	Position() = default;
};




class Pieces {
public:
	string name = "      ";
	char type = ' ';
	bool moved = false;
	string side = " ";
	Position pst;
	bool side_set = false;

	//set pieces' attributes
	void set(Position ppst, char ptype) {
		pst = ppst;
		type = ptype;

		//set side and name automately
		if (side_set == false) {
			side_set = true;
			if (ppst.r >= 7)
				side = "upper case";
			else if (ppst.r <= 2)
				side = "lower case";
		}
		map<char, string> name1 = { {'p'," PAWN "},{'n',"KNIGHT"},{'b',"BISHOP"},{'r'," ROOK "},{'q'," QUEEN"},{'k'," KING "} };
		if (side == "upper case")
			name = name1[ptype];
		map<char, string> name2 = { {'p'," pawn "},{'n',"knight"},{'b',"bishop"},{'r'," rook "},{'q'," queen"},{'k'," king "} };
		if (side == "lower case")
			name = name2[ptype];
	}
	//clear attributes(without position)
	void clear() {
		name = "      ";
		type = ' ';
		moved = false;
		side = " ";
	}
	//swap positions of two pieces
	void swap_pst(Pieces& apiece) {
		Position temp = pst;
		pst = apiece.pst;
		apiece.pst = temp;
	}
	//add and remove asterisk
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
	//return enemy's side
	string enemy_side() {
		if (side == "upper case")
			return "lower case";
		else if (side == "lower case")
			return "upper case";
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
	vector<vector<Pieces>> vboard = vector<vector<Pieces>>(9, vector<Pieces>(9));  //virtual board

	//put piece on string board
	void put(Pieces piece) {
		board[true_row[piece.pst.r]].replace(true_col[piece.pst.c], 6, piece.name);
	}

	//read a piece from position
	Pieces& read(Position pst) {
		return vboard[pst.r][pst.c];
	}


	//initialize the board
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

		//put pieces on board
		Position ipst;
		vector<string> itype;
		itype = { "rnbqkbnr","pppppppp","        " ,"        ","        ","        " , "pppppppp","rnbqkbnr" };
		for (int i = 1; i <= 8; i++) {
			ipst.r = i;
			for (int j = 1; j <= 8; j++) {
				ipst.c = j;
				vboard[i][j].set(ipst, itype[i - 1][j - 1]);
			}
		}
		//start recording the total time of the game
		t3.start();
	}

	void print() {
		//synchronize vector board and string board
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				put(vboard[i][j]);
			}
		}
		//print
		for (string i : board) {
			cout << i << endl;
		}
	}

	Timer t1, t2, t3;
	map < string, Timer > side_time = { {"upper case", t1}, { "lower case",t2 } };

	//get a piece to move
	void input1(string input_side) {
		string in;
		Position pst;
		cout << "Enter the position of a piece you want to move(" << input_side << " side)" << ": ";
		//record time and get input
		side_time[input_side].start();
		getline(cin, in);
		side_time[input_side].pause();

		//convert input into index
		for (char i : in) {
			if (i == 'a' || i == 'b' || i == 'c' || i == 'd' || i == 'e' || i == 'f' || i == 'g' || i == 'h')
				pst.c = int(i) - 96;
			else if (i == 'A' || i == 'B' || i == 'C' || i == 'D' || i == 'E' || i == 'F' || i == 'G' || i == 'H')
				pst.c = int(i) - 64;
			else if (i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6' || i == '7' || i == '8')
				pst.r = int(i) - 48;
		}
		//examine validity
		if (!pst.is_empty() && read(pst).type != ' ') {
			if (read(pst).side == input_side) {
				//search possible move
				move_search(pst);
			}
			else {
				cout << "wrong side, not your move" << endl;
				input1(input_side);
				return;
			}
		}
		else {
			cout << "Invalid input, please try again" << endl;
			input1(input_side);
		}
	}


	//add posssible move
	vector<Position> move_search(Position pself, int mode = 1) {
		Pieces& self = read(pself);
		vector<Position> pst_possible;

		//empty squares have no possible move
		if (self.type == ' ')
			return pst_possible;

		string input_side = self.side;
		Position pst1;
		vector<int> rlist(8);
		vector<int> clist(8);

		//logic of move
		switch (self.type) {
		case 'p'://pawn
			if (self.side == "lower case") {
				if (read(self.pst.move(1, 0)).type == ' ') {
					pst_possible.push_back(self.pst.move(1, 0));
					if (self.moved == false)
						pst_possible.push_back(self.pst.move(2, 0));
				}
				//add diagonal move
				if (read(self.pst.move(1, 1)).enemy_side() == self.side)
					pst_possible.push_back(self.pst.move(1, 1));
				if (read(self.pst.move(1, -1)).enemy_side() == self.side)
					pst_possible.push_back(self.pst.move(1, -1));
			}

			else if (self.side == "upper case") {
				if (read(self.pst.move(-1, 0)).type == ' ') {
					pst_possible.push_back(self.pst.move(-1, 0));
					if (self.moved == false)
						pst_possible.push_back(self.pst.move(-2, 0));
				}
				//add diagonal move
				if (read(self.pst.move(-1, 1)).enemy_side() == self.side)
					pst_possible.push_back(self.pst.move(-1, 1));
				if (read(self.pst.move(-1, -1)).enemy_side() == self.side)
					pst_possible.push_back(self.pst.move(-1, -1));
			}
			break;

		case 'n'://knight
			rlist = { 2,2,-2,-2,-1,1,-1,1 };
			clist = { -1,1,-1,1,-2,-2,2,2 };
			for (int i = 0; i < 8; i++) {
				pst1 = self.pst.move(rlist[i], clist[i]);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
			}
			break;

		case 'b'://bishop
			for (int i = 1; i < 8; i++) {
				pst1 = self.pst.move(i, i);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(-i, -i);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(i, -i);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(-i, i);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
			}
			break;

		case 'r'://rook
			for (int i = 1; i < 8; i++) {
				pst1 = self.pst.move(i, 0);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(0, i);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(-i, 0);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(0, -i);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
			}
			break;

		case 'q'://queen
			for (int i = 1; i < 8; i++) {
				pst1 = self.pst.move(i, i);
				if (pst1.c != 0 && pst1.r != 0)
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(-i, -i);
				if (pst1.c != 0 && pst1.r != 0)
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(i, -i);
				if (pst1.c != 0 && pst1.r != 0)
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(-i, i);
				if (pst1.c != 0 && pst1.r != 0)
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(i, 0);
				if (pst1.c != 0 && pst1.r != 0)
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(0, i);
				if (pst1.c != 0 && pst1.r != 0)
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(-i, 0);
				if (pst1.c != 0 && pst1.r != 0)
					pst_possible.push_back(pst1);
				pst1 = self.pst.move(0, -i);
				if (pst1.c != 0 && pst1.r != 0)
					pst_possible.push_back(pst1);
			}
			break;

		case 'k'://king
			rlist = { 1,-1,1,-1,1,0,-1,0 };
			clist = { 1,-1,-1,1,0,1,0,-1 };
			for (int i = 0; i < 8; i++) {
				pst1 = self.pst.move(rlist[i], clist[i]);
				if (!pst1.is_empty())
					pst_possible.push_back(pst1);
			}
			//castling
			if (self.moved == false) {
				for (int i = 1; i < 5; i++) {
					if (read(self.pst.move(0, i)).type == ' ')
						continue;
					else if (read(self.pst.move(0, i)).type == 'r' && read(self.pst.move(0, i)).moved == false)
						pst_possible.push_back(self.pst.move(0, 2));
					else
						break;
				}
				for (int i = 1; i < 5; i++) {
					if (read(self.pst.move(0, -i)).type != ' ')
						break;
					else if (read(self.pst.move(0, i)).type == 'r' && read(self.pst.move(0, i)).moved == false)
						pst_possible.push_back(self.pst.move(0, -2));
					else break;
				}
			}
			break;
		}
		return remove_blocked(pst_possible, self, mode);
	}


	//remove some illegal moves
	vector<Position> remove_blocked(vector<Position> pst_possible, Pieces& self, int mode) {
		Pieces apiece;
		for (auto it = pst_possible.begin(); it != pst_possible.end(); ) {
			apiece = read(*it);
			bool have_erased = false;

			//vertivally and horizontally blocked moves			
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

			//diagonally blocked moves
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
		return remove_check(pst_possible, self, mode);
	}



	vector<Position> remove_check(vector<Position> pst_possible, Pieces& self, int mode) {
		Pieces apiece;
		for (auto it = pst_possible.begin(); it != pst_possible.end();) {
			apiece = read(*it);
			bool find_king = false;
			Pieces save;

			//remove moves that touch allies
			if (apiece.side == self.side)
				it = pst_possible.erase(it);

			//assume possible moves have been done, then examinate whether the allied king will be captured
			//if the answer is yes, remove that move
			else if (mode <= 2) { //mode 1 and 2 accessible 
				apiece = vboard_swap(self.pst, apiece.pst);
				self.swap_pst(apiece);
				save = self;
				self.clear();

				if (is_check(apiece.side))
					it = pst_possible.erase(it);
				else
					it++;

				self = save;
				self.swap_pst(apiece);
				vboard_swap(self.pst, apiece.pst);
			}
			else
				it++;
		}
		//only mode 1 can access 
		if (mode <= 1) {
			if (pst_possible.size() != 0)
				input2(pst_possible, self.pst);
			else {
				cout << "No possible move, please try another piece" << endl;
				input1(self.side);
			}
		}
		return pst_possible;
	}

	//determine check state, iterate enemy pieces, find whether their possible moves coverd allied king
	bool is_check(string side) {
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				if (vboard[i][j].side != side && vboard[i][j].side != " ")
					for (Position epst : move_search(vboard[i][j].pst, 3)) //use move_search() mode 3 to avoid infinite recursion
						if (read(epst).type == 'k' && read(epst).side == side)
							return true;
		return false;
	}


	//input destination
	void input2(vector<Position> pst_possible, Position pst_self) {
		//add asterisk to squares of possible moves
		for (Position i : pst_possible) {
			read(i).asterisk("add");
		}
		print();

		cout << "Enter a destination. Enter 0 to cancel move('*' means you can move to that block): ";
		string in;
		Position pst_destination;
		//record time and get input
		side_time[read(pst_self).side].start();
		getline(cin, in);
		side_time[read(pst_self).side].pause();

		//convert input into index
		for (char i : in) {
			if (i == 'a' || i == 'b' || i == 'c' || i == 'd' || i == 'e' || i == 'f' || i == 'g' || i == 'h')
				pst_destination.c = int(i) - 96;
			else if (i == 'A' || i == 'B' || i == 'C' || i == 'D' || i == 'E' || i == 'F' || i == 'G' || i == 'H')
				pst_destination.c = int(i) - 64;
			else if (i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6' || i == '7' || i == '8')
				pst_destination.r = int(i) - 48;
			else if (i == '0') {
				for (Position i : pst_possible)
					read(i).asterisk("remove");
				print();
				input1(read(pst_self).side);
				return;
			}
		}
		//remove asterisk
		for (Position i : pst_possible)
			read(i).asterisk("remove");

		//move the piece if destination is legal
		for (Position apst : pst_possible) {
			if (apst.c == pst_destination.c && apst.r == pst_destination.r) {
				Pieces& self = read(pst_self);
				Pieces& target = read(pst_destination);
				self.moved = true;
				
				//swap and clear
				vboard_swap(self.pst, target.pst);
				self.swap_pst(target);
				self.clear();

				//castling
				Pieces& cast = read(target.pst.move(0, -1)), & rook = read(Position(self.pst.r, 8));
				if (target.type == 'k' && self.pst.move(0, 2).c == target.pst.c) {
					vboard_swap(cast.pst, rook.pst);
					rook.swap_pst(cast);
					rook.clear();
				}
				Pieces& cast2 = read(target.pst.move(0, 1)), & rook2 = read(Position(self.pst.r, 1));
				if (target.type == 'k' && self.pst.move(0, -2).c == target.pst.c) {
					vboard_swap(cast2.pst, rook2.pst);
					rook2.swap_pst(cast2);
					rook2.clear();
				}
				print();

				//examine game state
				if (is_check(target.enemy_side())) {
					for (int i = 1; i <= 8; i++)
						for (int j = 1; j <= 8; j++)
							if (vboard[i][j].type == 'k') {
								cout << "CHECK" << endl;
								//when king has no legal move, game over
								if (move_search(vboard[i][j].pst, 2).size() == 0) {
									cout << "GAME OVER\n" << target.side << " WIN" << endl;
									cout << target.side << " used " << side_time[target.side].get() << " seconds" << endl;
									cout << target.enemy_side() << " used " << side_time[target.enemy_side()].get() << " seconds" << endl;
									t3.pause();
									cout << "The total time of game is " << t3.get() << " seconds";
									exit(0);
								}
								return;
							}
				}
				//promotion of pawn
				if (target.type == 'p' && (target.pst.r == 1 || target.pst.r == 8)) {
					cout << "PROMOTION \nEnter 'n', 'b', 'r' or 'q' to change pawn into knight, bishop, rook or queen: ";
					target.set(target.pst, cin.get());
					print();
				}

				return;
			}
		}
		cout << "Invalid position, please try again";
		input2(pst_possible, pst_self);
	}

	//swap the pieces in virtual board
	Pieces vboard_swap(Position p1, Position p2) {
		Pieces temp;
		temp = vboard[p1.r][p1.c];
		vboard[p1.r][p1.c] = vboard[p2.r][p2.c];
		vboard[p2.r][p2.c] = temp;
		return temp;
	}
};

