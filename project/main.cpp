#include "mbed.h"
#include <sstream> // used for string conversion to int
#include <string>

DigitalIn keyColumns[3] = {PB_6, PB_7, PD_0}; // cleaner code than mbed DigitalIn example which required three separate lines
DigitalOut myLed(LED1);
DigitalOut keyRows[4] = {PA_5, PA_1, PA_2, PA_3}; // similar to DigitalIn explanation

int col_scan(void);
char keyPad_scan(void);
extern "C" int calc(int first, int second, int selection); // calling the assembly file

int main() {
    int first, second, selection, result;
    string firstNum, secondNum, menu;  
    char input;
    while(1) {
        printf("Enter No. 1 then #: ");
        fflush(stdout);
        while(1) { // continuously loop until user press '#' in which contains the break statement
            input = keyPad_scan();
            wait(0.2);
            if (input != 0xFF && input != '*' && input != '#') {  // if the input doesn't equal 0xFF (which won't happen since it's not on keypad) and as long as it isn't '#' and '*' then it will accept input char from keypad
                firstNum += input; // firstNum += input => firstNum = firstNum + input; meaning that whatever the input from the keypad comes then it will be add onto the firstNum; e.g. '1' then '2' equals '12'
                printf("%c", input);
                fflush(stdout); // will now print everything in the buffer without requiring '\n' in the above printf statement   
            }
            if (input == '#') {
                istringstream val1(firstNum); // store string firstNum 
                val1 >> first; // convert string of above into an integer (first)
                firstNum.clear(); // has to clear the string otherwise the final answer would keep adding onto this
                break; // above prints then clear string and finally break 
            }
        }  // end while for No. 1
        printf("\nEnter No. 2 then #: ");
        fflush(stdout);
        while(1) { 
            input = keyPad_scan();
            wait(0.2);
            if (input != 0xFF && input != '*' && input != '#') { 
                secondNum += input;
                printf("%c", input);
                fflush(stdout);
            }
            if (input == '#') {
                istringstream val2(secondNum); // convert to string
                val2 >> second;
                secondNum.clear(); // clear the string after printing to prevent adding onto the final result
                break;
            }
        }  // end while for No. 2
        printf("\nSelect Operation then # (1 - ADD, 2 - SUBTRACT, 3 - MULTIPLY, 4 - DIVIDE): ");  
        fflush(stdout);
        while(1) { 
            input = keyPad_scan();
            wait(0.25); // longer delay to prevent double press
            if (input != 0xFF && input != '*' && input != '#') {
                menu = input; // doesn't add to string like the others; e.g. += would make it so that '1' and then '2' would be 12, whereas '1' then '1' would just be '1' instead of 11
                printf("%c", input);
                fflush(stdout);
            } 
            if (input == '#') {
                istringstream val3(menu); 
                val3 >> selection;
                switch(selection) { // used to invalidate other keypad options if not 1-4
                    case 1:
                        result = calc(first, second, selection);
                        printf("\nResult = %i\n", result);
                        fflush(stdout);
                        printf("\n");
                        break;
                    case 2:
                        result = calc(first, second, selection);
                        printf("\nResult = %i\n", result);
                        printf("\n");
                        break;
                    case 3:
                        result = calc(first, second, selection);
                        printf("\nResult = %i\n", result);
                        printf("\n");
                        break;
                    case 4: 
                        result = calc(first, second, selection);
                        printf("\nResult = %i\n", result);
                        printf("\n");
                        break;
                    default:
                        printf("\nInvalid option.\n");
                        break;
                }
                break; // to leave the switch statement
            } // end if
        } // end while for selection
    } // end while for the whole keypad loop
}

char keyPad_scan(void){
    char keyPad[4][3] =         //Rows by Col
    {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
    };

    keyColumns[0].mode(PullUp);
    keyColumns[1].mode(PullUp);
    keyColumns[2].mode(PullUp);

    int rows, col;
    char key = 0xFF;    
    
    for (rows = 0; rows < 4; rows++) {
        keyRows[0] = 1;
        keyRows[1] = 1;
        keyRows[2] = 1;
        keyRows[3] = 1;
        if(rows == 0) {
            keyRows[0] = 0;
            wait(0.005);
            col = col_scan();
            wait(0.005);
        }
        else if(rows == 1) {
            keyRows[1] = 0;
            wait(0.005);
            col = col_scan();
            wait(0.005);
        }
        else if(rows == 2) {
            keyRows[2] = 0;
            wait(0.005);
            col = col_scan();
            wait(0.005);
        }
        else if(rows == 3) {
            keyRows[3] = 0;
            wait(0.005);
            col = col_scan();
            wait(0.005);
        } 
        if(col != 50) {
        break;
        }
    }    
        if(col != 50) {
            return key = keyPad[rows][col];
        }
        else {
            return key;
        }
} // end of keyPad_scan

int col_scan(void) {
    if (keyColumns[0] == 0)
        return 0;
    if (keyColumns[1] == 0)
        return 1;
    if (keyColumns[2] == 0)
        return 2;
    else 
        return 50; // no key press value
}