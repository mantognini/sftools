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
 @file sftools/ResourceManager/Loaders.hpp
 @brief Defines Locations class and ResourceLocations singleton object
 */

#ifndef __SFTOOLS_LOADERS_HPP__
#define __SFTOOLS_LOADERS_HPP__

#include <sftools/ResourceManager/Locations.hpp>
#include <string>

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{
    /*!
     @namespace sftools::loader
     @brief Contains loader utilities for the resource managers
     */
    namespace loader
    {
        /*!
         @brief Generic resource loader
         
         It's primary use is to help the GenericManager.
         This generic loader must be specialized by implementing load().
         
         @tparam R Resource type
         
         @see GenericManager
         @see LoadFromFile
         @see OpenFromFile
         */
        template <typename R>
        struct ResourceLoader
        {
            /*!
             @brief Virtual destructor
             */
            virtual ~ResourceLoader()
            {
                // Nothing to do
            }
            
            /*!
             @brief Load operator
             
             It create a resource and use load() to initialize its content.
             
             @param id Resource id to load
             @return a pointer to a valid R object if load() succeed or 0 if it
                     failed
             */
            R* operator()(std::string const& id)
            {
                R* ptr = new R;

                Locations& locs = singleton::ResourceLocations::getInstance();

                // Find the first location that holds an file called "id"
                for (Locations::ConstIterator it = locs.begin();
                     it != locs.end();
                     ++it)
                {
                    if (load(*ptr, *it + id))
                    {
                        return ptr; // Success!
                    }
                }

                // Hum... got here ?
                // This means the resource was not loaded properly.
                delete ptr;
                ptr = 0;
                return 0;
            }

            /*!
             @brief Load the content of a resource with the given file
             
             @note subclasses must implement this function in order to 
                   customize ResourceLoader.
             
             @param res Resource to be feed with a new content
             @param src File containing the new content to be loaded
             @return true if loading the resource succeed; false otherwise
             */
            virtual bool load(R& res, std::string src) = 0;
        };

        /*!
         @brief Specialisation of ResourceLoader for `loadFromFile()`-resources
         
         @tparam R Resource type
         */
        template <typename R>
        struct LoadFromFile : ResourceLoader<R>
        {
            bool load(R& res, std::string src)
            {
                return res.loadFromFile(src);
            }
        };

        /*!
         @brief Specialisation of ResourceLoader for `openFromFile()`-resources

         @tparam R Resource type
         */
        template <typename R>
        struct OpenFromFile : ResourceLoader<R>
        {
            bool load(R& res, std::string src)
            {
                return res.openFromFile(src);
            }
        };
    }
}

#endif // __SFTOOLS_LOADERS_HPP__
