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

#include "ImageManager.hpp"
#include <algorithm>

using namespace sftools;

/// Example of ResourceManager usage.
int main(int, char**) {
	const std::string& S1("pict1.png");
	const std::string& S2("pict2.png");

	ImageManager im;

	im.Load(S1);
	im.Load(S2);

	const sf::Image& i1 = im[S1];
	const sf::Image& i2 = im[S2];

	sf::Sprite s1(i1);
	sf::Sprite s2(i2, sf::Vector2f(i1.GetWidth(), 0));

	const unsigned int width(i1.GetWidth() + i2.GetWidth());
	const unsigned int height(std::max(i1.GetHeight(), i2.GetHeight()));

	sf::RenderWindow w(sf::VideoMode(width, height, 32), "ImageManager");

	while (w.IsOpened()) {
		sf::Event e;
		while (w.GetEvent(e)) {
			if (e.Type == sf::Event::Closed)
				w.Close();
		}

		w.Clear();
		w.Draw(s1);
		w.Draw(s2);
		w.Display();
	}

	return 0;
}


