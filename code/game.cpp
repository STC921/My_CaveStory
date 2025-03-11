#include "game.h"
#include "graphics.h"
#include "animated_sprite.h"
#include "input.h"
#include "first_cave_bat.h"
//TODO:
#include "number_sprite.h"
#include "timer.h"
#include <SDL.h>
#include <iostream>

namespace {
	const units::FPS kFps = 60;
	const units::MS kMaxFrameTime = 5 * 1000 / 60;
}

units::Tile Game::kScreenWidth = /*640*/ 20;
units::Tile Game::kScreenHeight = /*480*/ 15;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	eventLoop();
}

Game::~Game() {
	
	SDL_Quit();
}

void Game::eventLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	player_.reset(new Player(graphics,
							 units::tileToGame(kScreenWidth / 2),
							 units::tileToGame(kScreenHeight / 2)));
	damage_texts_.addDamageable(player_);
	bat_.reset(new FirstCaveBat(graphics,
			   units::tileToGame(7),
		       units::tileToGame(kScreenHeight / 2 + 1)));
	cockroach_.reset(new Cockroach(graphics,
		units::tileToGame(14),
		units::tileToGame(6) - (units::Game)40));
	door_.reset(new Door(graphics, units::tileToGame(12), units::tileToGame(9)));
	trap_.reset(new Trap(graphics, units::tileToGame(16), units::tileToGame(10), U));
	trap_2_.reset(new Trap(graphics, units::tileToGame(2), units::tileToGame(10), L));
	damage_texts_.addDamageable(bat_);
	damage_texts_.addDamageable(cockroach_);
	map_.reset(Map::createTestMap(graphics));

	bool running = true;
	units::MS last_update_time = SDL_GetTicks();
	while (running) {
		const units::MS start_time_ms = SDL_GetTicks();
		input.beginNewFrame();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				input.keyDownEvent(event);
				break;
			case SDL_KEYUP:
				input.keyUpEvent(event);
				break;
			default:
				break;
			}
		}

		if(input.wasKeyPressed(SDLK_ESCAPE)) {
			running = false;
		}

		if(input.isKeyHeld(SDLK_LEFT) && input.isKeyHeld(SDLK_RIGHT)){
			player_->stopMoving();
		}
		else if(input.isKeyHeld(SDLK_LEFT)){
			player_->startMovingLeft();
		}
		else if(input.isKeyHeld(SDLK_RIGHT)){
			player_->startMovingRight();
		}
		else{
			player_->stopMoving();
		}

		if(input.isKeyHeld(SDLK_UP) && input.isKeyHeld(SDLK_DOWN)){
			player_->lookHorizontal();
		}
		else if(input.isKeyHeld(SDLK_UP)){
			player_->lookUp();
		}
		else if(input.isKeyHeld(SDLK_DOWN)){
			player_->lookDown();
			if (door_->collisionRectangle().collidesWith(player_->damageRectangle()) && player_->on_ground()){
				units::HP health = player_->getHealth();
				printf("Go into the Door!\n");
				player_.reset(new Player(graphics,
					units::tileToGame(kScreenWidth / 2),
					units::tileToGame(kScreenHeight / 2)));
				player_->setHealth(health);
			}
		}
		else{
			player_->lookHorizontal();
		}

		if (input.wasKeyPressed(SDLK_x)){
			player_->startFire();
		}
		else if (input.wasKeyReleased(SDLK_x)){
			player_->stopFire();
		}

		if(input.wasKeyPressed(SDLK_z)){
			player_->startJump();
		}
		else if(input.wasKeyReleased(SDLK_z)){
			player_->stopJump();
		}

		const units::MS current_time_ms = SDL_GetTicks();
		const units::MS elapsed_time = current_time_ms - last_update_time;
		update(std::min(elapsed_time, kMaxFrameTime));
		last_update_time = current_time_ms;
		draw(graphics);
		const units::MS ms_per_frame = 1000 /* ms */ / kFps /* fps */;
		const units::MS elapsed_time_ms = SDL_GetTicks() - start_time_ms;
		if(elapsed_time_ms < ms_per_frame){
			SDL_Delay(ms_per_frame - elapsed_time_ms /* ms */);
		}

		/*const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
		const float fps = 1 / seconds_per_frame;
		std::cout << "fps = " << fps << std::endl;*/
	}
}

void Game::update(units::MS elapsed_time_ms) {
	Timer::updateAll(elapsed_time_ms);
	damage_texts_.update(elapsed_time_ms);
	if (trap_){
		trap_->update(elapsed_time_ms);
	}
	if (trap_2_){
		trap_2_->update(elapsed_time_ms);
	}
	door_->update(elapsed_time_ms);
	if (cockroach_){
		if (!cockroach_->update(elapsed_time_ms, *map_)){
			cockroach_.reset();
		}
	}
	player_->update(elapsed_time_ms, *map_);
	if (bat_){
		if (!bat_->update(elapsed_time_ms, player_->center_x())){
			bat_.reset();
		}
	}
	//printf("Checking collisions\n");
	std::vector<boost::shared_ptr<Projectile>> projectiles(player_->getProjectiles());
	for (size_t i = 0; i < projectiles.size(); i++){
		if (bat_ && bat_->collisionRectangle().collidesWith(projectiles[i]->collisionRectangle())){
			bat_->takeDamage(projectiles[i]->contactDamage());
			projectiles[i]->collideWithEnemy();
		}
		if (cockroach_ && cockroach_->collisionRectangle().collidesWith(projectiles[i]->collisionRectangle())){
			cockroach_->takeDamage(projectiles[i]->contactDamage());
			projectiles[i]->collideWithEnemy();
		}
	}
	if (trap_ && trap_->collisionRectangle().collidesWith(player_->damageRectangle())){
		player_->takeDamage(trap_->contactDamage());
	}
	if (trap_2_ && trap_2_->collisionRectangle().collidesWith(player_->damageRectangle())){
		player_->takeDamage(trap_2_->contactDamage());
	}
	if (bat_ && bat_->damageRectangle().collidesWith(player_->damageRectangle())){
		player_->takeDamage(bat_->contactDamage());
	}
	if (cockroach_ && cockroach_->damageRectangle().collidesWith(player_->damageRectangle())){
		player_->takeDamage(cockroach_->contactDamage());
	}
	//map_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
	graphics.clear();
	map_->drawBackground(graphics);
	door_->draw(graphics);
	if (trap_){
		trap_->draw(graphics);
	}
	if (trap_2_){
		trap_2_->draw(graphics);
	}
	if (cockroach_){
		cockroach_->draw(graphics);
	}
	player_->draw(graphics);
	if (bat_){
		bat_->draw(graphics);
	}
	map_->draw(graphics);
	damage_texts_.draw(graphics);
	player_->drawHUD(graphics);
	//NumberSprite::DamageNumber(graphics, 32).draw(graphics, 0, 0);
	//NumberSprite number(NumberSprite::ExperienceNumber(graphics, 60));
	//number.draw(graphics, -number.width() / 2 + 4 * units::kTileSize, -number.height() / 2 + 4 * units::kTileSize);
	graphics.flip();
}