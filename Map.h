#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/*Struct for RGB Colors and overloaded operator for printing struct data*/
struct Colors {
	int R;//Red color
	int G;//Green color
	int B;//Blue color
	friend ostream& operator << (ostream& s, Colors& my) {//Overloading the << operator for struct color
		return cout << "Red = " << my.R << " " << "Green = " << my.G << " " << "Blue = " << my.B << " " << endl;
	}

};

/*Class Map for uploading an image and painting out a rectangle then savith the result*/
class Map {
public:
	int  image_x; //Image resolution
	int  image_y;
public:
	Colors** p; // Creating an double array to store an image
	Map(int mx, int my); // Constructor to provide space for the array and fill array up with white color
	void Load(char* fname);// Loading an image then place its data to the array
	void Draw();// Findig houses with the color of R = 170 G = 224 B = 203 and then painting them out
	void Save(char* fname);// Saving the result
	void Show();//printing whats contained in the array p 
	~Map();// Destrucor for releasing the stored data
};

Map::Map(int mx, int my) {
	image_x = mx;
	image_y = my;
	Colors C;
	C.R = 255;
	C.G = 255;
	C.B = 255;
	p = new Colors*[image_x];// Gathering the new space for the pointers of array
	for (int i = 0; i < image_x; i++) {
		p[i] = new Colors[image_y];// Providing the space for the arrays of the pointers of arrays
		for (int j = 0; j < image_y; j++) {
			p[i][j] = C; // Equating the white color to the colors
		}
	}
}


void Map::Load(char* filename) {
	char buff[15];
	FILE* file = fopen(filename, "r");//Openning the file
	for (int i = 0; i < 15; i++) {
		fscanf(file, "%c", &buff);//Scaning the header of the PNM File format -> first goes the type then goes the size and in the end theres a maximum of colors
	}
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			fscanf(file, "%d", &p[i][j].R);
			fscanf(file, "%d", &p[i][j].G);
			fscanf(file, "%d", &p[i][j].B);
		}
	}
	fclose(file);//Closing the file
}

void Map::Draw() {
 // - fist corner;
	Colors T;//Struct of colors for the houses with the same color
		T.R = 170;
		T.G = 224;
		T.B = 203;
	Colors Image;// Struct of black pixel
		Image.R = 1;
		Image.G = 1;
		Image.B = 1;
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			if (p[i][j].R == T.R && p[i][j].G == T.G && p[i][j].B == T.B) { //Searching in the array of Image if condition is true then equate the colors to the black
				p[i][j] = Image;

			}
		}
	}
}

void Map::Save(char* fname) {
	FILE* file = fopen(fname, "w");//Openning the file
	fprintf(file, "P3\n950 616\n255\n");//Printing the type of PNM image;
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			fprintf(file, "%d %d %d\n", p[i][j].R, p[i][j].G, p[i][j].B);//Filling the file with the result of drawing
		}
	}
	fclose(file);//Closing the file
}

void Map::Show() {
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			cout << p[i][j];//Printig what's contained in the array 
		}
	}
}

Map::~Map() {
	for (int i = 0; i < image_x; i++) { 
	//Freeing the memory off in the array of data
	   delete p[i];
	}
	delete[] p;//Freeing the memory off in the array of pointers
}
