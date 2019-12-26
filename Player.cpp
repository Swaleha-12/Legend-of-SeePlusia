#include "Player.hpp"

Player::Player()
{
    m_crystals = 0;
    m_location = nullptr;
}

void Player::set_location(Location* loc)
{
    m_location = loc;
}

Location* Player::get_location()
{
    return m_location;
}

void Player::add_crystal()
{
    m_crystals++;
}

int Player::get_crystals()
{
    return m_crystals;
}
