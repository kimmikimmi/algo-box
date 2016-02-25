#include <iostream>
#include <fstream>

using namespace std;

#define DEAD 0
#define LIVE 1

#define CORNER_CHK 2
#define SIDE_CHK 3
#define IN_CHK 4

#define SURVIVAL -1

bool check_neighbors(bool **dish_square, int chk_r, int chk_c, int r_sz, int c_sz);
int bacteria_simulate(bool **dish_square, int row, int col);


// returns survival time
int bacteria_simulate(bool **dish_square, int row, int col) {
	int survival_time = 0;
	bool extinct = false;
	bool next_state;
	bool is_change = false;

	bool *buff_prev = new bool[col];
	bool *buff_curr = new bool[col];
	int num_of_live_cell = 0;
	int prev_live_cell;
	// test check func

	// cout << "-------- Live or Dead --------" << endl; 
	while(1) {
		for(int chk_r = 0; chk_r < row; ++chk_r) {
			for(int chk_c = 0; chk_c < col; ++chk_c) {

				next_state = check_neighbors(dish_square, chk_r, chk_c, row, col);
				buff_prev[chk_c] = next_state;

				if(next_state == LIVE) ++num_of_live_cell;
			}

			// update previous line
			if(chk_r > 0) { // except for the first line
				for(int i = 0; i < col; ++i)
					dish_square[chk_r - 1][i] = buff[i];
			}
			cout << endl;

		}
		++survival_time;
		if(num_of_live_cell == 0) return survival_time;
		if(num_of_live_cell == prev_live_cell) return SURVIVAL;
		prev_live_cell = num_of_live_cell;
		num_of_live_cell = 0;

		
	}
	

	// simulating...
	// while(1) {
	// 	for(int chk_r = 0; chk_r < row; ++chk_r) {
	// 		for(int chk_c = 0; chk_c < col; ++chk_c) {
	// 			state = dish_square[chk_c][chk_r];

	// 			if(state !=	(buff[chk_c] = check_neighbors(dish_square, chk_r, chk_c, row, col))) {

	// 				is_change = true;
	// 			}
	// 		}

	// 	}
		
	// }

	delete [] buff;

}

bool check_neighbors(bool **dish_square, int chk_r, int chk_c, int r_sz, int c_sz) {
	int live_cell = 0;

	// cell checked is dead or live
	if(dish_square[chk_r][chk_c] == 0) return DEAD;

	// check four corners
	if (chk_r == 0 && chk_c == 0) { // top left corner
		if(dish_square[0][1] == 0 || dish_square[1][0] == 0) return DEAD;
		else return LIVE;

	} else if(chk_r == 0 && chk_c == c_sz - 1) { // top right corner
		if(dish_square[0][chk_c - 1] == 0 || dish_square[1][chk_c] == 0) return DEAD;
		else return LIVE;

	} else if(chk_r == r_sz - 1 && chk_c == 0) { // bottom left corner
		if(dish_square[chk_r - 1][0] == 0 || dish_square[chk_r][1] == 0) return DEAD;
		else return LIVE;

	} else if(chk_r == r_sz - 1 && chk_c == c_sz - 1) {// bottom right corner
		if(dish_square[chk_r][chk_c - 1] == 0 || dish_square[chk_r - 1][chk_c] == 0) return DEAD;
		else return LIVE;

	}

	// check side lines(top, bottom, left, right)

	if(chk_r == 0) { // top line
		// printf("\ntop line(%d, %d)\nleft, down, right:(%d, %d, %d)\n", chk_r, chk_c, 
		// 	dish_square[0][chk_c - 1], dish_square[1][chk_c], dish_square[0][chk_c + 1]);

		if(dish_square[0][chk_c - 1] == LIVE) ++live_cell;
		if(dish_square[1][chk_c] == LIVE) ++live_cell;
		if(dish_square[0][chk_c + 1] == LIVE) ++live_cell;
		return (live_cell == 2) ? LIVE : DEAD;

	} else if(chk_r == r_sz - 1) { // bottom line
		if(dish_square[chk_r][chk_c - 1] == LIVE) ++live_cell;
		if(dish_square[chk_r - 1][chk_c] == LIVE) ++live_cell;
		if(dish_square[chk_r][chk_c + 1] == LIVE) ++live_cell;
		return (live_cell == 2) ? LIVE : DEAD;

	} else if(chk_c == 0) { // left line
		if(dish_square[chk_r + 1][0] == LIVE) ++live_cell;
		if(dish_square[chk_r - 1][0] == LIVE) ++live_cell;
		if(dish_square[chk_r][1] == LIVE) ++live_cell;
		return (live_cell == 2) ? LIVE : DEAD;

	} else if(chk_c == c_sz-1) { // right line
		if(dish_square[chk_r + 1][chk_c] == LIVE) ++live_cell;
		if(dish_square[chk_r - 1][chk_c] == LIVE) ++live_cell;
		if(dish_square[chk_r][chk_c-1] == LIVE) ++live_cell;
		return (live_cell == 2) ? LIVE : DEAD;
	}

	// check cells inside the dish square
	if(dish_square[chk_r - 1][chk_c] == 0) ++live_cell; // north
	if(dish_square[chk_r][chk_c - 1] == 0) ++live_cell; // west
	if(dish_square[chk_r][chk_c + 1] == 0) ++live_cell; // east
	if(dish_square[chk_r + 1][chk_c] == 0) ++live_cell; // south
	return (live_cell == 2) ? LIVE : DEAD;

}

void print_dish_square(bool **dish_square, int row, int col) {
	for(int i = 0; i < row; ++i) { 
		for(int j = 0; j < col; ++j) {
			cout << dish_square[i][j];
		}
		cout << endl;
	}

}
void dealloc_dishes(bool **dish, int row, int col) {
	for(int i = 0; i < row; ++i) {
		delete [] dish[i];
	}
	delete [] dish;
}
int main() {

	int test_case;
	int row, col;
	char c;
	cin >> test_case;

	do {
		cin >> col >> row;
		printf("row:%d, col:%d\n", row, col);
		bool **dish = new bool*[row];
		for(int i = 0; i < row; ++i) {
			dish[i] = new bool[col];
			for(int j = 0; j < col; ++j) {
				cin >> c;
				if(c == '*') dish[i][j] = 1;
				else if(c =='.') dish[i][j] = 0;
			}
		}



		print_dish_square(dish, row, col);
		
		int second = bacteria_simulate(dish, row, col);


		dealloc_dishes(dish, row, col);


	} while(--test_case > 0);
	


	return 0;
}