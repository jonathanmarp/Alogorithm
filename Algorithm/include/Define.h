#ifndef DEFINE_H
#define DEFINE_H

// Include header <C++>
#include <iostream>

// Include header <SDL2>
#include <SDL.h>

// This struct for position
struct Vec2 {
	std::string name;
	int x, y;
};

// This struct for save Vec2 and color
struct Model {
	std::vector<Vec2> datas;
	int scala;
	int polygon;
	SDL_Color color;
};

#endif // DEFINE_H