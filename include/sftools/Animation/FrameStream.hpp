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
 @file sftools/Animation/FrameStream.hpp
 @brief Define FrameStream abstract class
 */

#ifndef __SFTOOLS_FRAMESTREAM_HPP__
#define __SFTOOLS_FRAMESTREAM_HPP__

#include <SFML/System/Time.hpp>

#include <sftools/Animation/Frame.hpp>

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{
    /*!
     @class FrameStream
     @brief Abstract class for animation frames stream management
     
     @see Frame
     @see LoopFrameStream
     @see Animation
     */
    class FrameStream
    {
    public:
        /*!
         @brief Seek and fetch a frame at a given point in time
         
         Subclasses must implement this function in order to provide the
         Animation class all the tools required to render the animation.
         
         @param time time elapsed since the start of the animation
         @return the frame for the given point in time

         @see LoopFrameStream::getFrameAt
         */
        virtual Frame getFrameAt(sf::Time time) const = 0;

        /*!
         @brief Virtual destructor
         
         Does nothing special. It's here for inheritance purposes.
         */
        virtual ~FrameStream()
        {
            // No clean up
        }
    };
    
}

#endif // __SFTOOLS_FRAMESTREAM_HPP__
