#include "Game.hpp"

coup::Game::Game()
{
        this->curr_player =0;
}

std::string coup::Game::turn()
{
    if(this->my_players.empty())
    {
       throw std::invalid_argument("no players in the game");
    }
    return this->my_players[(ulong)this->curr_player];
}

std::vector<std::string> coup::Game::players()
{
    return this->my_players;
}

std::string coup::Game::winner()
{
    //check the game olredy started
    if(!this->is_start)
    {
               throw std::invalid_argument("not start yet");

    }
    //check that only one player left
    if(this->my_players.size() == 1)
    {
        return this->my_players[0];
    }
    throw std::invalid_argument("no one win yet");
}

void coup::Game::add(std::string const &player_name)
{
    //add to the end of the game
    this->my_players.push_back(player_name);
}

void coup::Game::add(std::string const &player_name, int place)
{
    //add to the old place
    if(place<this->curr_player)
    {
        this->curr_player++;
    }
    this->my_players.insert(this->my_players.begin()+(long)place,player_name);
}

int coup::Game::remove(std::string const &player_name)
{
    //remove the player and return it place in the vector
    int i = 0;
    for(i=0; i<this->my_players.size();i++)
    {
        if(this->my_players[(ulong)i]==player_name)
        {
            this->my_players.erase(this->my_players.begin()+(long)i);
            break;
        }
    }
    if(i<= this->curr_player)
    {
        this->curr_player--;
    }
    return i;
}

 void coup::Game::change_turn()
 {
     //change turn by 1 to the next player
    this->curr_player++;
    if(curr_player >=this->my_players.size())
    {
        curr_player=0;
    }
 }

bool coup::Game::check_live(std::string const &player_name)
{
    //check if the player is not dead
    return (std::find(this->my_players.begin(), this->my_players.end(), player_name) !=this-> my_players.end());
}
