/*

 sftools - Copyright (c) 2012-2013 Marco Antognini <antognini.marco@gmail.com>

 This software is provided 'as-is', without any express or implied warranty. In
 no event will the authors be held liable for any damages arising from the use
 of this software.

 Permission is granted to anyone to use this software for any purpose, including
 commercial applications, and to alter it and redistribute it freely, subject to
 the following restrictions:

 1. The origin of this software must not be misrepresented; you must not claim
 that you wrote the original software. If you use this software in a product,
 an acknowledgment in the product documentation would be appreciated but is
 not required.

 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.

 3. This notice may not be removed or altered from any source distribution.

 */

/*!
 @file sftools/Animation/Frame.hpp
 @brief Define Frame class
 */

#ifndef __SFTOOLS_FRAME_HPP__
#define __SFTOOLS_FRAME_HPP__

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include <sftools/Singleton.hpp>

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{
    
    /*!
     @class Frame
     @brief Hold the data required to render a frame
     
     @note Like sf::Sprite, Frame doesn't own the texture. You have to keep it
     'alive' for the lifetime of the frame that uses it, otherwise you'll get
     some undefined behaviour.
     
     @see FrameStream
     @see Animation
     */
    struct Frame
    {
        /*!
         @brief Constructor
         
         This constructor can be used as the default one, or as a way to define
         a frame without any texture (i.e. a uniformly colored rectangle).
         
         @param size the size of the frame
         @param color the color of the frame
         */
        Frame(sf::Vector2i size = sf::Vector2i(0, 0), sf::Color color = sf::Color::White)
        : texture(&getDummyTexture())
        , area(sf::Vector2i(0, 0), size)
        , color(color)
        {
            // That's it
        }

        /*!
         @brief Constructor
         
         This constructor can be used to create a frame with a texture.
         
         @param texture the texture of the frame
         @param area the subrect of the texture that should be displayed
         @param color the color of the frame, usually the default value, i.e. white
         */
        Frame(sf::Texture const& texture, sf::IntRect area, sf::Color color = sf::Color::White)
        : texture(&texture)
        , area(area)
        , color(color)
        {
            // That's it
        }

        sf::Texture const* texture; //!< the texture of the frame
        sf::IntRect area; //!< the area of the texture to be rendered
        sf::Color color; //!< the color of the frame

    private:
        /*
         In order to create uniformly colored frames we need a dummy texture.
         But we don't want a texture to be created before the main() function
         so we use our Singleton utility and create the dummy texture at the
         last moment.
         
         Hopefully the user won't use any global Frame object!
         */
        struct DummyTexture { sf::Texture texture; };
        static sf::Texture& getDummyTexture()
        {
            return Singleton<DummyTexture>::getInstance().texture;
        }
    };
    
}

#endif // __SFTOOLS_FRAME_HPP__
