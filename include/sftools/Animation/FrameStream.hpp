
#ifndef __SFTOOLS_FRAMESTREAM_HPP__
#define __SFTOOLS_FRAMESTREAM_HPP__

#include <SFML/System/Time.hpp>
#include <sftools/Animation/Frame.hpp>

namespace sftools
{
    
    class FrameStream
    {
    public:
        virtual Frame getFrameAt(sf::Time time) const = 0;

        virtual ~FrameStream()
        {
            // No clean up
        }
    };
    
}

#endif // __SFTOOLS_FRAMESTREAM_HPP__
