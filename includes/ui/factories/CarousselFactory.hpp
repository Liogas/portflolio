#ifndef CAROUSSELFACTORY_HPP
# define CAROUSSELFACTORY_HPP

# include "Caroussel.hpp"
# include "UIStyle.hpp"

class CarousselFactory
{
    public:
        CarousselFactory() = delete;
        static Caroussel    create(
            SDL_Rect    &container
        );
};

#endif