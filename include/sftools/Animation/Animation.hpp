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
 @file sftools/Animation/Animation.hpp
 @brief Define Animation class
 */

#ifndef __SFTOOLS_ANIMATION_HPP__
#define __SFTOOLS_ANIMATION_HPP__

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <sftools/Animation/FrameStream.hpp>

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{

    /*!
     @class Animation
     @brief Drawable capable of rendering an animation based on a stream of frames
     
     All sf::Transformable and sf::Drawable methods are publicly available.
     
     @see Frame
     @see FrameStream
     */
    class Animation : public sf::Drawable, public sf::Transformable
    {
    public:
        /*!
         @brief Constructor

         @param stream frame stream
         @param initialTime by default the animation start a time zero but 
                an offset can bet given
         */
        Animation(FrameStream const& stream, sf::Time initialTime = sf::Time::Zero)
        : m_stream(0)
        {
            setFrameStream(stream);
            restart(initialTime);
        }

        /*!
         @brief Change the animation stream
         
         @param stream the new stream to use
         */
        void setFrameStream(FrameStream const& stream)
        {
            m_stream = &stream;

            updateRender();
        }

        /*!
         @brief Restart the animation
         
         @param initialTime optional time offset
         */
        void restart(sf::Time initialTime = sf::Time::Zero)
        {
            m_timeElapsed = initialTime;

            updateRender();
        }

        /*!
         @brief Update the animation frame

         @note the dt parameter is used to allow custom time handling very
         easily : for example you can apply a factor on the elapsed time to
         create bullet time effect.
         
         @param dt time elapsed since the last update
         */
        void update(sf::Time dt)
        {
            m_timeElapsed += dt;
            
            updateRender();
        }

        /*!
         @brief Implement sf::Drawable::draw() method
         
         Look at <a href="http://www.sfml-dev.org/documentation/2.0/classsf_1_1Drawable.php">SFML's documentation of sf::Drawable</a>.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // Note : if the stream was not set it will simply draw nothing, like a sprite without any texture

            states.transform *= getTransform();
            target.draw(m_sprite, states);
        }

    private:
        /*!
         @brief Internal render updater
         
         Update our sprite
         */
        void updateRender()
        {
            if (m_stream)
            {
                Frame frame = m_stream->getFrameAt(m_timeElapsed);

                if (frame.texture) m_sprite.setTexture(*frame.texture);
                m_sprite.setTextureRect(frame.area);
                m_sprite.setColor(frame.color);
            }
        }

    private:
        FrameStream const* m_stream; //!< frame stream for the animation
        sf::Time m_timeElapsed; //!< current time position in the animation
        sf::Sprite m_sprite; //!< internal renderer
    };

}

#endif // __SFTOOLS_ANIMATION_HPP__
