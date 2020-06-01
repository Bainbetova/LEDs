// LEDs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Баинбетова Владлена В.
// Программа LEDs
// Основной модуль
// 12.05.2019
// Используется openCV версии 4.1.0

#include "pch.h"

/* Функция для проверки фотографии */
bool ValidatePhoto(const String);

/* Главная функция программы main *
/* Входные параметры: отстутсвуют 
   Возвращаемое значение: 
		1 - корректное завершение выполнения программы */
int main()
{
	// проверяем 1 фото - good_0.png
	if (ValidatePhoto("..//..//photo//good_0.png")) { // для отладки путь всех файлов заменить на - ..//photo//good_0.png
		cout << "Image 'good_0.png' is correct.\n";
	} else {
		cout << "Image 'good_0.png' is not correct.\n";
	}

	// проверяем 2 фото - good_1.png
	if (ValidatePhoto("..//..//photo//good_1.png")) {
		cout << "Image 'good_1.png' is correct.\n";
	} else {
		cout << "Image 'good_1.png' is not correct.\n";
	}

	// проверяем 3 фото - good_2.png
	if (ValidatePhoto("..//..//photo//good_2.png")) {
		cout << "Image 'good_2.png' is correct.\n";
	} else {
		cout << "Image 'good_2.png' is not correct.\n";
	}

	// проверяем 4 фото - good_3.png
	if (ValidatePhoto("..//..//photo//good_3.png")) {
		cout << "Image 'good_3.png' is correct.\n";
	} else {
		cout << "Image 'good_3.png' is not correct.\n";
	}

	// проверяем 5 фото - good_4.png
	if (ValidatePhoto("..//..//photo//good_4.png")) {
		cout << "Image 'good_4.png' is correct.\n";
	} else {
		cout << "Image 'good_4.png' is not correct.\n";
	}

	// проверяем 6 фото - good_5.png
	if (ValidatePhoto("..//..//photo//good_5.png")) {
		cout << "Image 'good_5.png' is correct.\n";
	} else {
		cout << "Image 'good_5.png' is not correct.\n";
	}

	// проверяем 7 фото - bad.png
	if (ValidatePhoto("..//..//photo//bad.png")) {
		cout << "Image 'bad.png' is correct.\n";
	} else {
		cout << "Image 'bad.png' is not correct.\n";
	}
	_getch();

	return 1;
}

/* Функция ValidatePhoto */
/* Назначение:
		проверка фотографии на корректность 
   Входной параметр: 
		name - наименование проверяемого файла 
   Возвращаемые значения: 
		true - было найдено 4 светодиода на изображении
		false - не было найдено 4 светодиода на изображении */
bool ValidatePhoto(const String name) {
	/* Объявление переменных */
	Mat src; // исходное изображение
	Mat src1; // дубликат изображения, чтобы не повредить исходное
	vector<Vec3f> circles; // обнаруженные окружности

	/* Открытие изображения */
	src = imread(name); // исходное изображение

	/* Проверка корректности файла */
	if (!src.data) {
		cout << "Image file not found.\n"; // невозможно открыть файл.
		return 1;
	}

	/* Сглаживание изображения */
	cvtColor(src, src1, COLOR_BGR2GRAY);
	medianBlur(src1, src1, 5);	
	
	/* Поиск светодиодов, используя алгоритм Хафа */
	// src1 - изображение, в котором производится поиск светодиодов
	// circles - переменная, в которую будут записаны окружности
	// HOUGH_GRADIENT - метод поиска
	// разрешение аккумулятора, в который будут складываться результаты преобразования Хафа (потенциальные центры окружностей)
	// src1.rows / 16 - минимальная дистанция между обнаруженными центрами
	// 120 - значение, используемое в процедуре выделения связных границ Кэнни (чем больше этот параметр, тем меньше шума попадёт в результат)
	// 20 - порог для обнаружения центра 
	HoughCircles(src1, circles, HOUGH_GRADIENT, 1, src1.rows / 16, 120, 20); 	

	/* Проверка количества светодиодов */
	if (circles.size() == 4) {
		return true; // были найдены все 4 светодиода
	} else {
		return false; // светодиодов не 4
	}	
}