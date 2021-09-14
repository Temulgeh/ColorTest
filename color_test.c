#include <curses.h>


void generate_color_pairs()
{
    start_color();
    for (int i = 0; i < COLOR_PAIRS; ++i)
    {
        init_pair(i, i, i);
    }
}


void draw_square(int x, int y, short color_pair)
{
    mvaddch(y, x * 2,     ' ' | COLOR_PAIR(color_pair));
    mvaddch(y, x * 2 + 1, ' ' | COLOR_PAIR(color_pair));
}


void draw_swatches()
{
    int color = 0;

    for (int i = 0; i < 8; ++i, ++color)
    {
        draw_square(i + 1, 1, color);
    }

    for (int i = 0; i < 8; ++i, ++color)
    {
        draw_square(i + 1, 2, color);
    }

    if (COLOR_PAIRS >= 256)
    {
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < 6; ++j)
            {
                for (int k = 0; k < 6; ++k, ++color)
                {
                    draw_square(1 + i * 7 + k, 5 + j, color);
                }
            }
        }

        for (int i = 0; i < 24; ++i, ++color)
        {
            draw_square(i + 1, 13, color);
        }
    }
}


int main()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    curs_set(0);

    generate_color_pairs();
    draw_swatches();

    bool running = true;
    while (running)
    {
        int ch;
        while ((ch = getch()) != ERR)
        {
            switch (ch)
            {
                case 'q': case 'Q':
                    running = false;
                    break;
            }
        }

        clearok(stdscr, true);
        refresh();
        napms(100);
    }

    endwin();
    return 0;
}
