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


#include "animated.hpp"
#include <iostream>

using namespace sftools;

enum DIRECTION {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};

/// Load an anim, with a constant format, from a picture.
Anim AnimFromImage(const sf::Image& img, int colone_px = 0)
{
    Anim ret;
    const int width_px(45);
    for (int i = 0; i < 4; ++i)
        ret.PushFrame(Frame(img, 
                            sf::IntRect(width_px * i, 
                                        colone_px * 64, 
                                        width_px * (1 + i), 
                                        (colone_px + 1) * 64)));
    return ret;
}

/// Update the boy's anim and made his moves.
void UpdateBoy(Animated& boy, const sf::Input& input, DIRECTION& direction, 
		float frame_time, Anim anims[4])
{
    // Update the boy.
    boy.Update();

    // If going upward...
    if (input.IsKeyDown(sf::Key::Up))
    {
        // Don't reset the anim.
        if (direction != UP) 
        {
            boy.SetAnim(anims[UP], true); // Set the new anim, and play it.
            direction = UP;
        }
        else
            boy.Play(); // In case of not currently playing.

        // Move the boy.
        boy.Move(0, -100 * frame_time);
    }

    // downward...
    else if (input.IsKeyDown(sf::Key::Down))
    {
        // Working the same.
        if (direction != DOWN) 
        {
            boy.SetAnim(anims[DOWN], true);
            direction = DOWN;
        }
        else
            boy.Play();
        
            
        boy.Move(0, 100 * frame_time);
    }

    // leftward...
    else if (input.IsKeyDown(sf::Key::Left))
    {
        // Working the same.
        if (direction != LEFT) 
        {
            boy.SetAnim(anims[LEFT], true);
            direction = LEFT;
        }
        else
            boy.Play();
        
        boy.Move(-100 * frame_time, 0);
    }

    // rightward...
    else if (input.IsKeyDown(sf::Key::Right))
    {
        // Working the same.
        if (direction != RIGHT) 
        {
            boy.SetAnim(anims[RIGHT], true);
            direction = RIGHT;
        }
        else
            boy.Play();

        boy.Move(100 * frame_time, 0);
    }
    
    // Doesn't move...
    else
        boy.Stop();
}

/// Our main function.
int main(int, char**)
{
    // Our beautiful window. :)
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), 
		    		"sftool::animation sample");

    // Loading a picture with four anims.
    sf::Image char_anim;
    if (!char_anim.LoadFromFile("character.png"))
    {
        std::cerr << "Error : cannot load character.png.\n";
        return EXIT_FAILURE;
    }
    char_anim.CreateMaskFromColor(sf::Color::Black);

    // Four anims : up, down, left, right.
    Anim go[4];
    for (int i = 0; i < 4; ++i)
        go[i] = AnimFromImage(char_anim, i);
 
    // In 'pause' and 'loop' mode ; frame time is 0.1 s ; looking upward :
    Animated boy(go[UP], 0.1f);
    boy.SetCenter(20, 32);
    boy.SetPosition(400, 300);
    DIRECTION direction = UP;
 
    // Main loop.
    sf::Event event;
    bool running = true;
    while (running)
    {
        // Events loop.
        while (window.GetEvent(event))
        {
            // Here we just deal with close event.
            // Moving is handle by sf::Input.
            switch (event.Type)
            {
                case sf::Event::Closed:
                    running = false;
                    break;
 
                case sf::Event::KeyReleased:
                    switch (event.Key.Code)
                    {
                        case sf::Key::Escape:
                            running = false;
                            break;
                            
                        default:
                        	break;
                    }
                    break;
                    
            	default:
            		break;
            }
        }
 
        // Make all updates.
        UpdateBoy(boy, window.GetInput(), direction, 
		  window.GetFrameTime(), go);
	
        // Draw everything.
        window.Clear(); 
        window.Draw(boy);
        window.Display();
    }
 
    return EXIT_SUCCESS;
}


