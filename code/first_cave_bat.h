#ifndef FIRST_CAVE_BAT_H
#define FIRST_CAVE_BAT_H

#include "sprite_state.h"
#include "units.h"
#include "rectangle.h"
#include "damage_text.h"
#include "damageable.h"

struct Sprite;
struct Graphics;

struct FirstCaveBat : public Damageable{
	FirstCaveBat(Graphics& graphics, units::Game x, units::Game y);

	void draw(Graphics& graphics);
	bool update(units::MS elapsed_time_ms, units::Game player_x);

	Rectangle collisionRectangle() const {
		return Rectangle(x_, y_, units::tileToGame(1), units::tileToGame(1));
	}
	Rectangle damageRectangle() const {
		return Rectangle(x_ + units::kHalfTile, y_ + units::kHalfTile, 0, 0);
	}

	units::HP contactDamage() const;
	void takeDamage(units::HP damage){
		printf("Hit the bat, the damage is %d\n", damage);
		damage_text_->setDamage(damage);
		health_--;
		if (health_ <= 0)
			alive_ = false;
	}

	units::Game center_x() const{
		return x_ + units::kHalfTile;
	}
	units::Game center_y() const{
		return y_ + units::kHalfTile;
	}
	boost::shared_ptr<DamageText> get_damage_text(){
		return damage_text_;
	};
private:
	typedef boost::tuple<HorizontalFacing> SpriteTuple;
	struct SpriteState : public SpriteTuple{
		SpriteState(SpriteTuple& tuple) : SpriteTuple(tuple){}
		HorizontalFacing horizontal_facing() const { return get<0>(); }
	};

	void initializeSprites(Graphics& graphics);
	void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
	SpriteState getSpriteState() const;

	const units::Game flight_center_y_;
	bool alive_;
	units::HP health_;
	units::Game x_, y_;
	units::Degrees flight_angle_;
	HorizontalFacing facing_;
	std::map<SpriteState, boost::shared_ptr<Sprite> > sprites_;
	boost::shared_ptr<DamageText> damage_text_;
};

#endif