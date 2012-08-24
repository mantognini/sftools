/*
  frame_anim_animated
  Copyright (C) 2009 Marco Antognini (hiura@romandie.com)
  License : CC-BY-SA 3.0
  	You can find the full legal code at 
  	http://creativecommons.org/licenses/by-sa/3.0/
  	or in the local file cc-by-sa-3.0-legalcode.html .
  	Here is only an abstract :

  You are free :
  	to Share — to copy, distribute and transmit the work
	to Remix — to adapt the work

  Under the following conditions :
  	Attribution. You must attribute the work in the manner 
		specified by the author or licensor (but not 
		in any way that suggests that they endorse you
		or your use of the work).
	Share Alike. If you alter, transform, or build upon this 
		work, you may distribute the resulting work only 
		under the same, similar or a compatible license.

  For any reuse or distribution, you must make clear to others 
  	the license terms of this work. The best way to do this 
	is with a link to this
       	(http://creativecommons.org/licenses/by-sa/3.0/) web page.
  
  Any of the above conditions can be waived if you get 
  	permission from the copyright holder.

  Nothing in this license impairs or restricts the author's 
  	moral rights.
  	
  SPECIAL THANKS TO SFML LIBRARY (See http://sfml-dev.org) 
  AND to Laurent Gomila.

*/


#ifndef FRAME_HPP
#define FRAME_HPP

/*!
 \file frame.hpp
 \brief Contains Frame class definition.
*/

#include <SFML/Graphics.hpp>

/*!
 \namespace sftools
 \brief namespace containing tools using SFML library.
*/
namespace sftools {

/*!
 \class Frame
 \brief A Frame is made up of a kind of pointer to a sf::Image, a sf::IntRect 
 	and a sf::Color.
 \note We do not ask the user for a pointer, like sf::Sprite does.
*/
class Frame
{
public :
    /*!
     \brief Default Ctor.
     \param color : sf::Color to use (default value : white).
    */
    Frame(const sf::Color& color = sf::Color::White);

    /*!
     \brief Copy ctor.
     \param copy : Frame to copy.
    */
    Frame(const Frame& copy);

    /*!
     \brief Full ctor.
     \param image : sf::Image to use.
     \param rect : sf::IntRect of the image to use.
     \param color : sf::Color to use (default value : white).
    */
    Frame(const sf::Image& image, const sf::IntRect& rect, 
		const sf::Color& color = sf::Color::White);

    /*!
     \brief Near full ctor.
     \param image : sf::Image to use.
     \param color : sf::Color to use (default value : white).
     \note The sf::IntRect is automatically fit to the size of the image.
    */
    Frame(const sf::Image& image, const sf::Color& color = sf::Color::White);

    /*!
     \brief Kind of pointer to the used sf::Image.
    */
    sf::ResourcePtr<sf::Image> my_image;

    /*!
     \brief sf::IntRect used to select an area of my_image.
    */
    sf::IntRect my_rect;

    /*!
     \brief Color of the Frame.
    */
    sf::Color my_color;
};

} // sftools namespace

#endif // FRAME_HPP


