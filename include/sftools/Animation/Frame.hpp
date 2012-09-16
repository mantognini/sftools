/*

 sftools - Copyright (c) 2012 Marco Antognini

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

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{
    
    /*!
     @class Frame
     @brief Hold the data required to render a frame
     */
    struct Frame
    {
        Frame(sf::IntRect area = sf::IntRect(0, 0, 0, 0), sf::Color color = sf::Color::White)
        : texture(0)
        , area(area)
        , color(color)
        {
            // That's it
        }

        Frame(sf::Texture const& texture, sf::IntRect area, sf::Color color = sf::Color::White)
        : texture(&texture)
        , area(area)
        , color(color)
        {
            // That's it
        }

        sf::Texture const* texture;
        sf::IntRect area;
        sf::Color color;
    };
    
}

#endif // __SFTOOLS_FRAME_HPP__
