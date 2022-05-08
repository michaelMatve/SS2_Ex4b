#include "Assassin.hpp"

coup::Assassin::Assassin(coup::Game &temp_game, std::string temp_name) : coup::Player(temp_game , temp_name)
{
   this->player_coup_place = 0;
   this->player_coup = " ";
};
//other ride the player coup func
void coup::Assassin::coup(Player &coup_player)
{
   //check the player turn
   if(this->my_game->turn() != this->my_name)
   {
      throw std::invalid_argument("not your turn");
   }
   //check that the player not dead
   if(coup_player.die())
   {  
      throw std::invalid_argument("olredi killed");
   }
   //check the number of coin more then 3
   if(this->coin_number < this->ass_num_kill)
   {
      throw std::invalid_argument("dont have coins");
   }
   //less then 7 else more then 7
   if(this->coin_number < this->kill_num)
   {
      this->player_coup_place =this->my_game->remove(coup_player.my_name);
      this->player_coup =coup_player.my_name;
      this->coin_number-=this->ass_num_kill;
      this->last_act = "scoup";
   } 
   else
   {
      this->my_game->remove(coup_player.my_name);
      this->coin_number-=this->kill_num;
      this->last_act = "coup ";
   }
   this->my_game->change_turn();

}
void coup::Assassin::cancel_act()
{
   //add the player to the game
   this->my_game->add(this->player_coup,this->player_coup_place);
}

std::string coup::Assassin::role()
{
    return "Assassin";
}
