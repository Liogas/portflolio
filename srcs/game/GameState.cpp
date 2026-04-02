#include "GameState.hpp"

GameState::GameState(RessourceManager &rm):
	player(std::make_unique<Player>(rm.getTexture("srcs/imgs/char1.png"), 64, 64))
{
	std::cout << "GameState created" << std::endl;
}
GameState::~GameState()
{
	std::cout << "GameState destroyed" << std::endl;
}

