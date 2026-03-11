#ifndef ANIMATIONSDL_HPP
# define ANIMATIONSDL_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <stdexcept>
# include <unordered_map>

typedef struct	Animation
{
	int			sizeH;
	int			sizeW;
	int			nbTiles;
	int			posX;
	int			posY;
	std::string name;
}	T_animation;

class AnimationSDL
{
	public:
		AnimationSDL(void);
		~AnimationSDL(void);
		void	addAnimation(std::string, T_animation);
		void	print();
		const T_animation	*getAnimation(std::string) const;
	private:
		std::unordered_map<std::string, T_animation> _animations;
};

#endif