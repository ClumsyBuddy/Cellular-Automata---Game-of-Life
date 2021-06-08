#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>



class CellManager {
public:
    CellManager(sf::RenderWindow &win, int Width, int Height) : window(win){
        XRectAmount = Width / RectSize;
        YRectAmount = Height/ RectSize;
        InitRects();
    }
    ~CellManager(){}

    void InitRects() {
        for (int i = 0; i < XRectAmount + 1; i++) {
            _rect.push_back(std::vector<sf::RectangleShape>());
            cells.push_back(std::vector<bool>());
            for (int j = 0; j < YRectAmount + 1; j++) {
                cells[i].push_back(RandomReturn());
                _rect[i].push_back(sf::RectangleShape());
                if (cells[i][j] == 0) {
                    _rect[i][j].setFillColor(sf::Color::White);
                }else{
                    _rect[i][j].setFillColor(sf::Color::Black);
                }
                _rect[i][j].setSize(sf::Vector2f(RectSize, RectSize));
                //_rect[i][j].setOutlineColor(sf::Color::Black);
                //_rect[i][j].setOutlineThickness(1);
                _rect[i][j].setPosition(i * RectSize, j *RectSize);
            }
        }
    }

    bool RandomReturn() {
        return rand() % 2;
    }

    void Update() {
        next_cells = cells;
        int sum = 0;
        for (int i = 0; i < next_cells.size() - 1; i++) {
            for (int j = 0; j < next_cells[i].size() - 1; j++) {
                if (i != next_cells.size() && j != next_cells[i].size() && i > 0 && j > 0) {
                    sum += next_cells[i + 1][j];
                    sum += next_cells[i - 1][j];
                    sum += next_cells[i + 1][j + 1];
                    sum += next_cells[i - 1][j - 1];
                    sum += next_cells[i][j - 1];
                    sum += next_cells[i][j + 1];
                    sum += next_cells[i + 1][j - 1];
                    sum += next_cells[i - 1][j + 1];
                    if (sum < 2) {
                        next_cells[i][j] = false;
                    }
                    else if (sum > 3) {
                        next_cells[i][j] = false;
                    }
                    else if (sum == 2 && next_cells[i][j] == false) {
                        next_cells[i][j] = true;
                    }
                    //std::cout << sum << std::endl;
                }
                sum *= 0;
                //cells[i][j] = next_cells[i][j];
            }
        }
        cells = next_cells;
    }

    void UpdateColor() {
        for (int i = 0; i < cells.size() - 1; i++) {
            for (int j = 0; j < cells[i].size() - 1; j++) {
                if (cells[i][j] == true) {
                    _rect[i][j].setFillColor(sf::Color::Black);
                }
                else {
                    _rect[i][j].setFillColor(sf::Color::White);
                }
            }
        }
    }


    void Draw() {
        for (int i = 0; i < _rect.size() - 1; i++) {
            for (int j = 0; j < _rect[i].size() - 1; j++) {
                window.draw(_rect[i][j]);
            }
        }
    }

private:
    int RectSize = 10;
    int XRectAmount;
    int YRectAmount;
    std::vector<std::vector<sf::RectangleShape>> _rect;
    sf::RenderWindow &window;
    std::vector<std::vector<bool>> cells;
    std::vector<std::vector<bool>> next_cells;
};




int main()
{
    int ScreenWidth = 800;
    int ScreenHeight = 400;

    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Cellular Automata");

    CellManager CM(window, ScreenWidth, ScreenHeight);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                continue;
            }
        }

        window.clear();
        CM.Draw();
        window.display();
        CM.Update();
        CM.UpdateColor();
    }

    return 0;
}