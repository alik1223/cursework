#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include <math.h>
#include "Yadro.h"
#include "Pushka.h"
#define PI 3.14159265
using namespace sf;
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	float alpha;//angle
	float V0;//starting speed
	float m;//core mass
	int i = 0;//
	bool b = false;
	bool b1 = false;
	bool flag = true;
	bool flag1 = true;
	int n;
	int length = 1300; // window length
	int height = 600;// window height
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
	gun1 = new Pushka(texture, 100, 500);//create gun1
	gun2 = new Pushka(texture1, 1100, 500);//create gun2
	Yadro *yadro = yadro->getinstance(texture2);
	while (1)
	{
		if (gun1->get_life() == false || gun2->get_life() == false)//hit check
		{
			do {
				cout << "Игра окончена. Желаете сыграть еще?" << endl;
				cout << "|1| - Да " << endl;
				cout << "|2| - Нет " << endl;
				cin >> n;
				try//error processing
				{
					if (cin.fail() || n < 1 || n > 2)
					{
						cin.clear();
						cin.ignore(10000, '\n');
						exception err("Ошибка ввода данных");
						throw err;
					}
					else
						flag = false;
					if (n == 2)
					{
						cout << "Спасибо за игру !!!" << endl;
						flag1 = false;
						system("pause");
						break;
					}
					if (n == 1)
					{
						gun1->set_life(true);
						gun2->set_life(true);
					}
				}
				catch (exception err)
				{
					cout << err.what() << endl;
				}
				system("pause");
				system("cls");
			} while (flag);
		}
		if (!flag1)
		{
			flag1 = false;
			break;
		}
		do 
		{
			if (i % 2 == 0)
			{
				cout << "Ход игрока №1 " << endl;
			}
			else
			{
				cout << "Ход игрока №2 " << endl;
			}
			try
			{
				cout << "Введите начальную скорость(Рекомендуемые значения 3-6)" << endl;
				cin >> V0;
				cout << "Введите массу ядра" << endl;
				cin >> m;
				cout << "Введите угол(0-90)" << endl;
				cin >> alpha;
				if (cin.fail() || V0 < 0 || alpha < 0 || alpha>90 || m<0)//error processing
				{
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						exception err("Ошибка ввода данных");
						throw err;
					}
					if (V0 < 0)
					{
						exception err("Ошибка ввода данных(Скорость не может быть < 0)");
						throw err;
					}
					if (alpha < 0 || alpha>90)
					{
						exception err("Ошибка ввода данных(Введите угол от 0 до 90)");
						throw err;
					}
					if (m<0)
					{
						exception err("Ошибка ввода данных(Масса не может быть < 0)");
						throw err;
					}
				}
				else flag1 = false;
			}
			catch (exception err)
			{
				cout << err.what() << endl;
			}
			system("pause");
			system("cls");
		} while (flag1);
		flag1 = true;
		yadro->set_V0(V0);//set value V0
		yadro->set_alpha(alpha);//set value alpha
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
						gun1->move(length);
					}
					else
					{
						gun2->set_state(0);
						gun2->move(length);
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					if (i % 2 == 0)
					{
						gun1->set_state(1);//rigt movement
						gun1->move(length);
					}
					else
					{
						gun2->set_state(1);
						gun2->move(length);
					}
				}
			}
			b = gun1->fire(yadro, i, gun2,length,height);//1 gun shot
			b1 = gun2->fire(yadro, i, gun1,length, height);//2 gun shot
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
		system("pause");
		system("cls");
		i++;
	}
	delete gun1;
	delete gun2;
	delete yadro;
	return 0;
}
