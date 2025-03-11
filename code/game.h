#ifndef GAME_H
#define GAME_H

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "player.h"
#include "map.h"
#include "units.h"
#include "damage_texts.h"
#include "trap.h"
#include "door.h"
#include "cockroach.h"

struct Graphics;
struct FirstCaveBat;

struct Game {
	Game();
	~Game();

	static units::Tile kScreenWidth;
	static units::Tile kScreenHeight;
private:
	void eventLoop();
	void update(units::MS elapsed_time_ms);
	void draw(Graphics& graphics);

	boost::shared_ptr<Player> player_;
	boost::shared_ptr<FirstCaveBat> bat_;
	boost::shared_ptr<Cockroach> cockroach_;
	boost::shared_ptr<Trap> trap_, trap_2_;
	boost::shared_ptr<Door> door_;
	boost::scoped_ptr<Map> map_;
	DamageTexts damage_texts_;
};

#endif
