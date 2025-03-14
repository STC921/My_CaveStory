#ifndef POLAR_STAR_H
#define POLAR_STAR_H

#include "units.h"
#include "sprite.h"
#include "sprite_state.h"
#include "projectile.h"
#include "rectangle.h"
#include <vector>

struct Graphics;
struct Map;

struct PolarStar{
	PolarStar(Graphics& graphics);

	void updateProjectiles(units::MS elapsed_time, const Map& map);

	void draw(Graphics& graphics,
		HorizontalFacing horizontal_facing,
		VerticalFacing vertical_facing, 
		bool gun_up,
		units::Game x, units::Game y);

	void startFire(units::Game player_x, units::Game player_y, 
		HorizontalFacing horizontal_facing, 
		VerticalFacing vertical_facing, 
		bool gun_up);
	void stopFire(){}

	std::vector<boost::shared_ptr<::Projectile>> getProjectiles();

private:
	typedef boost::tuple<HorizontalFacing, VerticalFacing> SpriteTuple;
	struct SpriteState : public SpriteTuple {
		SpriteState(SpriteTuple& tuple) : SpriteTuple(tuple){}
		HorizontalFacing horizontal_facing() const { return get<0>(); }
		VerticalFacing vertical_facing() const { return get<1>(); }
	};

	struct Projectile : public  ::Projectile{
		Projectile(boost::shared_ptr<Sprite> sprite,
			HorizontalFacing horizontal_direction,
			VerticalFacing vertical_direction,
			units::Game x, units::Game y);

		bool update(units::MS elapsed_time, const Map& map);
		void draw(Graphics& graphics);
		void collideWithEnemy() {
			alive_ = false;
		}
	private:
		Rectangle collisionRectangle() const;
		units::HP contactDamage() const{
			return 1;
		}
		units::Game getX() const;
		units::Game getY() const;
		boost::shared_ptr<Sprite> sprite_;
		const units::Game x_, y_;
		const HorizontalFacing horizontal_direction_;
		const VerticalFacing vertical_direction_;
		units::Game offset_;
		bool alive_;
	};

	units::Game gun_x(HorizontalFacing horizontal_facing, units::Game player_x) const{
		return horizontal_facing == LEFT ? player_x - units::kHalfTile : player_x;
	}
	units::Game gun_y(VerticalFacing vertical_facing, bool gun_up, units::Game player_y) const;

	void initializeSprites(Graphics& graphics);
	void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
	std::map<SpriteState, boost::shared_ptr<Sprite>> sprite_map_;
	boost::shared_ptr<Sprite> horizontal_projectile_;
	boost::shared_ptr<Sprite> vertical_projectile_;

	boost::shared_ptr<Projectile> projectile_a_;
	boost::shared_ptr<Projectile> projectile_b_;
};

#endif