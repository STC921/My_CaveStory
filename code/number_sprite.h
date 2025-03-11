#ifndef NUMBER_SPRITE_H
#define NUMBER_SPRITE_H

#include "units.h"
#include <boost/shared_ptr.hpp>
#include <vector>

struct Graphics;
struct Sprite;

struct NumberSprite{
	static NumberSprite HUDNumber(Graphics& graphics, int number, int num_digits = 0){
		return NumberSprite(graphics, number, num_digits, WHITE, NONE);
	}

	static NumberSprite DamageNumber(Graphics& graphics, int number){
		return NumberSprite(graphics, number, 0, RED, MINUS);
	}

	static NumberSprite ExperienceNumber(Graphics& graphics, int number){
		return NumberSprite(graphics, number, 0, WHITE, PLUS);
	}

	void draw(Graphics& graphics, units::Game x, units::Game y);
	void drawCentered(Graphics& graphics, units::Game x, units::Game y){
		draw(graphics, x - width() / 2, y - height() / 2);
	}

	units::Game width() const {
		return units::kHalfTile * reversed_glyphs_.size();
	}
	units::Game height() const {
		return units::kHalfTile;
	}
private:
	enum ColorType{
		RED,
		WHITE
	};
	enum OperatorType{
		PLUS,
		MINUS,
		NONE
	};
	NumberSprite(Graphics& graphics, int number, int num_digits, ColorType color, OperatorType op);

	std::vector<boost::shared_ptr<Sprite>> reversed_glyphs_;
	units::Game padding_;
};

#endif //NUMBER_SPRITE_H