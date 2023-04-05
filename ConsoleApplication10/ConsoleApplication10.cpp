
#include <iostream>
class Matrix //создаём класс Matrix
{
	int sizeY; //создаём переменные в  привате
	int sizeX;
	int* data;
	int index2D(int y, int x) //конструктор с параметрами 
		const {
		return y * sizeX + x;
	}
	int index2D(int y, int x, int sizeXP)
		const {
		return y * sizeXP + x;
	}
public: //публичное
	Matrix(int sizeYP, int sizeXP) //создаём конструктор по умолчанию 
		: sizeY{ sizeYP }, sizeX{ sizeXP },
		data{ new int[sizeYP * sizeXP] } {}

	int operator()(int y, int x)//перегрузка оператора 
		const {
		return *(data + index2D(y, x));//возвращает данные 
	}

	int& operator()(int y, int x) //перегрузка оператора 
	{
		return *(data + index2D(y, x));
	}

	void deleteColumn(int columnPos)
	{
		--sizeX;
		int* newData{ new int[sizeY * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)//создаём цикл for в котором ещё цикл - не понял 
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x)) =
					*(data + index2D(y, x + (x >=
						columnPos)));
			}
		}
		delete[] data; //удаляем  data 
		data = newData;//создаём новые данные
	}
	void addColumn(int columnPos, int* newCol = nullptr)         //
	{                                                            //
		int* newData{ new int[sizeY * (sizeX + 1)] } ;           //
		for (int y{ 0 }; y < sizeY; ++y)                         //
		{                                                        //
			for (int x{ 0 }; x < sizeX; ++x)                     // эту часть не понял 
			{                                                    //
				*(newData + index2D(y, x + (x >= columnPos),     //
					sizeX + 1)) = *(data + index2D(y, x));       //
			}                                                    //
			*(newData + index2D(y, columnPos, sizeX + 1)) =      //
				newCol ? *(newCol + y) : 0;                      //
		}
		delete[] data;//удаляем  data 
		data = newData;//создаём новые данные
		++sizeX;
	}
	void deleteRow(int rowPos)
	{
		--sizeY;
		int* newData{ new int[sizeY * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x)) =
					*(data + index2D(y + (y >= rowPos),
						x));
			}
		}
		delete[] data;//удаляем  data 
		data = newData; //создаём новые данные
	}
	void addRow(int rowPos, int* newRow = nullptr)
	{
		int* newData{ new int[(sizeY + 1) * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y + (y >= rowPos), x)) =  //не понял 
					*(data + index2D(y, x));
			}
		}
		for (int x{ 0 }; x < sizeX; ++x)
		{
			*(newData + index2D(rowPos, x)) =
				newRow ? *(newRow + x) : 0;
		}
		delete[] data; //удаляем  data 
		data = newData;//создаём новые данные
		++sizeY;
	}
	void print()const
	{
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				std::cout << (*this)(y, x) << '\t';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
	~Matrix() { delete[] data; } // деструктор 
};
int main()
{

#define USER_INPUT 0;
	int rows{ 3 };
	int columns{ 3 };
	int counter{ 1 };
#if USER_INPUT == 1
	std::cout << "Enter matrix rows count\n"; //выводим на экран
	std::cin >> rows;//считываем с клавиатуры
	std::cout << "Enter matrix columns count\n";//выводим на экран
	std::cin >> columns;//считываем с клавиатуры
#endif
	Matrix matrix{ rows, columns };
	for (int y{ 0 }; y < rows; ++y)
	{
		for (int x{ 0 }; x < columns; ++x) //не понял 
		{
			matrix(y, x) = counter++;
		}
	}
	matrix.print();
	std::cout << std::endl;

	matrix.deleteColumn(2);
	matrix.print();
	std::cout << std::endl;

	int* newColumn{ new int[columns] {11,22,33} };
	matrix.addColumn(0, newColumn);
	matrix.print();
	std::cout << std::endl;

	matrix.deleteRow(2);
	matrix.print();
	std::cout << std::endl;

	int* newRow{ new int[rows] {111,222,333} };
	matrix.addRow(2, newRow);
	matrix.print();
	std::cout << std::endl;

	delete[] newRow; //удаляем  newRow и newColumn
	delete[] newColumn;
}