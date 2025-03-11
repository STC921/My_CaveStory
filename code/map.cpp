#include "map.h"
#include "sprite.h"
#include "graphics.h"
#include "game.h"
#include "rectangle.h"

using boost::shared_ptr;
using std::vector;

Map* Map::createTestMap(Graphics& graphics){
	Map* map = new Map();

	map->backdrop_.reset(new FixedBackdrop("bkGreen", graphics));
	const units::Tile num_rows = 15;
	const units::Tile num_cols = 20;
	//foreground sprite is num_rows * num_cols in size
	map->tiles_ = vector<vector<Tile>>(num_rows, vector<Tile>(num_cols, Tile()));
	map->background_tiles_ = vector<vector<boost::shared_ptr<Sprite>>>(num_rows, vector<boost::shared_ptr<Sprite>>(num_cols, shared_ptr<Sprite>()));

	shared_ptr<Sprite> sprite(new Sprite(graphics, "PrtMaze", 0, units::tileToPixel(1), units::tileToPixel(1), units::tileToPixel(1)));
	Tile tile(WALL_TILE, sprite);
	const units::Tile row = 11;
	for (units::Tile col = 0; col < num_cols; ++col){
		map->tiles_[row][col] = tile;
		map->tiles_[0][col] = tile;
	}
	for (units::Tile row = 0; row < 15; ++row){
		map->tiles_[row][0] = tile;
		map->tiles_[row][19] = tile;
	}

	shared_ptr<Sprite> sprite_1(new Sprite(graphics, "PrtMaze", units::tileToPixel(3), 0, units::tileToPixel(1), units::tileToPixel(1)));
	shared_ptr<Sprite> sprite_2(new Sprite(graphics, "PrtMaze", units::tileToPixel(4), 0, units::tileToPixel(1), units::tileToPixel(1)));
	shared_ptr<Sprite> sprite_3(new Sprite(graphics, "PrtMaze", units::tileToPixel(3), units::tileToPixel(1), units::tileToPixel(1), units::tileToPixel(1)));
	shared_ptr<Sprite> sprite_4(new Sprite(graphics, "PrtMaze", units::tileToPixel(4), units::tileToPixel(1), units::tileToPixel(1), units::tileToPixel(1)));
	for (units::Tile col = 0; col < num_cols; ++col){
		for (units::Tile row = 12; row <= 14; ++row){
			if (col % 2 == 0 && row % 2 == 0){
				Tile rock(WALL_TILE, sprite_1);
				map->tiles_[row][col] = rock;
			}
			if (col % 2 != 0 && row % 2 == 0){
				Tile rock(WALL_TILE, sprite_2);
				map->tiles_[row][col] = rock;
			}
			if (col % 2 == 0 && row % 2 != 0){
				Tile rock(WALL_TILE, sprite_3);
				map->tiles_[row][col] = rock;
			}
			if (col % 2 != 0 && row % 2 != 0){
				Tile rock(WALL_TILE, sprite_4);
				map->tiles_[row][col] = rock;
			}
		}
	}

	map->tiles_[10][5] = tile;
	map->tiles_[9][4] = tile;
	map->tiles_[8][3] = tile;
	map->tiles_[7][2] = tile;
	map->tiles_[10][3] = tile;

	shared_ptr<Sprite> chain_top(new Sprite(graphics, "PrtMaze", units::tileToPixel(11), units::tileToPixel(5), units::tileToPixel(1), units::tileToPixel(1)));
	shared_ptr<Sprite> chain_middle(new Sprite(graphics, "PrtMaze", units::tileToPixel(11), units::tileToPixel(6), units::tileToPixel(1), units::tileToPixel(1)));
	shared_ptr<Sprite> chain_bottom(new Sprite(graphics, "PrtMaze", units::tileToPixel(11), units::tileToPixel(7), units::tileToPixel(1), units::tileToPixel(1)));
	
	for (units::Tile col = 5; col < 12; ++col){
		map->tiles_[4][col] = tile;
		if (col == 5 || col == 11){
			map->background_tiles_[1][col] = chain_top;
			map->background_tiles_[2][col] = chain_middle;
			map->background_tiles_[3][col] = chain_bottom;
		}
	}

	map->background_tiles_[8][2] = chain_top;
	map->background_tiles_[9][2] = chain_middle;
	map->background_tiles_[10][2] = chain_bottom;

	return map;
}

vector<Map::CollisionTile> Map::getCollidingTiles(const Rectangle& rectangle) const{
	const units::Tile first_row = units::gameToTile(rectangle.top());
	const units::Tile last_row = units::gameToTile(rectangle.bottom());
	const units::Tile first_col = units::gameToTile(rectangle.left());
	const units::Tile last_col = units::gameToTile(rectangle.right());

	vector<CollisionTile> collision_tiles;
	for (units::Tile row = first_row; row <= last_row; ++row){
		for (units::Tile col = first_col; col <= last_col; ++col){
			collision_tiles.push_back(CollisionTile(row, col, tiles_[row][col].tile_type));
		}
	}
	return collision_tiles;
}

void Map::update(units::MS elapsed_time_ms){
	for(size_t row = 0; row < tiles_.size(); ++row){
		for(size_t col = 0; col < tiles_[row].size(); ++col){
			if(tiles_[row][col].sprite){
				tiles_[row][col].sprite->update(elapsed_time_ms);
			}
		}
	}
}

void Map::drawBackground(Graphics& graphics) const{
	backdrop_->draw(graphics);

	for (size_t row = 0; row < background_tiles_.size(); ++row){
		for (size_t col = 0; col < background_tiles_[row].size(); ++col){
			if (background_tiles_[row][col]){
				background_tiles_[row][col]->draw(graphics, units::tileToGame(col), units::tileToGame(row));
			}
		}
	}

}

void Map::draw(Graphics& graphics) const{
	for(size_t row = 0; row < tiles_.size(); ++row){
		for(size_t col = 0; col < tiles_[row].size(); ++col){
			if(tiles_[row][col].sprite){
				tiles_[row][col].sprite->draw(graphics, units::tileToGame(col), units::tileToGame(row));
			}
		}
	}
}