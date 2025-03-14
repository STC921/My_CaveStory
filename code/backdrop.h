#ifndef BACKDROP_H
#define BACKDROP_H

#include "graphics.h"

#include <string>

struct Backdrop{
	virtual void draw(Graphics& graphics) const = 0;

};

struct FixedBackdrop : public Backdrop{
	FixedBackdrop(const std::string& path, Graphics& graphics);
	void draw(Graphics& graphics) const;
private:
	Graphics::SurfaceID surface_id_;
};

#endif