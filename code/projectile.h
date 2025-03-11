#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "rectangle.h"

struct Projectile{
	virtual Rectangle collisionRectangle() const = 0;
	virtual units::HP contactDamage() const = 0;
	virtual void collideWithEnemy() = 0;

	virtual ~Projectile() = 0;
};

inline Projectile::~Projectile(){}

#endif