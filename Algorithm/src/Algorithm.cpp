// Include header <C++>
#include <iostream>
#include <future>
#include <array>

// Include header <Win32>
#ifndef _DEBUG
#include <Windows.h>
#endif

// Include header <SDL2>
#include <SDL.h>
#include <SDL_ttf.h>

// Include header <Self>
#include "../include/Algorithm.h"

// Include header <MACRO>
#include "../include/Macro.h"

// Include header <Log>
#include "../include/Log.h"

// Setup global variable for debugging
bool debug = false;

// Constructor
Algorithm::Algorithm() : events(SDL_Event({})) {
	/**
	 * Init SDL2{Timer, Video, Events}
	 * And check intialize has been successfull
	 */
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) [[unlikely]] {
		// Show error message
		Log::Error(SDL_GetError());

		// Exit with error code
		exit(-1);
	}

	/**
	 * Init SDL2 TTF and check if
	 * Intialize has been successfull
	 */
	if (TTF_Init() == -1) {
		// Show error message
		Log::Error(TTF_GetError());

		// Exit with error code
		exit(-1);
	}

	// Call start function
	this->Start();

	// Start <Looping>
	while (this->running) [[likely]] {
		// Get ticks for first loop
		this->startTicks = SDL_GetTicks();

		// Get event
		while (SDL_PollEvent(&this->events)) [[likely]] {
			// Call handle event
			this->Event();
		}
		
		// Get size window
		SDL_GetWindowSize(this->window, &this->widthWindow, &this->heightWindow);

		// Set render color
		SDL_SetRenderDrawColor(this->render, 0x3f, 0x38, 0x51, 0);

		// Clear window and call update
		RenderClear(this->render);

		// Logic section
		//  Call update function
		this->Update();

		// Render Section
		// Call render function
		this->Render();

		// Present window
		RenderShow(this->render);

		// Proccess frame per seconds
		if (static_cast<float>((1000 / this->FPS)) 
			> static_cast<float>((SDL_GetTicks() - this->startTicks))) {
			SDL_Delay(1000 / this->FPS - (SDL_GetTicks() - this->startTicks));
		}
	}
}

// DeConstructor
Algorithm::~Algorithm() {
	// Quit SDL TTF
	TTF_Quit();

	// Quit SDL
	SDL_Quit();
}

// This function used for get one
constexpr inline int Algorithm::one(int number) {
	return number * static_cast<int>(this->sizePixel);
}

// This function used for get one X axis
constexpr inline int Algorithm::oneX(int number) {
	return int(this->widthWindow * 0.5) + this->one(number);
}

// This function used for get one Y axis
constexpr inline int Algorithm::oneY(int number) {
	return int(this->heightWindow * 0.5) - this->one(number);
}

// This function used for draw
// Polygon
void Algorithm::DrawPolygon(std::vector<Vec2>& data, SDL_Color color,
	int scala) {
	// Set color
	SDL_SetRenderDrawColor(this->render, color.r, color.g,
		color.b, color.a);

	// Draw
	for (size_t i = 0; i < data.size(); i++) {
		// Draw Line
		if (i != data.size() - 1) {
			SDL_RenderDrawLine(this->render,
				this->oneX(data[i].x * scala),
				this->oneY(data[i].y * scala),
				this->oneX(data[i + 1].x * scala),
				this->oneY(data[i + 1].y * scala));
		}
		else {
			SDL_RenderDrawLine(this->render,
				this->oneX(data[i].x * scala),
				this->oneY(data[i].y * scala),
				this->oneX(data[0].x * scala),
				this->oneY(data[0].y * scala));
		}
	}

	// Map
	for (auto& item : data) {
		// This render text
		this->text->Render(item.name + " " +
			std::string((scala != 1) ? std::to_string(scala) + "x" : "") +
			"(" + std::to_string(item.x) + ", " + std::to_string(item.y) + ")",
			{ 0xfD, 0xfD, 0xfD },
			this->oneX(item.x * scala),
			this->oneY(item.y * scala));
	}
}

// This function used for draw
// Line
void Algorithm::DrawLine(std::vector<Vec2>& data, SDL_Color color,
	int scala) {
	// Set color
	SDL_SetRenderDrawColor(this->render, color.r, color.g,
		color.b, color.a);

	// Draw
	for (size_t i = 0; i < data.size(); i++) {
		// Draw Line
		if (i != data.size() - 1) {
			SDL_RenderDrawLine(this->render,
				this->oneX(data[i].x * scala),
				this->oneY(data[i].y * scala),
				this->oneX(data[i + 1].x * scala),
				this->oneY(data[i + 1].y * scala));
		}
	}

	// Map
	for (auto& item : data) {
		// This render text
		this->text->Render(item.name + 
			std::string((scala != 1) ? std::to_string(scala) + "x" : "") +
			" (" + std::to_string(item.x) + ", " + std::to_string(item.y) + ")",
			{ 0xfD, 0xfD, 0xfD },
			this->oneX(item.x * scala),
			this->oneY(item.y * scala));
	}
}

