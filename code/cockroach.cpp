#include "cockroach.h"
#include "graphics.h"
#include "animated_sprite.h"
#include <cmath>

namespace{
	units::HP kDamage = 2;
	const units::Frame kNumStayFrames = 2;
	const units::Frame kStayFps = 1;
	const units::Acceleration kGravity = 0.00078125f;
	const units::Velocity kMaxSpeedY = 0.2998046875f;

	const units::Game kCollisionYTop = 2;
	const units::Game kCollisionYHeight = 41;
	const units::Game kCollisionTopWidth = 41;
	const units::Game kCollisionBottomWidth = 4;
	const units::Game kCollisionTopLeft = (units::tileToGame(1) - kCollisionTopWidth) / 2;
	const units::Game kCollisionBottomLeft = (units::tileToGame(1) - kCollisionBottomWidth) / 2;

	struct CollisionInfo{
		bool collided;
		units::Tile row, col;
	};
	CollisionInfo getWallCollisionInfo(const Map& map, const Rectangle& Rectangle){
		//check collision in the direction of delta
		CollisionInfo info = { false, 0, 0 };
		std::vector<Map::CollisionTile> tiles(map.getCollidingTiles(Rectangle));
		for (size_t i = 0; i < tiles.size(); ++i){
			if (tiles[i].tile_type == Map::WALL_TILE){
				info.collided = true;
				info.row = tiles[i].row;
				info.col = tiles[i].col;
				break;
			}
		}
		return info;
	}
}

Cockroach::Cockroach(Graphics& graphics, units::Game x, units::Game y) : 
	x_(x), y_(y),
	health_((units::HP)5),
	velocity_x_(0),
	velocity_y_(0),
	on_ground_(false),
	alive_(true),
	damage_text_(new DamageText()){
	initializeSprites(graphics);
}

void Cockroach::draw(Graphics& graphics){
	sprites_->draw(graphics, x_, y_);
}

bool Cockroach::update(units::MS elapsed_time_ms, const Map& map){
	sprites_->update(elapsed_time_ms);
	updateY(elapsed_time_ms, map);
	return alive_;
}

/*Rectangle Cockroach::leftCollision(units::Game delta) const{
	assert(delta <= 0);
	return Rectangle(x_ + kCollisionX.left() + delta,
		y_ + kCollisionX.top(),
		kCollisionX.width() / 2 - delta,
		kCollisionX.height());
}

Rectangle Cockroach::rightCollision(units::Game delta) const{
	assert(delta >= 0);
	return Rectangle(x_ + kCollisionX.left() + kCollisionX.width() / 2,
		y_ + kCollisionX.top(),
		kCollisionX.width() / 2 + delta,
		kCollisionX.height());
}*/

Rectangle Cockroach::bottomCollision(units::Game delta) const{
	assert(delta >= 0);
	return Rectangle(x_ + kCollisionBottomLeft,
		y_ + kCollisionYTop + kCollisionYHeight / 2,
		kCollisionBottomWidth,
		kCollisionYHeight / 2 + delta);
}

Rectangle Cockroach::topCollision(units::Game delta) const{
	assert(delta <= 0);
	return Rectangle(x_ + kCollisionTopLeft,
		y_ + kCollisionYTop + delta,
		kCollisionTopWidth,
		kCollisionYHeight / 2 - delta);
}

void Cockroach::updateY(units::MS elapsed_time_ms, const Map& map){
	//update velocity
	const units::Acceleration gravity = kGravity;
	velocity_y_ = std::min(velocity_y_ + gravity * elapsed_time_ms, kMaxSpeedY);
	//calculate the delta
	const units::Game delta = velocity_y_ * elapsed_time_ms;
	if (delta > 0){
		//check collision in the direction of delta
		CollisionInfo info = getWallCollisionInfo(map, bottomCollision(delta));
		// react to collision
		if (info.collided){
			y_ = units::tileToGame(info.row) - (kCollisionYTop + kCollisionYHeight);
			velocity_y_ = 0.0f;
			on_ground_ = true;
		}
		else{
			y_ += delta;
			on_ground_ = false;
		}
		//check collision in other direction
		info = getWallCollisionInfo(map, topCollision(0));
		if (info.collided){
			y_ = units::tileToGame(info.row) + kCollisionYHeight;
		}
	}
	else{
		CollisionInfo info = getWallCollisionInfo(map, topCollision(delta));
		if (info.collided){
			y_ = units::tileToGame(info.row) + kCollisionYHeight;
			velocity_y_ = 0.0f;
		}
		else{
			y_ += delta;
			on_ground_ = false;
		}
		info = getWallCollisionInfo(map, bottomCollision(0));
		if (info.collided){
			y_ = units::tileToGame(info.row) - (kCollisionYTop + kCollisionYHeight);
			on_ground_ = true;
		}
	}
}

units::HP Cockroach::contactDamage() const{
	return kDamage;
}

void Cockroach::initializeSprites(Graphics& graphics){
	sprites_ = boost::shared_ptr<Sprite>(new AnimatedSprite(
		graphics, "NpcMaze",
		0, 0,
		48, 48,
		kStayFps, kNumStayFrames));
}