#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Game *dir, PlayState* pS, uint xI, uint yI, uint Fcol) :GameCharacter(dir,pS, xI, yI)//Direcci�n al juego
{
	lives = 3;
}
Pacman::Pacman(Game *dir, PlayState* pS) : GameCharacter(dir, pS)//Direcci�n al juego
{
	Fcol = IniFcol= 10;
	lives = 3;
}

Pacman::~Pacman()
{
}
void Pacman::saveToFile(ofstream& archivo)//M�todo de guardado en archivo
{
	GameCharacter::saveToFile(archivo);
	archivo << lives;
}

void Pacman::loadFromFile(ifstream& archivo)//M�todo de cargado en archivo
{
	GameCharacter::loadFromFile(archivo);
	archivo >> lives;
	if (lives > 3)
	{
		throw FileFormatError("Vidas invalidas");
	}
}
int Pacman::getLives(){//Devuelve las vidas actuales
	return lives;
}
int Pacman::getPosX(){//Devuelve la posici�n x
	return x;
}
int Pacman::getPosY(){//Devuelve la posici�n y
	return y;
}

void Pacman::handleAnimation(){//Controla animaci�n que se ejecuta seg�n la direcci�n actual
	if (dirX == 1 && dirY == 0){
		rightAnimation();
	}
	else if (dirX == -1 && dirY == 0){
		leftAnimation();
	}
	else if (dirX == 0 && dirY == 1){
		downAnimation();
	}
	else if (dirX == 0 && dirY == -1){
		upAnimation();
	}
}
void Pacman::upAnimation(){//Animaci�n arriba
	Frow = 3;
	Fcol = IniFcol + ((SDL_GetTicks() / 150) % 2);
}
void Pacman::downAnimation(){//Animaci�n abajo
	Frow = 1;
	Fcol = IniFcol + ((SDL_GetTicks() / 150) % 2);
}
void Pacman::leftAnimation(){//Animaci�n izquierda
	Frow = 2;
	Fcol = IniFcol + ((SDL_GetTicks() / 150) % 2);
}
void Pacman::rightAnimation(){//Animaci�n derecha
	Frow = 0;
	Fcol = IniFcol + ((SDL_GetTicks() / 150) % 2);
}

void Pacman::changeDir(char dir){//Seg�n la letra introducida cambia la direcci�n
	int nx, ny;
	nx = ny = 0;
	if (dir == 'u'){//Up
		ndirX = 0;
		ndirY = -1;
	}
	else if (dir == 'd'){//Down
		ndirX = 0;
		ndirY = 1;
	}
	else if (dir == 'l'){//Left
		ndirX = -1;
		ndirY = 0;
	}
	else if (dir == 'r'){//Right
		ndirX = 1;
		ndirY = 0;
	}

}
void Pacman::move(){//Aplica la direcci�n siguiente si es posible
	int nx = 0;
	int ny = 0;
	if (pState->nextCell(x, y, ndirX, ndirY, nx, ny)){//Si la posici�n pulsada en ese momento es posible
		dirX = ndirX; // entonces la direcci�n actual toma ese valor (B�ffer)
		dirY = ndirY;
	}
	handleAnimation();//Aplica la animaci�n seg�n la direcci�n
	nx = ny = 0;
	if (pState->nextCell(x, y, dirX, dirY, nx, ny))//Si la posici�n siguiente devuelve true, entonces se puede mover
	{
		x = nx;
		y = ny;
		if (pState->getCell(nx, ny) == Vitamins)//Cuando choca con una vitamina los fantasmas regresan a su posici�n original
		{
			pState->substractVitamin();
			pState->changeCell(nx, ny, Empty);//Cambia el valor de vitamina por vac�o
			pState->vulnerabilityOff();
		}
		else if (pState->getCell(nx, ny) == Food)
		{
			pState->substractFood();
			pState->changeCell(nx, ny, Empty);
		}
	}
}

void Pacman::update(){//Lleva el movimiento y el lugar donde se pinta
	move();
	destRect.x = x*w;
	destRect.y = y*h;
}

void Pacman::die(){//Resta una vida a Pacman
	lives--;
	if (lives < 0){
		pState->gameOver();
	}
}

