#ifndef TEXT_H
#define TEXT_H

// Include header <C++>
#include <vector>

// Include header <SDL2>
#include <SDL.h>
#include <SDL_ttf.h>

// This struct for text
struct TextStruct {
	std::string text = "";
	SDL_Rect rect_text;
	SDL_Texture* text_texture = nullptr;
};

// Class <Text>
class Text {
private:
	// This variable used for font
	TTF_Font* font = nullptr;

	// This variable used for
	// Convert surface into texture
	SDL_Renderer* _render = nullptr;

	// This variable for text
	std::vector<TextStruct*> saveStore;

public:
	// Constructor
	Text(SDL_Renderer* render);

	// DeConstructor
	~Text();

public:
	/**
	 * This function will render text
	 * With the class text settings
	 */
	void Render(std::string text, SDL_Color color, int x, int y);
};

#endif // TEXT_H