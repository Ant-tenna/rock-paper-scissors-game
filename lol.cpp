#include <iostream>
#include <ctime>

char winner(char player, char pc);
char pcChoice();

int main(){

    std::cout << "rock pape siso \n";

    char player;
    std::cin >> player;

    std::cout << "the winner is: " << winner(player, pcChoice()) << std::endl;

    return 0;
}

char pcChoice(){

    srand(time(0));
	int num = rand() % 3 + 1;

    switch(num){
        case 1:
            return 'r';
            break;
        case 2:
            return 'p';
            break;
        case 3:
            return 's';
            break;    
        default:
            return '\0';
            break;
    }

}

char winner(char player, char pc){

    switch(player){
        case 'r':
            if(pc == 'r'){
                return 't';
            }
            else if(pc == 'p'){
                return 'l';
            }
            else if(pc == 's'){
                return 'w';
            }

        case 'p':
            if(pc == 'r'){
                return 'w';
            }
            else if(pc == 'p'){
                return 't';
            }
            else if (pc == 's'){
                return 'l';
            }

        case 's':
            if(pc == 'r'){
                return 'l';
            }
            else if(pc == 'p'){
                return 'w';
            }
            else if(pc == 's'){
                return 't';
            }
        
        default:
        return '\0';
    }
    return '\0';
}