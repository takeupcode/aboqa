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

Window::Window (int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: mY(y), mX(x), mHeight(height), mWidth(width), mClientForeColor(clientForeColor), mClientBackColor(clientBackColor),
  mBorderForeColor(borderForeColor), mBorderBackColor(borderBackColor), mBorder(border)
{
    mWindowPtr = newwin(mHeight, mWidth, mY, mX);
    if (!mWindowPtr)
    {
        string message = "Could not create window.";
        throw runtime_error(message);
    }
}

Window::~Window ()
{
    delwin(mWindowPtr);
}

void Window::draw () const
{
    if (mBorder)
    {
        ConsoleManager::drawBox(nullptr, mY, mX, mWidth, mHeight, mBorderForeColor, mBorderBackColor);
    }
    ConsoleManager::fillRect(nullptr, mY + 1, mX + 1, mWidth - 1, mHeight - 1, mClientForeColor, mClientBackColor);
}

int Window::y () const
{
    return mY;
}

void Window::setY (int y)
{
    mY = y;
}

int Window::x () const
{
    return mX;
}

void Window::setX (int x)
{
    mX = x;
}

void Window::move (int y, int x)
{
    mY = y;
    mX = x;
}

int Window::height () const
{
    return mHeight;
}

void Window::setHeight (int height)
{
    mHeight = height;
}

int Window::width () const
{
    return mWidth;
}

void Window::setWidth (int width)
{
    mWidth = width;
}

void Window::resize (int height, int width)
{
    mHeight = height;
    mWidth = width;
}

bool Window::hasBorder () const
{
    return mBorder;
}

void Window::setBorder (bool border)
{
    mBorder = border;
}
