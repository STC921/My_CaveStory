#ifndef DAMAGE_TEXTS_H
#define DAMAGE_TEXTS_H

#include "units.h"
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

struct DamageText;
struct Damageable;
struct Graphics;

struct DamageTexts{
	void addDamageable(boost::shared_ptr<Damageable> damageable);
	void update(units::MS elapsed_time);
	void draw(Graphics& graphics);

private:
	typedef std::map<boost::shared_ptr<DamageText>, boost::weak_ptr<Damageable>> DamageTextMap;

	DamageTextMap damage_text_map_;
};

#endif