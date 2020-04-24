#include <stdafx.h>

void DrawArrayOnScreen(sf::RenderWindow & window, sf::Drawable ** array, size_t count)
{
	window.clear();
	for (size_t i = 0; i < count; i++) {
		window.draw(*(*(array + i)));
	}
	window.display();
}