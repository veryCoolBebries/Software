#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
using namespace std;
typedef void (*sequnceGenerator)(int* array, int, int, int, int);
typedef void (*FunctionSort)(int*, int);
typedef void (*FunctionSortComparisons)(int* array, int size, int& permutations, int& comparisons);
typedef void (*FunctionSortInterimResults)(int* array, int size, int* arrayCheck, int sizeCheck);
void randSequence(int* array, int sizeOfArray, int minValue, int maxValue, int intervalLength = 0);
void selectionSort(int* array, int size);
void quickSort(int* array, int size);
void checkRuntimeFunction(FunctionSort func, string funcName, ofstream& out);
int main() {
	setlocale(LC_ALL, "ru");
	ofstream out("out.csv", ios::app);
	checkRuntimeFunction(selectionSort, "Selection Sort", out);
	checkRuntimeFunction(quickSort, "Quick Sort", out);
}
// Сортировка выбором
void selectionSort(int* array, int size) {
	for (int i = 0; i < size; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < size; j++)
			// Идём от выбранного элемента до конца
			// пока и ищем элемент меньше
		{
			if (array[j] < array[minIndex]) {
				minIndex = j;
			}
		}
		// Меняем найденный элемент с выбранным
		int temp = array[i];
		array[i] = array[minIndex];
		array[minIndex] = temp;
	}
}
// Быстрая сортировка
void quickSort(int* array, int size) {

	int left = 0;
	int right = size - 1;
	int base = array[right / 2];

	do {
		while (array[left] < base) left++;
		while (array[right] > base) right--;

		if (left <= right)
		{
			int temp = array[left];
			array[left] = array[right];
			array[right] = temp;

			left++;
			right--;
		}
	} while (left <= right);

	if (right > 0) quickSort(array, right + 1);
	if (left < size) quickSort(&array[left], size - left);
}
// Функция проверки времени работы
void checkRuntimeFunction(FunctionSort func, string funcName, ofstream& out) {
	out << endl << funcName << ";";
	cout << "Checking " << funcName << " function..." << endl << endl;
	int sizes[] = { 100,10000,1000 };
	for (int size : sizes) {
		int* array = new int[size];
		randSequence(array, size, 0, size * 10);// Заполяем массив для поиска
		out << size << ";";
		auto begin = chrono::steady_clock::now();// Засекаем время
		func(array, size);
		auto end = chrono::steady_clock::now();
		// Замеряем работу функции и выводим время работы
		out <<(chrono::duration_cast<std::chrono::microseconds>(end - begin)).count() << endl << ";";
		delete[] array;
	}
	cout << "Done! <3" << endl;
}
void randSequence(int* array, int sizeOfArray, int minValue, int maxValue, int intervalLength) {
	srand(time(NULL));
	for (size_t i = 0; i < sizeOfArray; i++)
	{
		array[i] = minValue + rand() % maxValue;
	}
}