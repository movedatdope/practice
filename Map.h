#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/*Структура RGB и перегруженный оператор для печати данных структуры*/
struct Colors {
	int R;//Red
	int G;//Green
	int B;//Blue
	friend ostream& operator << (ostream& s, Colors& my) {//Перегрузка  << 
		return cout << "Red = " << my.R << " " << "Green = " << my.G << " " << "Blue = " << my.B << " " << endl;
	}

};

/*Класс Map для загрузки изображения и */
class Map {
public:
	int  image_x; //Разрешение картинки
	int  image_y;
public:
	Colors** p; // Двойной массив для хранения изображения
	Map(int mx, int my); // Конструктор обеспечивает пространство для массива и заполняет массив белым цветом
	void Load(char* fname);// Загрузка изображения затем помещение его данных в массив
	void Draw();// Нахождение домов цвета  R = 170 G = 224 B = 203 и затем закрашивание
	void Save(char* fname);// Сохранение результата
	void Show();//вывод массива p
	~Map();// Деструктор
};

Map::Map(int mx, int my) {
	image_x = mx;
	image_y = my;
	Colors C;
	C.R = 255;
	C.G = 255;
	C.B = 255;
	p = new Colors*[image_x];// новое пространство для указателей массива
	for (int i = 0; i < image_x; i++) {
		p[i] = new Colors[image_y];// Предоставление пространства для массивов указателей массивов
		for (int j = 0; j < image_y; j++) {
			p[i][j] = C; // Приравнивание к белому цвету
		}
	}
}


void Map::Load(char* filename) {
	char buff[10];
	FILE* file = fopen(filename, "r");//Открытие файла
	for (int i = 0; i < 2; i++) {
		fscanf(file, "%c", &buff);//Сканирование заголовка формата PNM-файла -> сначала идет тип, затем идет размер, и в конце есть максимум цветов
	}
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			fscanf(file, "%d", &p[i][j].R);
			fscanf(file, "%d", &p[i][j].G);
			fscanf(file, "%d", &p[i][j].B);
		}
	}
	fclose(file);//Закрытие файла
}

void Map::Draw() {
	Colors T;//Структура цветов для домов одного цвета
	T.R = 170;
	T.G = 224;
	T.B = 203;
	Colors Image;// Структура черных пикселей
	Image.R = 1;
	Image.G = 1;
	Image.B = 1;
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			if (p[i][j].R == T.R && p[i][j].G == T.G && p[i][j].B == T.B) { //Поиск в массиве изображения, если условие истинно, тогда приравнивают цвета к черному
				p[i][j] = Image;

			}
		}
	}
}

void Map::Save(char* fname) {
	FILE* file = fopen(fname, "w");//Открытие файла
	fprintf(file, "P3\n");//Печать изображения типа PNM
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			fprintf(file, "%d %d %d\n", p[i][j].R, p[i][j].G, p[i][j].B);//Заполнение файла результатом рисования
		}
	}
	fclose(file);
}

void Map::Show() {
	for (int i = 0; i < image_x; i++) {
		for (int j = 0; j < image_y; j++) {
			cout << p[i][j];//Печать того, что содержится в массиве 
		}
	}
}

Map::~Map() {
	for (int i = 0; i < image_x; i++) { //Освобождение памяти в массиве данных
		delete p[i];
	}
	delete p;//Освобождение памяти в массиве указателей
}
