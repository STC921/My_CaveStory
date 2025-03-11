#ifndef UNITS_H
#define UNITS_H

#include <cmath>
#include "config.h"

namespace units{
	typedef int HP;
	typedef float Game;
	typedef int Pixel;
	typedef unsigned int Tile;
	typedef unsigned int Frame;
	typedef float Degrees;

	typedef unsigned int MS;
	typedef unsigned int FPS;

	typedef float Velocity;
	typedef float Acceleration;
	typedef float AngularVelocity;

	namespace{
		const Game kTileSize = 32.0f;
		const Pixel kPixelPriTile = 32;
		const double kPi = atan(1) * 4;
	}

	inline float degreesToRadians(Degrees degrees){
		return degrees * (float)kPi / 180.0f;
	}

	inline Pixel gameToPixel(Game game){
		// TODO:
		//return Pixel(round(game));
		/*return Pixel(round(game / (kTileSize / kPixelPriTile)));*/
		return config::getGraphicsQuality() == config::HIGH_QUALITY ?
			Pixel(round(game)) : Pixel(round(game) / 2);
	}

	inline Tile gameToTile(Game game){
		return Tile(game / kTileSize);
	}

	inline Game tileToGame(Tile tile){
		return tile * kTileSize;
	}

	inline Pixel tileToPixel(Tile tile){
		return gameToPixel(tileToGame(tile));
	}

	const Game kHalfTile = tileToGame(1) / 2.0f;
}

#endif