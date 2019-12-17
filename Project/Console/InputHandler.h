#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

class InputHandler
{
public:
    // If the result of the function is true then the input is consumed
    virtual bool onKeyPressed(unsigned short key) = 0;
    // Run through Config::Parse to get intented behavior
};

#endif // !INPUTHANDLER_H