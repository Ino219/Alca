#include "field.h"

using namespace Alca;
using namespace System::Windows::Forms;
using namespace System::Drawing;



field::field() {
}
field::field(Graphics^ gr) {
	create_wall(gr);
	create_bar(gr);
}
void field::create_wall(Graphics^ gr) {
	
	
	//�n�_y���̌v�Z
	int start = height - wall_column * block;
	walls = gcnew List<w_xy^>;
	//y�����[�v
	for (int n = 0; n < wall_column; n++) {
		int t_s = start + n * block;
		//x�����[�v
		for (int i = 0; i < line; i++) {
			int t_l = i * block;
			w_xy^ t_xy=gcnew w_xy();
			t_xy->w_x = t_l;
			t_xy->w_y = t_s;
			walls->Add(t_xy);
			create_box(gr, t_l, t_s);
		}
	}
}
void field::create_box(Graphics^ gr, int x, int y) {
	gr->FillRectangle(Brushes::Green, x, y, block, block);
	gr->DrawRectangle(Pens::Blue, x, y, block, block);
	
}
void field::create_bar(Graphics^ gr) {
	bar_length = 8;
	//�o�[�̃}�X����}��
	bar = gcnew List<int>;
	//�J�n�ʒu��x���W
	bar_start = (line - bar_length) / 2*block;
	for (int i = 0; i < bar_length; i++) {
		//�ʒu�̕␳��x���W�̊m��
		int temp_s = bar_start+(i*block);
		//bar[i] = temp_s;
		bar->Add(temp_s);
		//create_box(gr, temp_s, bar_y);
		gr->FillRectangle(Brushes::Green, temp_s, bar_y, block, block);
	}
}

bool field::wall_eq(List<w_xy^>^ li, w_xy^ data) {
	for (int i = 0; i < li->Count; i++) {
		if (li[i]->w_x == data->w_x&&li[i]->w_y == data->w_y) {
			wall_num = i;
			return true;
		}
	}
	return false;
}

void field::bar_delete(Graphics^ gr) {
	gr->FillRectangle(Brushes::Bisque, bar[bar->Count-1], bar_y, block, block);
	bar->RemoveAt(bar->Count-1);
}

void field::bar_move(Graphics^ gr) {
	//UI�̍폜
	for (int i = 0; i < bar->Count; i++) {
		gr->FillRectangle(Brushes::Bisque, bar[i], bar_y, block, block);
	}
	//�f�[�^�̍폜�ƐV��
	bar->Clear();
	bar = gcnew List<int>;
	//�܂�Ԃ��̔��]����
	if (slide_bar == -1 && bar_start-1*block < 0) {
		slide_bar = 1;
	}
	else if (slide_bar == 1 && bar_start+(bar_length+1)*block > width) {
		slide_bar = -1;
	}
	//�o�[�̃X�^�[�g�ʒu�𒲐�
	bar_start += slide_bar*block;
	for (int i = 0; i < bar_length; i++) {
		//�ʒu�̕␳��x���W�̊m��
		int temp_s = bar_start + (i*block);
		bar->Add(temp_s);
		gr->FillRectangle(Brushes::Green, temp_s, bar_y, block, block);
	}
}