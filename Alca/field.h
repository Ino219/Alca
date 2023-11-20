#pragma once

namespace Alca {

	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	ref class w_xy {
	public:
		int w_x;
		int w_y;
	};

	ref class field
	{
	protected:
		const int width=150;
		const int height = 200;
		const int block = 10;
		//1�s���̃}�X��
		int line = width / block;
		//��񕪂̃}�X��
		int column = height / block;

		//�o�[�̍��W�z��
		List<int>^ bar;
		//bar��y���W
		const int bar_y=height-30;
		//�ǂ̍��W�z��
		List<w_xy^>^ walls;
		//int wall_column = 3;
		int wall_column = 5;

		//�o�[�̒���
		int bar_length;
		int wall_num;
		//�o�[�̊J�n�ʒu
		int bar_start;
		//�E�ɓ������A���ɓ�����
		static int slide_bar=-1;
	public:
		field();
		field(Graphics^ gr);
		void create_box(Graphics^ gr,int cx, int cy);
		void create_bar(Graphics^ gr);
		void create_wall(Graphics^ gr);
		bool wall_eq(List<w_xy^>^ li, w_xy^ data);
		void bar_delete(Graphics^gr);
		void bar_move(Graphics^ gr);
		static void setslide_dir(int dir);
	};

	

}
