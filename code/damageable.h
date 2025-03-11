#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

#include "units.h"
#include <boost/shared_ptr.hpp>

struct DamageText;

struct Damageable{
	virtual units::Game center_x() const = 0;
	virtual units::Game center_y() const = 0;
	virtual boost::shared_ptr<DamageText> get_damage_text() = 0;

	virtual ~Damageable() = 0;
};

inline Damageable::~Damageable(){}

#endif