#include <stdafx.h>
#include <Graphics.hpp>
#include <SortAlgorithm.h>
#include <future>
#include <vector>
#include <filesystem>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <windows.h>
#endif


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1920
#define ARRAY_SIZE WINDOW_WIDTH / 4
#define LINE_THICKNESS 4
//#define DEBUG__

void UpdateWindowImpl(bool * cancell, sf::RenderWindow * window, sf::RectangleShape ** array, size_t size, std::mutex * _lock, int * lockElement)
{
	while (!(*cancell)) {
		window->clear();
/*
        Create a font and texts to display algorithm name,
        merges count and accessec count
 */
        sf::Font font;
        if (font.loadFromFile("fonts/ArialRegular.ttf")) {
            sf::Text algorihmName;
            algorihmName.setFont(font);
            algorihmName.setCharacterSize(WINDOW_HEIGHT * 0.04);
            algorihmName.setFillColor(sf::Color::Red);
            algorihmName.setStyle(sf::Text::Bold);
            algorihmName.setString("Bubble sort");
            sf::Text mergesCount;
            mergesCount.setFont(font);
            mergesCount.setCharacterSize(WINDOW_WIDTH * 0.02);
            mergesCount.setFillColor(sf::Color::Red);
            mergesCount.setStyle(sf::Text::Underlined);
            mergesCount.setString("10000");
            mergesCount.setPosition(sf::Vector2f(algorihmName.getPosition().x, algorihmName.getPosition().y + algorihmName.getCharacterSize() + 10));
            sf::Text accessesCount;
            accessesCount.setFont(font);
            accessesCount.setCharacterSize(WINDOW_WIDTH * 0.02);
            accessesCount.setFillColor(sf::Color::Red);
            accessesCount.setStyle(sf::Text::Underlined);
            accessesCount.setString("99999");
            accessesCount.setPosition(sf::Vector2f(algorihmName.getPosition().x, mergesCount.getPosition().y + mergesCount.getCharacterSize() + 10));
            window->draw(algorihmName);
            window->draw(mergesCount);
            window->draw(accessesCount);
        }
		for (size_t i = 0; i < size; i++) {
			{
				std::lock_guard<std::mutex> lock(*_lock);
				auto tmp = (*(array + i));
				assert(lockElement != nullptr);
				assert(_lock != nullptr);
				if (*lockElement != -1 && (int)tmp->getPosition().x == *lockElement)
					tmp->setFillColor(sf::Color::Red);
				else
					tmp->setFillColor(sf::Color::White);
			}
			window->draw(*(*(array + i)));
		}
		window->display();
	}
	window->setActive(false);
}

void RefreshArray(sf::RectangleShape ** array, size_t size) {
	for (size_t i = 0; i < size; i++)
		array[i]->setSize(sf::Vector2f(1, -std::rand() % WINDOW_HEIGHT));
}

int main(void)
{
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

	std::thread _renderThread;
	std::thread _sortThread;
	std::mutex currentElementLock;
	bool shouldBeCancell = false;
	int currentElement = -1;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sort window", sf::Style::Close);
	sf::RectangleShape * arr[ARRAY_SIZE];
	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		// Создаем новый прямоугольник (выделяем память)
		arr[i] = new sf::RectangleShape(sf::Vector2f(LINE_THICKNESS, -std::rand() % WINDOW_HEIGHT));
		arr[i]->setFillColor(sf::Color::White);
		arr[i]->setPosition(i * LINE_THICKNESS, WINDOW_HEIGHT);
	}
	window.setActive(false);
	_renderThread = std::thread(&UpdateWindowImpl, &shouldBeCancell, &window, arr, (size_t) ARRAY_SIZE, &currentElementLock, &currentElement);
	while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                case sf::Event::Resized: {
                    sf::Vector2u size;
                    size.x = evnt.size.width;
                    size.y = evnt.size.height;
                    window.setSize(size);
                    break;
                }
                default:
                    break;
            }
        }
        // Create base class vector and add child classes realization into it
        std::vector<Sort::Algorithm *> algs = std::vector<Sort::Algorithm *>();
		Sort::BubbleSort bubble = Sort::BubbleSort(&currentElementLock, &currentElement);
        algs.push_back(static_cast< Sort::Algorithm * >(&bubble));
        Sort::QuickSort quick = Sort::QuickSort(&currentElementLock, &currentElement);
        algs.push_back(static_cast< Sort::Algorithm * >(&quick));
		Sort::ShellSort shell = Sort::ShellSort(&currentElementLock, &currentElement);
        algs.push_back(static_cast< Sort::Algorithm * >(&shell));
		Sort::GnomeSort gnome = Sort::GnomeSort(&currentElementLock, &currentElement);
        algs.push_back(static_cast< Sort::Algorithm * >(&gnome));
        for (auto alg : algs) {
            _sortThread = std::thread(&Sort::Algorithm::Sort, alg, arr, ARRAY_SIZE);
            if (_sortThread.joinable())
                _sortThread.join();
            RefreshArray(arr, ARRAY_SIZE);
        }
        getchar();
        break;
	}
	shouldBeCancell = true;
	if (_renderThread.joinable())
		_renderThread.join();

	// Само собой нужно почистить память
	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		delete(arr[i]);
	}
    return 0;
}
