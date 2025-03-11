#ifndef DOOR_H
#define DOOR_H

#include "rectangle.h"
#include "units.h"
#include <boost/shared_ptr.hpp>

struct Graphics;
struct Sprite;

struct Door{
	Door(Graphics& graphics, units::Game x, units::Game y);

	void draw(Graphics& graphics);
	void update(units::MS elapsed_time);

	Rectangle collisionRectangle() const {
		return Rectangle(door_x_, door_y_, units::tileToGame(1), units::tileToGame(1));
	}
private:
	void initializeSprite(Graphics& graphics);
	units::Game x_, y_;
	units::Game door_x_, door_y_;
	boost::shared_ptr<Sprite> sprite_, sprite_2_;
};

#endif