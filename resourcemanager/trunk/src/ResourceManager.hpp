/*
  resourcemanager
  Copyright (C) 2009 Marco Antognini (hiura@romandie.com)
  License : CC-BY-SA 3.0
  	You can find the full legal code at 
  	http://creativecommons.org/licenses/by-sa/3.0/
  	or in the local file cc-by-sa-3.0-legalcode.html .
  	Here is only an abstract :

  You are free :
  	to Share — to copy, distribute and transmit the work
	to Remix — to adapt the work

  Under the following conditions :
  	Attribution. You must attribute the work in the manner 
		specified by the author or licensor (but not 
		in any way that suggests that they endorse you
		or your use of the work).
	Share Alike. If you alter, transform, or build upon this 
		work, you may distribute the resulting work only 
		under the same, similar or a compatible license.

  For any reuse or distribution, you must make clear to others 
  	the license terms of this work. The best way to do this 
	is with a link to this
       	(http://creativecommons.org/licenses/by-sa/3.0/) web page.
  
  Any of the above conditions can be waived if you get 
  	permission from the copyright holder.

  Nothing in this license impairs or restricts the author's 
  	moral rights.

*/

/*!
 \file ResourceManager.hpp
 \brief Definition and implementation of ResourceManager class.
*/

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <functional>
#include <stdexcept>

/*!
 \namespace sftools
 \brief namespace containing tools using SFML library.
*/
namespace sftools {

/*!
 \class ResourceManager
 \brief Virtual Template Manager
 \details Exception thrown's type is std::invalid_argument 
 	or std::runtime_error.
	ResourceType has to be copyable.
*/
template <class ResourceType, class ResourceInfo, 
	  class ResourceID, class ResourcePr = std::less<ResourceID> >
class ResourceManager {
	/// A little shortcut.
	typedef std::map<ResourceID, ResourceType, ResourcePr> map;

	public :
		/*!
		 \brief Virtual dtor.
		*/
		virtual ~ResourceManager(void) {
			// Remove all elements.
			while (my_resources.begin() != my_resources.end())
				Destroy(my_resources.begin()->first);
		}

		/*!
		 \brief Return the value connected to the key.
		 \details May throw an exception of type std::invalid_argument
			 if the key doesn't exist.
		 \note This function exists also as a const function member.
		 \param id : the key.
		*/
		ResourceType& operator[](const ResourceID& id) {
			typename map::iterator it = my_resources.find(id);

			if (it == my_resources.end())
				throw std::invalid_argument("ID not found");

			return it->second;
		}

		/*!
		 \see ResourceManager::operator[]
		 \note This is a const version of the operator.
		*/
		const ResourceType& operator[](const ResourceID& id) const {
			typename map::const_iterator it = my_resources.find(id);

			if (it == my_resources.end())
				throw std::invalid_argument("ID not found");

			return it->second;
		}

		/*!
		 \brief Load a resource before adding it to the map.
		 \details Have to use ResourceManager::Add in its definition,
		 	and may throw a std::runtime_error if an
			error occurs.
		 \note This function mays catch a 
		 	possible std::invalid_argument thrown 
			by ResourceManager::Add.
		 \param info : The data needed to build the ResourceType.
		*/
		virtual const ResourceID& Load(const ResourceInfo& info) = 0;
		
		/*!
		 \brief Destroy operation before removing it from the map.
		 \details Have to use ResourceManager::Remove in its 
		 	definition, and may throw a std::runtime_error 
			if an error occurs.
		 \note This funcion mays catch a possible std::invalid_argument
		 	throw by ResourceManager::Remove.
		 \note You may reimplement this function in a derived class.
		 \param id : The Key.
		*/
		virtual void Destroy(const ResourceID& id) {
			// Nothing.
			Remove(id);
		}

	protected :
		/*!
		 \brief Add the given pair into the map.
		 \details May throw a std::invalid_argument if the given id
		 	already exists in the map.
		 \param id : The key connected to the resource.
		 \param resource : The value.
		*/
		void Add(const ResourceID& id, const ResourceType& resource) {
			if (my_resources.find(id) != my_resources.end())
				throw std::invalid_argument("ID already added");

			my_resources[id] = resource;
		}

		/*!
		 \brief Remove a resource from the map.
		 \details May throw a std::invalid_argument if the given id
		 	doesn't exist in the map.
		 \param id : The key.
		*/
		void Remove(const ResourceID& id) {
			// Do not remove more than one element.
			// See dinkumware's doc about 
			// std::map::erase and its return value.
			if (my_resources.find(id) == my_resources.end())
				throw std::invalid_argument("ID not found");

			my_resources.erase(id);
		}

	private :
		/*!
		 \brief All resources.
		 \details A map from ResourceID to ResourceType sorted 
		 	by predicate ResourcePr.
		*/
		map my_resources;

}; // ResourceManager

} // namespace sftools

#endif


