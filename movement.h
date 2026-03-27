#pragma once
#include "polluter std.h"
class Movement{
public:
          static void movement(bool &changed,position2D& cache,position2D& pos,auto& game) {
                    changed=false;
                    cache.x=pos.x;
                    cache.y=pos.y;
                    int input;
                    #ifdef _WIN32
                              input=getch();
                    #endif
                    #ifdef __linux__
                              cin>>input;
                    #endif

                    if (input=='s') {
                              pos.y++;//they're inverse <- sorry for bad english
                              changed=true;
                    }
                    if (input=='d') {
                              pos.x++;//they're inverse <- sorry for bad english
                              changed=true;
                    }
                    if (input=='w') {
                              pos.y--;
                              changed=true;
                    }
                    if (input=='a') {
                              pos.x--;
                              changed=true;
                    }
                    if (input == 27) {
                              game=0;
                    }
                    changed=true;
          }
};