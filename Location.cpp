#include <iostream>
#include "Location.hpp"

using namespace std;

Location::Location()
{
    m_name = "";
}

Location::~Location()
{
    
}

Location::Location(std::string name, std::string special)
{
    m_north = nullptr;
    m_south = nullptr;
    m_east = nullptr;
    m_west = nullptr;;
}

void Location::set_name(std::string name)
{
    m_name = name;
}

std::string Location::get_name()
{
    return m_name;
}

void Location::set_special(std::string special)
{
    m_special = special;
}

std::string Location::get_special()
{
    return m_special;
}

void Location::remove_special(std::string done)
{
    m_special = "";
}

void Location::set_north(Location* loc, int days)
{
    m_north = new Road(this, loc, days);
}

void Location::set_south(Location* loc, int days)
{
    m_south = new Road(this, loc, days);
}

void Location::set_east(Location* loc, int days)
{
    m_east = new Road(this, loc, days);
}

void Location::set_west(Location* loc, int days)
{
    m_west = new Road(this, loc, days);
}

Road* Location::get_north()
{
    return this->m_north;
}

Road* Location::get_south()
{
    return this->m_south;
}

Road* Location::get_east()
{
    return this->m_east;
}

Road* Location::get_west()
{
    return this->m_west;
}
