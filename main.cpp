#include "Map.h"

int main() {
	Map* Image = new Map(950, 616);
	Image->Load("mai.pnm");
	Image->Draw();
	Image->Save("image.pnm");
	Image->Show();
	delete Image;
}
