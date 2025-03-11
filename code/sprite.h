#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "SDL.h"
#include "graphics.h"
#include "units.h"

struct Sprite{
	Sprite(Graphics& graphics,
		const std::string file_name, 
		units::Pixel source_x, units::Pixel source_y,
		units::Pixel width, units::Pixel height);

	virtual void update(units::MS) {}

	void draw(Graphics& graphics, units::Game x, units::Game y);
protected:
	SDL_Rect source_rect_;
private:
	SDL_Surface* sprite_sheet_;
};

#endif