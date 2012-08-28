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
 @file sftools/Singleton/Singleton.hpp
 @brief Defines Singleton tool
 */

#ifndef __SFTOOLS_SINGLETON_HPP__
#define __SFTOOLS_SINGLETON_HPP__

#include <sftools/Common.hpp>

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{
    namespace priv
    {
        template <typename T>
        class DefaultNew;
    }

    /*!
     @class Singleton
     @brief TODO
     
     TODO (example)
     
     @note With C++11 we could do even better : by using variadic template we
     can customize more easily the construction of the unique instance and
     probably even inherit from `T` so the singleton object could be used
     everywhere `T` is used. However there might be issues with NonCopyable
     and NonInstanceable.

     @tparam T TOOD
     @tparam C TODO
     */
    template <typename T, typename C = priv::DefaultNew<T>>
    class Singleton : NonCopyable, NonInstanceable
    {
    public:
        /*!
         @brief TODO
         
         Calls `create` if needed
         */
        static T& getInstance();

        /*!
         @brief TODO

         @param force TODO
         */
        static void create(bool force = false);

        /*!
         @brief TODO
         */
        static void destroy();

        /*!
         @brief TODO
         */
        static bool exists();
    };
}

#include <sftools/Singleton/Singleton.tpp>

#endif // __SFTOOLS_SINGLETON_HPP__
