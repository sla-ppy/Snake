#include <Windows.h>
#include <iostream>
#include <mmsystem.h>
#include <random>
#include <thread>
#include <vector>

#include "game.h"
#include "map.h"
#include "snake.h"

void Game::inputCheck(Direction& dir) {
    if (GetAsyncKeyState(VK_UP)) {
        dir = Direction::UP;
    } else if (GetAsyncKeyState(VK_DOWN)) {
        dir = Direction::DOWN;
    } else if (GetAsyncKeyState(VK_LEFT)) {
        dir = Direction::LEFT;
    } else if (GetAsyncKeyState(VK_RIGHT)) {
        dir = Direction::RIGHT;
    } else {
        dir = dir; // dir stays the same
    }
}

Game::Game() {
    // POLISH: main menu

    // INIT APPLE:
    bool appleSpawned = false;

    while (appleSpawned == false) {
        apple.genApplePos();

        if (map.m_boardArray[apple.randPosX][apple.randPosY] == '.') {
            map.m_boardArray[apple.randPosX][apple.randPosY] = 'O';
            appleSpawned = true;
        }
    }
}

void Game::update() {
    Direction dir = Direction::UP;

    // vector that contains snake objects
    std::vector<Snake> snake;

    // INIT SNAKE:
    snake.push_back({ map.width / 2, map.height / 2 });
    snake.push_back({ map.width / 2, map.height / 2 + 1 });
    snake.push_back({ map.width / 2, map.height / 2 + 1 });

    size_t game_score { 0 };

    while (true) {
        // DOUBLE BUFFER:
        std::wstring buffer;

        // LIMIT FRAMERATE:
        // POLISH: speed settings 1-3
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // SET CURSOR TO HOME:
        std::wcout << "\x1b[H" << std::flush;

        PlaySound(TEXT("sfx/move_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);

        // ILLUSION OF MOVEMENT 1/2:
        for (const Snake& part : snake) {
            map.m_boardArray[part.pos_x][part.pos_y] = '.';
        }

        Snake snake_head;

        // MOVEMENT:
        inputCheck(dir);

        if (dir == Direction::UP) {
            snake_head = Snake(snake.front().pos_x - 1, snake.front().pos_y);
        }
        if (dir == Direction::DOWN) {
            snake_head = Snake(snake.front().pos_x + 1, snake.front().pos_y);
        }
        if (dir == Direction::LEFT) {
            snake_head = Snake(snake.front().pos_x, snake.front().pos_y - 1);
        }
        if (dir == Direction::RIGHT) {
            snake_head = Snake(snake.front().pos_x, snake.front().pos_y + 1);
        }

        snake.insert(snake.begin(), snake_head);

        // SNAKE COLLISION:
        // taken from javidx9's snake from scratch video
        for (std::vector<Snake>::iterator it = snake.begin(); it != snake.end(); it++) {
            if (it != snake.begin() && it->pos_x == snake.front().pos_x && it->pos_y == snake.front().pos_y) {
                PlaySound(TEXT("sfx/snake_hit.wav"), NULL, SND_FILENAME);

                // just so the error message doesn't ruin our map after game over
                for (int i = 0; i < 22; i++) {
                    std::wcout << "\n";
                }
                std::wcout << "The snek bit its tail! :(" << std::endl;
                PlaySound(TEXT("sfx/game_over.wav"), NULL, SND_FILENAME);
                return;
            }
        }

        // WALL COLLISION:
        if (snake_head.pos_x <= 0
            || snake_head.pos_y <= 0
            || snake_head.pos_x >= (map.width - 1)
            || snake_head.pos_y >= (map.height - 1)) {
            PlaySound(TEXT("sfx/wall_hit.wav"), NULL, SND_FILENAME);
            break;
        }

        // APPLE COLLISION:
        if (snake_head.pos_x == apple.randPosX && snake_head.pos_y == apple.randPosY) {
            map.m_boardArray[apple.randPosX][apple.randPosY] = '.';
            PlaySound(TEXT("sfx/apple_pickup.wav"), NULL, SND_FILENAME | SND_ASYNC);

            bool appleSpawned = false;

            while (appleSpawned == false) {
                apple.genApplePos();

                if (map.m_boardArray[apple.randPosX][apple.randPosY] == '.') {
                    map.m_boardArray[apple.randPosX][apple.randPosY] = 'O';
                    appleSpawned = true;
                }
            }
        } else {
            // if we dont encounter an apple, we keep the same size, hence movement.
            snake.erase(snake.end() - 1);
        }

        // RENDER SNAKE:
        for (const Snake& part : snake) {
            map.m_boardArray[part.pos_x][part.pos_y] = '#';
        }

        // SCORE:
        // POLISH: highscores
        game_score = snake.size();

        std::wcout << "Score: " << game_score - 3;

        // ILLUSION OF MOVEMENT 2/2:
        map.m_boardArray[snake_head.pos_x][snake_head.pos_y] = 'X';

        // UPDATE GAME MAP:
        for (int x = 0; x < map.width; x++) {
            buffer += '\n';
            for (int y = 0; y < map.height; y++) {
                buffer += map.m_boardArray[x][y];
            }
        }
        std::wcout << buffer;
    }
    std::wcout << "Game over. "
               << "Your final score: " << game_score - 3 << std::endl;

    PlaySound(TEXT("sfx/game_over.wav"), NULL, SND_FILENAME);

    // just so the error message doesn't ruin our map after game over
    for (int i = 0; i < 20; i++) {
        std::wcout << "\n";
    }
}