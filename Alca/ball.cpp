#include "ball.h"

using namespace Alca;
using namespace System;
using namespace System::Windows::Forms;

void ball::setX(int x) {
	b_x = x;
}
void ball :: setY(int y) {
	b_y = y;
}
int ball::getX() {
	return b_x;
}
int ball::getY() {
	return b_y;
}
void ball::ball_start(Graphics^ gr) {
	b_x = width / 2+block/2;
	b_y = bar_y - (2 * block);
	//初期位置にボールを描写
	create_ball(gr,b_x, b_y);
}
bool ball::rightleft() {
	if (new_lr < 0) {
		leftright = 1;
		new_lr = last_x + leftright * block;
		wall_xy->w_x = new_lr;
		return true;
	}
	else if (new_ud < 0) {
		updown = 1;
		new_ud = last_y + updown * block;
		wall_xy->w_y = new_ud;
		return true;
	}
	else if (new_ud > height - block / 2) {

		updown = -1;
		new_ud = last_y + updown * block;
		wall_xy->w_y = new_ud;
		return true;
	}
	else if (new_lr > width - block / 2) {
		leftright = -1;
		new_lr = last_x + leftright * block;
		wall_xy->w_x = new_lr;
		return true;
	}
	else {
		return false;
	}
}

bool ball::bar_judge() {
	if (bar->Contains(new_lr) && new_ud == bar_y) {
		/*Random^ rnd = gcnew Random();
		int num = rnd->Next(1, 4);*/
		if (updown == 1) {
			updown = -1;
		}
		else {
			updown = 1;
		}
		new_ud = last_y + updown * block;
		return true;
	}
	else {
		return false;
	}
}

bool ball::block_judge(Graphics^ gr) {
	if (wall_eq(walls, wall_xy)) {
		//ブロックを塗りつぶす
		gr->FillRectangle(Brushes::Bisque, new_lr, new_ud, block, block);
		gr->DrawRectangle((gcnew Pen(Color::Bisque)), new_lr, new_ud, block, block);


		reDraw(gr, new_lr, new_ud);
		//配列から消去
		walls->RemoveAt(wall_num);
		Random^ rnd = gcnew Random();
		int num = rnd->Next(1, 4);
		//跳ね返り判定
		if (updown == 1) {
			updown = -1;
		}
		else {
			updown = 1;
		}
		new_ud = last_y + updown * block;
		wall_xy->w_y = new_ud;
		return true;
	}
	else {
		return false;
	}
}

void ball::move_ball(Graphics^ gr) {

	//以前の位置を取得し、ボールを削除
	if (last_x == -1) {
		last_x = b_x;
		last_y = b_y;
	}
	delete_white(gr, last_x, last_y);

	//移動先を計算
	new_lr = last_x + leftright * block;
	new_ud = last_y + updown * block;

	wall_xy = gcnew w_xy();
	wall_xy->w_x = new_lr;
	wall_xy->w_y = new_ud;

	//移動先のif分岐処理
	//移動先が壁かバーだった場合は跳ね返る

	while (block_judge(gr) || bar_judge() || rightleft()) {
		
		bar_judge(); 
		rightleft();
		block_judge(gr);
	}

	/*if (block_check(new_lr, new_ud)) {
				//ランダムでの跳ね返り補正値
				int re = 0;
				//3パターン用意
				int hosei = (gcnew Random())->Next(0, 4);
				if (hosei == 0) {
					new_lr -= 1 * block;
				}
				else if (hosei == 1) {
					new_lr += 1 * block;
				}
				else if (hosei == 2) {
					new_ud += 1 * block;
				}
				else if (hosei == 3) {
					new_ud -= 1 * block;
				}
			}*/

	last_x = new_lr;
	last_y = new_ud;

	create_ball(gr, new_lr, new_ud);
}



void ball::reDraw(Graphics^ gr, int lr, int ud) {
	int up = ud - 1 * block;
	int down = ud + 1 * block;
	int left = lr - 1 * block;
	int right = lr + 1 * block;

	for (int i = 0; i < walls->Count; i++) {
		//上にブロックがあるかどうか
		if (walls[i]->w_x == lr && walls[i]->w_y == up) {
			//あれば、線を引く
			gr->DrawLine(Pens::Blue, lr, ud, right, ud);
		}
		//下にブロックがあるかどうか
		if (walls[i]->w_x == lr && walls[i]->w_y == down) {
			//あれば、線を引く
			gr->DrawLine(Pens::Blue, lr, down, right, down);
		}
		//左にブロックがあるかどうか
		if (walls[i]->w_x == left && walls[i]->w_y == ud) {
			//あれば、線を引く
			gr->DrawLine(Pens::Blue, lr, ud, lr, down);
		}
		//右にブロックがあるかどうか
		if (walls[i]->w_x == right && walls[i]->w_y == ud) {
			//あれば、線を引く
			gr->DrawLine(Pens::Blue, right, ud, right, down);
		}

		//なければ、そのまま、塗りつぶす
	}
}

bool ball::block_check(int bx, int by) {
	int up = bx - 1 * block;
	int down = bx + 1 * block;
	int left = by - 1 * block;
	int right = by + 1 * block;

	for (int i = 0; i < walls->Count; i++) {
		//下左右にブロックがあるかどうか
		if (walls[i]->w_x == bx && walls[i]->w_y == down) {
			MessageBox::Show("#");
		return true;
			
		}
	}
	
	return false;
}

void ball::delete_white(Graphics^ gr, int dx, int dy) {
	gr->FillEllipse(Brushes::Bisque, dx+1, dy+1, block-2, block-2);
	gr->DrawEllipse((gcnew Pen(Color::Bisque)), dx + 1, dy + 1, block - 2, block - 2);
}
void ball::create_ball(Graphics^ gr, int crx, int cry) {
	gr->FillEllipse(Brushes::Green, crx+1, cry+1, block-2, block-2);
	gr->DrawEllipse((gcnew Pen(Color::Navy)), crx + 1, cry + 1, block - 2, block - 2);
}


void ball::reflect(Graphics^ gr,int rx, int ry) {
	if (wall_eq(walls, wall_xy)) {
		//ブロックを塗りつぶす
		gr->FillRectangle(Brushes::Bisque, rx, ry, block, block);
		reDraw(gr, rx, ry);
		//配列から消去
		walls->RemoveAt(wall_num);
		//跳ね返り判定
		if (updown == 1) {
			updown = -1;
		}
		else {
			updown = 1;
		}
		ry = last_y + updown * block;
		//バーでの跳ね返り
	}
	else if (bar->Contains(rx) && ry == bar_y) {
		if (updown == 1) {
			updown = -1;
		}
		else {
			updown = 1;
		}
		ry = last_y + updown * block;
		//左右の壁の跳ね返り補正
	}
	else if (rx < 0) {
		leftright = 1;
		rx = last_x + leftright * block;
	}
	else if (ry < 0) {
		updown = 1;
		ry = last_y + updown * block;
	}
	else if (ry > height - block / 2) {

		updown = -1;
		ry = last_y + updown * block;
	}
	else if (rx > width - block / 2) {
		leftright = -1;
		rx = last_x + leftright * block;
	}
	
}