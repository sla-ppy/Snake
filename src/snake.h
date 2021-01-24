#ifndef SNAKE_H
#define SNAKE_H

struct Snake {
public:
	int pos_x{ 0 };
	int pos_y{ 0 };

    int prev_pos_x{ 0 };
    int prev_pos_y{ 0 };

    // TODO: snake body goes here, we ask for the size through function, find last segment through that and turn last cell's prev position into '.'
    Snake* cells{ nullptr };
    size_t cell_count{ 3 };

    void resize_cells_to(size_t new_size) {
        Snake* new_cells = new Snake[new_size];
        for (size_t i = 0; i < cell_count; ++i) {
            // added a -1 to prevent buffer overrun, might fuck it up
            new_cells[i - 1] = cells[i];
        }
        delete[] cells;
        cells = new_cells;
        cell_count = new_size;
    }
    // we need a last ptr, which we always assign the value for, being the previous last node's location
};

#endif // !SNAKE_H