#include <iostream>
#include <fstream>
#include "Map.hpp"
using namespace std;

Map::Map()
{
    m_start = nullptr;
}

Map::~Map()
{
    delete[] m_start;
}

void Map::set_map()
{
    Location *allLocations = new Location[9];

    for (int i = 0; i < 9; i++)
    {
        switch (i)
        {
        case 0:
            allLocations[i].set_name("Enchanted Forest");
            allLocations[i].set_north(&allLocations[3], 1);
            allLocations[i].set_south(&allLocations[5], 3);
            allLocations[i].set_east(&allLocations[1], 2);
            allLocations[i].set_west(&allLocations[7], 1);
            allLocations[i].set_special("start");
            break;

        case 1:
            allLocations[i].set_name("Swamps of Despair");
            allLocations[i].set_north(&allLocations[2], 2);
            allLocations[i].set_south(&allLocations[4], 1);
            allLocations[i].set_east(nullptr, 1);
            allLocations[i].set_west(&allLocations[0], 2);
            allLocations[i].set_special("");
            break;

        case 2:
            allLocations[i].set_name("Sands of Quick");
            allLocations[i].set_north(nullptr, 1);
            allLocations[i].set_south(nullptr, 1);
            allLocations[i].set_east(nullptr, 1);
            allLocations[i].set_west(nullptr, 1);
            allLocations[i].set_special("death");
            break;

        case 3:
            allLocations[i].set_name("Marsh of the Undead");
            allLocations[i].set_north(nullptr, 1);
            allLocations[i].set_south(&allLocations[0], 1);
            allLocations[i].set_east(&allLocations[2], 1);
            allLocations[i].set_west(nullptr, 1);
            allLocations[i].set_special("crystal");
            break;

        case 4:
            allLocations[i].set_name("Elven Waterfall");
            allLocations[i].set_north(&allLocations[1], 1);
            allLocations[i].set_south(nullptr, 1);
            allLocations[i].set_east(nullptr, 1);
            allLocations[i].set_west(nullptr, 1);
            allLocations[i].set_special("crystal");
            break;

        case 5:
            allLocations[i].set_name("Vampire Cove");
            allLocations[i].set_north(&allLocations[0], 3);
            allLocations[i].set_south(&allLocations[6], 3);
            allLocations[i].set_east(nullptr, 1);
            allLocations[i].set_west(nullptr, 1);
            allLocations[i].set_special("");
            break;

        case 6:
            allLocations[i].set_name("Werewolf Hill");
            allLocations[i].set_north(&allLocations[5], 3);
            allLocations[i].set_south(nullptr, 1);
            allLocations[i].set_east(nullptr, 1);
            allLocations[i].set_west(nullptr, 1);
            allLocations[i].set_special("crystal");
            break;

        case 7:
            allLocations[i].set_name("Bridge of Death");
            allLocations[i].set_north(nullptr, 1);
            allLocations[i].set_south(nullptr, 1);
            allLocations[i].set_east(&allLocations[0], 1);
            allLocations[i].set_west(&allLocations[8], 5);
            allLocations[i].set_special("");
            break;

        case 8:
            allLocations[i].set_name("Wizard's Castle");
            allLocations[i].set_north(nullptr, 1);
            allLocations[i].set_south(nullptr, 1);
            allLocations[i].set_east(nullptr, 1);
            allLocations[i].set_west(nullptr, 1);
            allLocations[i].set_special("prince");
            break;
        }
    }
    m_start = &allLocations[0]; // set start location to Enchanted Forest
}

Location *Map::get_start_location()
{
    return m_start;
}

Road *Map::get_road(Location *location, std::string choice)
{
    if (location != nullptr)
    {
        if (choice == "NORTH")
            return location->get_north();
        else if (choice == "SOUTH")
            return location->get_south();
        else if (choice == "EAST")
            return location->get_east();
        else if (choice == "WEST")
            return location->get_west();
    }

    return nullptr; //In case of no road in that direction
}

void Map::read_map(std::string file_name)
{
    string line;
    fstream Mapfile(file_name);
    getline(Mapfile, line);
    int loc_id = stoi(line);
    Location *allLocations = new Location[loc_id];
    int i = 0, pos;
    //this loop will extract all the location names from the file
    while (i < loc_id)
    {
        getline(Mapfile, line); //location id
        getline(Mapfile, line); //location name
        pos = line.find(":");
        string name = line.substr(pos + 2);
        (allLocations + i)->set_name(name);
        i++;
    }
    //this loop will extract neighbouring locations for each location id
    for (int i = 0; i < loc_id; i++)
    {
        pos = 0;
        getline(Mapfile, line); //location id
        //for each location the loop will run 4 times to get neighbouring locations
        for (int j = 0; j < 4; j++)

        {
            int id_loc;
            getline(Mapfile, line);     // direction
            id_loc = line.back() - '0'; // location in that particular direction
            pos = line.find(":");
            string dir = line.substr(0, pos - 1);
            getline(Mapfile, line); //days
            cout << line.substr(0, pos - 1);
            if (line.substr(0, pos - 1) == "north")
            {
                if (line.back() - '0' != ':')
                {
                    (allLocations + i)->set_north(allLocations + id_loc, line.back() - '0');
                }
                else
                {
                    (allLocations + i)->set_north(nullptr, 1); //invalid move increases days by 1
                }
            }
            else if (line.substr(0, pos - 1) == "south")
            {
                if (line.back() - '0' != ':')
                {
                    (allLocations + i)->set_south(allLocations + id_loc, line.back() - '0');
                }
                else
                {
                    (allLocations + i)->set_south(nullptr, 1);
                }
            }
            else if (line.substr(0, pos - 1) == "east")
            {
                if (line.back() - '0' != ':')
                {
                    (allLocations + i)->set_east(allLocations + id_loc, line.back() - '0');
                }
                else
                {
                    (allLocations + i)->set_east(nullptr, 1); //invalid move increases days by 1
                }
            }
            else if (line.substr(0, pos - 1) == "west")
            {
                if (line.back() - '0' != ':')
                {
                    (allLocations + i)->set_west(allLocations + id_loc, line.back() - '0');
                }
                else
                {
                    (allLocations + i)->set_west(nullptr, 1); //invalid move increases days by 1
                }
            }
        }
        getline(Mapfile, line); //special
        pos = line.find(":");
        string special;
        if (pos != (line.size() - 1))
        {
            special = line.substr(pos + 2);
        }
        else
        {
            special = "";
        }
        if (special == "start")
        {
            m_start = (allLocations + i);
        }
        (allLocations + i)->set_special(special);
        //update special
    }
}
