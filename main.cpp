// ConsoleApplication9.cpp : Defines the entry point for the console application.
//
#include "Map.h"

int main()
{
	Map *Image;
	Image = new Map(950, 616);
	Image->Load("mai.pnm");
	Image->Draw();
	Image->Save("image.pnm");
	Image->Show();
}

