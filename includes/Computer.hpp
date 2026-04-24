#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include "Player.hpp"

class Computer : public Entity
{
	public:
		Computer(int x, int y, int width, int height, std::string direction);
		~Computer();
		void	update(float deltaTime) override;
		bool	canInteract(const Player &player) const;
		void	interact(const Entity &e) override;
		[[nodiscard]] bool	isOn() const;
	private:
		std::string	_direction;
		bool		_on;
};

#endif