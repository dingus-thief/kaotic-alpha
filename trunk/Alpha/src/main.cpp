/*
	Author: Aaron Klein	
	Start Date: 2/8/2012
	Description: A simple 2D platformer created with the intention of expanding architecture knowledge
*/

#include "Game.h"
#include <iostream>

int main()
{
	Kaotic_Alpha::Game game;

	game.Startup();
	game.Run();
	game.Shutdown();

	return 0;
}