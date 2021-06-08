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

    int IsAlive() {
        return Alive;
    }

    void ToggleCell() {
        Alive = !Alive;
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



class CellManager {
public:
    CellManager(sf::RenderWindow &win) : window(win) {
        CreateCells();

    }
    ~CellManager(){}

    void DrawCells() {
        std::vector<std::vector<Cell> >::iterator row;
        std::vector<Cell>::iterator col;
        for (row = cells.begin(); row != cells.end(); row++) {
            for (col = row->begin(); col != row->end(); col++) {
                col->UpdateColor();
                window.draw(col->RRect());
            }
        }
    }

    int FindNeighbors() {
        int sum = 0;
        next = cells;
        for (std::size_t i = 0; i < cells.size()-1; i++) {
            for (std::size_t j = 0; j < cells[i].size()-1; j++) {
                if (i != cells.size() && j != cells[i].size() && i > 0 && j > 0) {
                    sum += cells[i + 1][j].IsAlive();
                    sum += cells[i - 1][j].IsAlive();
                    sum += cells[i + 1][j + 1].IsAlive();
                    sum += cells[i - 1][j - 1].IsAlive();
                    sum += cells[i][j - 1].IsAlive();
                    sum += cells[i][j + 1].IsAlive();
                    sum += cells[i + 1][j - 1].IsAlive();
                    sum += cells[i - 1][j + 1].IsAlive();
                    if (sum < 2 && cells[i][j].IsAlive() == true) {
                        cells[i][j].ToggleCell();
                    }
                    else if (sum > 3 && cells[i][j].IsAlive() == true) {
                        cells[i][j].ToggleCell();
                    }
                    else if (sum == 2 && cells[i][j].IsAlive() == false) {
                        cells[i][j].ToggleCell();
                    }
                    sum *= 0;
                }
                else {
                    continue;
                }
            }
        }
        return sum;
    }


private:
    void CreateCells() {
        for (int i = 0; i < CellAmountX; i++) {
            cells.push_back(std::vector<Cell>());
            for (int j = 0; j < CellAmountY; j++) {
                cells[i].push_back(Cell(window, i, j));
            }
        }
    }

    std::vector<std::vector<Cell>> cells;
    std::vector<std::vector<Cell>> next;
    sf::RenderWindow &window;
    int CellAmountX = 50;
    int CellAmountY = 25;


};







int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 400), "Cellular Automata");

    CellManager CM(window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        CM.DrawCells();
        window.display();
        CM.FindNeighbors();
    }

    return 0;
}