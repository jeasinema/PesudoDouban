/*-----------------------------------------------------
 File Name : main.cpp
 Purpose :
 Creation Date : 28-05-2017
 Last Modified : Sun May 28 19:51:51 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "back_end/backend.h"

int main(int argc, char **argv) {
    std::cout << "starting backend!" << std::endl;
    auto backend = std::make_shared<persudo::backend::PersudoBackend>("http://127.0.0.1:3000");

    if (backend->start()) {
        std::cerr << "backend start failed!" << std::endl;
    } else {
        std::cout << "backedn start successfully!" << std::endl;
    }
}
