/*
 *Library for sending commands wich triggers callback functions.
 *
 * Created 31 Dec 2018
 * by David Mårsäter
 *
 * https://github.com/marsater
 */

#ifndef CommandTerminal_h
#define CommandTerminal_h

#include "Arduino.h"


/*
 * A callback contains both a function and a pointer to arbitrary data
 * that will be passed as argument to the function.
 * And a command
 */
struct Callback {
    Callback(void (*f)(void *) = 0, void *d = 0, char *c = 0)
        : function(f), data(d), command(c){}
    void (*function)(void *);
    void *data;
    char *command;
};


class CommandTerminal
{
public:
    CommandTerminal(HardwareSerial * serial, int inputSize, char input[]);
    void main();
    void setCallbacks(Callback cb[], int num);
private:
    boolean interperateCommand(char* _message);

    HardwareSerial * _serial;

    Callback* _callbacks;
    int _callbackNum;

    // terminal
    //#define _INPUT_SIZE 10 // max input size expected from one command
    int _inputSize = 10;
    // Get next command from Serial (add 1 for final 0)
    //char _input[_INPUT_SIZE+1];
    char* _input;
    byte _size;
    // Read command && split on :
    char* _msg; // store incomming command for terminal (first value of command)
    char* _seperator; // holds the second value of command

    int _i;

};


#endif
