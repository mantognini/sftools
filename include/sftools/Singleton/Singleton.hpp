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
 @file sftools/Singleton/Singleton.hpp
 @brief Defines Singleton tool
 */

#ifndef __SFTOOLS_SINGLETON_HPP__
#define __SFTOOLS_SINGLETON_HPP__

#include <sftools/Common.hpp>

#include <sftools/Singleton/SingletonPriv.hpp>

/*!
 @namespace sftools
 @brief Simple and Fast Tools
 */
namespace sftools
{
    /*!
     @class Singleton
     @brief Non intruisive and customizable singleton system
     
     Basic usage example :
     
     @code

     typedef sftools::Singleton<MyClass> MySingleton;

     MyClass& mySingleton = MySingleton::getInstance();
     mySingleton.foo();

     // Or

     MySingleton::getInstance().foo();
     
     @endcode
     
     Usually you don't have to specify a type for `F`; the default type
     should be enough. However if `T` can't be instanciated with
     `new T();` (e.g. it need some parameters) you can create a factory type
     that :
     
     \li can has a default constructor
     \li has `T* operator()() const` method
     
     Sometimes your might want to use a factory with custom parameters (i.e.
     using the default constructor for the factory doesn't fit your plan). In
     that case you can do as in the following example
     
     @code
     
        #include <sftools/Singleton.hpp>

        #include <iostream>

        // Class to be singletonized
        class Foo
        {
            int const m_bar;
        public:
            // No default constructor here
            Foo(int bar) : m_bar(bar) { }
            void print() const { std::cout << "Foo:" << m_bar << std::endl; }
        };

        // Factory
        class FooFactory
        {
            int const m_param;
        public:
            // We need a default constructor
            FooFactory() : m_param(0) { }
            // But we can also use a customized constructor and pass a factory
            // object to Singleton::create
            FooFactory(int param) : m_param(param) { }

            // And we need a factory method : operator()
            Foo* operator()() const { return new Foo(m_param); }
        };

        typedef sftools::Singleton<Foo, FooFactory> SingletonFoo;

        void f()
        {
            // Initialize our singleton with a custom factory
            FooFactory factory(58);
            SingletonFoo::create(false, factory);

            SingletonFoo::getInstance().print(); // prints: "Foo:58"
        }

     @endcode

     @todo With C++11 we could do even better : by using variadic template we
     can customize more easily the construction of the unique instance and
     probably even inherit from `T` so the singleton object could be used
     everywhere `T` is used. However there might be issues with NonCopyable
     and NonInstanceable.

     @tparam T Type to be "singletonized"
     @tparam F Factory type used to create an instance of T.
     */
    template <typename T, typename F = priv::DefaultNew<T>>
    class Singleton : NonCopyable, NonInstanceable
    {
    public:
        /*!
         @brief Get the unique instance
         
         Calls `create` (with its default parameters) if the instance
         doesn't exist yet.
         
         @see create
         */
        static T& getInstance();

        /*!
         @brief Initialise the instance
         
         `F` is used to generate a object of type `T`.

         @param force if `force` is true then the instance is destroyed and
                      recreated; otherwise the instance is only created if
                      it doesn't exist yet.
         @param factory factory object used to create the instance.
         
         @see destroy
         @see exists
         */
        static void create(bool force = false, F const& factory = F());

        /*!
         @brief Destroy the instance if it exists
         
         @see exists
         */
        static void destroy();

        /*!
         @brief Tells if the instance was created
         
         @see create
         */
        static bool exists();
    };
}

#include <sftools/Singleton/Singleton.tpp>

#endif // __SFTOOLS_SINGLETON_HPP__
