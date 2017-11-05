# aboqa
A game based on curses.

The GameManager class handles multiple named windows and keeps one active at all times.
The active window is resized in the game loop.

Create concrete Window derived classes in main and add them to the GameManager.
Then set the next active window before beginning play.

Each window will be called to process input and draw its client area.
