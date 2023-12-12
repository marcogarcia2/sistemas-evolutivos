#include "functions.h"


int main(int argc, char *argv[]) {

    int f;

    scanf("%d", &f);

    switch(f){
        
        case 1:
            func1();

        case 2: 
            //func2();
        
        default:
            break;

    }

    return 0;
}
