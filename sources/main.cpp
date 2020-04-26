/**
    @file
	Основной файл программы.
	Здесь происходит создание окна а также потока для его отрисовки;
	Содание объектов алгоритмов сортировки и поочередного их запуска;
    @author
	Zyukov Alexander Vadimovich (ellusive)
    @date
	2020 April 25
*/
#include <stdafx.h>
#include <Graphics.hpp>
#include <SortAlgorithm.h>
#include <AppEnv.h>
#include <future>
#include <vector>
#include <filesystem>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <windows.h>
#endif


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define LINE_THICKNESS 8
#define ARRAY_SIZE WINDOW_WIDTH / LINE_THICKNESS
//#define DEBUG__

/**
    Функция для отрисовки массива элементов в окне программы
*/
void UpdateWindowImpl(sf::RectangleShape ** array, size_t size, Sort::AppEnv & environment)
{
	while (!(*environment.GetCancelled())) {
		environment.GetWindow()->clear();
/*
        Create a font and texts to display algorithm name,
        merges count and accessec count
 */
#ifndef WIN32
	std::string internalAlgName;
	std::string internalMergeCount;
	std::string internalAccessCount;
	{
		std::lock_guard< std::mutex > lock(*environment.GetCurrentAlgMutex());
		internalAlgName = std::string(environment.GetCurrentAlgName());
		internalMergeCount = std::to_string(*environment.GetCurrentMergeCount());
		internalAccessCount = std::to_string(*environment.GetCurrentAccessCount());
	}
        sf::Font font;
        if (font.loadFromFile("fonts/ArialRegular.ttf")) {
            sf::Text algorihmName;
            algorihmName.setFont(font);
            algorihmName.setCharacterSize(WINDOW_HEIGHT * 0.04);
            algorihmName.setFillColor(sf::Color::Cyan);
            algorihmName.setStyle(sf::Text::Bold);
            algorihmName.setString(internalAlgName.c_str());
            sf::Text mergesCount;
            mergesCount.setFont(font);
            mergesCount.setCharacterSize(WINDOW_WIDTH * 0.02);
            mergesCount.setFillColor(sf::Color::Cyan);
            mergesCount.setStyle(sf::Text::Bold);
            std::string tmpStr = std::string("Merges count: " + internalMergeCount);
            mergesCount.setString(tmpStr);
            mergesCount.setPosition(sf::Vector2f(algorihmName.getPosition().x, algorihmName.getPosition().y + algorihmName.getCharacterSize() + 10));
            sf::Text accessesCount;
            accessesCount.setFont(font);
            accessesCount.setCharacterSize(WINDOW_WIDTH * 0.02);
            accessesCount.setFillColor(sf::Color::Cyan);
            accessesCount.setStyle(sf::Text::Bold);
    	    tmpStr = std::string("Accesses count: " + internalAccessCount);
            accessesCount.setString(tmpStr);
            accessesCount.setPosition(sf::Vector2f(algorihmName.getPosition().x, mergesCount.getPosition().y + mergesCount.getCharacterSize() + 10));
            environment.GetWindow()->draw(algorihmName);
            environment.GetWindow()->draw(mergesCount);
            environment.GetWindow()->draw(accessesCount);
        }
#endif
		// По очереди перебираем все элементы массива и добавляем их на отрисовку
		for (size_t i = 0; i < size; i++) {
			{
				// Обязательно должен быть мьютекс для доступа к текущему элементу
				// сортировки
				assert(environment.GetLockElementMutex() != nullptr);
				std::lock_guard<std::mutex> lock(*environment.GetLockElementMutex());
				auto tmp = (*(array + i));
				// Обязательно должен быть указатель на текущий элемент сортировки
				assert(environment.GetLockElement() != nullptr);
				// Проверяем нужно ли красить линию красным (если этот элемент сейчас в обработке)
				if (*environment.GetLockElement() != -1 && (int)tmp->getPosition().x == *environment.GetLockElement())
					tmp->setFillColor(sf::Color::Red);
				else
					tmp->setFillColor(sf::Color::White);
			}
			// Рисуем линию в окне
			environment.GetWindow()->draw(*(*(array + i)));
		}
		// Отображаем все элементы из буффера в окно
		environment.GetWindow()->display();
	}
    // Отдаем управление окном родительскому потоку
    environment.GetWindow()->setActive(false);
}

