//'The Gambling Snake'
//CPSC 254
//Da Hang        dhang0129@gmail.com
//Xinxue Wang    xinxue0209@csu.fullerton.edu
//Juheng Mo      henrymo@csu.fullerton.edu


#include "input.h"
#include <termios.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <string>
#include <stdio.h>

using namespace std;

struct termios t;

//turn off input
void input_enter_off()
{
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
//turn on input
void input_enter_on()
{
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

/*program will read input from the user to determine which 
direction to go. If the input is not listed, the screen will
appear 'incorrect buttom clicked' to warn*/

enum Direction get_input()
{
    enum Direction result = East;
    char user_input = getchar();//reading input from user
    
    //keyboard assigned for direction control
    switch (user_input)
    {
    case 'a':
        result = West;
        break;
    case 'w':
        result = North;
        break;
    case 'd':
        result = East;
        break;
    case 's':
        result = South;
        break;
    default:
        result = Error;
        cout << "Incorrect button clicked(" << user_input << ")" << endl;
        break;
    }
    return result;
}

void input_init()
{
    
}
