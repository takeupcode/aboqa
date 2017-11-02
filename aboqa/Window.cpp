//
//  Window.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/1/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "Window.h"

#include <stdexcept>
#include <curses.h>

using namespace std;

Window::Window (int y, int x, int height, int width, bool border)
: mY(y), mX(x), mHeight(height), mWidth(width)
{
    setBorder(border);
}

Window::~Window ()
{
    
}

void Window::draw () const
{
    if (mBorder)
    {
        mvaddch(mY, mX, ACS_ULCORNER);
        mvaddch(mY, mX + mWidth - 1, ACS_URCORNER);
        mvaddch(mY + mHeight - 1, mX, ACS_LLCORNER);
        mvaddch(mY + mHeight - 1, mX + mWidth - 1, ACS_LRCORNER);
        mvhline(mY, mX + 1, ACS_HLINE, mWidth - 2);
        mvhline(mY + mHeight - 1, mX + 1, ACS_HLINE, mWidth - 2);
        mvvline(mY + 1, mX, ACS_VLINE, mHeight - 2);
        mvvline(mY + 1, mX + mWidth - 1, ACS_VLINE, mHeight - 2);
    }
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
