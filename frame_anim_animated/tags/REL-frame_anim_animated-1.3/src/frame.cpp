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


/*!
 \file frame.cpp
 \brief Implementation of Frame class.
*/
 
#include "frame.hpp"
 
/*!
 \namespace sftools
 \brief namespace containing tools using SFML library.
*/
namespace sftools {

Frame::Frame(const sf::Color& color)
: my_image(0)
, my_rect()
, my_color(color)
{
    /* Nothing else. */
}
 
Frame::Frame(const Frame& copy)
: my_image(copy.my_image)
, my_rect(copy.my_rect)
, my_color(copy.my_color)
{
    /* Nothing else. */
}
 
Frame::Frame(const sf::Image& image, const sf::IntRect& rect, 
		const sf::Color& color)
: my_image(&image)
, my_rect(rect)
, my_color(color)
{
    /* Nothing else. */
}
 
Frame::Frame(const sf::Image& image, const sf::Color& color)
: my_image(&image)
, my_rect()
, my_color(color)
{
    if (my_image)
        my_rect = sf::IntRect(0, 0, my_image->GetWidth(), 
				my_image->GetHeight());
}


} // sftools namespace

