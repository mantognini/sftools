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
 @file sftools/ResourceManager/Locations.hpp
 @brief Defines Locations class and ResourceLocations singleton object
 */

#ifndef __SFTOOLS_LOCATIONS_HPP__
#define __SFTOOLS_LOCATIONS_HPP__

#include <sftools/Common/NonCopyable.hpp>
#include <sftools/Singleton.hpp>

#include <string>
#include <vector>
#include <algorithm>

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{
    /*!
     @class Locations
     @brief Minimalist locations manager
     
     Basically it's a collection of paths. ResourceLocations makes something
     useful from it.
     
     @note When use add() to, well, add a location be careful and check if the
           path ends with `/` or not. Here is the difference :
           - If $path ends with a slash then ResourceLoader will look into the
             folder named $path;
           - Otherwise it will look for files with a prefix of "$path" 
             (e.g. if $path is "high_definition_" implies that load("foo") will
             load "hight_definition_foo" files).

     @todo It could be interesting to have a `Path` class and be able to
           do something like
           `Locations loc; loc.add({"res"}.add({"img"}, {"snd"}), {"extra"})`.

     @see ResourceLocations
     @see ResourceLoader
     */
    class Locations : sftools::NonCopyable
    {
        typedef std::vector<std::string> Storage; //!< Private storage type
        typedef Storage::iterator Iterator; //!< Private mutable iterator type
        Storage m_locations; //!< locations storage

    public:
        typedef Storage::const_iterator ConstIterator; //!< Constant iterator type

        /*!
         @brief Add a path to the locations

         @param path location to be added
         */
        void add(std::string const& path)
        {
            m_locations.push_back(path);
        }

        /*!
         @brief Remove a location

         If `path` was not previously added nothing is done.
         
         @note This method invalids any iterator.

         @param path location to be removed
         */
        void remove(std::string const& path)
        {
            Iterator it = std::find(m_locations.begin(), m_locations.end(), path);
            if (it != m_locations.end())
            {
                m_locations.erase(it);
            }
        }

        /*!
         @brief Remove all locations
         
         @note This method invalids any iterator.
         */
        void clear()
        {
            m_locations.clear();
        }

        /*!
         @brief Return an iterator on the first location

         If no location was added yet this method return the same iterator as `end`.

         @return constant iterator on the first location
         */
        ConstIterator begin() const
        {
            return m_locations.begin();
        }

        /*!
         @brief Return an iterator to the element following the last location

         @return constant iterator to the element following the last location
         */
        ConstIterator end() const
        {
            return m_locations.end();
        }
    };

    /*!
     @namespace sftools::singleton
     @brief Contains singleton object typedefs
     */
    namespace singleton
    {
        /*!
         @typedef sftools::singleton::ResourceLocations
         @brief Singleton Locations object used my sftools resource managers.

         Locations stored in this singleton object are used to find and
         load resources.

         Use the following code snippet to add a resource location :

         @code

         Locations& locations = singleton::ResourceLocations::getInstance();
         locations.add(resourcePath());
         
         @endcode
         
         where `resourcePath()` returns the system path to the location folder.
         
         @see Locations
         */
        typedef sftools::Singleton<Locations> ResourceLocations;
    }
}

#endif // __SFTOOLS_LOCATIONS_HPP__
