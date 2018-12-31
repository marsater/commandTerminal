# Arduino terminal
### Easy control of arduino through serial terminal

## Usage
send command in format **command** or **command:data** to trigger callback functions.

#### Example
This snippet from the example code shows how easy it is to define a callback and associate it with a command. ***For more examples, see the examples directory.***
```c++
char *hello = "Hello World!";
static char *command = "hej";
callbacks[2] = Callback(print_string, hello, command); // define a callback

// This callback expects a C string.
void print_string(void *data)
{
    char * parameter = (char *) data;
    Serial.println(parameter);
}
```
Now we can do the following in the serial terminal.
```
hej
>>> Hello World!

hej:Goodbye World!
>>> Goodbye World!
```


## Authors

* **David Mårsäter** - *Initial work*



## License

See the *LICENSE.md* file.
