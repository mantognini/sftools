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
 @file sftools/Animation/LoopFrameStream.hpp
 @brief Define LoopFrameStream class
 */

#ifndef __SFTOOLS_LOOPFRAMESTREAM_HPP__
#define __SFTOOLS_LOOPFRAMESTREAM_HPP__

#include <SFML/System/Time.hpp>

#include <sftools/Animation/FrameStream.hpp>

#include <vector>
#include <algorithm>
#include <stdexcept>

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{

    /*!
     @brief Define a animation's frame stream based on a sprite sheet
     
     @note Like sf::Sprite, LoopFrameStream doesn't own the texture. 
     You have to keep it 'alive' for the lifetime of the stream that uses it,
     otherwise you'll get some undefined behaviour.
     
     @todo It could be usefull to provide a 'combine(LoopFrameStream)' method
     to use more than one sprite sheet for an animation.
     
     @todo In the same vein a 'add(Frame)' or 'add(begin, end)' could be useful
     too.
     
     @todo Does 'loop == false' means the animation should keep displaying the
     last frame or display nothing at all when the last frame is reached ?
     Currently the first solution is implemented but it might be more cleaver
     to implement the second one. Or add a LoopPolicy..
     
     @see FrameStream
     @see Animation
     @see Frame
     */
    class LoopFrameStream : public FrameStream
    {
    public:
        /*!
         @enum HorizontalStartFromPolicy
         @brief Define how a sprite sheet should be horitontally read.
         
         i.e. from left to right or from right to left ?
         
         @see LoopFrameStream::Settings
         @see VerticalStartFromPolicy
         @see PrecedencePolicy
         */
        enum HorizontalStartFromPolicy
        {
            FromLeft = 0, //!< Read the sprite sheet from left to right
            FromRight     //!< Read the sprite sheet from right to left
        };

        /*!
         @enum VerticalStartFromPolicy
         @brief Define how a sprite sheet should be vertically read.
         
         i.e. from top to bottom or from bottom to top ?
         
         @see LoopFrameStream::Settings
         @see HorizontalStartFromPolicy
         @see PrecedencePolicy
         */
        enum VerticalStartFromPolicy
        {
            FromTop = 0, //!< Read the sprite sheet from top to bottom
            FromBottom   //!< Read the sprite sheet from bottom to top
        };

        /*!
         @enum PrecedencePolicy
         @brief Define how a sprite sheet should be read.
         
         i.e. by row or by column ?

         @see LoopFrameStream::Settings
         @see VerticalStartFromPolicy
         @see HorizontalStartFromPolicy
         */
        enum PrecedencePolicy
        {
            HorizontalFirst = 0, //!< Read the sprite sheet by row
            VerticalFirst        //!< Read the sprite sheet by column
        };

        /*!
         @struct Settings
         @brief Combine horizontal, vertical and precedence policies together
         to define how a sprite sheet should be read
         
         @see PrecedencePolicy
         @see VerticalStartFromPolicy
         @see HorizontalStartFromPolicy
         */
        struct Settings
        {
            /*!
             @brief Constructor

             @param horizontalPolicy tell which horizontal policy should be used
             @param verticalPolicy tell which vertical policy should be used
             @param precedencePolicy tell which precedence policy should be used
             */
            Settings(HorizontalStartFromPolicy horizontalPolicy = FromLeft,
                     VerticalStartFromPolicy   verticalPolicy   = FromTop,
                     PrecedencePolicy          precedencePolicy = HorizontalFirst)
            : horizontalPolicy(horizontalPolicy)
            , verticalPolicy(verticalPolicy)
            , precedencePolicy(precedencePolicy)
            {
                // That's it
            }

            HorizontalStartFromPolicy horizontalPolicy; //!< Tell which horizontal policy should be used
            VerticalStartFromPolicy   verticalPolicy;   //!< Tell which vertical policy should be used
            PrecedencePolicy          precedencePolicy; //!< Tell which precedence policy should be used
        };
        
    public:
        /*!
         @brief Default constructor
         
         Doesn't load any frame at all.
         
         @note You must call create() at least once before usign this stream in
         an animation
         */
        LoopFrameStream()
        : m_count(0)
        {
            // We don't care about setting all default values
            // because create will be called
        }

        /*!
         @brief Copy constructor
         
         @param stream object to copy
         */
        LoopFrameStream(LoopFrameStream const& stream)
        : m_count(stream.m_count)
        , m_frameTime(stream.m_frameTime)
        , m_loop(stream.m_loop)
        , m_frames(stream.m_frames)
        {
            // That's it
        }

        /*!
         @brief Constructor
         
         Load a sprite sheet

         @param texture sprite sheet
         @param frameSize size of a frame
         @param frameCount number of frame as a vector where x is the number of column and y is the number of row
         @param frameTime time by frame
         @param loop define if the animation should loop or stay on the last frame
         @param settings settings used to read the sprite sheet
         
         @throw std::invalid_argument if the number of frame is zero
         @throw std::invalid_argument if the frame time is zero

         @see create()
         */
        LoopFrameStream(sf::Texture const& texture,
                        sf::Vector2i frameSize,
                        sf::Vector2u frameCount,
                        sf::Time frameTime,
                        bool loop = true,
                        Settings const& settings = Settings())
        {
            create(texture, frameSize, frameCount, frameTime, loop, settings);
        }

        /*!
         @brief Copy assignment operator
         
         @param rhs stream to be copied
         @return this stream
         */
        LoopFrameStream& operator=(LoopFrameStream const& rhs)
        {
            m_count       = rhs.m_count;
            m_frameTime   = rhs.m_frameTime;
            m_loop        = rhs.m_loop;
            m_frames      = rhs.m_frames;
            
            return *this;
        }

        /*!
         @brief Load a sprite sheet

         @param texture sprite sheet
         @param frameSize size of a frame
         @param frameCount number of frame as a vector where x is the number of column and y is the number of row
         @param frameTime time by frame
         @param loop define if the animation should loop or stay on the last frame
         @param settings settings used to read the sprite sheet

         @throw std::invalid_argument if the number of frame is zero
         @throw std::invalid_argument if the frame time is zero
         */
        void create(sf::Texture const& texture,
                    sf::Vector2i frameSize,
                    sf::Vector2u frameCount,
                    sf::Time frameTime,
                    bool loop = true,
                    Settings const& settings = Settings())
        {
            // First, check some assertions
            if (frameCount == sf::Vector2u(0, 0)) throw std::invalid_argument("frameCount can't be 0");
            if (frameTime == sf::Time::Zero)      throw std::invalid_argument("frameTime can't be 0");

            // Then copy some stuff
            m_count     = frameCount.x * frameCount.y;
            m_frameTime = frameTime;
            m_loop      = loop;

            // And initialize some other stuff
            m_frames.clear();
            m_frames.reserve(m_count);

            // Now we can create the frames

            // Define the first point according to the choosen policies
            int const initX = settings.horizontalPolicy == FromLeft ? 0 : texture.getSize().x - frameSize.x;
            int const initY = settings.verticalPolicy   == FromTop  ? 0 : texture.getSize().y - frameSize.y;
            int const stepX = settings.horizontalPolicy == FromLeft ? frameSize.x : -frameSize.x;
            int const stepY = settings.verticalPolicy   == FromTop  ? frameSize.y : -frameSize.y;
            int const endX  = initX + frameCount.x * stepX;
            int const endY  = initY + frameCount.y * stepY;

            // Create the invariants
            int x = 0;
            int y = 0;

            // Set up the loop order (X or Y first ?) according to the choosen policy
            int& first  = settings.precedencePolicy == HorizontalFirst ? x : y;
            int& second = settings.precedencePolicy == HorizontalFirst ? y : x;
            int const& init1st = settings.precedencePolicy == HorizontalFirst ? initX : initY;
            int const& init2nd = settings.precedencePolicy == HorizontalFirst ? initY : initX;
            int const step1st = settings.precedencePolicy == HorizontalFirst ? stepX : stepY;
            int const step2nd = settings.precedencePolicy == HorizontalFirst ? stepY : stepX;
            int const end1st = settings.precedencePolicy == HorizontalFirst ? endX  : endY;
            int const end2nd = settings.precedencePolicy == HorizontalFirst ? endY  : endX;

            // Finally we can go through the process of creating the frames
            for (first = init1st; first < end1st; first += step1st)
            {
                for (second = init2nd; second < end2nd; second += step2nd)
                {
                    sf::Vector2i point(x, y);
                    sf::IntRect area(point, frameSize);
                    m_frames.push_back(Frame(texture, area));
                }
            }
        }

        /*!
         @brief Seek and fetch a frame at a given point in time
         
         See FrameStream::getFrameAt() for more details.

         @param time time elapsed since the start of the animation
         @return the frame for the given point in time
         
         @throw std::runtime_error if the stream was not yet loaded
         
         @see FrameStream::getFrameAt()
         */
        virtual Frame getFrameAt(sf::Time time) const
        {
            if (m_count == 0) throw std::runtime_error("the stream was not properly initialized");

            unsigned int frameIndex = time.asMilliseconds() / m_frameTime.asMilliseconds();

            if (m_loop) frameIndex %= m_count;
            else        frameIndex  = std::min(frameIndex, m_count - 1);

            return m_frames[frameIndex];
        }
        
	private:
        /* Setting variables */
        unsigned int m_count; //!< number of frames
        sf::Time m_frameTime; //!< frame time
        bool m_loop; //!< loop mode

        /* State */
        std::vector<Frame> m_frames; //!< set of frames
    };

}

#endif // __SFTOOLS_LOOPFRAMESTREAM_HPP__