/**
    Функция для обновления рандомных значений массива
*/
void RefreshArray(sf::RectangleShape ** array, size_t size) {
	for (size_t i = 0; i < size; i++)
		// Добавляем линию с рандомной высотой в пределах окна
		array[i]->setSize(sf::Vector2f(1, -std::rand() % WINDOW_HEIGHT));
}

int main(void)
{
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif
	// Поток для отрисовки окна
	std::thread _renderThread;
	// Поток для сортировки массива
	std::thread _sortThread;
	// Окружение приложения
	Sort::AppEnv environment(WINDOW_WIDTH, WINDOW_HEIGHT);
	// Массив значений
	sf::RectangleShape * arr[ARRAY_SIZE];
	// Заполняем массив рандомными (в пределах высоты окна) значениями
	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		// Создаем новый прямоугольник (выделяем память)
		arr[i] = new sf::RectangleShape(sf::Vector2f(LINE_THICKNESS, -std::rand() % WINDOW_HEIGHT));
		std::cout << arr[i]->getSize().y << " ";
		arr[i]->setFillColor(sf::Color::White);
		// Указываем положение с учетом толщины линии
		arr[i]->setPosition(i * LINE_THICKNESS, WINDOW_HEIGHT);
	}
	// Отдаем управление окном в поток для отрисовки
	environment.GetWindow()->setActive(false);
	// Создаем и запускаем поток для отрисовки окна
	_renderThread = std::thread(&UpdateWindowImpl, arr, (size_t) ARRAY_SIZE, std::ref(environment));
	while (environment.GetWindow()->isOpen()) {
    	    sf::Event evnt;
	    while (environment.GetWindow()->pollEvent(evnt)) {
	    switch (evnt.type) {
		case sf::Event::Closed: {
		    environment.GetWindow()->close();
                    break;
                }
                case sf::Event::Resized: {
                    sf::Vector2u size;
                    size.x = evnt.size.width;
                    size.y = evnt.size.height;
		    environment.GetWindow()->setSize(size);
                    break;
                }
                default:
                    break;
            }
        }
        // Create base class vector and add child classes realization into it
        std::vector<Sort::Algorithm *> algs = std::vector<Sort::Algorithm *>();
		Sort::BubbleSort bubble = Sort::BubbleSort(&environment);
        algs.push_back(static_cast< Sort::Algorithm * >(&bubble));
        Sort::QuickSort quick = Sort::QuickSort(&environment);
        algs.push_back(static_cast< Sort::Algorithm * >(&quick));
		Sort::ShellSort shell = Sort::ShellSort(&environment);
        algs.push_back(static_cast< Sort::Algorithm * >(&shell));
		Sort::GnomeSort gnome = Sort::GnomeSort(&environment);
        algs.push_back(static_cast< Sort::Algorithm * >(&gnome));
    		Sort::InsertionSort insertion = Sort::InsertionSort(&environment);
    	algs.push_back(static_cast< Sort::Algorithm * >(&insertion));
    		Sort::TreeSort tree = Sort::TreeSort(&environment);
    	algs.push_back(static_cast< Sort::Algorithm * >(&tree));
	// По очереди запускаем все алгоритмы из вектора
        for (auto alg : algs) {
            _sortThread = std::thread(&Sort::Algorithm::Sort, alg, arr, ARRAY_SIZE);
            if (_sortThread.joinable())
                _sortThread.join();
                // Перемешиваем массив
	    std::this_thread::sleep_for(std::chrono::milliseconds(300));
            RefreshArray(arr, ARRAY_SIZE);
        }
        break;
	}
	*environment.GetCancelled() = true;
	// Дожидаемся пока завершится поток для отрисовки
	if (_renderThread.joinable())
		_renderThread.join();

	// Само собой нужно почистить память
	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		delete(arr[i]);
	}
    return 0;
}
