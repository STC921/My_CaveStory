#include "door.h"
#include "graphics.h"
#include "sprite.h"

//10, 2

Door::Door(Graphics& graphics, units::Game x, units::Game y) : 
	x_(x), y_(y), 
	door_x_(x + units::kTileSize),
	door_y_(y + units::kTileSize){
	initializeSprite(graphics);
}

void Door::draw(Graphics& graphics){
	sprite_->draw(graphics, x_, y_);
	sprite_2_->draw(graphics, x_, y_ - units::kTileSize);
}

void Door::update(units::MS elapsed_time){
	sprite_->update(elapsed_time);
	sprite_2_->update(elapsed_time);
}

void Door::initializeSprite(Graphics& graphics){
	sprite_ = boost::shared_ptr<Sprite>(new Sprite(
		graphics, "PrtMaze",
		units::tileToPixel(0), units::tileToPixel(6),
		units::tileToPixel(4), units::tileToPixel(2)));
	sprite_2_ = boost::shared_ptr<Sprite>(new Sprite(
		graphics, "PrtMaze",
		units::tileToPixel(7), units::tileToPixel(6),
		units::tileToPixel(4), units::tileToPixel(1)));
}