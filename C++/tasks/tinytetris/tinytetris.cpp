#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

class Tetris {
private:
    int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
    int score = 0;

    void drawBlock(int x, int y) {
        attron(COLOR_PAIR(1));
        mvprintw(y + 1, x * 2 + 1, "[]");
        attroff(COLOR_PAIR(1));
    }

    void drawBoard() {
        clear();
        box(stdscr, 0, 0);

        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                if (board[i][j]) {
                    drawBlock(j, i);
                }
            }
        }
        
        mvprintw(BOARD_HEIGHT + 1, 1, "分数: %d", score);
        refresh();
    }

public:
    Tetris() {
        initscr();
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        noecho();
        curs_set(0);
        timeout(0);
        resize_term(BOARD_HEIGHT + 2, BOARD_WIDTH * 2 + 2);
    }

    void run() {
        while (true) {
            int ch = getch();
            if (ch == 'q') break;
            drawBoard();
            usleep(100000);
        }
    }

    ~Tetris() {
        endwin();
    }
};

int main() {
    Tetris game;
    game.run();
    return 0;
}

