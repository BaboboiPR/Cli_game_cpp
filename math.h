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
        //Idk for what is this
        double Pytagora_Theorem(auto cat1,auto cat2) {
            if (perfect_sqrt(cat1*cat1+cat2*cat2)>=0) {
                return perfect_sqrt(cat1*cat1+cat2*cat2);
            }
            else {
                return sqrt(cat1*cat1+cat2*cat2);
            }
        }
        //ragebait something if the numbers have 2 numbers you choose one after another something pbinfo type shit
        void nice_numbers(auto n,auto cif_1,auto cif_2) {
            using namespace std;
            long long x,cif,cif2,cnt=0;
            cif=0;
            cif2=0;
            for(long long i=1;i<=n;i++){
                cin>>x;
                while(x){
                    cif=x%10;
                    cif2=(x/10)%10;
                    if(cif2==cif_1 && cif_2==9){
                        cnt++;
                        break;
                    }
                    x=x/10;
                }

            }
            cout<<cnt;
        }
        //divisors
        void find_divisors(long long n) {
            using namespace std;
            long long i1;
            double start=clock();
            for (long i = 1; i <=sqrt(n); i++) {
                if (n%i==0) {
                    i1=n/i;
                    cout<<i<<" "<<i1<<"\n";
                }

            }
            clock_t end = clock();
            cout<<(end-start)/CLOCKS_PER_SEC;
        }


    };
