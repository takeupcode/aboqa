//
//  Window.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/1/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "Window.h"

#include <stdexcept>

#include "ConsoleManager.h"

using namespace std;

Window::Window (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: mBorderWindowPtr(nullptr), mClientWindowPtr(nullptr), mName(name),
  mY(y), mX(x), mHeight(height), mWidth(width), mClientForeColor(clientForeColor), mClientBackColor(clientBackColor),
  mBorderForeColor(borderForeColor), mBorderBackColor(borderBackColor), mBorder(border)
{
    createWindows();
}

Window::~Window ()
{
    destroyWindows();
}

WINDOW * Window::cursesWindow () const
{
    return mClientWindowPtr;
}

void Window::processInput (GameManager * gm)
{
    MEVENT mouseEvent;
    int c = wgetch(cursesWindow());
    switch(c)
    {
    case ERR:
        break;
    case KEY_MOUSE:
        if (getmouse(&mouseEvent) == OK)
        {
            onMouseEvent(gm, mouseEvent.id, mouseEvent.y, mouseEvent.x, mouseEvent.bstate);
        }
        break;
    default:
        onKeyPress(gm, c);
    }
}

void Window::draw () const
{
    if (mBorder)
    {
        ConsoleManager::drawBox(mBorderWindowPtr, 0, 0, mHeight, mWidth, mBorderForeColor, mBorderBackColor);
        touchwin(mBorderWindowPtr);
        wnoutrefresh(mBorderWindowPtr);
        
        ConsoleManager::fillRect(mClientWindowPtr, 0, 0, mHeight - 2, mWidth - 2, mClientForeColor, mClientBackColor);
    }
    else
    {
        ConsoleManager::fillRect(mClientWindowPtr, 0, 0, mHeight, mWidth, mClientForeColor, mClientBackColor);
    }
    onDrawClient();
    touchwin(mClientWindowPtr);
    wnoutrefresh(mClientWindowPtr);
}

void Window::onKeyPress (GameManager * gm, int key) const
{ }

void Window::onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const
{ }

void Window::onDrawClient () const
{ }

const std::string & Window::name () const
{
    return mName;
}

int Window::y () const
{
    return mY;
}

void Window::setY (int y)
{
    if (mY != y)
    {
        destroyWindows();
        mY = y;
        createWindows();
    }
}

int Window::x () const
{
    return mX;
}

void Window::setX (int x)
{
    if (mX != x)
    {
        destroyWindows();
        mX = x;
        createWindows();
    }
}

void Window::move (int y, int x)
{
    if (mY != y || mX != x)
    {
        destroyWindows();
        mY = y;
        mX = x;
        createWindows();
    }
}

int Window::height () const
{
    return mHeight;
}

void Window::setHeight (int height)
{
    if (mHeight != height)
    {
        destroyWindows();
        mHeight = height;
        createWindows();
    }
}

int Window::width () const
{
    return mWidth;
}

void Window::setWidth (int width)
{
    if (mWidth != width)
    {
        destroyWindows();
        mWidth = width;
        createWindows();
    }
}

void Window::resize (int height, int width)
{
    if (mHeight != height || mWidth != width)
    {
        destroyWindows();
        mHeight = height;
        mWidth = width;
        createWindows();
    }
}

void Window::moveAndResize (int y, int x, int height, int width)
{
    if (mY != y || mX != x || mHeight != height || mWidth != width)
    {
        destroyWindows();
        mY = y;
        mX = x;
        mHeight = height;
        mWidth = width;
        createWindows();
    }
}

bool Window::hasBorder () const
{
    return mBorder;
}

void Window::setBorder (bool border)
{
    if (mBorder != border)
    {
        destroyWindows();
        mBorder = border;
        createWindows();
    }
}

void Window::createWindows ()
{
    if (mY < 0 || mX < 0)
    {
        throw std::out_of_range("y or x cannot be less than 0.");
    }

    if (mBorder)
    {
        if (mHeight < 3 || mWidth < 3)
        {
            throw std::out_of_range("height or width cannot be less than 3 when using a border.");
        }
        mBorderWindowPtr = newwin(mHeight, mWidth, mY, mX);
        mClientWindowPtr = newwin(mHeight - 2, mWidth - 2, mY + 1, mX + 1);
        if (!mBorderWindowPtr || !mClientWindowPtr)
        {
            string message = "Could not create window.";
            throw runtime_error(message);
        }

        nodelay(mBorderWindowPtr, true);
        keypad(mBorderWindowPtr, true);
    }
    else
    {
        if (mHeight < 1 || mWidth < 1)
        {
            throw std::out_of_range("height or width cannot be less than 1.");
        }
        
        mClientWindowPtr = newwin(mHeight, mWidth, mY, mX);
        if (!mClientWindowPtr)
        {
            string message = "Could not create window.";
            throw runtime_error(message);
        }
    }
    
    nodelay(mClientWindowPtr, true);
    keypad(mClientWindowPtr, true);
}

void Window::destroyWindows ()
{
    if (mClientWindowPtr)
    {
        delwin(mClientWindowPtr);
        mClientWindowPtr = nullptr;
    }

    if (mBorderWindowPtr)
    {
        delwin(mBorderWindowPtr);
        mBorderWindowPtr = nullptr;
    }
}
