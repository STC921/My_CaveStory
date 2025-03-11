#ifndef TRAP_H
#define TRAP_H

#include "rectangle.h"
#include "units.h"
#include "sprite_state.h"
#include <boost/shared_ptr.hpp>

struct Sprite;
struct Graphics;

struct Trap{
	Trap(Graphics& graphics, units::Game x, units::Game y, TrapFacing facing);
	
	void draw(Graphics& graphics);
	void update(units::MS elapsed_time);

	units::HP contactDamage() const;
	Rectangle collisionRectangle() const {
		return Rectangle(x_, y_, units::tileToGame(1), units::tileToGame(1));
	}
private:
	void initializeSprite(Graphics& graphics);
	units::Game x_, y_;
	TrapFacing facing_;
	boost::shared_ptr<Sprite> sprite_;
};

#endif