


#ifndef MAIN_DRAFT_CPP_

#define MAIN_DRAFT_CPP_


#include <string.h>
#include "./core/SN.hpp"



/*
 * Main SDL
 */
int main(int argc, char* argv[]){
	SN<float, char> nb;
	SN<int, char> nb2;
	
    printf("Hello %s\n", typeid(nb).name());
    printf("Hello %s\n", typeid(nb2).name());
    
    std::string mes;
    std::stringstream ss;
	ss << (typeid(nb).name());
	mes+=ss.str();
	
	std::cout << mes.substr(0, 3) << "\n";
    //printf("Hello %s\n", str.substr(0, 3));
    return 0;
}


#endif /* MAIN_DRAFT_CPP_ */
