#ifndef ALGORITHM_H
#define ALGORITHM_H

// Include header <C++>
#include <iostream>
#include <vector>

// Include header <SDL2>
#include <SDL.h>

// Include header <Text>
#include "Text.h"

// Include header <Define>
#include "Define.h"

// Include header <JSON>
#include "Json.h"

// Class <Algorithm (Core)>
class Algorithm {
private:
	/**
	 * This variable from SDL2
	 * This used for make window,
	 * Render, and get event
	 */
	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
	SDL_Event events;

	/**
	 * This variable used for information
	 * Size and the program is still running
	 */
	int widthWindow = 800;
	int heightWindow = 600;
	float sizePixel = 32.0f;
	bool running = true;
	float maxZoom = 50.0f;
	float minZoom = 20.0f;

	/**
	 * This variable used for information of
	 * Limit frame per seconds
	 */
	uint8_t FPS = 60;
	uint32_t startTicks = SDL_GetTicks();

	/**
	 * This variable used for manage,
	 * and Render font
	 */
	Text* text = nullptr;

	/**
	 * This variable used to get information,
	 * And getting file for model
	 */
	Json* informationModels;
	std::vector<std::vector<Model>> models;

	/**
	 * This variable used for select models
	 * Will showing, and variable for key break
	 */
	int indexModel = 0;
	bool breakKey = false;

public:
	// Constructor
	Algorithm();

	// DeConstructor
	~Algorithm();

private:
	// This function used for draw
	// Polygon
	void DrawPolygon(std::vector<Vec2>& data, SDL_Color color,
		int scala = 1);

	// This function used for draw
	// Line
	void DrawLine(std::vector<Vec2>& data, SDL_Color color,
		int scala = 1);

private:
	// This function used for get one
	constexpr inline int one(int number);

	// This function used for get one X axis
	constexpr inline int oneX(int number);

	// This function used for get one Y axis
	constexpr inline int oneY(int number);

private:
	/**
	 * This function used for intialize
	 * All the window and renderer
	 * Or maybe something
	 */
	inline void Start();

	/**
	 * This function used for handle
	 * event like that is controller
	 * Or maybe somthing
	 */
	inline void Event();

	/**
	 * This function used for logic
	 * Do something for render or maybe
	 * logic
	 */
	inline void Update();

	/**
	 * This function used for render
	 * Somthing into window
	 */
	inline void Render();
};

#endif // ALGORITHM_H