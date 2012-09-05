/*

 sftools - Copyright (c) 2012 Macro Antognini

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
 @file sftools/PausableClock.hpp
 @brief Defines PausableClock
 
 @todo write doc
 */

#ifndef __SFTOOLS_BASE_PAUSABLECLOCK_HPP__
#define __SFTOOLS_BASE_PAUSABLECLOCK_HPP__

#include <SFML/System/Clock.hpp>

namespace sftools
{
    class PausableClock
    {
    public:
        PausableClock()
        {
            reset();
        }

        sf::Time reset(bool start = false)
        {
            sf::Time time = getElapsedTime();

            m_time = sf::Time::Zero;
            m_state = STOPPED;

            if (start) resume();

            return time;
        }

        sf::Time pause()
        {
            if (isRunning())
            {
                m_state = PAUSED;
                m_time += m_clock.getElapsedTime();
            }
            return getElapsedTime();
        }

        sf::Time resume()
        {
            if (!isRunning())
            {
                m_state = RUNNING;
                m_clock.restart();
            }
            return getElapsedTime();
        }

        sf::Time toggle()
        {
            if (isRunning())    pause();
            else                resume();

            return getElapsedTime();
        }

        bool isRunning() const
        {
            return m_state == RUNNING;
        }

        sf::Time getElapsedTime() const
        {
            switch (m_state) {
                case STOPPED:
                    return sf::Time::Zero;

                case RUNNING:
                    return m_time + m_clock.getElapsedTime();

                case PAUSED:
                    return m_time;
            }
        }

        operator sf::Time() const
        {
            return getElapsedTime();
        }

    private:
        enum { STOPPED, RUNNING, PAUSED } m_state;
        sf::Time m_time;
        sf::Clock m_clock;
    };
}


#endif // __SFTOOLS_BASE_PAUSABLECLOCK_HPP__
