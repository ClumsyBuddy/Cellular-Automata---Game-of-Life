#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>

class Cell{
public:

    Cell(sf::RenderWindow& win, int x, int y) : window(win) {
        
        Alive = rand() % 2;

        PositionX = x * RectSize;
        PositionY = y * RectSize;

        _rect.setSize(sf::Vector2f(RectSize, RectSize));
        _rect.setPosition(PositionX, PositionY);
    }
    ~Cell() {
    }

    void UpdateColor() {
        switch (Alive)
        {
        case true:
            _rect.setFillColor(sf::Color::Black);
            break;
        case false:
            _rect.setFillColor(sf::Color::White);
            break;
        }
    }

    void SetPosition(int x, int y) {

    }

    void Draw() {
        window.draw(_rect);
    }

    sf::RectangleShape RRect() {
        return _rect;
    }

private:
    bool Alive;
    int PositionX, PositionY;
    int RectSize = 16;
    sf::RectangleShape _rect;
    sf::RenderWindow &window;
};



int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 400), "Cellular Automata");
    std::vector<std::vector<Cell>> _Cells;

    for (int i = 0; i < 50; i++) {
        _Cells.push_back(std::vector<Cell>());
        for (int j = 0; j < 25; j++) {
            _Cells[i].push_back(Cell(window, i, j));
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        std::vector<std::vector<Cell> >::iterator row;
        std::vector<Cell>::iterator col;
        for (row = _Cells.begin(); row != _Cells.end(); row++) {
            for (col = row->begin(); col != row->end(); col++) {
                col->UpdateColor();
                window.draw(col->RRect());
            }
        }

        window.display();
    }

    return 0;
}