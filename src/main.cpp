#include <raylib.h>
#include <iostream>
#include "buttons.hpp"

enum GameState {
    MENU,
    PLAYING
};

enum RoundState {
    WAITING,
    REVEAL,
    RESULT
};

char pcChoice();
char winner(char player, char pc);

int main() 
{

    InitWindow(800, 800, "(Not) Epic game");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    
    Texture2D background = LoadTexture("graphics/menu.png");
    Button startButton{"graphics/play.png", {550, 430}, 0.3};
    Button exitButton{"graphics/exit.png", {550, 550}, 0.3};

    Texture2D nothing = LoadTexture("graphics/ready.png");
    Texture2D perder = LoadTexture("graphics/ganar.png");
    Texture2D ganar = LoadTexture("graphics/perder.png");
    Texture2D rock = LoadTexture("graphics/rock.png");
    Texture2D paper = LoadTexture("graphics/paper.png");
    Texture2D scissors = LoadTexture("graphics/scissors.png");
    Texture2D tutorial = LoadTexture("graphics/tutorial.png");
    Texture2D tie = LoadTexture("graphics/tie.png");
    Texture2D piedra = LoadTexture("graphics/piedra.png");
    Texture2D papel = LoadTexture("graphics/papel.png");
    Texture2D tijera = LoadTexture("graphics/tijera.png");

    double phaseStart = 0.0;          
    const double minPhaseTime = 0.2;  

    GameState currentState = MENU;
    bool exit = false;
    RoundState roundState = WAITING;
    bool firstTime = true;

    char playerChoice = ' ';
    char computerChoice = ' ';
    char result = ' ';

    //Game loop
    while(WindowShouldClose() == false && exit == false){

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        // menu thing
        if(currentState == MENU){
            if(startButton.isTouched(mousePosition, mousePressed)){
                currentState = PLAYING;
                std::cout << "Boton" << std::endl;
            }

            if(exitButton.isTouched(mousePosition, mousePressed)){
            std::cout << "Exit button pressed!" << std::endl;
            exit = true;
            }
        }

        // playing thing
        else if(currentState == PLAYING){

            if (roundState == WAITING){

                if(IsKeyPressed(KEY_Z)){
                    playerChoice = 'r';
                }
                else if(IsKeyPressed(KEY_X)){
                    playerChoice = 'p';
                }
                else if(IsKeyPressed(KEY_C)){
                    playerChoice = 's';
                }

               if (playerChoice != ' '){
                    computerChoice = pcChoice();
                    result = winner(playerChoice, computerChoice);

                    if(result == 'w')      std::cout << "You win!" << std::endl;
                    else if(result == 'l') std::cout << "You lose!" << std::endl;
                    else if(result == 't') std::cout << "It's a tie!" << std::endl;

                    firstTime = false;
                    roundState = REVEAL;
                    phaseStart = GetTime();
               }

            }

            else if (roundState == REVEAL){
                if (IsKeyPressed(KEY_ENTER) && GetTime() - phaseStart > minPhaseTime){
                    roundState = RESULT;
                    phaseStart = GetTime();
                }
            }

            else if (roundState == RESULT){
                if (IsKeyPressed(KEY_ENTER) && GetTime() - phaseStart > minPhaseTime){
                // again
                playerChoice = ' ';
                computerChoice = ' ';
                result = ' ';
                roundState = WAITING;
                }
            }

            // escape to menu
            if (IsKeyPressed(KEY_ESCAPE)){
                currentState = MENU;
                playerChoice = ' ';
                computerChoice = ' ';
                result = ' ';
                roundState = WAITING;
                firstTime = true;
            }


        }

        // 3. Drawin
        BeginDrawing();
        ClearBackground(BLACK);

        if (currentState == MENU){
            DrawTexture(background, 0, 0, WHITE);
            startButton.Draw();
            exitButton.Draw();
        }

        else if(currentState == PLAYING){

            ClearBackground(RAYWHITE);

            if (firstTime == true){
                DrawTexture(tutorial, 0, 0, WHITE);
            }

            else if (roundState == REVEAL){
                if(computerChoice ==  'r'){
                    DrawTexture(rock, 0, 0, WHITE);
                }
                else if(computerChoice == 'p'){
                    DrawTexture(paper, 0, 0, WHITE);
                }
                else if(computerChoice == 's'){
                    DrawTexture(scissors, 0, 0, WHITE);
                }

                if(playerChoice == 'r'){

                    DrawTexture(piedra, 250, 600, WHITE);
                }
                else if(playerChoice == 'p'){

                    DrawTexture(papel, 250, 600, WHITE);
                }
                else if(playerChoice == 's'){
                    DrawTexture(tijera, 250, 600, WHITE);
                }
            }

            else if(roundState == RESULT){
                    if (result == 'w') {
                        DrawTexture(ganar, 0, 0, WHITE);
                    }
                    else if (result == 'l') {
                        DrawTexture(perder, 0, 0, WHITE);
                    }
                    else if (result == 't') {
                        DrawTexture(tie, 0, 0, WHITE);
                    }

            }    

            else{
               DrawTexture(nothing, 0, 0, WHITE);
            }

        }

        EndDrawing();

    }

    UnloadTexture(nothing);
    UnloadTexture(ganar);
    UnloadTexture(perder);
    UnloadTexture(rock);
    UnloadTexture(paper);
    UnloadTexture(scissors);
    UnloadTexture(tie);
    UnloadTexture(background);  
    UnloadTexture(tutorial);  
    UnloadTexture(piedra);
    UnloadTexture(papel);
    UnloadTexture(tijera);

    CloseWindow();

    return 0;
}


char pcChoice(){

    int random = GetRandomValue(1, 3);

    switch(random){
        case 1:
            return 'r';
            break;
        case 2:
            return 'p';
            break;
        
    default: return 's';
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
        break;

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

        break;

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
        break;
    }
}