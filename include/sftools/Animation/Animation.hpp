/*

 sftools - Copyright (c) 2012 Marco Antognini

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

namespace sftools
{

    class Animation : public sf::Drawable, public sf::Transformable
    {
    public:
        Animation(FrameStream const& stream, sf::Time initialTime = sf::Time::Zero)
        : m_stream(0)
        {
            setFrameStream(stream);
            resetTime(initialTime);
        }
        
        void setFrameStream(FrameStream const& stream)
        {
            m_stream = &stream;

            updateRender();
        }

        void resetTime(sf::Time initialTime = sf::Time::Zero)
        {
            m_timeElapsed = initialTime;

            updateRender();
        }

        void update(sf::Time dt) // We don't use an internal clock so the user can apply some time speed factor
        {
            m_timeElapsed += dt;
            
            updateRender();
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // Note : if the stream was not set it will simply draw nothing, like a sprite without any texture

            states.transform *= getTransform();
            target.draw(m_sprite, states);
        }

    private:
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
        FrameStream const* m_stream;
        sf::Time m_timeElapsed;
        sf::Sprite m_sprite;
    };

}

#endif // __SFTOOLS_ANIMATION_HPP__
