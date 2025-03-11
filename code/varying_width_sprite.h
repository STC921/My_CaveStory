#ifndef VARYING_WIDTH_SPRITE_H
#define VARYING_WIDTH_SPRITE_H

#include "sprite.h"

struct VaryingWidthSprite : public Sprite{
	VaryingWidthSprite(Graphics& graphics,
		const std::string file_name,
		units::Pixel source_x, units::Pixel source_y,
		units::Pixel initial_width, units::Pixel initial_height) :
		Sprite(graphics, file_name, source_x, source_y, initial_width, initial_height){}

	void set_width(units::Pixel width){
		source_rect_.w = width;
	}
};

#endif