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
  mY(y), mX(x), mHeight(height), mWidth(width), mAnchorTop(-1), mAnchorBottom(-1), mAnchorLeft(-1), mAnchorRight(-1),
  mClientForeColor(clientForeColor), mClientBackColor(clientBackColor),
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
    
    for (auto & control: mControls)
    {
        control->processInput(gm);
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
    
    for (const auto & control: mControls)
    {
        control->draw();
    }
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

int Window::anchorTop () const
{
    return mAnchorTop;
}

void Window::setAnchorTop (int anchor)
{
    mAnchorTop = anchor;
}

int Window::anchorBottom () const
{
    return mAnchorBottom;
}

void Window::setAnchorBottom (int anchor)
{
    mAnchorBottom = anchor;
}

int Window::anchorLeft () const
{
    return mAnchorLeft;
}

void Window::setAnchorLeft (int anchor)
{
    mAnchorLeft = anchor;
}

int Window::anchorRight () const
{
    return mAnchorRight;
}

void Window::setAnchorRight (int anchor)
{
    mAnchorRight = anchor;
}

void Window::setAnchorsAll (int anchor)
{
    mAnchorTop = anchor;
    mAnchorBottom = anchor;
    mAnchorLeft = anchor;
    mAnchorRight = anchor;
}

void Window::setAnchorsAll (int top, int bottom, int left, int right)
{
    mAnchorTop = top;
    mAnchorBottom = bottom;
    mAnchorLeft = left;
    mAnchorRight = right;
}

void Window::setAnchorsTopBottom (int top, int bottom)
{
    mAnchorTop = top;
    mAnchorBottom = bottom;
}

void Window::setAnchorsLeftRight (int left, int right)
{
    mAnchorLeft = left;
    mAnchorRight = right;
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

int Window::clientForeColor () const
{
    return mClientForeColor;
}

void Window::setClientForeColor (int color)
{
    mClientForeColor = color;
}

int Window::clientBackColor () const
{
    return mClientBackColor;
}

void Window::setClientBackColor (int color)
{
    mClientBackColor = color;
}

int Window::borderForeColor () const
{
    return mBorderForeColor;
}

void Window::setBorderForeColor (int color)
{
    mBorderForeColor = color;
}

int Window::borderBackColor () const
{
    return mBorderBackColor;
}

void Window::setBorderBackColor (int color)
{
    mBorderBackColor = color;
}

void Window::addControl(std::unique_ptr<Window> && control)
{
    mControls.push_back(std::move(control));
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
    
    for (const auto & control: mControls)
    {
        if (control->anchorTop() != -1 && control->anchorBottom() != -1)
        {
            int newTop = control->anchorTop();
            int newBottom = mHeight - control->anchorBottom(); // This is one past the bottom row.
            if (newBottom <= newTop)
            {
                newBottom = newTop + 1;
            }
            control->moveAndResize(newTop, control->x(), newBottom - newTop, control->width());
        }
        else if (control->anchorTop() != -1)
        {
            int newTop = control->anchorTop();
            control->setY(newTop);
        }
        else if (control->anchorBottom() != -1)
        {
            int newBottom = mHeight - control->anchorBottom(); // This is one past the bottom row.
            int newTop = newBottom - control->height();
            if (newTop < 0)
            {
                newTop = 0;
            }
            control->setY(newTop);
        }
        
        if (control->anchorLeft() != -1 && control->anchorRight() != -1)
        {
            int newLeft = control->anchorLeft();
            int newRight = mWidth - control->anchorRight(); // This is one past the right column.
            if (newRight <= newLeft)
            {
                newRight = newLeft + 1;
            }
            control->moveAndResize(control->y(), newLeft, control->height(), newRight - newLeft);
        }
        else if (control->anchorLeft() != -1)
        {
            int newLeft = control->anchorLeft();
            control->setX(newLeft);
        }
        else if (control->anchorRight() != -1)
        {
            int newRight = mWidth - control->anchorRight(); // This is one past the right column.
            int newLeft = newRight - control->width();
            if (newLeft < 0)
            {
                newLeft = 0;
            }
            control->setX(newLeft);
        }
        
        control->createWindows();
    }
}

void Window::destroyWindows ()
{
    for (const auto & control: mControls)
    {
        control->destroyWindows();
    }

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
