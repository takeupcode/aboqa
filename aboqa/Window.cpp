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

Window::Window (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border, int focusForeColor, int focusBackColor)
: mClientCursesWindow(nullptr), mBorderWindow(nullptr), mName(name),
  mY(y), mX(x), mHeight(height), mWidth(width),
  mAnchorTop(-1), mAnchorBottom(-1), mAnchorLeft(-1), mAnchorRight(-1),
  mClientForeColor(clientForeColor), mClientBackColor(clientBackColor),
  mBorderForeColor(borderForeColor), mBorderBackColor(borderBackColor),
  mFocusForeColor(focusForeColor), mFocusBackColor(focusBackColor),
  mParent(nullptr), mBorder(border), mHasFocus(false), mHasDirectFocus(false),
  mFillClientArea(true)
{
    createWindows();
    
    setFocus(true);
}

Window::~Window ()
{
    destroyWindows();
}

WINDOW * Window::cursesWindow () const
{
    return mClientCursesWindow;
}

void Window::processInput (GameManager * gm)
{
    MEVENT mouseEvent;
    int c = wgetch(cursesWindow());
    switch(c)
    {
    case ERR:
        break;
            
    case 9: // Tab
        if (!advanceFocus())
        {
            // If we couldn't advance the focus, start the cycle over again.
            setFocus(true);
        }
        break;
            
    case KEY_MOUSE:
        if (getmouse(&mouseEvent) == OK)
        {
            setFocus(mouseEvent.y, mouseEvent.x);
            const Window * control = findWindow(mouseEvent.y, mouseEvent.x);
            if (control)
            {
                control->onMouseEvent(gm, mouseEvent.id, mouseEvent.y, mouseEvent.x, mouseEvent.bstate);
            }
        }
        break;
    default:
        {
            const Window * control = findFocus();
            if (control)
            {
                control->onKeyPress(gm, c);
            }
        }
    }
}

void Window::draw () const
{
    if (mBorder)
    {
        mBorderWindow->drawBorder();
        touchwin(mBorderWindow->cursesWindow());
        wnoutrefresh(mBorderWindow->cursesWindow());
    }
    
    if (mFillClientArea)
    {
        ConsoleManager::fillRect(*this, 0, 0, clientHeight(), clientWidth(), mClientForeColor, mClientBackColor);
    }

    onDrawClient();
    touchwin(mClientCursesWindow);
    wnoutrefresh(mClientCursesWindow);
    
    for (const auto & control: mControls)
    {
        control->draw();
    }
}

bool Window::onKeyPress (GameManager * gm, int key) const
{
    return false;
}

void Window::onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const
{
}

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

