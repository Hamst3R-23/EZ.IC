/*
* Думал переписать код с твоей идеей, но, к сожелению, идея с возрастом хвоста сильнее меня.
* Это решение имеет право на жизнь, но в следующий раз советую посоветоватся со сташими, прежде чем делать такое решение.
* Потому что оно СУУУПЕР-неоптимальное, очень много тонких мест, а каждая последующая модификация это сущий ад.
* Не буду менять идею, просто отмечу места, которые должны быть лучше. Но, опять же, решение супер ебанутое.
*/
#include <ncurses.h>
#include <stdio.h>

struct xboct
{
	int x;
	int y;
	int age;
};



int main(void)
{
	initscr();
	keypad(stdscr,TRUE);
	curs_set(0);
	noecho();

	uint32_t ch;

	struct xboct mass[4];

	char oper = '0'; // Вот ты этими d, u, l, r супер затрудняешь решение, потому что при нажимании НЕ стрелочек, хвост пропадает,
	int count = 0;   // а из-за этого, как я понимаю, тикает возраст хвоста и он отпадает. 
	
	int current_y = LINES/2;
	int current_x = COLS/2; 
	int temp;

	mass[0].x = COLS/2;
	mass[0].y = LINES/2;
	
	mass[0].age = 0; // АААААААААА
	mass[1].age = 3; // Это возраст, ебануться
	mass[2].age = 2; // Ты ебанный псих
	mass[3].age = 1; // Пиздец, только псих может такое придумать

	

	mvaddch(LINES/2,COLS/2,'*');
	while((ch = getch()) != 'q')
	{
		if((ch == KEY_UP && oper == 'd') || (ch == KEY_DOWN && oper == 'u') || (ch == KEY_RIGHT && oper == 'l') || (ch == KEY_LEFT && oper == 'r')) //Dvizhenie nazad
		{ 
			for(int i = 0; i < 4;i++)//Iscli4enie nepravilnoi situation
			{
				for (int j = 0; j < 4 ;j++) // Я честно пытался понять, что ты тут пытаешься отловить, но так и не понял
				{							// Все и так норм работает, что тут должно исправлятся я не понимаю 
											// Наткнулся на странную фигню, 
											/*
											 *				 	 *
											 *    *  			 *			 *
											 *	 **   нач   -> 	**  /\ 	->  **  \/ - это как? задний ход? почему тогда габариты не включены?
											 *   *							*
											 * 
											*/
					if(mass[i].age == 3 && mass[j].age == 2)
					{
						if(ch == KEY_UP && mass[i].y - 1 == mass[j].y)
						{
							count++;
							break;
						}
						if(ch == KEY_DOWN && mass[i].y + 1 == mass[j].y)
						{
							count++;
							break;
						}
						if(ch == KEY_RIGHT && mass[i].x + 1 == mass[j].x)
						{
							count++;
							break;
						}
						if(ch == KEY_LEFT && mass[i].x - 1 == mass[j].x)
						{
							count++;
							break;
						}
					}
				}
			}

			if (count != 0) 
			{
				count = 0;
				continue;
			}

			for(int i = 0; i < 4;i++)//povorot zmei,kogda golova stanovitca hvostom i naoborot
			{
				for(int j = 0;j < 4;j++)// dve {
				{
					if(mass[i].age == 3 && mass[j].age == 0 && i != j)
					{
						
						current_x = mass[i].x;
						current_y = mass[i].y;
						
						temp =	mass[i].x;
						mass[i].x = mass[j].x;
						mass[j].x = temp;

						temp =	mass[i].y;
						mass[i].y = mass[j].y;
						mass[j].y = temp;

					}
					if(mass[i].age == 2 && mass[j].age == 1 && i != j)
					{
						
						
						temp =	mass[i].x;
						mass[i].x = mass[j].x;
						mass[j].x = temp;

						temp =	mass[i].y;
						mass[i].y = mass[j].y;
						mass[j].y = temp;
					}
				}							
			}
	
		}
	
		if(ch == KEY_UP) //dvizhenie golovi
		{
			current_y--; 
			mvaddch(current_y,current_x,'*'); // Почему вывод основаны на x,y, а не на положении головы
										      // Двигай голову верх вниз и рисуй её, а не выводи позицию (1/2)
			oper = 'u';
		}
	
	
		if(ch == KEY_DOWN)
		{
			current_y++;
			mvaddch(current_y,current_x,'*');
			oper = 'd';
		}

		if(ch == KEY_LEFT)
		{
			current_x--;
			mvaddch(current_y,current_x,'*');
			oper = 'l';
		}
	
		if(ch == KEY_RIGHT)
		{
			current_x++;
			mvaddch(current_y,current_x,'*');
			oper = 'r';
		}

		for(int i = 0; i < 4;i++)//dobavlenie k kajdoi 4asti zmei god zhizni
		{
				mass[i].age++;
				if(mass[i].age == 4)// pri 4 godah XBOCT otmiraet // Зачем проверять 4 раза, если в 100 случаях из 100 отмирает последний хвост?
				{
					if(current_x != mass[i].x || current_y != mass[i].y)//Yslovie kogda golova ne  vstaet na mesto XBOCTa
					mvaddch(mass[i].y,mass[i].x,' '); // 
													  /*
													   * Лучше не закрашивать последний хвост, а перерисовывай все заново
													   * Вот смотри: 
													   * ты загружаешь в буффер новое положение головы и последний хвост (' ') (2 символа)
													   * ИЛИ
													   * ты затираешь весь экран и рисуешь 4 *звездочки* (4 символа)
													   * 
													   * НО,
													   * В первом случае, ты делаешь 4 х 2 проверок, но выводишь 2 символа
													   * Во втором случае, ты делаешь 0 проверок, но выводишь 4 символа + отчистка экрана
													   * 
													   * Я, конечно, не эксперт, но лучше 4 символа выводить, а не 8 проверок делать
													  */
					mass[i].x = current_x;//otrashivanie golovi 
					mass[i].y = current_y;// Вот. Ты же записываешь координаты головы в массив
					mass[i].age = 0;	  // Выводи по этим координатам, а то в чем смысл массива. Просто хранить координаты? (2/2)
				}
		}
	


	}
	refresh();
	endwin();

	return 0;
}
