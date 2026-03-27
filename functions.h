    #pragma once


    #include <cmath>
    #include <iostream>
    #include <ctime>
    #include <vector>
    #include <conio.h>


    //why not
    class function {
    public:

        auto abs_(auto n) {
            if (n < 0) {
                return -n;
            }
            else {
                return n;
            }
        }
        //why not
        auto floor(auto n) {
            long long f=n;
            return f;
        }

        //Idk for what is this
        double Pytagora_Theorem(auto cat1,auto cat2) {
            if (perfect_sqrt(cat1*cat1+cat2*cat2)>=0) {
                return perfect_sqrt(cat1*cat1+cat2*cat2);
            }
            else {
                return sqrt(cat1*cat1+cat2*cat2);
            }
        }


    };

    class player {
    public:
        long long x = 5;
        long long y = 5;
        char symbol = '#';
        long long health = 10;
        long long maxhealth = 10;
        player(long long pos_x,long long pos_y,char symbol_,long long health_,long long maxhealth_) {
            x=pos_x;
            y=pos_y;
            symbol=symbol_;
            health=health_;
            maxhealth=maxhealth_;
        }

    };

    class thing {
        public:
        long long x = 0;
        long long y = 0;
        char symbol = ' ';
        bool collider = false;
        int color = 0;
        thing(long long thing_pos_x=10,long long thing_pos_y=10,char stone='@',bool collider1 =false,int color_=0) {
            x=thing_pos_x;
            y=thing_pos_y;
            symbol=stone;
            collider=collider1;
            color =color_;
        }

    };

    class functions_things {
        public:

        vector<thing> things_stack;
        vector<thing*> things_heap;


        void new_stack(auto thing_pos_x,auto thing_pos_y,auto car,auto collider,auto color){
            things_stack.emplace_back(thing_pos_x,thing_pos_y,car,collider,color);

        }
        void new_heap(auto thing_pos_x,auto thing_pos_y,auto car,auto collider) {
            things_heap.push_back(new thing(thing_pos_x,thing_pos_y,car,collider));
        }
        void new_player(long long pos_x,long long pos_y,char symbol_,long long health_,long long maxhealth_) {
            player(pos_x,pos_y,symbol_,health_, maxhealth_);
        }
    };

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

        void bush(auto x,auto y,char symbol,bool collider,int color,int color1) {
            new_stack(x,y,symbol,collider,color);
            new_stack(x+1,y,symbol,collider,color);

            new_stack(x,y+1,symbol,collider,color);
            new_stack(x+1,y+1,symbol,collider,color);
        }
        void map_() {
            tree(2,2,'0',true,2,3);
            house(10,10,'@','O',true,1,3);
            bush(6,7,'&',false,2,3);
        }

    };


    class movement_{
    public:
        void movement(bool &changed,auto& cache_x,auto& cache_y,auto& pos_x,auto& pos_y) {
            changed=false;
            cache_x=pos_x;
            cache_y=pos_y;
            string input;
            input=getch();
            if (input=="s") {
              pos_y++;//they're inverse <- sorry for bad english
               changed=true;


            }
            if (input=="d") {
                pos_x++;//they're inverse <- sorry for bad english
                changed=true;

            }
            if (input=="w") {
                pos_y--;
                changed=true;

            }
            if (input=="a") {
                pos_x--;
                changed=true;

            }
        }
    };

    class render {
        public:

        colors color;
        player player1;

        Game_map map;
        movement_ mover;

        bool collider=false;

        void render_(auto full_x,auto full_y) {
        char basic='_';

        map.map_();
        string line="";


        long long size=0,min_x=0,min_y=0;
        bool changed=true;


        long long cache_x=0,cache_y=0;
        bool draw=true;

        while(1) {
            collider=false;
            while (min_y<full_y) {

                while (min_x<full_x) {

                    draw=true;
                    if (player1.x==min_x && player1.y==min_y ) {
                        line+=player1.symbol;
                        draw=false;
                    }
                    for (auto t:map.things_stack)
                    {
                        if (t.color==1) line+=color.red();
                        if (t.color==100) line+=color.brown();
                        if (t.color==2) line+=color.green();
                        if (t.color==3) line+=color.yellow();

                            if (t.x==min_x && t.y==min_y&& collider==false)
                            {
                                line+=t.symbol;
                                draw=false;
                                break;
                            }
                        line+=color.color_reset();
                    }


                    if (draw==true)
                    {
                        line+=basic;
                    }



                    min_x++;
                }

                min_x=0;//back to zero

                line+="\n";

                min_y++;
            }
            cout<<line<<flush;
            mover.movement(changed,cache_x,cache_y,player1.x,player1.y);




            for (auto object: map.things_stack) {
            if (object.collider && object.x==player1.x && object.y==player1.y) {
                collider=true;
                break;

            }
            }
            if (collider) {
                ;
                player1.x=cache_x;
                player1.y=cache_y;
                changed=false;
            }

            changed=true;
            if (changed) {
                min_x=0;
                min_y=0;
                line.clear();
                cout <<system("CLS");
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