/**
 * This function used for intialize
 * All the window and renderer
 * Or maybe something
 */
inline void Algorithm::Start() {
	// Intialize window
	this->window = SDL_CreateWindow("Algorithm",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		this->widthWindow, this->heightWindow, 0);

	// Settings
	// <Resize>
	SDL_SetWindowResizable(this->window, SDL_TRUE);

	// <Minimal>
	SDL_SetWindowMinimumSize(this->window,
		int(this->widthWindow * 0.5), int(this->heightWindow * 0.5));

	// Intialize Render
	this->render = SDL_CreateRenderer(this->window, -1, 
		SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	// Check window and render have error
	if (!window || !render) [[unlikely]] {
		// Show error message
		Log::Error(SDL_GetError());

		// Exit with error code
		exit(-1);
	}
	else {
		// If success
		Log::Init("Window and Render Engine");
	}

	// Intialize information models
	this->informationModels = new Json("..\\Algorithm\\data\\data.json");

	// Get models
	std::future<void> modelAsync = std::async(std::launch::async, [&]() -> void {
		for (auto& item : this->informationModels->data["files"].items()) {
			// Get data
			Json temp = Json("..\\Algorithm\\data\\pages\\" +
				item.value().get<std::string>());

			// Setup Models
			std::vector<Model> tempModels;

			// Mapping data
			for (auto& modelData : temp.data.items()) {
				// Make models
				Model model;

				// Get color
				model.color.r = modelData.value()["color"]["red"].get<int>();
				model.color.g = modelData.value()["color"]["green"].get<int>();
				model.color.b = modelData.value()["color"]["blue"].get<int>();

				// Get scala
				model.scala = modelData.value()["scala"].get<int>();

				// Get scala
				model.polygon = modelData.value()["polygon"].get<int>();

				// Get names
				std::vector<std::string> names;

				// Map
				for (auto& name : modelData.value()["names"].items()) {
					// Push
					names.push_back(std::move(name.value().get<std::string>()));
				}

				// Get positon
				std::vector<std::vector<int>> positions;

				// Map
				for (auto& position : modelData.value()["positions"].items()) {
					// Setup
					std::vector<int> pos;

					for (auto& x : position.value().items()) {
						pos.push_back(std::move(x.value().get<int>()));
					}

					// Push
					positions.push_back(std::move(pos));
				}

				// Map position
				for (size_t y = 0; y < positions.size(); y++) {
					// Setup
					Vec2 temp;

					// Set name
					if (names.size() > y) {
						temp.name = names[y];
					}

					// Set position
					temp.x = positions[y][0];
					temp.y = positions[y][1];

					// Push
					model.datas.push_back(std::move(temp));
				}

				// Push
				tempModels.push_back(std::move(model));
			}

			// Push
			this->models.push_back(std::move(tempModels));
		}
	});

	// Intialize text
	this->text = new Text(this->render);

	// Wait
	modelAsync.wait();
}

/**
 * This function used for handle
 * event like that is controller
 * Or maybe somthing
 */
inline void Algorithm::Event() {
	// Switch
	switch (this->events.type) {
		// If Mouse scroll
		case SDL_MOUSEWHEEL: {
			if (this->events.wheel.y > 0) // scroll up
			{
				// Put code for handling "scroll up" here!
				if (this->sizePixel < this->maxZoom) {
					this->sizePixel += 3;
				}
			}
			else if (this->events.wheel.y < 0) // scroll down
			{
				// Put code for handling "scroll down" here!
				if (this->sizePixel > this->minZoom) {
					this->sizePixel -= 3;
				}
			}
		} break;

		// If Key Down
		case SDL_KEYDOWN: {
			// Switch
			switch (this->events.key.keysym.sym) {
				// Into left
				case SDLK_LEFT: {
					// Check
					if (!this->breakKey) {
						// Set into false
						this->breakKey = true;

						// Min 1
						this->indexModel -= 1;

						// Check
						if ((int)this->indexModel < 0) {
							this->indexModel = static_cast<uint8_t>(this->models.size()) - 1;
						}
					}
				} break;

				// Into right
				case SDLK_RIGHT: {
					// Check
					if (!this->breakKey) {
						// Set into false
						this->breakKey = true;

						// Plus 1
						this->indexModel += 1;

						// Check
						if ((size_t)this->indexModel > this->models.size() - 1) {
							this->indexModel = 0;
						}
					}
				} break;
			}
		} break;

		// If Key Up
		case SDL_KEYUP: {
			// Switch
			switch (this->events.key.keysym.sym) {
				case SDLK_LEFT:
				case SDLK_RIGHT: {
					// Set into false
					this->breakKey = false;
				} break;
			}
		} break;

		// If SDL Request quit
		[[unlikely]] case SDL_QUIT: {
			// Quit
			this->running = false;
		} break;

		// If SDL Window event
		[[unlikely]] case SDL_WINDOWEVENT: {
			// Get event
			const uint32_t DT = this->events.window.type;

			// Check if close request
			if (DT == SDL_WINDOWEVENT_CLOSE) {
				// Quit
				this->running = false;
			}
		} break;
	}
}

/**
 * This function used for logic
 * Do something for render or maybe
 * logic
 */
inline void Algorithm::Update() {
	// Map
	for (auto& item : this->models[this->indexModel]) {
		// Switch
		switch (item.polygon) {
			// Polygon
			case 1: {
				// Draw polygon
				this->DrawPolygon(item.datas, item.color, item.scala);
			} break;

			default: {
				// Draw line
				this->DrawLine(item.datas, item.color, item.scala);
			} break;
		}
	}
}

/**
 * This function used for render
 * Somthing into window
 */
inline void Algorithm::Render() {
	// Render Line
	SDL_SetRenderDrawColor(this->render, 0xff, 0xff, 0xff, 0x00);
	SDL_RenderDrawLine(this->render, int(this->widthWindow * 0.5), 0,
		int(this->widthWindow * 0.5), this->heightWindow);
	SDL_RenderDrawLine(this->render, 0, int(this->heightWindow * 0.5),
		this->widthWindow, int(this->heightWindow * 0.5));

	// Draw zoom
	this->text->Render(std::to_string(int(((this->sizePixel - this->minZoom) / 
		(this->maxZoom - this->minZoom)) * 100.0f)) + "%", 
		{0xfd, 0xfd, 0xfd}, 20, 20);

	// Async
	std::future<void> temp = std::async(std::launch::async, [&]() -> void {
		SDL_SetRenderDrawColor(this->render, 0xff, 0xff, 0xff, 0x00);
		
		// Render text 0
		this->text->Render("0", { 0xfD, 0xfD, 0xfD },
			int(this->widthWindow * 0.5), int(this->heightWindow * 0.5));

		// Setup index
		int index = 1;

		for (int x = int(this->widthWindow * 0.5) + static_cast<int>(this->sizePixel);
			x < this->widthWindow; x += static_cast<int>(this->sizePixel)) {
			// Render text
			this->text->Render(std::to_string(index++), {0xfD, 0xfD, 0xfD},
				x, int(this->heightWindow * 0.5) + 1);
			
			// Render line
			SDL_RenderDrawLine(this->render, x, int(this->heightWindow * 0.5) - 1,
				x, int(this->heightWindow * 0.5) + 1);
		}

		index = -1;
		for (int x = int(this->widthWindow * 0.5) - static_cast<int>(this->sizePixel);
			x > 0; x -= static_cast<int>(this->sizePixel)) {
			// Render text
			this->text->Render(std::to_string(index--), { 0xfD, 0xfD, 0xfD },
				x, int(this->heightWindow * 0.5) + 1);

			// Render line
			SDL_RenderDrawLine(this->render, x, int(this->heightWindow * 0.5) - 1,
				x, int(this->heightWindow * 0.5) + 1);
		}

		index = 1;
		for (int y = int(this->heightWindow * 0.5) + static_cast<int>(this->sizePixel);
			y < this->heightWindow; y += static_cast<int>(this->sizePixel)) {
			// Render text
			this->text->Render(std::to_string(index++), { 0xfD, 0xfD, 0xfD },
				int(this->widthWindow * 0.5) + 1, y);

			// Render line
			SDL_RenderDrawLine(this->render, int(this->widthWindow * 0.5) - 1, y,
				int(this->widthWindow * 0.5) + 1, y);
		}

		index = -1;
		for (int y = int(this->heightWindow * 0.5) - static_cast<int>(this->sizePixel);
			y > 0; y -= static_cast<int>(this->sizePixel)) {
			// Render text
			this->text->Render(std::to_string(index--), { 0xfD, 0xfD, 0xfD },
				int(this->widthWindow * 0.5) + 1, y);

			// Render line
			SDL_RenderDrawLine(this->render, int(this->widthWindow * 0.5) - 1, y,
				int(this->widthWindow * 0.5) + 1, y);
		}
	});
}

// Main
auto main(int argc, const char* argv[]) -> decltype(0) {
	// Setup
#ifndef _DEBUG
	// Free console / hide the console
	FreeConsole();
#endif

	// Set debug into true if debug compile
#ifdef _DEBUG
	debug = true;
#endif

	// Set SDL2 into ready
	SDL_SetMainReady();

	// Intialize Algorithm <Core>
	Algorithm algorithm;
	{
		(void)argc;
		(void)argv;
	}
	return 0;
}