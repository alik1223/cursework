#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Yadro.h"
#include "Pushka.h"
#define PI 3.14159265
using namespace sf;
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	float alpha;
	float V0;
	bool b = false;
	bool b1 = false;
	int n;
	int length = 1300;
	int height = 600;
	int i = 0;
	RenderWindow window(VideoMode(length, height), "SFML Works!");
	Image puhka1;
	Image puhka2;
	Image shell;
	Texture texture;//texture for 1 gun
	Texture texture1;//texture for 2 gun
	Texture texture2;//texture for core
	Texture texture3;//texture for map
	puhka1.loadFromFile("images\\Pushka.png");//upload picture
	puhka1.createMaskFromColor(Color(255, 255, 255));//set the mask by color
	puhka2.loadFromFile("images\\Pushka1.png");
	puhka2.createMaskFromColor(Color(255, 255, 255));
	shell.loadFromFile("images\\yadro.png");
	shell.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(puhka1);
	texture1.loadFromImage(puhka2);
	texture2.loadFromImage(shell);
	texture3.loadFromFile("images\\karta.png");//Loading map
	Sprite sprite(texture3);
	Pushka *gun1;
	Pushka *gun2;
	gun1 = new Pushka(texture, 100, 500);
	gun2 = new Pushka(texture1, 1100, 500);
	//Yadro  *yadro = new Yadro(texture2);
	Yadro *yadro = yadro->getinstance(texture2);
	while (1)
	{
		if (gun1->get_life() == false || gun2->get_life() == false)//hit check
		{
			cout << "Игра окончена. Желаете сыграть еще?" << endl;
			cout << "|1| - Да " << endl;
			cout << "|2| - Нет " << endl;
			cin >> n;
			if (n == 2)
			{
				cout << "Спасибо за игру !!!" << endl;
				system("pause");
				break;
			}
			if (n == 1)
			{
				gun1->set_life(true);
				gun2->set_life(true);
			}

		}
		if (i % 2 == 0)
		{
			cout << "Ход игрока №1 " << endl;
		}
		else
		{
			cout << "Ход игрока №2 " << endl;
		}
		cout << "Введите начальную скорость(м/c)" << endl;
		cin >> V0;
		cout << "Введите угол(в градусах)" << endl;
		cin >> alpha;
		yadro->set_V0(V0);
		yadro->set_alpha(alpha);
		while (window.isOpen())
		{
			window.clear(Color::White);
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)//window closing check
					window.close();
				if (Keyboard::isKeyPressed(Keyboard::Space)) {//shot check
					if (i % 2 == 0)
					{
						gun1->set_isShoot(true);
						yadro->set_x(gun1->get_x()+90);//Set the x coordinate for the kernel
						yadro->set_y(gun1->get_y()); //Set the y coordinate for the kernel
					}
					else
					{
						gun2->set_isShoot(true);
						yadro->set_x(gun2->get_x() - 30);
						yadro->set_y(gun2->get_y());
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {//Moving gun
					if (i % 2 == 0)
					{
						gun1->set_state(0);//Left movement
						gun1->move();
					}
					else
					{
						gun2->set_state(0);
						gun2->move();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					if (i % 2 == 0)
					{
						gun1->set_state(1);//rigt movement
						gun1->move();
					}
					else
					{
						gun2->set_state(1);
						gun2->move();
					}
				}
			}
			b = gun1->fire(yadro, i, gun2);//1 gun shot
			b1 = gun2->fire(yadro, i, gun1);//2 gun shot
			window.draw(sprite);//map rendering
			if (gun1->get_isShoot() || gun2->get_isShoot())//shot check
			{
				window.draw(yadro->sprite);//kernel rendering
			}
			window.draw(gun1->sprite);//draw guns1
			window.draw(gun2->sprite);//draw guns2
			window.display();
			if (!(gun2->get_life()))//hit check Player1
			{
				cout << "Попадание!!!" << endl;
				cout << "Игрок №1 победил" << endl;
				break;
			}
			if (!(gun1->get_life())) // hit check Player2
			{
				cout << "Попадание!!!" << endl;
				cout << "Игрок №2 победил" << endl;
				break;
			}
			if (b || b1)//miss check
			{
				cout << "Промах" << endl;
				b = b1 = false;
				break;
			}
		}
		i++;
	}
	delete gun1;
	delete gun2;
	delete yadro;
	return 0;
}
