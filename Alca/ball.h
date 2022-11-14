#pragma once
#include"field.h"

namespace Alca {

	ref class ball:public field
	{
	private:
		int size = block;
		//ボールのx,y座標
		int b_x=-1;
		int b_y=-1;
		int last_x=-1;
		int last_y=-1;
		//進行方向
		//上下
		int updown=1;
		int leftright=1;
		w_xy^ wall_xy;
		int new_lr;
		int new_ud;
		bool refrect;
	public:
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
		void ball_start(Graphics^ gr);
		void move_ball(Graphics^ gr);
		void create_ball(Graphics^ gr, int x, int y);
		void delete_white(Graphics^ gr, int d_x, int d_y);
		void reDraw(Graphics^ gr, int lr, int ud);
		bool block_check(int bx, int by);
		void reflect(Graphics^ gr,int rx, int ry);
		//void rightleft();
		//void bar_judge();
		//void block_judge(Graphics^ gr);
		bool rightleft();
		bool bar_judge();
		bool block_judge(Graphics^ gr);
	};

}