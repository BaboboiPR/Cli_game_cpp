#pragma once
#include <cmath>
#include <iostream>
class function {
    public:
        long long factorial(long long n) {
            long long sum=1;
            for (auto i = 1; i <= n; i++) {
                sum *= i;
            }
            return sum;
        }
        //why not
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
        //why not
        auto perfect_sqrt(auto n) {
            for (auto i = 1; i <= n; i++) {
                if (i*i == n) {
                    return i;
                }
            }
            return -n;
        }
        //IDK for what is this
        double Pytagora_Theorem(auto cat1,auto cat2) {
            if (perfect_sqrt(cat1*cat1+cat2*cat2)>=0) {
                return perfect_sqrt(cat1*cat1+cat2*cat2);
            }
            else {
                return sqrt(cat1*cat1+cat2*cat2);
            }
        }

    };
