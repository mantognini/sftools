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
 @file sftools/ResourceManager/GenericManager.tpp
 @brief Implementation of GenericManager class
 */

#include <stdexcept> // std::invalid_argument

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{
    template <typename Resource, typename Id, typename OnLoad>
    GenericManager<Resource, Id, OnLoad>::GenericManager()
    : m_onLoad(OnLoad())
    {
    }

    template <typename Resource, typename Id, typename OnLoad>
    bool GenericManager<Resource, Id, OnLoad>::load(Id const& id, bool forceReload)
    {
        // Already loaded ?
        if (m_resources.count(id) != 0)
        {
            if (!forceReload)
            {
                // Don't do it twice!
                return true;
            }
            else
            {
                unload(id);
            }
        }
        
        // No ? Ok, let my onLoad method do it.
        ResourcePtr ptr = m_onLoad(id);
        
        // Was it correctly loaded ?
        if (ptr)
        {
            m_resources[id] = ptr;
            
            return true;
        }
        else
        {
            return false;
        }
    }
    
    template <typename Resource, typename Id, typename OnLoad>
    void GenericManager<Resource, Id, OnLoad>::unload(Id const& id)
    {
        delete m_resources[id];
        m_resources.erase(id);
    }
    
    template <typename Resource, typename Id, typename OnLoad>
    void GenericManager<Resource, Id, OnLoad>::unloadAll()
    {
        for (MapIterator it = m_resources.begin(); it != m_resources.end(); ++it)
        {
            delete it->second;
        }
        m_resources.clear();
    }
    
    template <typename Resource, typename Id, typename OnLoad>
    Resource const& GenericManager<Resource, Id, OnLoad>::operator[](Id const& id) const
    {
        MapConstIterator it = m_resources.find(id);
        
        if (it != m_resources.end())
        {
            return *it->second;
        }
        else
        {
            throw std::invalid_argument("Resource not loaded");
        }
    }
    
    template <typename Resource, typename Id, typename OnLoad>
    Resource& GenericManager<Resource, Id, OnLoad>::operator[](Id const& id)
    {
        MapIterator it = m_resources.find(id);
        
        if (it != m_resources.end())
        {
            return *it->second;
        }
        else
        {
            throw std::invalid_argument("Resource not loaded");
        }
    }
}
