#include "Game.hpp"
#include <iostream>

Game::Game()
{
    select_map();
    m_player.set_location(m_map.get_start_location());
    m_days = 30;
    m_game_over = false;
}

void Game::select_map()
{
    char s;
    std::cout << "Select the map you want to play!\nType 'd' for default map or 'c' for custom map.\n";
    std::cin >> s;
    while(s != 'c' && s!= 'd')
    {
        std::cout << "Please enter a valid input\n";
        std::cin >> s;
    }
    if (s == 'c')
        m_map.read_map("mymap.txt"); //reads custom map of game from text file
    else if(s == 'd')
    {
       m_map.set_map(); //sets default map of game
    }
}

void Game::run()
{
    char choice; //single character user input
    std::string input; //holds string user input
    execute_special(m_player.get_location()->get_special()); //Display welcome message
    path = new Road(nullptr, nullptr, 0);
    do                  //main game loop
    {
        show_state(); //Displays player state after each move
        std::cout << "\nWhich direction would you like to go next?\n";
        std::cout << "Enter n for north, s for south, w for west or e for east..\n"; //User input: N, S, E, W
        std::cin>> choice; //takes user input
        choice = toupper(choice); //converts lower case user input to upper case

        //Check for a valid direction
        while(choice != 'N' && choice != 'S' && choice != 'E' && choice != 'W') //User input: must be one of N, S, E, W
        {   std::cout << "Please enter a valid move: \n";
            std::cin >> choice;
            choice = toupper(choice); //changes lower case input to upper case
        }
        //convert from single character user input to string
        if(choice == 'N')
            input = "NORTH";
        else if(choice == 'S')
            input = "SOUTH";
        else if(choice == 'E')
            input = "EAST";
        else if(choice == 'W')
            input = "WEST";

        // Set road according to user's choice of direction
        path = m_map.get_road(m_player.get_location(), input);

        //If player cannot move further
        if (path->get_end(m_player.get_location()) == nullptr)
        {
            m_days--;
            std::cout << "\nOops! You cannot go any further!\n";
            std::cout<<"You had to go back to where you were before.\n";
            std::cout<<"You sadly lost one entire day.\n";
        }

        //If player tries to cross Bridge of Death with less than 3 crystals
        else if (path->get_end(m_player.get_location())->get_special() == "prince" && m_player.get_crystals() <3)
        {
            std::cout << "\nBLOCKED!!!\n";
            std::cout<<"You do not have all the crystals yet! Go back!\n";
            m_days--;
        }

        //Set player's location to the next location
        else
        {
            m_player.set_location(path->get_end(m_player.get_location()));
            m_days = m_days - path->get_days();
        }

        // executes and removes special
        execute_special(m_player.get_location()->get_special());

        //if food runs out during game play, player dies
        if(m_game_over == false && m_days < 0)
        {
            std::cout << "You ran out of food and have lost all your energy.\n";
            std::cout << "You die of starvation only to be eaten by wild animals later.\n";
            std::cout << "You lose!\n";
            m_game_over = true;
        }
    }
    while (m_days>0 && m_game_over == false);

    path = nullptr;
}

void Game::show_state()
{
    std::cout << "\nYou are currently at the " << m_player.get_location()->get_name() << ".\n";
    if(m_days == 30) //for first call
    {
        std::cout << "Your journey has just begun!\n";
    }
    else
    {
        std::cout << "It has been " << 30 - m_days << " days since your journey began.\n";
    }
    std::cout << "You have enough food to last you " << m_days << " days.\n";
    std::cout << "You have collected " << m_player.get_crystals() << " crystals.\n";
    std::cout << "\n********************************************************************\n";
}

void Game::execute_special(std::string special)
{
    //Displays message at the beginning of game
    if(special == "start")
    {
        std::cout << "*********************************************************************\n";
        std::cout << "** Welcome Zeldana! The adventurous world of SeePlusia awaits you! **\n";
        std::cout << "*********************************************************************\n";
        m_player.get_location()->remove_special(special);
    }

    //Displays message when player retrieves a crystal
    else if (special == "crystal")
    {
        std::cout << "\nCongratulations!! You have found an Objectos crystal!\n";
        m_player.add_crystal();
        m_player.get_location()->remove_special(special);
    }

    //Displays message if player dies at Sands of Quick
    else if(special == "death")
    {
        std::cout << "\nYou stepped in the Sands of Quick! x_x\n";
        std::cout << "You try to get out but the sand pulls you in more!\n";
        std::cout << "You die a slow, painful death.\n";
        std::cout << "You lose!\n";
        m_game_over = true;
    }

    //Displays victory message
    else if (special == "prince")
    {
        std::cout << "\nCONGRATULATIONS!!\nYou overcame all the challenges faced at SeePlusia.\n";
        std::cout << "You saved Prince Lazy with the power of all the 3 Objectos crystals.\n";
        std::cout << "You win!\n";
        m_game_over = true;
    }
}
