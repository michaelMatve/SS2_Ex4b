#include "Captain.hpp"

coup::Captain::Captain(coup::Game &temp_game, std::string temp_name): coup::Player(temp_game , temp_name){this->from_player_steal = NULL;};

std::string coup::Captain::role()
{
    return "Captain";
}
        
void coup::Captain::steal(Player &from_p)
{
    //check the number of coins 
    if(this->coin_number>=this->max_coins)
   {
      throw std::invalid_argument("too much coins ");

   }
   //check that the player turn
    if(this->my_game->turn() != this->my_name)
    {
        throw std::invalid_argument("not your turn");
    }
    // check not die
    if(from_p.die())
    {
        throw std::invalid_argument("players are not exist");
    }
    //check the number of coins that the player can steel and save it
    if(from_p.coins()>=2)
    {
        this->number_coin_steal =2;
    }
    else if(from_p.coins()==1)
    {
        this->number_coin_steal =1;
    }
    else{
        this->number_coin_steal =0;
    }
    //take the number of coin that was saved from other player
    from_p.coin_number-=this->number_coin_steal;
    this->coin_number+=this->number_coin_steal;
    this->from_player_steal = &from_p;
    this->last_act ="steal";
    this->my_game->change_turn();
}

void coup::Captain::cancel_act()
{
    //return the number off coins that was stolen
    this->from_player_steal->coin_number +=this->number_coin_steal;
    this->coin_number-=this->number_coin_steal;
}       
void coup::Captain::block(Player &block_player)
{
    //check live
    if(!this->my_game->check_live(block_player.my_name))
    {
        throw std::invalid_argument("cant blook");
    }
    //check act
    if(block_player.last_act!= "steal")
    {
        throw std::invalid_argument("cant blook");
    }
    //tell the player to cancel it
    block_player.cancel_act();
}
