
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
