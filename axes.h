//
// Created by Persist on 3/5/24.
//



#include <complex>

void coordinate_plane(sf::RenderWindow &window,
                         sf::VertexArray &graph,
                         double size,
                         double view_center_x,
                         double view_center_y,
                         double x_angle,
                         double y_angle,
                         double psy
) {
    sf::Color transparentRed = sf::Color(0, 0, 0, 50);
    double phi = pi * y_angle / 120;
    double theta = pi * x_angle / 120;
    double length = 1;

    double x_start = view_center_x - 50;
    double x_end = view_center_x + 50;
    double y_start = view_center_y - 50;
    double y_end = view_center_y + 50;

    for (double x = x_start; x <= x_end; x += length) {
        for (double y = y_start; y <= y_end; y += length) {
            double z = 0;

            double x_final = -x * sin(theta) + y * cos(theta);
            double y_final = sin(phi) * (-x * cos(theta) - y * sin(theta)) + z * cos(phi);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size), y_scale(y_final, size)), transparentRed));
        }
        window.draw(graph);
        graph.clear();
    }

    for (double y = y_start; y <= y_end; y += length) {
        for (double x = x_start; x <= x_end; x += length) {
            double z = 0;
            double x_final = -x * sin(theta) + y * cos(theta);
            double y_final = sin(phi) * (-x * cos(theta) - y * sin(theta)) + z * cos(phi);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size), y_scale(y_final, size)), transparentRed));
        }
        window.draw(graph);
        graph.clear();
    }
        //Z축은 나중에
}
