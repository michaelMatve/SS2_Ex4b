#include "Duke.hpp"

coup::Duke::Duke(coup::Game &temp_game, std::string temp_name) : coup::Player(temp_game , temp_name){};

std::string coup::Duke::role()
{
    return "Duke";
}

void coup::Duke::tax()
{
    //check the max coin
    if(this->coin_number>=this->max_coins)
   {
      throw std::invalid_argument("too much coins ");

   }
   //check the turn
    if(this->my_game->turn() != this->my_name)
    {
        throw std::invalid_argument("not your turn");
    }
    //add 3 coins
    this->coin_number+=3;
    this->my_game->change_turn();
}

void coup::Duke::block(Player &block_player)
{
    //check the player is alive
    if(!this->my_game->check_live(block_player.my_name))
    {
        throw std::invalid_argument("cant blook");
    }
    //check the last act
    if(block_player.last_act!= "foreign_aid")
    {
        throw std::invalid_argument("cant blook");
    }
    //take down 2 coins
    block_player.coin_number-=2;
    
}