#include "SFML-2.6.2/include/SFML/Graphics.hpp" // for displaying the graph in a new window
#include "config.h"
#include <cmath> // for square roots

void draw_textlabels(sf::RenderWindow& window, sf::Text& text, int axis) {
    for (int x = (int)cfg.d1(); x <= (int)cfg.d2(); x += 5 * (int)cfg.scale_factor) {
        if (abs(x) < .1) { // skips zero and near-zero values
            continue;
        }
        text.setString(std::to_string((int)(((double)x)/cfg.scale_factor)));
        // the above math finds an increment number that fits well to the graph given the scale factor
        if (axis == 0) {
            text.setPosition(x, 5);  // place label above the X-axis
        } else if (axis == 1) {
            text.setPosition(5, -x);  // next to the Y-axis
        }
        window.draw(text); // this line does weird stuff
        // when text is drawn, the graphed functions lose their colors
        // when this line is commented, not only does the text disappear (expected) ...
        // ... but also, the axes disappear
    }
}

void draw_axes(sf::RenderWindow& window) {
    // sf::View originalView = window.getView();
    // sf::View view(sf::FloatRect(d1, -d2, d2 - d1, d2 * 2));
    // window.setView(view);

    sf::VertexArray axes(sf::Lines, 4);

    // x-axis
    axes[0].position = sf::Vector2f(cfg.d1(), 0);
    axes[1].position = sf::Vector2f(cfg.d2(), 0);

    // y
    axes[2].position = sf::Vector2f(0, cfg.d1());
    axes[3].position = sf::Vector2f(0, cfg.d2());

    // draw the axes
    window.draw(axes);

    // set up font to label each axis
    sf::Font font;
    if (!font.loadFromFile("rainyhearts.ttf")) {
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(12);

    // label for X-axis numbers
    draw_textlabels(window, text, 0);
    draw_textlabels(window, text, 1);
    // std::cout << "hello" << std::endl;

    // window.setView(originalView);
}

// double constant_func(double a,                                                  double _0, double _1, double _2, double _3) {
//     return a;
// }

double linear_func(double x,         double m, double b,                        double _0, double _1) { 
    return m*x + b; // guys its y = mx + b 🤯
}

double quadratic_func(double x,      double a, double b, double c,              double _0) {
    return a* pow(x, 2) + b * x + c;
}

double cubic_func(double x,          double a, double b, double c, double d) {
    return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
}

double n_root_func(double x,         double n, double a, double b,              double _0) {
    return a * pow(x, 1/n) + b;
}

// sample math functions

// double parabola(double x) {
//     return pow(x, 2);
// }

// double steep_slope(double x) {
//     return 2 * x;
// }

// double complicated(double x) {
//     return -2 * pow(x, 3) + pow(x, 2) + 7 * x + 3;
// }