int Window::clientY () const
{
    return mBorder ? mY + 1 : mY;
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

int Window::clientX () const
{
    return mBorder ? mX + 1 : mX;
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

int Window::clientHeight () const
{
    return mBorder ? mHeight - 2 : mHeight;
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

int Window::clientWidth () const
{
    return mBorder ? mWidth - 2 : mWidth;
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

int Window::focusForeColor () const
{
    return mFocusForeColor;
}

void Window::setFocusForeColor (int color)
{
    mFocusForeColor = color;
}

int Window::focusBackColor () const
{
    return mFocusBackColor;
}

void Window::setFocusBackColor (int color)
{
    mFocusBackColor = color;
}

void Window::addControl(std::unique_ptr<Window> && control)
{
    control->setParent(this);
    
    anchorWindow(control.get());
    
    mControls.push_back(std::move(control));
    
    setFocus(true);
}

const Window * Window::findWindow (int y, int x) const
{
    if (y >= mY && y < (mY + mHeight) &&
        x >= mX && x < (mX + mWidth))
    {
        for (auto & control: mControls)
        {
            const Window * result = control->findWindow(y, x);
            if (result)
            {
                return result;
            }
        }
        
        return this;
    }
    
    return nullptr;
}

const Window * Window::findFocus () const
{
    if (!mHasFocus)
    {
        // This window and none of its control windows have the focus.
        return nullptr;
    }
    
    if (mHasDirectFocus)
    {
        return this;
    }
    
    for (auto & control: mControls)
    {
        const Window * result = control->findFocus();
        if (result)
        {
            return result;
        }
    }
    
    throw std::logic_error("mHasFocus was set but no focus could be found.");
}

bool Window::canHaveDirectFocus () const
{
    return true;
}

bool Window::hasDirectFocus () const
{
    return mHasDirectFocus;
}

bool Window::setFocus (bool focus)
{
    // If focus is false, then this method will clear the focus
    // from this window and all control windows.
    // If focus is true, then this method will try to set the
    // focus to the first control window descendent. And if
    // there are no control windows that can accept the focus,
    // then this window will try to accept direct focus.
    bool foundFirstFocusControl = false;
    for (auto & control: mControls)
    {
        if (!foundFirstFocusControl)
        {
            // This works for both clearing as well as setting focus.
            foundFirstFocusControl = control->setFocus(focus);
        }
        else
        {
            // We can't exit the loop early. Once we set the first
            // focus, we clear any other focus that might exist.
            control->setFocus(false);
        }
    }
    
    if (foundFirstFocusControl)
    {
        mHasFocus = true;
        mHasDirectFocus = false;
    }
    else if (canHaveDirectFocus())
    {
        mHasFocus = focus;
        mHasDirectFocus = focus;
    }
    else
    {
        mHasFocus = false;
        mHasDirectFocus = false;
    }
    
    return mHasFocus;
}

bool Window::setFocus (int y, int x)
{
    bool foundDirectFocus = false;
    
    if (y >= mY && y < (mY + mHeight) &&
        x >= mX && x < (mX + mWidth))
    {
        for (auto & control: mControls)
        {
            bool result = control->setFocus(y, x);
            if (result)
            {
                // Some child control was able to accept the direct focus.
                foundDirectFocus = true;
                
            }
        }
        
        if (foundDirectFocus)
        {
            mHasFocus = true;
            mHasDirectFocus = false;
        }
        else
        {
            if (canHaveDirectFocus())
            {
                // No child can have direct focus but this window can.
                foundDirectFocus = true;
                
                mHasFocus = true;
                mHasDirectFocus = true;
            }
            else
            {
                // This window would normally have at least had focus but since
                // no child could be found to take direct focus and this window
                // also cannot take direct focus, then this window cannot accept
                // any focus.
                mHasFocus = false;
                mHasDirectFocus = false;
            }
        }
    }
    else
    {
        // The coordinates are outside this window so it and its children cannot have focus.
        if (mHasFocus)
        {
            setFocus(false);
        }
    }
    
    return foundDirectFocus;
}

bool Window::advanceFocus ()
{
    if (mHasDirectFocus)
    {
        // The parent window gets focus last. So if we have the focus,
        // then we can't advance any more.
        mHasFocus = false;
        mHasDirectFocus = false;
        return false;
    }
    else if (mHasFocus)
    {
        // One of the child windows has focus. Find it and then advance.
        bool foundFirstFocusControl = false;
        for (auto & control: mControls)
        {
            if (!foundFirstFocusControl)
            {
                if (control->mHasFocus)
                {
                    // We found the first control with focus. Give it the first
                    // chance to advance.
                    foundFirstFocusControl = true;
                    if (control->advanceFocus())
                    {
                        return true;
                    }
                }
            }
            else
            {
                // Now we try each control until one can accept the focus.
                if (control->advanceFocus())
                {
                    return true;
                }
            }
        }
        
        // We went through all the child controls with no further advancement.
        if (canHaveDirectFocus())
        {
            mHasDirectFocus = true;
            return true;
        }
        else
        {
            mHasFocus = false;
            return false;
        }
    }
    else
    {
        // Since we did not yet have focus, set the focus to the first
        // available window or to this window if necessary and allowed.
        return setFocus(true);
    }
}

const Window * Window::parent () const
{
    return mParent;
}

void Window::setParent (const Window * parent)
{
    mParent = parent;
}

void Window::setFillClientArea (bool value)
{
    mFillClientArea = value;
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
        
        mBorderWindow.reset(new Window("border", mY, mX, mHeight, mWidth, mBorderForeColor, mBorderBackColor, mBorderForeColor, mBorderBackColor, false, mBorderForeColor, mBorderBackColor));
    }
    else
    {
        if (mHeight < 1 || mWidth < 1)
        {
            throw std::out_of_range("height or width cannot be less than 1.");
        }
    }
    
    mClientCursesWindow = newwin(clientHeight(), clientWidth(), clientY(), clientX());
    if (!mClientCursesWindow)
    {
        string message = "Could not create window.";
        throw runtime_error(message);
    }
    
    nodelay(mClientCursesWindow, true);
    keypad(mClientCursesWindow, true);
    
    for (const auto & control: mControls)
    {
        anchorWindow(control.get());
        
        control->createWindows();
    }
}

void Window::destroyWindows ()
{
    for (const auto & control: mControls)
    {
        control->destroyWindows();
    }

    if (mClientCursesWindow)
    {
        delwin(mClientCursesWindow);
        mClientCursesWindow = nullptr;
    }

    mBorderWindow.reset();
}

void Window::anchorWindow (Window * win)
{
    int newTop = clientY();
    int newBottom = clientY() + clientHeight();
    int newLeft = clientX();
    int newRight = clientX() + clientWidth();
    
    if (win->anchorTop() != -1 && win->anchorBottom() != -1)
    {
        newTop = clientY() + win->anchorTop();
        newBottom = clientY() + clientHeight() - win->anchorBottom(); // This is one past the bottom row.
        if (newBottom <= newTop)
        {
            newBottom = newTop + 1;
        }
    }
    else if (win->anchorTop() != -1)
    {
        newTop = clientY() + win->anchorTop();
    }
    else if (win->anchorBottom() != -1)
    {
        newBottom = clientY() + clientHeight() - win->anchorBottom(); // This is one past the bottom row.
        newTop = newBottom - win->height();
        if (newTop < clientY())
        {
            newTop = clientY();
        }
    }
    
    if (win->anchorLeft() != -1 && win->anchorRight() != -1)
    {
        newLeft = clientX() + win->anchorLeft();
        newRight = clientX() + clientWidth() - win->anchorRight(); // This is one past the right column.
        if (newRight <= newLeft)
        {
            newRight = newLeft + 1;
        }
    }
    else if (win->anchorLeft() != -1)
    {
        newLeft = clientX() + win->anchorLeft();
    }
    else if (win->anchorRight() != -1)
    {
        newRight = clientX() + clientWidth() - win->anchorRight(); // This is one past the right column.
        newLeft = newRight - win->width();
        if (newLeft < clientX())
        {
            newLeft = clientX();
        }
    }
    
    win->moveAndResize(newTop, newLeft, newBottom - newTop, newRight - newLeft);
}

void Window::drawBorder () const
{
    // Draw an inside border. This should normally only need to be called for a border window.
    ConsoleManager::drawBox(*this, mY, mX, mHeight, mWidth, mBorderForeColor, mBorderBackColor);
}
