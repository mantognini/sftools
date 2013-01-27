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
 @file sftools/ResourceManager/GenericManager.hpp
 @brief Defines GenericManager class
 */

#ifndef __SFTOOLS_GENERICMANAGERS_HPP__
#define __SFTOOLS_GENERICMANAGERS_HPP__

#include <SFML/System/NonCopyable.hpp>
#include <string>
#include <map>
#include <functional> // std::less

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{
    typedef sf::NonCopyable NonCopyable; //!< A simple alias

    /*!
     @brief A generic resource manager ready to be customized
     
     Resource objects are stored in a `std::map<Id, Resource*>`.

     `OnLoad` type must have an operator `()` taking an `Id` as unique parameter
     and returning a pointer to `Resource` (or 0 if loading failed).
     
     @tparam Resource   Type of the resource to manage
     @tparam Id         Type of resources' identifiers
     @tparam OnLoad     Procedure type to load resources
     */
    template <typename Resource, typename Id, typename OnLoad>
    class GenericManager : NonCopyable
    {
    public:
        /*!
         @brief Constructor
         */
        GenericManager();

        /*!
         @brief Load a new resource
         
         @param id id of the resource to load
         @param forceReload ensure the resource is (re)loaded
         @return true if the resource was loaded properly
         
         @see onLoad
         */
        bool load(Id const& id, bool forceReload = false);

        /*!
         @brief Unload a resource
         
         @param id id of the resource to unload
         */
        void unload(Id const& id);
        
        /*!
         @brief Unload all resources
         */
        void unloadAll();

        /*!
         @brief Fetch a resource

         A `std::invalid_argument` exception is thrown if `id` doesn't exist.

         @param id the id of the resource to be fetched
         @return the resource corresponding to `id`

         @throw std::invalid_argument
         */
        Resource const& operator[](Id const& id) const;

        /*!
         @brief Fetch a resource

         A `std::invalid_argument` exception is thrown if `id` doesn't exist.

         @param id the id of the resource to be fetched
         @return the resource corresponding to `id`

         @throw std::invalid_argument
         */
        Resource& operator[](Id const& id);

    private:
        typedef Resource* ResourcePtr; //!< A simple alias
        
        typedef std::map<Id, ResourcePtr> Map; //!< Internal storage type

        typedef typename Map::iterator MapIterator; //!< Internal storage iterator
        typedef typename Map::const_iterator MapConstIterator; //!< Internal storage const iterator

        Map m_resources; //!< Internal resources storage

        OnLoad m_onLoad; //!< Procedure to load a resource
    };
}

#include <sftools/ResourceManager/GenericManager.tpp>

#endif // __SFTOOLS_GENERICMANAGERS_HPP__
