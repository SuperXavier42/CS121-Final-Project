#ifndef CONFIG_H
#define CONFIG_H

struct Config {
    int res_x = 800;
    int res_y = 600;

    double domain = 15;

    double scale_factor = 10.0;

    double d1() const {return -domain * scale_factor;};
    double d2() const {return domain * scale_factor;};
};

extern Config cfg;

#endif