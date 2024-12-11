#ifndef GRAPHING_H
#define GRAPHING_H

#include "SFML-2.6.2/include/SFML/Graphics.hpp"
#include <utility>
#include <iostream>
#include "config.h"

// this double _0 thing is so janky idk what to say
// the number of function arguments must match between all function types
// if they dont, the code errors, so doing this just fixed it
// double constant_func(double a,                                                  double _0, double _1, double _2, double _3);

double linear_func(double x,         double m, double b,                        double _0, double _1);

double quadratic_func(double x,      double a, double b, double c,              double _0);

double cubic_func(double x,          double a, double b, double c, double d);

double n_root_func(double x,         double n, double a, double b,              double _0);

template <typename Func, typename... Args>
void draw_graph(
    sf::RenderWindow& window, 
    Func&& f, // the mathematical function f(x)
    Args&&... args // the coefficients for f(x)
) 
{
    double step = 0.1;
    sf::View view(sf::FloatRect(cfg.d1(), -cfg.d2(), cfg.d2() - cfg.d1(), cfg.d2() * 2));
    window.setView(view);

    sf::VertexArray lines(sf::LinesStrip);
    for (double x = cfg.d1(); x <= cfg.d2(); x += step) {
        double y = std::forward<Func>(f)(x, std::forward<Args>(args)...);
        // if (f == n_root_func && x < 0 && x > -2) {
        //     std::cout << x << " <- x || y -> " << y << std::endl;
        // }
        // we use the function argument 'f' and call it with x along with the coefficient arguments 'args'
        lines.append(sf::Vertex(sf::Vector2f(x * cfg.scale_factor, -y * cfg.scale_factor)));
        // window.display();
        // sf::sleep(sf::milliseconds((int)(step/(d2-d1)) * 1000));
    }
    window.draw(lines);
}

void draw_textlabels(sf::RenderWindow& window, sf::Text& text, int axis);

void draw_axes(sf::RenderWindow& window);

#endif