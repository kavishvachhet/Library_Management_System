#pragma once
#include <string>

class Address {
private:
    std::string street;
    std::string city;
    std::string state;
    std::string zipCode;
    std::string country;

public:
    Address(const std::string& street,
            const std::string& city,
            const std::string& state,
            const std::string& zipCode,
            const std::string& country)
        : street(street),
          city(city),
          state(state),
          zipCode(zipCode),
          country(country) {}
};
