#pragma once

#include <fstream>
#include "polluter std.h"
#include "other.h"
auto add_vectors_x(auto& pos1x,auto& pos2x) {
    auto poslastx=pos1x+pos2x;
    return poslastx;

}
auto add_vectors_y(auto& pos1y,auto& pos2y) {
    auto poslastx=pos1y+pos2y;
    return poslastx;

}

class Saving {
public:
    static void save_player_pos(const string& file,const position2D& position,long long player_health) {
        ofstream file1(file);
        file1<<"x:"<<endl;
        file1 <<to_string(position.x)<<endl;
        file1 <<"y:"<<endl;
        file1 <<to_string(position.y)<<endl;
        file1 <<"health:"<<endl;
        file1 <<to_string(player_health)<<endl;

        file1.close();
    }
    static void save_player_pos(const string& file,const position2D& position) {
        ofstream file1(file);
        file1<<"x:"<<endl;
        file1 <<to_string(position.x)<<endl;
        file1 <<"y:"<<endl;
        file1 <<to_string(position.y)<<endl;
        file1.close();
    }
    //

    static void read_player_pos(const string& file,position2D& position,auto& health) {
        ifstream file1(file);
        string line;
        long long player_data=0;
        while (file1>>line) {
            if (line=="x:"){
                if (file1>> player_data) {
                    position.x=player_data;
                }
            }
            if (line=="y:") {
                if (file1>> player_data) {
                    position.y=player_data;
                }

            }
            if (line=="health:") {
                if (file1>> player_data) {
                    health=player_data;
                }
            }

        }
    }
    //

    //



};
