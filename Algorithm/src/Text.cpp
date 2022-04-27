// Include header <C++>
#include <iostream>

// Include header <Self>
#include "../include/Text.h"

// Include header <File>
#include "../include/File.h"

// Constructor
Text::Text(SDL_Renderer* render) : _render(render) {
	// Get file
	std::string path = File::GetPath("..\\assets\\font\\Inter-Regular.ttf");

	// Open font
	this->font = TTF_OpenFont(path.c_str(), 10);

	// Check if font have error
	if (!this->font) {
		// Print error
		std::cout << "Error: " << TTF_GetError() << std::endl;

		// Exit with error code
		exit(-1);
	}
}

// DeConstructor
Text::~Text() {
	// Destroy Font
	TTF_CloseFont(this->font);
}

/**
 * This function will render text
 * With the class text settings
 */
void Text::Render(std::string text, SDL_Color color, int x, int y) {
	// Setup bool for check, and index
	bool had = false;
	uint32_t index = 0;

	// Map
	for (size_t i = 0; i < this->saveStore.size(); i++) {
		if (this->saveStore[i]->text == text) {
			// Set had to true and set index into search index
			had = true;
			index = i;

			// Break
			break;
		}
	}

	// Check
	if (had == false) {
		// Make text
		SDL_Surface* text_surface = TTF_RenderText_Blended(this->font,
			text.c_str(), color);

		// Convert into texture
		SDL_Texture* text_texture = SDL_CreateTextureFromSurface(
			this->_render, text_surface);

		// Get rect
		SDL_Rect rect_text = {
			.w = text_surface->w,
			.h = text_surface->h,
		};

		// Make
		TextStruct* textStruct = new TextStruct;
		textStruct->text = text;
		textStruct->text_texture = text_texture;
		textStruct->rect_text = rect_text;

		// Push
		this->saveStore.push_back(std::move(textStruct));

		// Set into index into end
		index = this->saveStore.size() - 1;
	}

	// Set position
	this->saveStore[index]->rect_text.x = x;
	this->saveStore[index]->rect_text.y = y;

	// Render
	SDL_RenderCopy(this->_render, 
		this->saveStore[index]->text_texture, NULL, 
		&this->saveStore[index]->rect_text);
}