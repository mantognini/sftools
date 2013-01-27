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
 @file sftools/ResourceManager/SFMLManagers.hpp
 @brief Defines a few managers for SFML resources
 */

#ifndef __SFTOOLS_SFMLMANAGERS_HPP__
#define __SFTOOLS_SFMLMANAGERS_HPP__

#include <sftools/ResourceManager/Loaders.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>

// SFML's audio module is not always used. We don't want the user to be forced
// to link against sfml-audio if he doesn't use it.
#ifndef SFTOOLS_NO_AUDIO
    #include <SFML/Audio/Sound.hpp>
    #include <SFML/Audio/SoundBuffer.hpp>
    #include <SFML/Audio/Music.hpp>
#endif

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
         @typedef sftools::loader::TextureLoaderFromFile
         @brief Load sf::Texture from file
         */
        typedef loader::LoadFromFile<sf::Texture> TextureLoaderFromFile;

        /*!
         @typedef sftools::loader::ImageLoaderFromFile
         @brief Load sf::Image from file
         */
        typedef loader::LoadFromFile<sf::Image> ImageLoaderFromFile;

        /*!
         @typedef sftools::loader::FontLoaderFromFile
         @brief Load sf::Font from file
         */
        typedef loader::LoadFromFile<sf::Font> FontLoaderFromFile;
        
#ifndef SFTOOLS_NO_AUDIO

        /*!
         @typedef sftools::loader::SoundBufferLoaderFromFile
         @brief Load sf::SoundBuffer from file
         */
        typedef loader::LoadFromFile<sf::SoundBuffer> SoundBufferLoaderFromFile;

        /*!
         @typedef sftools::loader::MusicOpenerFromFile
         @brief Open sf::Music from file
         */
        typedef loader::OpenFromFile<sf::Music> MusicOpenerFromFile;
        
#endif
    }

    /*!
     @typedef sftools::TextureManager
     @brief A manager type for sf::Texture
     */
    typedef sftools::GenericManager<sf::Texture,
                                    std::string,
                                    loader::TextureLoaderFromFile>
            TextureManager;

    /*!
     @typedef sftools::ImageManager
     @brief A manager type for sf::Image
     */
    typedef sftools::GenericManager<sf::Image,
                                    std::string,
                                    loader::ImageLoaderFromFile>
            ImageManager;
    
    /*!
     @typedef sftools::FontManager
     @brief A manager type for sf::Font
     */
    typedef sftools::GenericManager<sf::Font,
                                    std::string,
                                    loader::FontLoaderFromFile>
            FontManager;

#ifndef SFTOOLS_NO_AUDIO
    
    /*!
     @typedef sftools::SoundBufferManager
     @brief A manager type for sf::SoundBuffer
     */
    typedef sftools::GenericManager<sf::SoundBuffer,
                                    std::string,
                                    loader::SoundBufferLoaderFromFile>
            SoundBufferManager;

    /*!
     @typedef sftools::MusicManager
     @brief A manager type for sf::Music
     */
    typedef sftools::GenericManager<sf::Music,
                                    std::string,
                                    loader::MusicOpenerFromFile>
            MusicManager;

#endif

    /*!
     @namespace sftools::singleton
     @brief Contains singleton object typedefs
     */
    namespace singleton
    {
        /*!
         @typedef sftools::singleton::TextureManager
         @brief A singleton manager for sf::Texture
         */
        typedef sftools::Singleton<TextureManager> TextureManager;
        
        /*!
         @typedef sftools::singleton::ImageManager
         @brief A singleton manager for sf::Image
         */
        typedef sftools::Singleton<ImageManager> ImageManager;

        /*!
         @typedef sftools::singleton::FontManager
         @brief A singleton manager for sf::Font
         */
        typedef sftools::Singleton<FontManager> FontManager;

#ifndef SFTOOLS_NO_AUDIO

        /*!
         @typedef sftools::singleton::SoundBufferManager
         @brief A singleton manager for sf::SoundBuffer
         */
        typedef sftools::Singleton<SoundBufferManager> SoundBufferManager;

        /*!
         @typedef sftools::singleton::MusicManager
         @brief A singleton manager for sf::Music
         */
        typedef sftools::Singleton<MusicManager> MusicManager;

#endif
    }
}


#endif // __SFTOOLS_SFMLMANAGERS_HPP__
