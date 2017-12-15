#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/*��������� RGB � ������������� �������� ��� ������ ������ ���������*/
struct Colors {
	int R;//Red
	int G;//Green
	int B;//Blue
	friend ostream& operator << (ostream& s, Colors& my) {//����������  << 
		return cout << "Red = " << my.R << " " << "Green = " << my.G << " " << "Blue = " << my.B << " " << endl;
	}

};

/*����� Map ��� �������� ����������� � */
class Map {
public:
	int  image_x; //���������� ��������
	int  image_y;
public:
	Colors** p; // ������� ������ ��� �������� �����������
	Map(int mx, int my); // ����������� ������������ ������������ ��� ������� � ��������� ������ ����� ������
	void Load(char* fname);// �������� ����������� ����� ��������� ��� ������ � ������
	void Draw();// ���������� ����� �����  R = 170 G = 224 B = 203 � ����� ������������
	void Save(char* fname);// ���������� ����������
	void Show();//����� ������� p
	~Map();// ����������
};

Map::Map(int mx, int my) {
	image_x = mx;
	image_y = my;
	Colors C;
	C.R = 255;
	C.G = 255;
	C.B = 255;
	p = new Colors*[image_x];// ����� ������������ ��� ���������� �������
	for (int i = 0; i < image_x; i++) {
		p[i] = new Colors[image_y];// �������������� ������������ ��� �������� ���������� ��������
		for (int j = 0; j < image_y; j++) {
			p[i][j] = C; // ������������� � ������ �����
		}
	}
}


void Map::Load(char* filename) {
	char buff[10];
	FILE* file = fopen(filename, "r");//�������� �����
	for (int i = 0; i < 2; i++) {
		fscanf(file, "%c", &buff);//������������ ��������� ������� PNM-����� -> ������� ���� ���, ����� ���� ������, � � ����� ���� �������� ������
	}
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			fscanf(file, "%d", &p[i][j].R);
			fscanf(file, "%d", &p[i][j].G);
			fscanf(file, "%d", &p[i][j].B);
		}
	}
	fclose(file);//�������� �����
}

void Map::Draw() {
	Colors T;//��������� ������ ��� ����� ������ �����
	T.R = 170;
	T.G = 224;
	T.B = 203;
	Colors Image;// ��������� ������ ��������
	Image.R = 1;
	Image.G = 1;
	Image.B = 1;
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			if (p[i][j].R == T.R && p[i][j].G == T.G && p[i][j].B == T.B) { //����� � ������� �����������, ���� ������� �������, ����� ������������ ����� � �������
				p[i][j] = Image;

			}
		}
	}
}

void Map::Save(char* fname) {
	FILE* file = fopen(fname, "w");//�������� �����
	fprintf(file, "P3\n");//������ ����������� ���� PNM
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			fprintf(file, "%d %d %d\n", p[i][j].R, p[i][j].G, p[i][j].B);//���������� ����� ����������� ���������
		}
	}
	fclose(file);
}

void Map::Show() {
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			cout << p[i][j];//������ ����, ��� ���������� � ������� 
		}
	}
}

Map::~Map() {
	for (int i = 0; i < image_x; i++) { //������������ ������ � ������� ������
		delete p[i];
	}
	delete p;//������������ ������ � ������� ����������
}
