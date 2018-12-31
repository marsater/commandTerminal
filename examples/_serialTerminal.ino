/*
 * Example sketch for the CommandTerminal libary.
 * After uploading send 'hoj' in the serial terminal to trigger  the 1st callback,
 * 'noj' or 'noj:Goodbye world!' to trigger the second callback.
 *
 * Created 31 Dec 2018
 * by David Mårsäter
 *
 * https://github.com/marsater
 */

#include <commandTerminal.h>

#define _INPUT_SIZE 20 // Max expected command length
char input[_INPUT_SIZE+1];
CommandTerminal terminal(&Serial, _INPUT_SIZE, input);

Callback callbacks[2];
#define numberOfCallbacks 2 // we have to know how many we have

void setup() {
    Serial.begin(9600);

    static int forty_two = 42;
    char *hello = "Hello, World!";

    static char *command = "hoj";
    static char *commandOne = "noj";

    callbacks[0] = Callback(print_int, &forty_two, command);
    callbacks[1] = Callback(print_string, hello, commandOne);

    terminal.setCallbacks(callbacks, numberOfCallbacks); //pass the callbacks and the lenght of the array

}

void loop() {
    terminal.main();
}


// This callback expects an int.
void print_int(void *data)
{
    int parameter = * (int *) data;
    Serial.println(parameter);
}

// This one expects a C string.
void print_string(void *data)
{
    char * parameter = (char *) data;
    Serial.println(parameter);
}
