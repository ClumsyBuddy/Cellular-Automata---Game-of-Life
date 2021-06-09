#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <Windows.h>


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
        int num = rand() % 20 + 0;
        if (num > 13) {
            return true;
        }
        else {
            return false;
        }
    }

    void Update() {
        next_cells = cells;
        int sum = 0;
        for (int i = 0; i < next_cells.size() - 1; i++) {
            for (int j = 0; j < next_cells[i].size() - 1; j++) {

                for (int x = -1; x < 2; x++) {
                        for (int y = -1; y < 2; y++) {
                            if (x == 0 && y == 0) {
                                continue;
                            }
                            else {
                                int cols = (i + x + (next_cells.size()-1)) % (next_cells.size()-1);
                                int rows = (j + y + (next_cells[i].size()-1)) % (next_cells[i].size()-1);
                                sum += next_cells[cols][rows];
                            }
                        }
                    }

                    if (sum < 2 && next_cells[i][j] == true) {
                        cells[i][j] = false;
                    }
                    else if (sum > 3 && next_cells[i][j] == true) {
                        cells[i][j] = false;
                    }
                    else if ((sum == 2 || sum == 3) && next_cells[i][j] == true) {
                        cells[i][j] = true;
                    }
                    else if (sum == 3 && next_cells[i][j] == false) {
                        cells[i][j] = true;
                    }
                    UpdateColor(i, j);
                sum *= 0;
            }
        }
    }

    void UpdateColor(int i, int j) {
        if (cells[i][j] == true) {
            _rect[i][j].setFillColor(sf::Color::Black);
        }
        else {
            _rect[i][j].setFillColor(sf::Color::White);
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
    int ScreenWidth = 1280;
    int ScreenHeight = 720;

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
    }

    return 0;
}