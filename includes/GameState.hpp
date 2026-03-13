#ifndef GAMESTATE_HPP
# define GAMESTATE_HPP

# include "Player.hpp"
# include "RessourceManager.hpp"

class Player;

class GameState
{
	public:
		GameState(RessourceManager &rm);
		~GameState(void);
		std::unique_ptr<Player> player;
};

#endif