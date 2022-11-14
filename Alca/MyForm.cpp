#include "MyForm.h"

using namespace Alca;

[STAThreadAttribute]

int main() {
	Application::Run(gcnew MyForm());
	return 0;
}