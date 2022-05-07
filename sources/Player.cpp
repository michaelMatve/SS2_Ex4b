#include "Player.hpp"

coup::Player::Player(coup::Game &temp_game, std::string &temp_name)
{
   if(temp_game.players().size()>=this->max_players)
   {
      throw std::invalid_argument("to much players ");
   }
   if(temp_game.is_start)
   {
       throw std::invalid_argument("olredy start ");
   }
   this->my_game = &temp_game;
   this->my_name = temp_name;
   this->my_game->add(temp_name);
   this->coin_number =0;
   this->last_act = "no active";
}

void coup::Player::income()
{
   if(this->coin_number>=this->max_coins)
   {
      throw std::invalid_argument("too much coins ");

   }
   if(this->my_game->players().size()<2)
   {
      throw std::invalid_argument("less players ");
   }
   if(this->my_game->turn() != this->my_name)
   {
      throw std::invalid_argument("not your turn");
   }
   this->coin_number++;
   this->last_act = "income";
   this->my_game->change_turn();
   this->my_game->is_start = true;
}

void coup::Player::foreign_aid()
{
   if(this->coin_number>=this->max_coins)
   {
      throw std::invalid_argument("too much coins ");

   }
   if(this->my_game->players().size()<2)
   {
      throw std::invalid_argument("less players ");
   }
   if(this->my_game->turn() != this->my_name)
   {
      throw std::invalid_argument("not your turn");
   }
   this->coin_number+=2;
   this->last_act = "foreign_aid";
   this->my_game->change_turn();
   this->my_game->is_start = true;
}

void coup::Player::coup(Player &coup_player)
{
   if(this->my_game->players().size()<2)
   {
      throw std::invalid_argument("less players ");
   }
   if(this->my_game->turn() != this->my_name)
   {
      throw std::invalid_argument("not your turn");
   }
   if(this->coin_number < this->kill_num)
   {
       throw std::invalid_argument("dont have coins");
   }
   if(coup_player.die())
   {  
      throw std::invalid_argument("olredi killed");
   }
   this->my_game->remove(coup_player.my_name);
   this->coin_number-=this->kill_num;
   this->last_act = "coup ";
   this->my_game->change_turn();
   this->my_game->is_start = true;
}

void coup::Player::cancel_act(){};

int coup::Player::coins() const
{
   return this->coin_number;
}

bool coup::Player::die() const
{
   return !(this->my_game->check_live(this->my_name));
  
}

