#include "Road.hpp"
#include <iostream>

Road::Road(Location *start, Location *stop, int days)
{
    m_a = start;
    m_b = stop;
    m_days = days;
}

Location* Road::get_end(Location* curr)
{
    if (this->m_a == curr) //If next location is valid
        return m_b;
    return m_a;
}

int Road::get_days()
{
    return m_days;
}
