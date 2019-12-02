#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <string>

// idk anything about cars ;_;
class Vehicle {
    friend std::istream &read(std::istream &is, Vehicle vhcl);

public:
    Vehicle(std::string t, std::string mk, std::string mdl, unsigned yr = 0,
            unsigned tspeed = 0, double accl = 0.0,
            std::string elecgas = "", double mlage = 0.0,
            unsigned seat = 1) :
            type(t), make(mk), model(mdl), year(yr),
            topspeed(tspeed), zto60(accl),
            fuel(elecgas), mileage(mlage),
            seating(seat) {}

    Vehicle(std::istream &is) { read(is, *this); }

private:
    std::string type;
    std::string make;
    std::string model;
    unsigned year = 0;
    unsigned topspeed = 0;
    double zto60 = 0.0;
    std::string fuel;
    double mileage = 0.0;
    unsigned seating = 1;
};

std::istream &read(std::istream &is, Vehicle vhcl);

#endif
