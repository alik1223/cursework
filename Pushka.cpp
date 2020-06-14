#include <iostream>
#include "Pushka.h"
#define PI 3.14159265
using namespace std;

Pushka::Pushka(Texture & texture, int x, int y)
{
	sprite.setTexture(texture);
	this->x = x;
	this->y = y;
	sprite.setPosition(x, y);
}

//setting parameters
void Pushka::set_x(int x)
{
	this->x = x;
}

void Pushka::set_y(int y)
{
	this->y = y;
}

void Pushka::set_dx(int dx)
{
	this->dx = dx;
}

void Pushka::set_dy(int dy)
{
	this->dy = dy;
}

void Pushka::set_state(int state)
{
	this->state = state;
}

void Pushka::set_time(float time)
{
	this->time = time;
}

void Pushka::set_life(bool life)
{
	this->life = life;
}

void Pushka::set_isShoot(bool isShoot)
{
	this->isShoot = isShoot;
}
//getting parameters
int Pushka::get_x()
{
	return x;
}

int Pushka::get_y()
{
	return y;
}

int Pushka::get_dx()
{
	return dx;
}

int Pushka::get_dy()
{
	return dy;
}

float Pushka::get_time()
{
	return time;
}

int Pushka::get_state()
{
	return state;
}

bool Pushka::get_life()
{
	return life;
}

bool Pushka::get_isShoot()
{
	return isShoot;
}

FloatRect Pushka::getRect()
{
	return FloatRect(x, y, 100, 100);
}

Sprite Pushka::get_sprite()
{
	return sprite;
}

bool Pushka::fire(Yadro * yadro, int i, Pushka * gun)
{
	if (isShoot)
	{
		time += 0.001;
		if (i % 2 == 0)
		{
			yadro->set_dx(time* yadro->get_V0()*cos(PI*yadro->get_alpha() / 180));//Dx calculation for gun1
		}
		else {
			yadro->set_dx(-time * yadro->get_V0()*cos(PI*yadro->get_alpha() / 180));//Dx calculation for gun2
		}
		yadro->set_x(yadro->get_x() + yadro->get_dx());//calculate x coordinate
		yadro->set_dy(-time * yadro->get_V0()*sin(PI*yadro->get_alpha() / 180) + 0.5*9.81*time*time);//Dy calculation for gun
		yadro->set_y(yadro->get_y() + yadro->get_dy());//calculate y coordinate
		yadro->sprite.setPosition(yadro->get_x(), yadro->get_y());//set kernel offsets
		if ((yadro->get_x() > 1300 || yadro->get_x() < 0) && (yadro->get_y() > 600))// check for a kernel out of the window
		{
			isShoot = false;
			time = 0;
			yadro->set_life(false);
			return true;
		}
		if (yadro->getRect().intersects(gun->getRect()))//hit check
		{
			isShoot = false;
			gun->set_life(false);
			time = 0;
			yadro->set_life(false);
			return false;
		}
	}
	return false;
}

void Pushka::move()
{
	//Moving the gun to the left
	if (state == 0)
	{
		dx = -1;
		x += dx;
		sprite.setPosition(x, y);

	}
	//Moving the gun to the right
	if (state == 1)
	{
		dx = 1;
		x += dx;
		sprite.setPosition(x, y);
	}
}
