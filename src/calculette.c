
#include "../headers/analyse_syntaxique.h"




int main (int argc,char**argv) {

    // int res = -1;

    if (argc!=2)
        return -1;
    
    else{
        analyser(argv[1]);
        
    }
    return 0;
}




