#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX 1
#endif
#define _NO_STD_BYTE 1
#include <cstddef>
#include  "functionsSave.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

class WinApi {
public:
    static void enable_ansi_colors()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }

    static void fastPrint(const std::string& s) {
        DWORD written;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        WriteConsoleA(h, s.c_str(), s.size(), &written, nullptr);
    }

    static void clearScreen() {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(h, &csbi);

        DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
        DWORD count;

        COORD home = {0, 0};

        // fill entire buffer with spaces
        FillConsoleOutputCharacter(h, ' ', cellCount, home, &count);

        // reset all attributes (color, bold, etc)
        FillConsoleOutputAttribute(h, csbi.wAttributes, cellCount, home, &count);

            // put cursor at top-left
        SetConsoleCursorPosition(h, home);
        std::cout << "\033[2J";
    }

    void Input(char& line) {
        if (GetAsyncKeyState('Q') & 0x8000) line='q';
        if (GetAsyncKeyState('W') & 0x8000) line='w';
        if (GetAsyncKeyState('E') & 0x8000) line='e';
        if (GetAsyncKeyState('R') & 0x8000) line='r';
        if (GetAsyncKeyState('T') & 0x8000) line='t';
        if (GetAsyncKeyState('Y') & 0x8000) line='y';
        if (GetAsyncKeyState('U') & 0x8000) line='u';
        if (GetAsyncKeyState('I') & 0x8000) line='i';
        if (GetAsyncKeyState('O') & 0x8000) line='o';
        if (GetAsyncKeyState('P') & 0x8000) line='p';
        if (GetAsyncKeyState('A') & 0x8000) line='a';
        if (GetAsyncKeyState('S') & 0x8000) line='s';
        if (GetAsyncKeyState('D') & 0x8000) line='d';
        if (GetAsyncKeyState('F') & 0x8000) line='f';
        if (GetAsyncKeyState('G') & 0x8000) line='g';
        if (GetAsyncKeyState('H') & 0x8000) line='h';
        if (GetAsyncKeyState('J') & 0x8000) line='j';
        if (GetAsyncKeyState('K') & 0x8000) line='k';
        if (GetAsyncKeyState('L') & 0x8000) line='l';
        if (GetAsyncKeyState('Z') & 0x8000) line='z';
        if (GetAsyncKeyState('X') & 0x8000) line='x';
        if (GetAsyncKeyState('C') & 0x8000) line='c';
        if (GetAsyncKeyState('V') & 0x8000) line='v';
        if (GetAsyncKeyState('B') & 0x8000) line='b';
        if (GetAsyncKeyState('N') & 0x8000) line='n';
        if (GetAsyncKeyState('M') & 0x8000) line='m';
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) line=' ';
        }
    };

    //

    class player {
    public:
        long long x;
        long long y;
        char symbol;
        long long health;
        long long maxhealth;
        long long damage;
        player() : x(15), y(15), symbol('#'), health(100), maxhealth(100), damage(5) {}
        player(long long pos_x,long long pos_y,char symbol_,long long health_,long long maxhealth_) {
            x=pos_x;
            y=pos_y;
            symbol=symbol_;
            health=health_;
            maxhealth=maxhealth_;

        }
    };

    //

    class thing {
        public:
        long long x;
        long long y;
        char symbol;
        bool collider;
        int color;
        int damage;
        int health;
        thing(long long thing_pos_x=10,long long thing_pos_y=10,char stone='@',bool collider1 =false,int color_=0,int damage_=0,int _health=-1) {
            x=thing_pos_x;
            y=thing_pos_y;
            symbol=stone;
            collider=collider1;
            color =color_;
            damage=damage_;
            health=_health;
        }

    };

    //

    class functions_things {
        public:

        vector<thing> things_stack;
        vector<thing*> things_heap;


        void new_stack(auto thing_pos_x,auto thing_pos_y,auto car,auto collider,auto color){
            things_stack.emplace_back(thing_pos_x,thing_pos_y,car,collider,color);

        }
        void new_stack(auto thing_pos_x,auto thing_pos_y,auto car,auto collider,auto color,auto damage){
            things_stack.emplace_back(thing_pos_x,thing_pos_y,car,collider,color,damage);

        }
        void new_stack(auto thing_pos_x,auto thing_pos_y,auto car,auto collider,auto color,auto damage,auto health) {
            things_stack.push_back(thing(thing_pos_x,thing_pos_y,car,collider,color,damage,health));
        }
        void new_heap(auto thing_pos_x,auto thing_pos_y,auto car,auto collider,auto color,auto damage) {
            things_heap.push_back(new thing(thing_pos_x,thing_pos_y,car,collider,color,damage));
        }

        void new_player(long long pos_x,long long pos_y,char symbol_,long long health_,long long maxhealth_) {
            player(pos_x,pos_y,symbol_,health_, maxhealth_);
        }
    };

    //

    class colors {
    public:

        string green() { //2
            return "\033[32m";
        }
        string color_reset() {
            return  "\033[0m";
        }
        string yellow() { //3
            return "\033[33m";
        }
        string brown() { //100
            return  "\033[33;1m";
        }
        string red() { //1
            return  "\033[31m";
        }
    };

    //

    class Game_map:public functions_things{
    public:
        colors color;
        void tree(auto x,auto y,char symbol,bool collider,int color,int color1) {
            new_stack(x,y,symbol,collider,color);//2=x,1=y
            new_stack(x+1,y+1,symbol,collider,color);
            new_stack(x,y+1,symbol,collider,color);
            new_stack(x-1,y+1,symbol,collider,color);
            new_stack(x-2,y+2,symbol,collider,color);//
            new_stack(x-1,y+2,symbol,collider,color);
            new_stack(x+2,y+2,symbol,collider,color);
            new_stack(x,y+2,symbol,collider,color);//base
            new_stack(x,y+2,symbol,collider,color);
            new_stack(x+1,y+2,symbol,collider,color);//
            new_stack(x,y+3,symbol,collider,color1);//start
        }

        void house(auto x,auto y,char symbol,char symbol2,bool collider,int color,int color1) {
            //00#00

            //0###0
            new_stack(x+1,y+1,symbol2,collider,color);
            new_stack(x+2,y+1,symbol2,collider,color);
            new_stack(x+3,y+1,symbol2,collider,color);
            //#####
            new_stack(x,y+2,symbol2,collider,color);
            new_stack(x+1,y+2,symbol2,collider,color);
            new_stack(x+2,y+2,symbol2,collider,color);
            new_stack(x+3,y+2,symbol2,collider,color);
            new_stack(x+4,y+2,symbol2,collider,color);

            //0%%%0
            new_stack(x+1,y+3,symbol,collider,color1);
            new_stack(x+2,y+3,symbol,collider,color1);
            new_stack(x+3,y+3,symbol,collider,color1);
            //0%%%0
            new_stack(x+1,y+4,symbol,collider,color1);
            new_stack(x+2,y+4,symbol,collider,color1);
            new_stack(x+3,y+4,symbol,collider,color1);

        }
        void food(auto x,auto y,char symbol,bool collider,int color,long long health) {
            new_stack(x,y,symbol,collider,color,-health);
        }
        void enemy(auto x,auto y,char symbol,bool collider,int color,long long damage,auto health) {
            new_stack(x,y,symbol,collider,color,damage,health);
        }
        void bush(auto x,auto y,char symbol,bool collider,int color,int color1) {
            new_stack(x,y,symbol,collider,color,1);
            new_stack(x+1,y,symbol,collider,color,1);

            new_stack(x,y+1,symbol,collider,color,1);
            new_stack(x+1,y+1,symbol,collider,color,1);
        }
        void car(auto x,auto y,bool collider,int color) {
            new_stack(x+1,y,'|',collider,color);
            new_stack(x+2,y,'#',collider,color);
            new_stack(x+3,y,'|',collider,color);
            new_stack(x,y+1,'[',collider,color);
            new_stack(x+1,y+1,'=',collider,color);
            new_stack(x+2,y+1,'=',collider,color);
            new_stack(x+3,y+1,'=',collider,color);
            new_stack(x+4,y+1,']',collider,color);
            new_stack(x+1,y+2,'@',collider,color);
            new_stack(x+3,y+2,'@',collider,color);
        }
        void map_() {
            tree(2,2,'0',true,2,3);
            house(10,10,'@','O',true,1,3);
            bush(6,7,'&',false,2,3);
            car(20,10,true ,1);
            food(10,10,'0',false,1,3);
            enemy(9 ,10,'&',true,2,3,10);
        }

    };

    //

    class movement_{
    public:
        void movement(bool &changed,auto& cache_x,auto& cache_y,auto& pos_x,auto& pos_y,auto&min_x,auto&max_x,auto&min_y,auto&max_y,auto& game) {
            changed=false;
            cache_x=pos_x;
            cache_y=pos_y;
            int input;
            input=getch();
            if (input=='s') {
                    pos_y++;//they're inverse <- sorry for bad english
                changed=true;
            }
            if (input=='d') {
                    pos_x++;//they're inverse <- sorry for bad english
                changed=true;
            }
            if (input=='w') {
                    pos_y--;
                changed=true;
            }
            if (input=='a') {
                    pos_x--;
                changed=true;
            }
            if (input == 27) {
                game=0;
            }
        }
    };

    //

    class Camera {
        public:
        long long x_1=0;
        long long y_1=0;
        long long x_2=10;
        long long y_2=10;
        long long ofset_x=9;
        long long ofset_y=8;
        colors color;
        player player;
        void update_camera(long long &x,long long &y,long long &full_x,long long &full_y) {
            if (x-ofset_x>=0) x_1=x-ofset_x;
            if (y-ofset_y>=0) y_1=y-ofset_y;
            if (x+ofset_y<=full_x) x_2=x+ofset_x;
            if (y+ofset_x<=full_y) y_2=y+ofset_y;
        }
        void map_camera(auto& color_arr,auto&map_full,auto& mp) {

            for (long long yy=y_1;yy<y_2;yy++) {
                for (long long xx=x_1;xx<x_2;xx++) {
                    if (color_arr[xx][yy]==1)
                    {
                        map_full+=color.red();
                    }
                    if (color_arr[xx][yy]==2)
                    {
                        map_full+=color.green();
                    }
                    if (color_arr[xx][yy]==3)
                    {
                        map_full+=color.yellow();
                    }
                    if (color_arr[xx][yy]==100)
                    {
                        map_full+=color.brown();
                    }

                        map_full+=mp[xx][yy];
                        map_full+=color.color_reset();



                }
                map_full+="\n";
            }
        }
    };

    //

    //

    class render {
        public:
        Camera camera;
        bool game=true;

        colors color;
        player player;

        Game_map map;
        movement_ mover;

        bool collider=false;
        WinApi win_api;

        void render_(auto full_x,auto full_y) {
            Saving::read_player_pos("player_data.txt",player.x,player.y,player.health);
            char basic='_';


            string line="";


            string map_full="";
            vector <vector <char>> mp(full_x,vector<char>(full_y));
            vector <vector <int>> color_arr(full_x,vector<int>(full_y));
            long long cleaner=0;


            long long min_x=0,min_y=0;
            bool changed=true;
            bool once=0;


            long long cache_x=0,cache_y=0;
            bool draw=true;
            map.map_();
            while(game) {

                camera.update_camera(player.x,player.y,full_x,full_y);

                collider=false;
                //creating the map
                while (min_y<full_y) {
                    while (min_x<full_x) {
                        draw=true;
                        if (player.x==min_x && player.y==min_y ) {
                            mp[player.x][player.y]=player.symbol;
                            draw=false;
                        }
                        for (int t=map.things_stack.size()-1;t>=0;t--)
                        {

                            if (map.things_stack[t].x==min_x and map.things_stack[t].y==min_y and map.things_stack[t].collider==false)
                            {
                                if (map.things_stack[t].x==player.x and map.things_stack[t].y==player.y) {
                                    player.health=player.health-map.things_stack[t].damage;
                                    if (map.things_stack[t].damage<0) {
                                        cleaner++;


                                        color_arr[map.things_stack[t].x][map.things_stack[t].y]=0;
                                        map.things_stack.erase(map.things_stack.begin() + t);

                                        continue;
                                    }
                                }
                                color_arr[map.things_stack[t].x][map.things_stack[t].y]=map.things_stack[t].color;
                                mp[map.things_stack[t].x][map.things_stack[t].y]=map.things_stack[t].symbol;
                                draw=false;
                                break;
                            }


                        }

                        if (once!=true) {

                            for (int t=map.things_stack.size()-1;t>=0;t--)
                            {

                            if (map.things_stack[t].x==min_x and map.things_stack[t].y==min_y and map.things_stack[t].collider==true)
                            {
                                if (map.things_stack[t].x==player.x and map.things_stack[t].y==player.y) {
                                    player.health=player.health-map.things_stack[t].damage;
                                    if (map.things_stack[t].damage<0) {
                                        cleaner++;

                                        color_arr.erase(color_arr.begin() + t);
                                        map.things_stack.erase(map.things_stack.begin() + t);

                                        continue;
                                    }
                                }
                                color_arr[map.things_stack[t].x][map.things_stack[t].y]=map.things_stack[t].color;
                                mp[map.things_stack[t].x][map.things_stack[t].y]=map.things_stack[t].symbol;
                                draw=false;
                                break;
                            }


                            }
                                if (draw==true)
                                {
                                    mp[min_x][min_y]=basic;
                                }
                            }



                        if (draw==true)
                        {
                            mp[cache_x][cache_y]=basic;
                        }


                        min_x++;
                    }
                    min_x=0;

                    min_y++;

                }

                map_full="";

                camera.map_camera(color_arr,map_full,mp);

                once=true;
                win_api.clearScreen();
                cout<<""<<"Player health: "<<player.health<<""<<endl;
                cout<<map_full;


                mover.movement(changed,cache_x,cache_y,player.x,player.y,min_x,full_x,min_y,full_y,game);
                Saving::save_player_pos("player_data.txt",player.x,player.y,player.health);


                for (int i=map.things_stack.size()-1;i>=0;i--) {

                    if (map.things_stack[i].collider && map.things_stack[i].x==player.x && map.things_stack[i].y==player.y) {
                        collider=true;
                        if (map.things_stack[i].health>0)
                        {
                            map.things_stack[i].health-=player.damage;
                            player.health-=map.things_stack[i].damage;
                        }
                        if (map.things_stack[i].health==0)
                        {
                            color_arr[map.things_stack[i].x][map.things_stack[i].y]=0;
                            map.things_stack.erase(map.things_stack.begin()+i);

                        }

                        break;
                    }
                }
                if (collider) {
                    player.x=cache_x;
                    player.y=cache_y;
                    changed=false;
                }

                changed=true;
                if (changed) {
                    min_x=0;
                    min_y=0;


                    map_full.clear();
                }
            }
        }
    };

    //

    class gameloop:public render {
        public:
            long long a,b;

            void game_loop() {
                cin>>a>>b;
                render_(a,b);

            }
    };

    //