#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <cassert>
#include <vector>
#include <Graphics.hpp>

void DrawArrayOnScreen(sf::RenderWindow & window, sf::Drawable ** array, size_t count);

void SwapTwoRect(sf::RenderWindow & window, sf::RectangleShape & firstShape, sf::RectangleShape & secondShape);