#ifndef Pushka_h
#define Pushka_h
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Yadro.h"
using namespace sf;
using namespace std;
class Pushka
{
private:
	int x, y, dx, dy = 0;
	float time = 0.001;
	int state;
	bool life = true;
	bool isShoot = NULL;
public:
	Pushka(Texture &texture, int x, int y);
	Sprite sprite;
	void set_x(int x);
	void set_y(int y);
	void set_dx(int dx);
	void set_dy(int dy);
	void set_state(int state);
	void set_time(float time);
	void set_life(bool life);
	void set_isShoot(bool isShoot);
	int get_x();
	int get_y();
	int get_dx();
	int get_dy();
	float get_time();
	int get_state();
	bool get_life();
	bool get_isShoot();
	FloatRect getRect();
	Sprite get_sprite();
	bool fire(Yadro *yadro, int i, Pushka *gun,int length, int height);
	void move(int length);
};


#endif
