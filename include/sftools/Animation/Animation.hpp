
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
