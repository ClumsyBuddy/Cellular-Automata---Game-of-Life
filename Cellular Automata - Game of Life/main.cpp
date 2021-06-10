#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <Windows.h>
#include <vector>

class CellManager {
public:
    CellManager(sf::RenderWindow &win, int Width, int Height) : window(win){
        XRectAmount = Width / RectSize;
        YRectAmount = Height/ RectSize;
        CameraSpeed = RectSize * CameraOffsetSpeed;
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
        for (int i = 0; i < XRectAmount; i++) {
            for (int j = 0; j < YRectAmount; j++) {

                for (int x = -1; x < 2; x++) {
                        for (int y = -1; y < 2; y++) {

                            if (x == 0 && y == 0) {
                                continue;
                            }else{
                                int cols = (i + x + (XRectAmount)) % (XRectAmount);
                                int rows = (j + y + (YRectAmount)) % (YRectAmount);

                                sum += next_cells[cols][rows];
                                
                            }
                        }
                    }
                    if ((sum == 2 || sum == 3) && next_cells[i][j] == true) {
                        cells[i][j] = true;
                    }
                    else  if (sum < 2 && next_cells[i][j] == true) {
                        cells[i][j] = false;
                        UpdateColor(i, j);
                    }
                    else if (sum > 3 && next_cells[i][j] == true) {
                        cells[i][j] = false;
                        UpdateColor(i, j);
                    }
                    else if (sum == 3 && next_cells[i][j] == false) {
                        cells[i][j] = true;
                        UpdateColor(i, j);
                    }
                    
                sum = 0;
            }
        }
    }

    void ChangePosition(int x, int y) {
        for (int i = 0; i < XRectAmount; i++) {
            for (int j = 0; j < YRectAmount; j++) {
                sf::Vector2f oldpos = _rect[i][j].getPosition();
                _rect[i][j].setPosition(oldpos.x + x, oldpos.y + y);
            }
        }
    }



    void Resize(int num) {
        for (int i = 0; i < XRectAmount; i++) {
            for (int j = 0; j < YRectAmount; j++) {
                sf::Vector2f OldSize = _rect[i][j].getSize();
                if (OldSize.x <= 5 && num < 0)
                    break;
                sf::Vector2f OldPos = _rect[i][j].getPosition();
                sf::Vector2f NewSize = sf::Vector2f(OldSize.x + num, OldSize.y + num);

                sf::Vector2f NewPos;

                float XDiff = (OldPos.x - i * OldSize.x);
                float YDiff = (OldPos.y - j * OldSize.y);
                
                NewPos.x = i * NewSize.x + XDiff;
                NewPos.y = j * NewSize.y + YDiff;

                _rect[i][j].setSize(NewSize);
                _rect[i][j].setPosition(NewPos);
                CameraSpeed = NewSize.x * CameraOffsetSpeed;

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
        for (int i = 0; i < XRectAmount; i++) {
            for (int j = 0; j < YRectAmount; j++) {
                window.draw(_rect[i][j]);
            }
        }
    }


    float CameraSpeed;

private:
    float CameraOffsetSpeed = 3;
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

    bool Pause = false;
    int ResizeOffset = 5;

    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Cellular Automata");

    window.setFramerateLimit(10);
    CellManager CM(window, ScreenWidth, ScreenHeight);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                    CM.Resize(ResizeOffset);
                    break;
                case sf::Mouse::Right:
                    CM.Resize(-ResizeOffset);
                default:
                    break;
                }
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    Pause = !Pause;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    CM.ChangePosition(-CM.CameraSpeed, 0);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    CM.ChangePosition(CM.CameraSpeed, 0);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    CM.ChangePosition(0, -CM.CameraSpeed);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    CM.ChangePosition(0, CM.CameraSpeed);
                break;
            }
        }

        window.clear();
        CM.Draw();
        window.display();
        if (Pause == false) {
            CM.Update();
        }
       
    }

    return 0;
}