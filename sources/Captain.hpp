#include "Player.hpp"

namespace coup{

    class Captain : public coup::Player{
        public:
        Player *from_player_steal;
        int number_coin_steal = 0;
        Captain(coup::Game &temp_game, std::string temp_name);
        std::string role();
        void steal(Player &from_p);
        
        void block(Player &block_player);

        void cancel_act();

        
    };
    
}