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
 @file sftools/Singleton/Singleton.tpp
 @brief Implements Singleton tool
 */
 
 
 namespace sftools
 {
    template <typename T, typename F>
    T& Singleton<T, F>::getInstance()
    {
        if (!exists())
        {
            create();
        }
        
        return *priv::Unique<T>::instance;
    }
    
    template <typename T, typename F>
    void Singleton<T, F>::create(bool force, F const& ctor)
    {
        if (exists() && force)
        {
            destroy();
            create(force, ctor);
        }
        else
        {
            priv::Unique<T>::instance = ctor();
        }
    }
    
    template <typename T, typename F>
    void Singleton<T, F>::destroy()
    {
        if (exists())
        {
            delete priv::Unique<T>::instance;
            priv::Unique<T>::instance = 0;
        }
    }
    
    template <typename T, typename F>
    bool Singleton<T, F>::exists()
    {
        return priv::Unique<T>::instance != 0;
    }
 }
