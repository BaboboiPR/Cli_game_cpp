#pragma once

class colors {
public:
    static string green() { //2
        return "\033[32m";
    }

    static string color_reset() {
        return  "\033[0m";
    }

    static string yellow() { //3
        return "\033[33m";
    }

    static string brown() { //100
        return  "\033[33;1m";
    }

    static string red() { //1
        return  "\033[31m";
    }
};