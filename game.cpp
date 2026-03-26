#define WIN32_LEAN_AND_MEAN

#define NO_STD_BYTE 1
#include  "functionsSave.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include "colors.h"
#include "WIN_API.h"
#include "polluter std.h"
#include "other.h"
    //


    struct player
    {
        position2D position;
        char symbol;
        long long health;
        long long maxhealth;
        long long damage;
    };


    class thing {
        public:

        position2D position;
        char symbol;
        bool collider;
        int color;
        int damage;
        int health;
        thing(long long thing_pos_x = 10, long long thing_pos_y = 10,char stone = '@', bool collider1 = false, int color_ = 0,int damage_ = 0, int _health = -1)
        {
            position.x = thing_pos_x;
            position.y = thing_pos_y;
            symbol = stone;
            collider = collider1;
            color = color_;
            damage = damage_;
            health = _health;
        }
        thing(const position2D position,char stone='@',bool collider1 =false,int color_=0,int damage_=0,int _health=-1) {
            this->position.x=position.x;
            this->position.y=position.y;
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

        auto rand_(auto& i,auto max,auto min) {

            i=min+rand()%(max-min+1);
            return i;
        }

        auto rand_(auto max,auto min) {
            long long i;

            i=min+rand()%(max-min+1);
            return i;
        }

        vector<thing> things_stack;
        vector<thing*> things_heap;

        void new_stack(position2D position,auto car,auto collider,auto color){
            things_stack.emplace_back(position.x,position.y,car,collider,color);

        }
        void new_stack(position2D position,auto car,auto collider,auto color,auto damage) {
            things_stack.push_back(thing(position.x,position.y,car,collider,color,damage));

        }
        void new_stack(position2D position,auto car,auto collider,auto color,auto damage,auto health) {
            things_stack.push_back(thing(position.x,position.y,car,collider,color,damage,health));
        }
        void new_heap(position2D position,auto car,auto collider,auto color,auto damage) {
            things_heap.push_back(new thing(position.x,position.y,car,collider,color,damage));
        }
        void new_stack(long long x, long long y, auto car, auto collider, auto color) {
            position2D pos{ x, y };
            new_stack(pos, car, collider, color);
        }
        void new_stack(long long x, long long y, auto car, auto collider, auto color, auto damage) {
            position2D pos{ x, y };
            new_stack(pos, car, collider, color, damage);
        }

    };

    //



    //

    class Game_map:public functions_things{
    public:
        colors color;
        void tree(auto x,auto y,char symbol,bool collider,int color,int color1) {
            position2D position;
            position.x=x;
            position.y=y;
            new_stack(  position2D{x,y},symbol,collider,color);//2=x,1=y
            new_stack(  position2D{x,y+1},symbol,collider,color);
            new_stack(  position2D{x,y+1},symbol,collider,color);
            new_stack({x-1,y+1},symbol,collider,color);
            new_stack({x-2,y+2},symbol,collider,color);//
            new_stack({x-1,y+2},symbol,collider,color);
            new_stack({x+2,y+2},symbol,collider,color);
            new_stack(  position2D{x,y+2},symbol,collider,color);//base
            new_stack(  position2D{x,y+2},symbol,collider,color);
            new_stack({x+1,y+2},symbol,collider,color);//
            new_stack(  position2D{x,y+3},symbol,collider,color1);//start
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
        void food(auto x,auto y,char symbol,bool collider, const int color,long long health) {
            //rand()%100;

            int random = rand_(random,100,30);
            for (long long i = 0;i<random;i++) {
                new_stack(rand_(20,10),rand_(20,10),symbol,collider,color,-rand_(10,1));
            }


        }
        void enemy(const position2D position,char symbol,bool collider,int color,long long damage,auto health) {
            new_stack(position,symbol,collider,color,damage,health);
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
            enemy({9 ,10},'&',true,2,3,10);
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
            #ifdef _WIN32
            input=getch();
            #endif
            #ifdef __linux__
            cin>>input;
            #endif

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
            changed=true;
        }
    };



    struct Camera {
        long long x_1=0;
        long long y_1=0;
        long long x_2=10;
        long long y_2=10;
        long long ofset_x=9;
        long long ofset_y=8;
    };
    //

    class Rendering{


        public:
        Camera cam{0,0,10,10,9,8};





        void creating_map(auto& min_y,auto& full_y,auto& min_x,auto& full_x,auto& draw,auto& map,auto& color_arr,auto& mp,auto& once,auto& basic,auto&cache_x,auto&cache_y,auto& player){
            while (min_y<full_y) {
                    while (min_x<full_x) {
                        draw=true;
                        for (int t=map.things_stack.size()-1;t>=0;t--)
                        {

                            if (map.things_stack[t].position.x==min_x and map.things_stack[t].position.y==min_y and map.things_stack[t].collider==false)
                            {
                                if (map.things_stack[t].position.x==player.position.x and map.things_stack[t].position.y==player.position.y) {
                                    player.health=player.health-map.things_stack[t].damage;
                                    if (map.things_stack[t].damage<0){
                                        color_arr[map.things_stack[t].position.x][map.things_stack[t].position.y]=0;
                                        map.things_stack.erase(map.things_stack.begin() + t);

                                    }
                                    continue;
                                }
                                color_arr[map.things_stack[t].position.x][map.things_stack[t].position.y]=map.things_stack[t].color;
                                mp[map.things_stack[t].position.x][map.things_stack[t].position.y]=map.things_stack[t].symbol;
                                draw=false;
                                break;
                            }


                        }

                        if (once!=true)
                            {

                            for (int t=map.things_stack.size()-1;t>=0;t--)
                                {

                                if (map.things_stack[t].position.x==min_x and map.things_stack[t].position.y==min_y and map.things_stack[t].collider==true)
                                    {
                                    if (map.things_stack[t].position.x==player.position.x and map.things_stack[t].position.y==player.position.y)
                                        {
                                        player.health=player.health-map.things_stack[t].damage;
                                        if (map.things_stack[t].damage<0)
                                            {


                                            color_arr.erase(color_arr.begin() + t);
                                            map.things_stack.erase(map.things_stack.begin() + t);

                                            continue;
                                            }
                                        }
                                color_arr[map.things_stack[t].position.x][map.things_stack[t].position.y]=map.things_stack[t].color;
                                mp[map.things_stack[t].position.x][map.things_stack[t].position.y]=map.things_stack[t].symbol;
                                draw=false;
                                break;
                                    }
                                }
                                if (draw==true)
                                {
                                    mp[min_x][min_y]=basic;
                                }
                            }

                        if (player.position.x==min_x && player.position.y==min_y ) {
                            mp[player.position.x][player.position.y]=player.symbol;
                            draw=false;
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
        }
        void map_camera(auto& color_arr,auto&map_full,auto& mp) {

            for (long long yy=cam.y_1;yy<cam.y_2;yy++) {
                for (long long xx=cam.x_1;xx<cam.x_2;xx++) {
                    if (color_arr[xx][yy]==1)
                    {
                        map_full+=colors::red();
                    }
                    if (color_arr[xx][yy]==2)
                    {
                        map_full+=colors::green();
                    }
                    if (color_arr[xx][yy]==3)
                    {
                        map_full+=colors::yellow();
                    }
                    if (color_arr[xx][yy]==100)
                    {
                        map_full+=colors::brown();
                    }
                        map_full+=mp[xx][yy];
                        map_full+=colors::color_reset();

                }
                map_full+="\n";
            }
        }

    };

    class View_Camera : public Rendering{
    public:
        void update_camera(Camera& cam,long long &x,long long &y,long long &full_x,long long &full_y) {
            if (x-cam.ofset_x>=0) cam.x_1=x-cam.ofset_x;
            if (y-cam.ofset_y>=0) cam.y_1=y-cam.ofset_y;
            if (x+cam.ofset_y<=full_x) cam.x_2=x+cam.ofset_x;
            if (y+cam.ofset_x<=full_y) cam.y_2=y+cam.ofset_y;
        }
    };

    //

    //

    class render {
        public:

        Rendering camera;
        bool game=true;

        Game_map map;
        movement_ mover;

        bool collider=false;
        WinApi win_api;

        player player{1,1,'#',100,100,3};

        void render_(auto full_x,auto full_y) {

            Saving::read_player_pos("player_data.txt",player.position,player.health);
            char basic='_';

            string line="";
            View_Camera view_camera;

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

                view_camera.update_camera(camera.cam,player.position.x,player.position.y,full_x,full_y);

                collider=false;

                camera.creating_map(min_y,full_y,min_x,full_x,draw,map,color_arr,mp,once,basic,cache_x,cache_y,player);
                map_full="";

                camera.map_camera(color_arr,map_full,mp);

                once=true;

                #ifdef _WIN32
                    WinApi::clearScreen();
                #else
                    System("CLS");
                #endif
                cout<<""<<"Player health: "<<player.health<<""<<endl;
                cout<<map_full;


                mover.movement(changed,cache_x,cache_y,player.position.x,player.position.y,min_x,full_x,min_y,full_y,game);
                Saving::save_player_pos("player_data.txt",player.position,player.health);


                for (int i=map.things_stack.size()-1;i>=0;i--) {

                    if (map.things_stack[i].collider && map.things_stack[i].position.x==player.position.x && map.things_stack[i].position.y==player.position.y) {
                        collider=true;
                        if (map.things_stack[i].health>0)
                        {
                            map.things_stack[i].health-=player.damage;
                            player.health-=map.things_stack[i].damage;
                        }
                        if (map.things_stack[i].health==0)
                        {
                            color_arr[map.things_stack[i].position.x][map.things_stack[i].position.y]=0;
                            map.things_stack.erase(map.things_stack.begin()+i);

                        }

                        break;
                    }
                }
                if (collider) {
                    player.position.x=cache_x;
                    player.position.y=cache_y;
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