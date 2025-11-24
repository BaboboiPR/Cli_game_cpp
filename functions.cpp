#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <string>
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
    static void save_player_pos(const string& file,long long player_data) {
        ofstream file1(file);
        file1<<"{1"<<endl;
        file1 <<to_string(player_data)<<endl;

        file1.close();
    }

    //

    static auto read_player_pos(const string& file) {
        ifstream file1(file);
        string line;
        long long player_data=0;
        while (file1>>line) {
            if (line=="{1"){
                if (file1>> player_data) {
                    return player_data;
                }
            }
        }
        return player_data;
    }

    //

    //

    static void save_player_health(const string& file,long long player_data) {
        ofstream file1(file);
        file1<<"{2"<<endl;
        file1 <<to_string(player_data)<<endl;
        file1.close();
    }

    //

    static auto read_player_health(const string& file) {
        ifstream file1(file);
        string line;
        long long player_data=0;
        while (file1>>line) {
            if (line=="{2"){
                if (file1>> player_data) {
                    return player_data;
                }
            }
        }
        return player_data;
    }

};
