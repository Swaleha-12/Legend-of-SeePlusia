#pragma once
#include "Road.hpp"
#include <iostream>

class Location
{
private:
    std::string m_name;                        // the name of this location.

    /* The special characteristic of this location, one of
        - start: this is the start location,
        - crystal: a crystal is present here,
        - death: getting here results in the player's death
        - prince: the prince is imprisoned here.
        The string is empty if this location has no special characteristic.
    */
    std::string m_special;

    // Outgoing roads. A road is set to NULL if there is travel is not possible in
    // that directions.
    Road *m_north, *m_south, *m_east, *m_west;

public:
    Location();
    ~Location();
    Location(std::string, std::string); // initialize name and special.
    void set_name(std::string); // sets the name of the location.
    std::string get_name();    // returns this location's name.
    void set_special(std::string); // sets special characteristic of the location, if any.
    std::string get_special(); // returns this location's special characteristic.
    void remove_special(std::string); // removes the given special characteristic.

    // Set a neighbour by setting the corresponding road appropriately.
    void set_north(Location*, int);
    void set_south(Location*, int);
    void set_east(Location*, int);
    void set_west(Location*, int);

    // Get a neighbour - NULL if travel is not possible in that direction.
    Road* get_north();
    Road* get_south();
    Road* get_east();
    Road* get_west();
};
