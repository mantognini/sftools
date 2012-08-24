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


#ifndef ANIM_HPP
#define ANIM_HPP

/*!
 \file anim.hpp
 \brief Definition of Anim class.
*/

#include <vector>
#include "frame.hpp"

/*!
 \namespace sftools
 \brief namespace containing tools using SFML library.
*/
namespace sftools {
 
/*!
 \class Anim
 \brief This class is almost a simple vector interface.
*/
class Anim : public sf::Resource<Anim>
{
    public :
    	/*!
    	 \brief default ctor.
    	*/
    	Anim(void)
    	: my_frames()
    	{
    		/* Nothing else. */
    	}
    	
        /*!
         \brief Add a new frame to the animation.
         \param frame : frame to add.
         \return Position of the Frame in the animation.
        */
        std::size_t PushFrame(const Frame& frame)
        {
            my_frames.push_back(frame);
            return my_frames.size() - 1;
        }
 
        /*!
         \brief Get the number of frame(s).
         \return Number of frame(s).
        */
        std::size_t Size() const
        {
            return my_frames.size();
        }
 
        /*!
         \brief Get the Nth frame.
         \param N : Nth frame in the animation.
         \warning : Does not check the given value ! 
        */
        Frame& operator[](const size_t N)
        {
            return my_frames[N];
        }

        /*!
         \brief Get the Nth frame. Const function.
         \param N : Nth frame in the animation.
         \warning : Does not check the given value ! 
        */
        const Frame& operator[](const size_t N) const
        {
            return my_frames[N];
        }
 
    private :
        /*!
         \brief Vector of Frame used to represent the animation.
        */
        std::vector<Frame> my_frames;
};

} // sftools namespace
 
#endif // ANIM_HPP


