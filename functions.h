//
// Created by Persist on 3/5/24.
//


#include <complex>
const double pi = 3.14159265358979;

double one_variable_function(double x, double y) {
//    std::complex<double> z(x, y);
//    std::complex<double> a(0, 1);

//    std::complex<double> function_value = exp(-1.0/(sin(z) + 2.0));
    double function_value = 0;

    return function_value;
}

void origin_function_one(sf::RenderWindow &window,
                         sf::VertexArray &graph,
                         double size,
                         double one_variable_input_function(double, double),
                         double view_center_x,
                         double view_center_y,
                         double x_angle,
                         double y_angle
) {
    sf::Color transparentRed = sf::Color(0, 0, 255, 100);
    double phi = pi * y_angle / 120;
    double theta = pi * x_angle / 120;
    double length = 0.1;


    double x_start = view_center_x - 5;
    double x_end = view_center_x + 5;
    double y_start = view_center_y - 5;
    double y_end = view_center_y + 5;

    for (double x = x_start; x <= x_end; x += length) {
        for (double y = y_start; y <= y_end; y += length) {
            double z = one_variable_input_function(x, y);

            double x_final = -x * sin(theta) + y * cos(theta);
            double y_final = sin(phi) * (-x * cos(theta) - y * sin(theta)) + z * cos(phi);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size), y_scale(y_final, size)), transparentRed));
        }
        window.draw(graph);
        graph.clear();
    }

    for (double y = y_start; y <= y_end; y += length) {
        for (double x = x_start; x <= x_end; x += length) {
            double z = one_variable_input_function(x, y);

            double x_final = -x * sin(theta) + y * cos(theta);
            double y_final = sin(phi) * (-x * cos(theta) - y * sin(theta)) + z * cos(phi);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size), y_scale(y_final, size)), transparentRed));
        }
        window.draw(graph);
        graph.clear();
    }
}
