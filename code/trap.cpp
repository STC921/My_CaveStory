#include "trap.h"
#include "sprite.h"

//15, 0

namespace{
	units::HP kDamage = 2;
}

Trap::Trap(Graphics& graphics, units::Game x, units::Game y, TrapFacing facing) :
	x_(x), y_(y), facing_(facing){
	initializeSprite(graphics);
}

void Trap::draw(Graphics& graphics){
	sprite_->draw(graphics, x_, y_);
}
void Trap::update(units::MS elapsed_time){
	sprite_->update(elapsed_time);
}

units::HP Trap::contactDamage() const{
	return kDamage;
}

void Trap::initializeSprite(Graphics& graphics){
	units::Tile trap_x, trap_y;
	switch (facing_){
	case U:
		trap_x = 15;
		trap_y = 0;
		break;
	case D:
		trap_x = 15;
		trap_y = 2;
		break;
	case L:
		trap_x = 14;
		trap_y = 1;
		break;
	case R:
		trap_x = 15;
		trap_y = 1;
		break;
	default:
		break;
	}
	sprite_ = boost::shared_ptr<Sprite>(new Sprite(
		graphics, "PrtMaze",
		units::tileToPixel(trap_x), units::tileToPixel(trap_y),
		units::tileToPixel(1), units::tileToPixel(1)));
}

