#include "Player.hpp"

coup::Player::Player(coup::Game &temp_game, std::string &temp_name)
{
   //check that there is no more then 6 players
   if(temp_game.players().size()>=this->max_players)
   {
      throw std::invalid_argument("to much players ");
   }
   // check the game not start yet
   if(temp_game.is_start)
   {
       throw std::invalid_argument("olredy start ");
   }
   // add the player to the game and set defult values
   this->my_game = &temp_game;
   this->my_name = temp_name;
   this->my_game->add(temp_name);
   this->coin_number =0;
   this->last_act = "no active";
}

void coup::Player::income()
{
   //check have less then 10 coins
   if(this->coin_number>=this->max_coins)
   {
      throw std::invalid_argument("too much coins ");

   }
   //check the game can start
   if(this->my_game->players().size()<2)
   {
      throw std::invalid_argument("less players ");
   }
   //check the turn
   if(this->my_game->turn() != this->my_name)
   {
      throw std::invalid_argument("not your turn");
   }
   //take one coins
   this->coin_number++;
   this->last_act = "income";
   this->my_game->change_turn();
   this->my_game->is_start = true;
}

void coup::Player::foreign_aid()
{
   //check have less then 10 coins
   if(this->coin_number>=this->max_coins)
   {
      throw std::invalid_argument("too much coins ");

   }
   //check have more the 2 players
   if(this->my_game->players().size()<2)
   {
      throw std::invalid_argument("less players ");
   }
   //check the turn
   if(this->my_game->turn() != this->my_name)
   {
      throw std::invalid_argument("not your turn");
   }
   //take to coins 
   this->coin_number+=2;
   this->last_act = "foreign_aid";
   this->my_game->change_turn();
   this->my_game->is_start = true;
}

void coup::Player::coup(Player &coup_player)
{
   //check have more then 2 players
   if(this->my_game->players().size()<2)
   {
      throw std::invalid_argument("less players ");
   }
   //check the turn
   if(this->my_game->turn() != this->my_name)
   {
      throw std::invalid_argument("not your turn");
   }
   //check have more then 7 coins
   if(this->coin_number < this->kill_num)
   {
       throw std::invalid_argument("dont have coins");
   }
   //check the player not dead
   if(coup_player.die())
   {  
      throw std::invalid_argument("olredi killed");
   }
   //remove the player from the game
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
//check if the player is dead
bool coup::Player::die() const
{
   return !(this->my_game->check_live(this->my_name));
  
}

