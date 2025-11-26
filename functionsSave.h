#pragma once

#include <fstream>
using namespace std;

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
    static void save_player_pos(const string& file,long long player_x,long long player_y,long long player_health) {
        ofstream file1(file);
        file1<<"x:"<<endl;
        file1 <<to_string(player_x)<<endl;
        file1 <<"y:"<<endl;
        file1 <<to_string(player_y)<<endl;
        file1 <<"health:"<<endl;
        file1 <<to_string(player_health)<<endl;

        file1.close();
    }
    static void save_player_pos(const string& file,long long player_x,long long player_y) {
        ofstream file1(file);
        file1<<"x:"<<endl;
        file1 <<to_string(player_x)<<endl;
        file1 <<"y:"<<endl;
        file1 <<to_string(player_y)<<endl;
        file1.close();
    }
    //

    static auto read_player_pos(const string& file,auto& posX, auto& posY,auto& health) {
        ifstream file1(file);
        string line;
        long long player_data=0;
        while (file1>>line) {
            if (line=="x:"){
                if (file1>> player_data) {
                    posX=player_data;
                }
            }
            if (line=="y:") {
                if (file1>> player_data) {
                    posY=player_data;
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
