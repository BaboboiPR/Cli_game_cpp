#define WIN32_LEAN_AND_MEAN

#define NO_STD_BYTE 1
#include  "functionsSave.h"

#include "colors.h"
#include "movement.h"
#include "WIN_API.h"
#include "polluter std.h"
#include "other.h"
    //


          struct player
          {
                    position2D position;
                    int health;
                    int maxhealth;
                    int damage;
                    char symbol;
          };


          class thing
          {
                    public:

                    position2D position;
                    short color;
                    short damage;
                    short health;
                    char symbol;
                    bool collider;
                    thing(long long thing_pos_x = 10, long long thing_pos_y = 10, const char stone = '@', bool collider1 = false, const int color_ = 0,int damage_ = 0, int _health = -1)
                    {
                              position.x = thing_pos_x;
                              position.y = thing_pos_y;
                              symbol = stone;
                              collider = collider1;
                              color = color_;
                              damage = damage_;
                              health = _health;
                    }
                    thing(const position2D position,char stone='@',bool collider1 =false,int color_=0, const int damage_=0,int _health=-1) {
                              this->position = position;
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
              static auto rand_(auto& i,auto max,auto min) {

            i=min+rand()%(max-min+1);
            return i;
        }

        static auto rand_(auto max,auto min) {
                  long long i = min + rand() % (max - min + 1);
            return i;
        }

        vector<thing> things_stack;
        vector<thing*> things_heap;

        void new_stack(position2D position,auto car,auto collider,auto color){
            things_stack.emplace_back(position.x,position.y,car,collider,color);

        }
        void new_stack(position2D position,char character,bool collider,short color,short damage) {
            things_stack.push_back(thing(position,character,collider,color,damage));

        }
        void new_stack(position2D position,char character,bool collider,short color,short damage,short health) {
            things_stack.push_back(thing(position,character,collider,color,damage,health));
        }
        // void new_heap(position2D position,char car,bool collider,short color,short damage) {
        //     things_heap.push_back( new thing(position,car,collider,color,damage));
        // }
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
        void tree(long long x,long long y,char symbol, const bool collider, const short color, const short color1) {
            position2D position{};
            position.x=x;
            position.y=y;
            new_stack({x,y},symbol,collider,color);//2=x,1=y
            new_stack({x,y+1},symbol,collider,color);
            new_stack({x,y+1},symbol,collider,color);
            new_stack({x-1,y+1},symbol,collider,color);
            new_stack({x-2,y+2},symbol,collider,color);//
            new_stack({x-1,y+2},symbol,collider,color);
            new_stack({x+2,y+2},symbol,collider,color);
            new_stack({x,y+2},symbol,collider,color);//base
            new_stack({x,y+2},symbol,collider,color);
            new_stack({x+1,y+2},symbol,collider,color);//
            new_stack({x,y+3},symbol,collider,color1);//start
        }

        void house(long long x,long long y,char symbol,char symbol2,bool collider,short color,short color1) {
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





struct Camera
{
          position2D pos_1 ={0,0};
          position2D pos_2 = {10,10};
          position2D offset= {9,8};

};
    //

          class Rendering{


                    public:
                    Camera cam{0,0,10,10,9,8};





                    void creating_map(position2D full,position2D min,auto& draw,auto& map,auto& color_arr,auto& mp,auto& once,auto& basic,position2D cache,auto& player){
                              while (min.y<full.y) {
                                        while (min.x<full.x) {
                                                  draw=true;
                                                            for (int t=map.things_stack.size()-1;t>=0;t--)
                                                            {

                                                                      if (map.things_stack[t].position.x==min.x and map.things_stack[t].position.y==min.y and map.things_stack[t].collider==false)
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

                            for (int t=map.things_stack.size()-1;t>=0;--t)
                                {

                                if (map.things_stack[t].position.x==min.x and map.things_stack[t].position.y==min.y and map.things_stack[t].collider==true)
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
                                    mp[min.x][min.y]=basic;
                                }
                            }

                        if (player.position.x==min.x && player.position.y==min.y ) {
                            mp[player.position.x][player.position.y]=player.symbol;
                            draw=false;
                        }

                        if (draw==true)
                        {
                            mp[cache.x][cache.y]=basic;
                        }


                        min.x++;
                    }
                    min.x=0;

                    min.y++;

                }
        }
        void map_camera(auto& color_arr,auto&map_full,auto& mp) {

            for (long long yy=cam.pos_1.y;yy<cam.pos_2.y;yy++) {
                for (long long xx=cam.pos_1.x;xx<cam.pos_2.x;xx++) {
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
              static void update_camera(Camera& cam,position2D& pos,position2D full) {
            if (pos.x-cam.offset.x>=0) cam.pos_1.x=pos.x-cam.offset.x;
            if (pos.y-cam.offset.y>=0) cam.pos_1.y=pos.y-cam.offset.y;
            if (pos.x+cam.offset.y<=full.x) cam.pos_2.x=pos.x+cam.offset.x;
            if (pos.y+cam.offset.x<=full.y) cam.pos_2.y=pos.y+cam.offset.y;
        }
    };

    //

    //

    class render {
        public:

        Rendering camera;
        bool game=true;

        Game_map map;
        Movement mover;

        bool collider=false;
        WinApi win_api;

        player player{ {1,1},100,100,3,'#'};

        void render_(position2D full) {

            //Saving::read_player_pos("player_data.txt",player.position,player.health);
            char basic='_';

            string line="";
            View_Camera view_camera;

            string map_full="";
            vector <vector <char>> mp(full.x,vector<char>(full.y));

            vector <vector <short>> color_arr(full.x,vector<short>(full.y));
            long long cleaner=0;

            position2D min = {};
            bool changed=true;

            bool once=0;


            position2D cache = {};
            bool draw=true;

            map.map_();

            while(game) {

                view_camera.update_camera(camera.cam,player.position,full);

                collider=false;

                camera.creating_map(full,min,draw,map,color_arr,mp,once,basic,cache,player);
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


                mover.movement(changed,cache,player.position,game);


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
                    player.position.x=cache.x;
                    player.position.y=cache.y;
                    changed=false;
                }

                changed=true;
                if (changed) {
                    min.x=0;
                    min.y=0;


                    map_full.clear();
                }
            }
        }
    };

    //

class gameloop: public render
          {
                    public:
                    position2D a = {100,100};
                    bool once = true;
                    void game_loop() {

                                        render::render_(a);
                                        //Saving::save_player_pos(player.position,player.health);

                    }
          };

    //