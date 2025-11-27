#include <iostream>
#include <windows.h>
#include <vector>

struct Position {
    int x = 0;  
    int y = 0;
};

enum class Direction {
    UP,
    DOWN,
    FORWARD, //Droite
    BACKWARD //Gauche
};

struct Move {
    Direction direction;
    int distance;
};

void moveSubmarine(Position& subPos, const Move& move) {
    switch (move.direction) {
        case Direction::UP:
            subPos.y -= move.distance;
            break;
        case Direction::DOWN:
            subPos.y += move.distance;
            break;
        case Direction::FORWARD:
            subPos.x += move.distance;
            break;
        case Direction::BACKWARD:
            subPos.x -= move.distance;
            break;
    }
}

void Display(const Position& pos) {
    std::cout << "Position du sous-marin : (" << pos.x << ", " << pos.y << ")" << std::endl;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD07 - EX01 -" << std::endl;

    Position submarinePosition;

    std::vector<Move> moves = {
        {Direction::FORWARD, 10},
        {Direction::DOWN, 5},
        {Direction::BACKWARD, 3},
        {Direction::UP, 2},
        {Direction::FORWARD, 5},
        {Direction::DOWN, 1},
        {Direction::BACKWARD, 2},
        {Direction::FORWARD, 3},
        {Direction::DOWN, 1},
        {Direction::UP, 3},
        {Direction::FORWARD, 1},
        {Direction::DOWN, 5},
        {Direction::BACKWARD, 2},
        {Direction::FORWARD, 6}
    };

    for (const auto& move : moves) {
        moveSubmarine(submarinePosition, move);
        Display(submarinePosition);
    }

    std::cout << "Position finale du sous-marin : (" << submarinePosition.x << ", " << submarinePosition.y << ")" << std::endl;

    return 0;
}