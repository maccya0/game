#include"Game.h"

int main(int argc, char** argv)
{
	Game game ;

	bool result = game.Initialize();

	if (result)
	{
		game.MainLoop();
	}

	game.ShotDown();
	return 0;

}