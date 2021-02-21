#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>


typedef struct  // Позиция
{
    int64_t y;
    int64_t x;
} Position;

// Положение пушки
enum Gun            
{
    FORWARD_LEFT,   // * 1 // Впереди левее
    FORWARD,        // * 2 // Впереди
    FORWARD_RIGHT,  // * 3 // Впереди правее                       
    LEFT,           // * 4 // Слева                                // ^ 123 //
    RIGHT,          // * 5 // Справа                               // ^ 4*5 //  
    BACK_LEFT,      // * 6 // Сзади левее (относительно переда)    // ^ 678 //
    BACK,           // * 7 // Сзади                                
    BACK_RIGHT      // * 8 // Сзади правее (относительно переда)
};

// Структура танка
typedef struct 
{
    Position head;

    Position forward_vector;

    enum Gun guns_vector;

} Tank;

void print_char_position(Position p, char ch)
{
    mvaddch(p.y, p.x, ch);
}

void print_tank(Tank tank)
{
    // ГОЛОВА //
    print_char_position(tank.head, '*');

    // ГУСЕНИЦЫ //
    if (tank.forward_vector.y == 0)
    {
        // * Левый край (правый)* //
        mvaddch(tank.head.y - 1, tank.head.x + 0, '#');
        mvaddch(tank.head.y - 1, tank.head.x + 1, '#');
        mvaddch(tank.head.y - 1, tank.head.x - 1, '#');

        // * Правый край (левый)* //
        mvaddch(tank.head.y + 1, tank.head.x + 0, '#');
        mvaddch(tank.head.y + 1, tank.head.x + 1, '#');
        mvaddch(tank.head.y + 1, tank.head.x - 1, '#');
    }

    if (tank.forward_vector.x == 0)
    {
        // * Левый край (правый)* //
        mvaddch(tank.head.y + 0, tank.head.x - 1, '#');
        mvaddch(tank.head.y + 1, tank.head.x - 1, '#');
        mvaddch(tank.head.y - 1, tank.head.x - 1, '#');

        // * Правый край (левый)* //
        mvaddch(tank.head.y + 0, tank.head.x + 1, '#');
        mvaddch(tank.head.y + 1, tank.head.x + 1, '#');
        mvaddch(tank.head.y - 1, tank.head.x + 1, '#');
    }

    // БАШНАЯ //
    switch (tank.guns_vector)
    {
    case FORWARD_LEFT:
        mvaddch(tank.head.y - 1, tank.head.x - 1, '\\');
        break;
    case FORWARD:
        mvaddch(tank.head.y - 1, tank.head.x + 0, '|');
        break;
    case FORWARD_RIGHT:
        mvaddch(tank.head.y - 1, tank.head.x + 1, '/');
        break;
    case LEFT:
        mvaddch(tank.head.y + 0, tank.head.x - 1, '-');
        break;
    case RIGHT:
        mvaddch(tank.head.y + 0, tank.head.x + 1, '-');
        break;
    case BACK_LEFT:
        mvaddch(tank.head.y + 1, tank.head.x - 1, '/');
        break;
    case BACK:
        mvaddch(tank.head.y + 1, tank.head.x + 0, '|');
        break;
    case BACK_RIGHT:
        mvaddch(tank.head.y + 1, tank.head.x + 1, '\\');
        break;
    }
}

void move_tank(Tank *tank, int64_t delta_y, int64_t delta_x)
{
    tank->head.y = tank->head.y + delta_y;
    tank->head.x = tank->head.x + delta_x; 
}

int main()
{
    char str_hello[] = "Want play my game?";
    char str_continue[] = "press any key...";

    int ch;

    initscr();
    noecho(); // Не выводить символы
    curs_set(0); // Отключить курсор
    keypad(stdscr, true); // Корректный вывод системных кпопок
    uint8_t exit = 0; // Проверка выхода

    Tank player;
    player.head.y = LINES / 2;
    player.head.x = COLS / 2;

    player.forward_vector.y = 0;
    player.forward_vector.x = 1;
    
    player.guns_vector = FORWARD;
    


    // * Привет! * // 
    mvaddstr(LINES / 2, COLS / 2 - 10, str_hello);
    mvaddstr(LINES - 2, COLS / 2 - 8, str_continue);
    box(stdscr, 0, 0);

    refresh();
    getch();

    // * Первая отрисовка * //
    clear();
    box(stdscr, 0, 0);
    print_tank(player);
    refresh();

// * Главный игровой цикл * //
    while (!exit)
    {
        ch = getch();
        clear();

        switch (ch)
        {
        case KEY_UP: // Вверх
            move_tank(&player, -1, 0);
            player.forward_vector.y = -1;
            player.forward_vector.x = 0;
            break;
        case KEY_DOWN: // Вниз
            move_tank(&player, 1, 0);
            player.forward_vector.y = 1;
            player.forward_vector.x = 0;
            break;
        case KEY_RIGHT: // Вправо
            move_tank(&player, 0, 1);
            player.forward_vector.y = 0;
            player.forward_vector.x = 1;
            break;
        case KEY_LEFT: // Влево
            move_tank(&player, 0, -1);
            player.forward_vector.y = 0;
            player.forward_vector.x = -1;
            break;

        case 'q':
            player.guns_vector = FORWARD_LEFT;
            break;
        case 'w':
            player.guns_vector = FORWARD;
            break;
        case 'e':
            player.guns_vector = FORWARD_RIGHT;
            break;
        case 'a':
            player.guns_vector = LEFT;
            break;
        case 'd':
            player.guns_vector = RIGHT;
            break;
        case 'z':
            player.guns_vector = BACK_LEFT;
            break;
        case 'x':
            player.guns_vector = BACK;
            break;
        case 'c':
            player.guns_vector = BACK_RIGHT;
            break;

        case 'p': // Выход
            exit = 1;
            break;
        }

        box(stdscr, 0, 0);
        print_tank(player);
        refresh();
    }



    endwin();

    return 0;
}