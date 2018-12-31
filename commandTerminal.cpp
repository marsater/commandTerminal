/*
 *Library for sending commands wich triggers callback functions.
 *
 * Created 31 Dec 2018
 * by David Mårsäter
 *
 * https://github.com/marsater
 */

#include "Arduino.h"
#include "CommandTerminal.h"

CommandTerminal::CommandTerminal(HardwareSerial * serial, int inputSize, char input[])
{
    _serial = serial;
    _inputSize = inputSize;
    _input = input;
}

void CommandTerminal::main()
{


    if(_serial->available() > 0){
        // Get next command from Serial (add 1 for final 0)
        _size = _serial->readBytes(_input, _inputSize+1);
        _input[_size] = 0; // Add the final 0 to end the C string

        // read command && split on ":" into two values
        _msg = _input;
        _seperator = strchr(_msg, ':');

        if(_seperator != 0){ // if there is two parts of the command
            *_seperator = 0;
            //_serial->println(_msg);
            ++_seperator; // holds second value
            //_serial->println(_seperator);
        } else { // just one value
            //_serial->println(_msg);
        }

        // interperate the command
        if(CommandTerminal::interperateCommand(_msg) == false){
            _serial->print("Error: "); _serial->print(_msg); _serial->println(" is not recognized as a command.");
        }

    }

}

boolean CommandTerminal::interperateCommand(char * _message){
    // loop through list of callbacks
    for(_i=0; _i < _callbackNum; _i++){
        if(strcmp(_msg, _callbacks[_i].command) == 0){ // if a match, then run the callback
            _serial->println("match");
            if(_seperator != 0){ // if then there is two parts of the command
                _callbacks[_i].data = _seperator; // set data to 2nd part of command
            }
            _callbacks[_i].function(_callbacks[_i].data); // call the callback function
            return true;
        }
    }
    return false;
}

void CommandTerminal::setCallbacks(Callback cb[], int num){
    _callbacks = cb; // list of callbacks
    _callbackNum = num; // How many callbacks
}
