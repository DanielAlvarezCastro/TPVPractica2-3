#pragma once
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "GameMap.h"
#include  <cstdlib>
#include <time.h>
#include "checkML.h"
#include "GameCharacter.h"

struct par{//Struct para guardar las direcciones
	int x;
	int y;
};

using namespace std;
class Game;
class Ghost: public GameCharacter
{
private:
	vector<par> dir;//Vector que guarda las direcciones accesibles
	uint bFrow, bFcol;//Filas y columnas de los sprites azules
	bool vulnerable;//Booleano que indica si el fantasma se puede comer o no
	clock_t startTime;

public:
	Ghost(Game *dir, uint xI, uint yI, uint FcolI);
	~Ghost();

	int getPosX();
	int getPosY();
	bool getVulnerability();

	void blueAnimation();
	void standardAnimation();

	void vulnerabilityOn();
	void vulnerabilityOff();

	void searchDir();
	void move();
	virtual void update();
	void backToIni();
};

