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
	//�����ʒu�Ƀ{�[����`��
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
		//�u���b�N��h��Ԃ�
		gr->FillRectangle(Brushes::Bisque, new_lr, new_ud, block, block);
		gr->DrawRectangle((gcnew Pen(Color::Bisque)), new_lr, new_ud, block, block);


		reDraw(gr, new_lr, new_ud);
		//�z�񂩂����
		walls->RemoveAt(wall_num);
		Random^ rnd = gcnew Random();
		int num = rnd->Next(1, 4);
		//���˕Ԃ蔻��
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

	//�ȑO�̈ʒu���擾���A�{�[�����폜
	if (last_x == -1) {
		last_x = b_x;
		last_y = b_y;
	}
	delete_white(gr, last_x, last_y);

	//�ړ�����v�Z
	new_lr = last_x + leftright * block;
	new_ud = last_y + updown * block;

	wall_xy = gcnew w_xy();
	wall_xy->w_x = new_lr;
	wall_xy->w_y = new_ud;

	//�ړ����if���򏈗�
	//�ړ��悪�ǂ��o�[�������ꍇ�͒��˕Ԃ�

	while (block_judge(gr) || bar_judge() || rightleft()) {
		
		bar_judge(); 
		rightleft();
		block_judge(gr);
	}

	/*if (block_check(new_lr, new_ud)) {
				//�����_���ł̒��˕Ԃ�␳�l
				int re = 0;
				//3�p�^�[���p��
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
		//��Ƀu���b�N�����邩�ǂ���
		if (walls[i]->w_x == lr && walls[i]->w_y == up) {
			//����΁A��������
			gr->DrawLine(Pens::Blue, lr, ud, right, ud);
		}
		//���Ƀu���b�N�����邩�ǂ���
		if (walls[i]->w_x == lr && walls[i]->w_y == down) {
			//����΁A��������
			gr->DrawLine(Pens::Blue, lr, down, right, down);
		}
		//���Ƀu���b�N�����邩�ǂ���
		if (walls[i]->w_x == left && walls[i]->w_y == ud) {
			//����΁A��������
			gr->DrawLine(Pens::Blue, lr, ud, lr, down);
		}
		//�E�Ƀu���b�N�����邩�ǂ���
		if (walls[i]->w_x == right && walls[i]->w_y == ud) {
			//����΁A��������
			gr->DrawLine(Pens::Blue, right, ud, right, down);
		}

		//�Ȃ���΁A���̂܂܁A�h��Ԃ�
	}
}

bool ball::block_check(int bx, int by) {
	int up = bx - 1 * block;
	int down = bx + 1 * block;
	int left = by - 1 * block;
	int right = by + 1 * block;

	for (int i = 0; i < walls->Count; i++) {
		//�����E�Ƀu���b�N�����邩�ǂ���
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
		//�u���b�N��h��Ԃ�
		gr->FillRectangle(Brushes::Bisque, rx, ry, block, block);
		reDraw(gr, rx, ry);
		//�z�񂩂����
		walls->RemoveAt(wall_num);
		//���˕Ԃ蔻��
		if (updown == 1) {
			updown = -1;
		}
		else {
			updown = 1;
		}
		ry = last_y + updown * block;
		//�o�[�ł̒��˕Ԃ�
	}
	else if (bar->Contains(rx) && ry == bar_y) {
		if (updown == 1) {
			updown = -1;
		}
		else {
			updown = 1;
		}
		ry = last_y + updown * block;
		//���E�̕ǂ̒��˕Ԃ�␳
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