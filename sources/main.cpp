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


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define ARRAY_SIZE WINDOW_WIDTH / 4
#define LINE_THICKNESS 4
//#define DEBUG__

void UpdateWindowImpl(sf::RectangleShape ** array, size_t size, Sort::AppEnv & environment)
{
	while (!(*environment.GetCancelled())) {
		environment.GetWindow()->clear();
/*
        Create a font and texts to display algorithm name,
        merges count and accessec count
 */
#ifndef WIN32
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
#endif
		for (size_t i = 0; i < size; i++) {
			{
				std::lock_guard<std::mutex> lock(*environment.GetLockElementMutex());
				auto tmp = (*(array + i));
				assert(environment.GetLockElement() != nullptr);
				assert(environment.GetLockElementMutex() != nullptr);
				if (*environment.GetLockElement() != -1 && (int)tmp->getPosition().x == *environment.GetLockElement())
					tmp->setFillColor(sf::Color::Red);
				else
					tmp->setFillColor(sf::Color::White);
			}
			environment.GetWindow()->draw(*(*(array + i)));
		}
		environment.GetWindow()->display();
	}
	environment.GetWindow()->setActive(false);
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
	Sort::AppEnv environment(WINDOW_WIDTH, WINDOW_HEIGHT);
	sf::RectangleShape * arr[ARRAY_SIZE];
	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		// Создаем новый прямоугольник (выделяем память)
		arr[i] = new sf::RectangleShape(sf::Vector2f(LINE_THICKNESS, -std::rand() % WINDOW_HEIGHT));
		arr[i]->setFillColor(sf::Color::White);
		arr[i]->setPosition(i * LINE_THICKNESS, WINDOW_HEIGHT);
	}
	environment.GetWindow()->setActive(false);
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
        for (auto alg : algs) {
            _sortThread = std::thread(&Sort::Algorithm::Sort, alg, arr, ARRAY_SIZE);
            if (_sortThread.joinable())
                _sortThread.join();
            RefreshArray(arr, ARRAY_SIZE);
        }
        getchar();
        break;
	}
	*environment.GetCancelled() = true;
	if (_renderThread.joinable())
		_renderThread.join();

	// Само собой нужно почистить память
	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		delete(arr[i]);
	}
    return 0;
}
