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
 \file animated.cpp
 \brief Implementation of Animated class.
*/

#include "animated.hpp"

/*!
 \namespace sftools
 \brief namespace containing tools using SFML library.
*/
namespace sftools {
 
Animated::Animated(float time, bool play, bool loop)
: my_time(time)
, my_clock(0.f)
, am_i_paused(!play)
, am_i_on_loop(loop)
, my_anim(0)
, my_current_frame(0)
{
    /* Nothing else. */
}
 
Animated::Animated(const Anim& anim, float time, bool play, bool loop)
: my_time(time)
, my_clock(0.f)
, am_i_paused(!play)
, am_i_on_loop(loop)
, my_anim(&anim)
, my_current_frame(0)
{
    /* Nothing else. */
}

Animated::~Animated()
{
	// Nothing to do.
}
 
void Animated::SetAnim(const Anim& anim, bool play)
{
    my_anim = &anim;
 
    Stop();
    
    if (play)
        Play();
}
 
void Animated::UnsetAnim()
{
    my_anim = 0;
 
    Stop();
}
 
const Anim* Animated::GetAnim() const
{
    return (my_anim) ? my_anim : 0;
}
 
void Animated::SetFrame(std::size_t N)
{
    if (my_anim)
    {
        if (my_anim->Size() > 0 && // If anim is not empty and,
            my_anim->Size() - 1 >= N) // N is not an overflow value.
        {
            // Setting up the var. 
            SetColor((*my_anim)[N].my_color);
            my_current_frame = N;
        }
    }
}
 
std::size_t Animated::GetCurrentFrame() const
{
    return my_current_frame;
}
 
void Animated::SetFrameTime(float time)
{
    my_time = time;
}
 
float Animated::GetFrameTime() const
{
    return my_time;
}
 
void Animated::SetLoop(bool loop)
{
    am_i_on_loop = loop;
}
 
bool Animated::IsLoop() const
{
    return am_i_on_loop;
}
 
void Animated::Pause()
{
    am_i_paused = true;
    my_clock.Pause();
}
 
void Animated::Play()
{
    am_i_paused = false;
    my_clock.Start();
}
 
void Animated::Stop()
{
    SetFrame(0);
    am_i_paused = true;
    my_clock.Reset();
    my_clock.Pause();
}
 
bool Animated::IsPaused() const
{
    return am_i_paused;
}
 
bool Animated::IsStopped() const
{
    // True if three things :
    return (am_i_paused && // first : the animation must be in 'pause' mode ;
            my_current_frame == 0 && // second : it must be at its beginning ;
            my_clock.GetElapsedTime() <= 0.01f); // third : no time 
    						 // must be elapsed.
}
 
void Animated::Update()
{
    // Update only in certain conditions.
 
    // If not in 'pause' mode, and has a valid Anim... 
    if (!am_i_paused && my_anim)
    {
        // If time spend is greater or equal than time between two frames...
        if (my_clock.GetElapsedTime() >= my_time)
        {
            // Setting up for the next frame.
	    my_clock.Reset();
 
            if (my_current_frame + 1 < my_anim->Size())
                ++my_current_frame;
            else
            {
                // The animation is ended.
                // Is the animation a loop ?
                if (am_i_on_loop)
                    my_current_frame = 0;
                else
                    Stop();
            }
 
            SetFrame(my_current_frame);
        }
    }
}

void Animated::Render(sf::RenderTarget&) const
{
	// If the anim is set...
	if (my_anim)
	{
		// Get the current Frame.
		const Frame& f = (*my_anim)[my_current_frame];

		// Get the size.
		float width  = static_cast<float>(f.my_rect.GetWidth());
		float height = static_cast<float>(f.my_rect.GetHeight());

		// Check if the image is valid.
		if (f.my_image)
		{
			// Set the texture
			f.my_image->Bind();

			// Calculate the texture coordinates
			sf::FloatRect rect = 
					f.my_image->GetTexCoords(f.my_rect);

			// Draw the animation's triangles
			glBegin(GL_QUADS);
            			glTexCoord2f(rect.Left,  rect.Top);    
				glVertex2f(0,     0);
			        
				glTexCoord2f(rect.Left,  rect.Bottom); 
				glVertex2f(0,     height);
            			
				glTexCoord2f(rect.Right, rect.Bottom); 
				glVertex2f(width, height);
            			
				glTexCoord2f(rect.Right, rect.Top);    
				glVertex2f(width, 0) ;
			glEnd();
		}
		else
		{
        		// Disable texturing
        		glDisable(GL_TEXTURE_2D);

        		// Draw the animation's triangles
        		glBegin(GL_QUADS);
            			glVertex2f(0,     0);
            			glVertex2f(0,     height);
            			glVertex2f(width, height);
            			glVertex2f(width, 0);
		        glEnd();
		}
	}	
	// Else we do not draw anything.
}

} // sftools namespace

