#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>
#include "types.h"

void CheckEvent (Settings* sets);
int ChangeSets(Settings* sets, sf::Event::KeyEvent key);
void ChangePixelColor (Settings* sets, int x, int y, char r, char g, char b);
void ChangePixel (Settings* sets, int n, int x, int y);

#endif