#ifndef COCKROACH_H
#define COCKROACH_H

#include "sprite_state.h"
#include "units.h"
#include "rectangle.h"
#include "damage_text.h"
#include "damageable.h"
#include "map.h"

struct Sprite;
struct Graphics;

namespace{
	const units::Game kCockRoachSize = 48;
	const units::Game kHalfCockRoach = kCockRoachSize / 2;
}

struct Cockroach : public Damageable{
	Cockroach(Graphics& graphics, units::Game x, units::Game y);

	void draw(Graphics& graphics);
	bool update(units::MS elapsed_time_ms, const Map& map);

	void startMovingLeft();
	void startMovingRight();
	void stopMoving();

	void updateY(units::MS elapsed_time_ms, const Map& map);

	Rectangle collisionRectangle() const {
		return Rectangle(x_, y_, units::tileToGame(1), units::tileToGame(2));
	}
	Rectangle damageRectangle() const {
		return Rectangle(x_ + units::kHalfTile, y_ + units::kHalfTile, units::kHalfTile, units::kTileSize);
	}

	Rectangle leftCollision(units::Game delta) const;
	Rectangle rightCollision(units::Game delta) const;
	Rectangle bottomCollision(units::Game delta) const;
	Rectangle topCollision(units::Game delta) const;

	units::HP contactDamage() const;
	void takeDamage(units::HP damage){
		printf("Hit the cockroach, the damage is %d\n", damage);
		damage_text_->setDamage(damage);
		health_--;
		if (health_ <= 0)
			alive_ = false;
	}

	units::Game center_x() const{
		return x_ + kHalfCockRoach;
	}
	units::Game center_y() const{
		return y_ + kHalfCockRoach;
	}
	boost::shared_ptr<DamageText> get_damage_text(){
		return damage_text_;
	};
private:
	void initializeSprites(Graphics& graphics);
	bool alive_;
	units::Game x_, y_;
	units::HP health_;
	units::Velocity velocity_x_, velocity_y_;
	bool on_ground_;
	boost::shared_ptr<Sprite> sprites_;
	boost::shared_ptr<DamageText> damage_text_;
};

#endif