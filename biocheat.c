#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WHITE  0xffffff
#define GREEN  0x00e60c
#define YELLOW 0x46ffff

const struct {
    int value, x, y;
} PIXELS[] = {
    {1,  51, 16},
    {4,  40, 36},
    {7,  64, 20},
    {9,  76, 19},
    {10, 88, 20},
    {11, 39, 18},
    {12, 86, 49},
    {13, 38, 22},
    {14, 78, 17},
    {16, 88, 43},
    {2,  75, 17},
    {3,  67, 19},
    {6,  29, 30},
    {8,  38, 16},
    {15, 83, 11},
    {5,  50, 28}
};

int read_number()
{
    int basex = 674, basey = 545;
    HDC hdc = GetWindowDC(GetDesktopWindow());
    for (int i = 0; i < sizeof(PIXELS) / sizeof(*PIXELS); i++) {
        if (GetPixel(hdc, basex + PIXELS[i].x, basey + PIXELS[i].y) == WHITE)
            return PIXELS[i].value;
    }
    return 0;
}

void move(int x, int y)
{
    x = (x * 65535) / 1680;
    y = (y * 65535) / 1050;
    INPUT m[] = {
        {0, {{x, y, 0, MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE}}}
    };
    SendInput(sizeof(m) / sizeof(*m), m, sizeof(*m));
}

void click(int x, int y)
{
    for (int i = 25; i > 0; i--) {
        move(x - i, y - i);
        Sleep(10);
    }
    move(x, y);
    INPUT m[] = {
        {0, {{0, 0, 0, MOUSEEVENTF_LEFTDOWN}}},
        {0, {{0, 0, 0, MOUSEEVENTF_LEFTUP}}}
    };
    Sleep(200);
    SendInput(1, m+0, sizeof(*m));
    Sleep(200);
    SendInput(1, m+1, sizeof(*m));
}

static inline void go_high()
{
    printf("high\n");
    click(470, 740);
}

static inline void go_low()
{
    printf("low\n");
    click(960, 740);
}

static inline void payout()
{
    printf("payout\n");
    click(725, 740);
}

static inline void play_again()
{
    printf("play again\n");
    click(720, 490);
}

void (*MAP[])() = {
    NULL,
    go_low, go_low, go_high, go_high, go_high, go_low, go_low, go_low,
    go_high, go_high, go_high, go_high, go_low, go_low, go_low, go_high
};

int main(int argc, char **argv)
{
    unsigned toggle = 0;
    while (1) {
        POINT p;
        GetCursorPos(&p);
        int n = read_number();
        if (n > 0) {
            printf("%d\n", n);
            MAP[n]();
            toggle = 0;
            Sleep(3000);
        } else if ((toggle % 2) == 0) {
            payout();
            toggle++;
            Sleep(1000);
        } else {
            play_again();
            toggle++;
            Sleep(3000);
        }
    }
    return 0;
}
