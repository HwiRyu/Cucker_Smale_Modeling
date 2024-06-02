#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "scale.h"
#include "functions.h"
#include "axes.h"
#include "cucker_smale.h"
#include <random>

Particle particles[N];


int main() {
    // Window initial setting-------------------------------------------------------
    const int width = 1200;
    const int height = 800;

    sf::RenderWindow window(sf::VideoMode(width, height), "3D Graph basis");

    sf::VertexArray one(sf::LineStrip);
    sf::VertexArray plane(sf::LineStrip);
    sf::VertexArray cs(sf::LineStrip);

    sf::Font font;
    if (!font.loadFromFile("/System/Library/Fonts/Monaco.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::View graphView(sf::FloatRect(-width / 2, -height / 2, width, height));
    window.setView(graphView);

    // 텍스트 객체 생성 및 초기화
    sf::Text text_1("Basis", font, 12);
    text_1.setPosition(graphView.getCenter().x + width / 2 - 100, graphView.getCenter().y - height / 2 + 20);
    text_1.setFillColor(sf::Color::Black);

    //---------------------------------------------------------------------------

    //Initialize

    double size = 30;
    double x_angle = -10;
    double y_angle = 5;
    const double pi = 3.14159265358979;
    double t = 0;

    bool domain_fixed = true;

    sf::Clock clock;
    sf::Clock clock_t;

    sf::Time lastClickTime = sf::Time::Zero;
    sf::Vector2i lastMousePos;
    sf::Vector2f startPoint;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> pos_dist(-5.0, 5.0); // 위치 범위
    std::uniform_real_distribution<double> vel_dist(-100.0, 150.0);   // 속도 범위
    std::uniform_real_distribution<double> acc_dist(-10.0, 10.0);     // 가속도 범위
    sf::Time elapsedTime;
    // 입자 초기화
    for (int i = 0; i < N; i++) {
        particles[i].position[0] = pos_dist(eng);
        particles[i].position[1] = pos_dist(eng);
        particles[i].position[2] = pos_dist(eng);

        particles[i].velocity[0] = vel_dist(eng);
        particles[i].velocity[1] = vel_dist(eng);
        particles[i].velocity[2] = vel_dist(eng);

//        particles[i].acceleration[0] = acc_dist(eng);
//        particles[i].acceleration[1] = acc_dist(eng);
//        particles[i].acceleration[2] = acc_dist(eng);
    }


    // Main loop
    while (window.isOpen()) {
        elapsedTime = clock_t.getElapsedTime();
        if (elapsedTime.asSeconds() >= 1.0f) {
            t += 0.00001f;
            clock_t.restart();
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //In euler_method, control step size.
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        y_angle -= 1;
                        break;
                    case sf::Keyboard::Down:
                        y_angle += 1;
                        break;
                    case sf::Keyboard::Left:
                        x_angle += 1;
                        break;
                    case sf::Keyboard::Right:
                        x_angle -= 1;
                        break;
                    case sf::Keyboard::F:
                        if (domain_fixed)
                            domain_fixed = false;
                        else
                            domain_fixed = true;
                        break;
                    case sf::Keyboard::W:
                        size += 5;
                        break;
                    case sf::Keyboard::S:
                        size -= 5;
                        break;
                    default:
                        break;
                }
                size = (size < 5) ? 5 : ((size > 200.0) ? 200.0 : size);
            }

            //Choose Initial point in window
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Time currentTime = clock.getElapsedTime();
                    lastMousePos = sf::Mouse::getPosition(window);
                    startPoint = window.mapPixelToCoords(lastMousePos); // 초기 클릭 위치 저장
                    lastClickTime = currentTime;
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i newMousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f delta = window.mapPixelToCoords(newMousePos) - window.mapPixelToCoords(lastMousePos);
                    graphView.move(-delta); // 시야 이동
                    window.setView(graphView); // 뷰 설정 업데이트
                    lastMousePos = newMousePos; // 새로운 마우스 위치 저장

                }
            }
        }

        window.clear(sf::Color::White);

        //시야각
        double psy = pi * y_angle / 120;
        double theta = pi * (x_angle / 120);
        psy = std::fmod(psy, 2 * pi);
        theta = std::fmod(theta, 2 * pi);
        if (psy < 0) {
            psy += 2 * pi;
        }
        if (theta < 0) {
            theta += 2 * pi;
        }


        double view_center_x = graphView.getCenter().x / (size);
        double view_center_y = -graphView.getCenter().y / (size);
        double center_x = -view_center_x * sin(theta) - cos(theta) * view_center_y / sin(psy);
        double center_y = view_center_x * cos(theta) - sin(theta) * view_center_y / sin(psy);
        double current_center_x;
        double current_center_y;


        if (0.01 * pi < psy && psy < 1.99 * pi && !domain_fixed) {
            current_center_x = center_x;
            current_center_y = center_y;
        }



        coordinate_plane(window, plane, size, current_center_x, current_center_y,
                            x_angle, y_angle, psy);
        cucker_smale_equation(window, cs, particles, 0, t, psi_function, norm_distant, size, theta, psy);

        window.display();


    }
    return 0;

}