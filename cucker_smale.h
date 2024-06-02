//
// Created by Persist on 6/1/24.
//

#ifndef INC_3D_GRAPH_BASIS_CUCKER_SMALE_H
#define INC_3D_GRAPH_BASIS_CUCKER_SMALE_H

const int N = 50;

struct Point {
    double x;
    double y;
    double z;
};

double psi_function(double s) {
    return 1 / pow(s, 1) ;
}

double norm_distant(const double vec_i[3], const double vec_j[3]) {
    double dist_x = vec_i[0] - vec_j[0];
    double dist_y = vec_i[1] - vec_j[1];
    double dist_z = vec_i[2] - vec_j[2];
    return std::sqrt(dist_x * dist_x + dist_y * dist_y + dist_z * dist_z);
}



struct Particle {
    double position[3];
    double velocity[3];
    double acceleration[3];
};

extern Particle particles[N];


void cucker_smale_equation(sf::RenderWindow &window, sf::VertexArray &graph, Particle *particles,
                           double t_start, double t,
                           double (*psi_function)(double),
                           double (*norm_distant)(const double *, const double *),
                           double size,
                           double theta,
                           double phi) {
    double lambda = (99 / N);
    double step = 0.00001;
    for (double time = t_start; time <= t; time += step) {
        for (int i = 0; i < N; i++) {
            double sigma[3] = {0, 0, 0}; // 각 성분별 차이 누적을 위한 배열
            for (int j = 0; j < N; j++) {
                if (i != j) {
                    double distance = norm_distant(particles[i].position, particles[j].position);
                    double psi = psi_function(distance);

                    // 각 성분별로 sigma를 업데이트
                    for (int k = 0; k < 3; k++) {
                        sigma[k] += psi * (particles[j].velocity[k] - particles[i].velocity[k]);
                    }
                }
            }
            for (int k = 0; k < 3; k++) {
                particles[i].acceleration[k] = lambda * sigma[k];
            }
        }
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < 3; k++) {
                particles[i].velocity[k] += step * particles[i].acceleration[k];
                particles[i].position[k] += step * particles[i].velocity[k];
            }
        }
    }
    // 원형 객체 생성 및 초기화
    std::vector<sf::CircleShape> circles(N, sf::CircleShape(std::max(size / 20.0, 3.0)));
    for (auto &circle : circles) {
        circle.setFillColor(sf::Color::Black);
    }
    for (int i = 0; i < N; i++) {
        circles[i].setPosition(x_scale(-particles[i].position[0] * sin(theta) + particles[i].position[1] * cos(theta), size),
                               y_scale(sin(phi) * (-particles[i].position[0] * cos(theta) - particles[i].position[1] * sin(theta)) + particles[i].position[2] * cos(phi), size));
    }
    // 원형 객체 그리기
    for (const auto &circle : circles) {
        window.draw(circle);
    }
}




#endif //INC_3D_GRAPH_BASIS_CUCKER_SMALE_H
