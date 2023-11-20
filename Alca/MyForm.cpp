#include "MyForm.h"
#include"field.h"

using namespace Alca;

[STAThreadAttribute]

int main() {
	Application::Run(gcnew MyForm());
	return 0;
}

bool Alca::MyForm::ProcessDialogKey(Keys keyData)
{
	/*if (!ctrlFlag) {
		return false;
	}*/
	//キー操作を定義
	//このメソッドはプリプロセス時に呼び出されるので、これをオーバーライドする
	switch (keyData)
	{
	case Keys::Right:
		//field::setslide_dir(1);
		//b->bar_move(gr);
		//pictureBox1->Image = bmp;
		break;
	case Keys::Left:
		//field::setslide_dir(-1);
		b->bar_move(gr);
		pictureBox1->Image = bmp;
		break;
	case Keys::Enter:
		timer1->Enabled = true;

	default:
		return true;
		//return ProcessDialogKey(keyData);
		//return IsInputKey(keyData);
		break;
	}
	return true;
}

System::Void Alca::MyForm::timer1_Tick(System::Object ^ sender, System::EventArgs ^ e)
{
	b->move_ball(gr);
	pictureBox1->Image = bmp;
	return System::Void();
}
