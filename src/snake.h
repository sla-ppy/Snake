#ifndef SNAKE_H
#define SNAKE_H

struct Snake {
public:
    int pos_x { 0 };
    int pos_y { 0 };

    Snake(int x, int y)
        : pos_x(x)
        , pos_y(y) {
    }
    Snake() = default;
};

#endif // !SNAKE_H