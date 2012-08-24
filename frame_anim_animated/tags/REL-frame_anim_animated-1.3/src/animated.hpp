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


#ifndef ANIMATED_HPP
#define ANIMATED_HPP
 
/*!
 \file animated.hpp
 \brief Definition of Animated class.
*/

#include "anim.hpp"
#include "pausableclock.hpp"
 
/*!
 \namespace sftools
 \brief namespace containing tools using SFML library.
*/
namespace sftools {

/*!
 \class Animated
 \brief An animated sf::Sprite.
 \details It is made up of two things. First the time between each Frames. 
 	And a pointer to the Animation that will be drawn. \n
        This special sf::Sprite provide some features like Play, Pause, 
	Stop or Loop.
*/
class Animated : public sf::Drawable
{
    public :
        /*!
         \brief Semi-default ctor.
         \param time : Amount of time between two frames.
         \param play : Does start immediately in 'play' mode ?
         \param loop : Does the animation must be played in loop ?
        */
        Animated(float time = 0.f, bool play = false, bool loop = true);
 
        /*!
         \brief Ctor.
         \param anim : Anim used.
         \param time : Amount of time between two frames.
         \param play : Does start immediately in 'play' mode ?
         \param loop : Does the animation must be played in loop ?
        */
        Animated(const Anim& anim, float time = 0.f, bool play = false,
		 bool loop = true);
        
        /*!
         \brief Virtual dtor.
        */
        virtual ~Animated();
 
        /*!
         \brief Set another Anim.
         \param anim : Anim used.
         \param play : Does start immediately in 'play' mode ?
        */
        void SetAnim(const Anim& anim, bool play = false);
 
        /*!
         \brief Unset the Anim.
        */
        void UnsetAnim();
 
        /*!
         \brief Get the Anim used.
         \return A pointer to the Anim.
         \warning 0 can be returned.
        */
        const Anim* GetAnim() const;
 
        /*!
         \brief Jump to a given Frame.
         \param N : Nth Frame of Anim.
        */
        void SetFrame(std::size_t N);
 
        /*!
         \brief Get the current Frame.
         \return Return the 'id' of the current Frame.
        */
        std::size_t GetCurrentFrame() const;
 
        /*!
         \brief Set a new time between two frames.
         \param time : Amount of time between two frames.
        */
        void SetFrameTime(float time);
 
        /*!
         \brief Get the time between two frames.
         \return Amount of time between two frames.
        */
        float GetFrameTime() const ;
 
        /*!
         \brief Does the animation must be played in loop ?
         \param loop : Your choice.
        */
        void SetLoop(bool loop);
 
        /*!
         \brief Tell if the animation is in 'loop' mode.
         \return What d'you think ? :p
        */
        bool IsLoop() const;
 
        /*!
         \brief Set the animation in 'pause' mode.
        */
        void Pause();
 
        /*!
         \brief Set the animation in 'play' mode.
        */
        void Play();
 
        /*!
         \brief Stop the animation.
         \note Also rewind the animation to its beginning.
        */
        void Stop();
 
        /*!
         \brief Tell if the animation is in 'pause' mode.
         \return What d'you think ? :p
        */
        bool IsPaused() const;
 
        /*!
         \brief Tell if the animation is stopped ; means at beginning and 
	 	in 'pause' mode.
         \return What d'you think ? :p
        */
        bool IsStopped() const;
 
        /*!
         \brief Update the Animation at the level of Frame.
         \note Must be called once before each drawing.
        */
        void Update();

    protected :
        /*!
         \brief \see sf::Drawable::Render .
        */
        virtual void Render(sf::RenderTarget&) const;
 
    private :
        /*!
         \brief Amount of time between two frames.
        */
        float my_time;
 
        /*!
         \brief Time elapsed since current frame is 'activ'.
        */
	PausableClock my_clock;
 
        /*!
         \brief Tell if the animation is in 'pause' mode.
        */
        bool am_i_paused;
 
        /*!
         \brief Tell if the animation is in 'loop' mode.
        */
        bool am_i_on_loop;
 
        /*!
         \brief Anim used.
        */
	sf::ResourcePtr<Anim> my_anim;
 
        /*!
         \brief Current 'position' in the Anim.
        */
        std::size_t my_current_frame;
};

} // sftools namespace
 
#endif // ANIMATED_HPP


