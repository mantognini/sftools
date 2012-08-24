/*
  pausableclock
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



#ifndef PAUSABLECLOCK_HPP
#define PAUSABLECLOCK_HPP

/*!
 \file pausableclock.hpp
 \brief Definition and implementation of PausableClock class.
*/

#include <SFML/System.hpp>

/*!
 \namespace sftools
 \brief namespace containing tools using SFML library.
*/
namespace sftools {

/*!
 \class PausableClock
 \brief sf::Clock with Pause function.
*/
class PausableClock
{
	public :
		/*!
		 \brief Semi-default ctor.
		 \param paused : does the clock start paused ?
		*/
		PausableClock(bool paused = false)
		: am_i_paused(paused)
		, my_time(0.f)
		, my_clock()
		{
			// Nothing else.
		}

		/*!
		 \brief Set the clock in 'pause' mode.
		*/
		void Pause(void)
		{
			// If not yet paused...
			if (!am_i_paused)
			{
				am_i_paused = true;
				my_time += my_clock.GetElapsedTime();
			}
		}

		/*!
		 \brief Start the clock (again).
		*/
		void Start(void)
		{
			// If not yet started...
			if (am_i_paused)
			{
				my_clock.Reset();
				am_i_paused = false;
			}
		}

		/*!
		 \brief Get the time elapsed since last Reset.
		*/
		float GetElapsedTime(void) const
		{
			// If not paused...
			if (!am_i_paused)
				return my_time + my_clock.GetElapsedTime();
			else
				return my_time;
		}

		/*!
		 \brief Reset the clock.
		 \param paused : does the clock start paused ?
		*/
		void Reset(bool paused = false)
		{
			am_i_paused = paused;
			my_time = 0.f;
			my_clock.Reset();
		}
	
	private :
		/*!
		 \brief Is the PausableClock paused ?
		*/
		bool am_i_paused;

		/*!
		 \brief Time buffer.
		*/
		float my_time;


		/*!
		 \brief The sf::Clock used.
		*/
		sf::Clock my_clock;
};

} // sftools namespace

#endif // PAUSABLECLOCK_HPP


