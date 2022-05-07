#include "Captain.hpp"

coup::Captain::Captain(coup::Game &temp_game, std::string temp_name): coup::Player(temp_game , temp_name){this->from_player_steal = NULL;};

std::string coup::Captain::role()
{
    return "Captain";
}
        
void coup::Captain::steal(Player &from_p)
{
    if(this->coin_number>=this->max_coins)
   {
      throw std::invalid_argument("too much coins ");

   }
    if(this->my_game->turn() != this->my_name)
    {
        throw std::invalid_argument("not your turn");
    }
    if(from_p.die())
    {
        throw std::invalid_argument("players are not exist");
    }
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
    from_p.coin_number-=this->number_coin_steal;
    this->coin_number+=this->number_coin_steal;
    this->from_player_steal = &from_p;
    this->last_act ="steal";
    this->my_game->change_turn();
}

void coup::Captain::cancel_act()
{
    
    this->from_player_steal->coin_number +=this->number_coin_steal;
    this->coin_number-=this->number_coin_steal;
}       
void coup::Captain::block(Player &block_player)
{
    if(!this->my_game->check_live(block_player.my_name))
    {
        throw std::invalid_argument("cant blook");
    }
    if(block_player.last_act!= "steal")
    {
        throw std::invalid_argument("cant blook");
    }
    block_player.cancel_act();
}
