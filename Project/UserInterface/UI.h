#ifndef UI_H
#define UI_H

#include <vector>
#include <string>

#include "../Console/Console.h"
#include "../Console/InputHandler.h"

class UI : public InputHandler
{
protected:
    int _x = 0;
    int _y = 0;
    int _width = 120;
    int _height = 41;
    bool _show = false;
    bool _hover = false;

public:
    virtual int width() const;
    virtual int height() const;

    virtual bool isShowing() const;
    virtual bool isHovered() const;

    virtual void draw() = 0;
    virtual void cls();
    virtual void show();
    virtual void hide();
    virtual void highlight();
    virtual void unHighlight();
};

#endif // !UI_H