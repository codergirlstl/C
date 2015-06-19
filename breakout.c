//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3


//width and height of paddle
#define PADDLEHEIGHT 60
#define PADDLEWIDTH 10

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void removeGWindow(GWindow window, GObject object);
int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
       
    //set velocity of ball
    double x_velocity = drand48() * 2;
    double y_velocity = 2.5;  
    // to start game and move ball 
    waitForClick();
       
    // keep playing until game over           ./
    while (lives > 0 && bricks > 0)
    {
       
       getLabel(label);
       // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {           
            //if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure circle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                double y = (getHeight(window) - getHeight(paddle)) * 5/6;
                setLocation(paddle, x, y);
            }
         } 
         
         move(ball, x_velocity, y_velocity);
                   
        // ball bounces off bottom of window
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            pause(10);
            double x = (getWidth(window) -getWidth(ball)) / 2;
            double y = (getHeight(window) -getHeight(ball))/ 2;
            setLocation(ball,x,y);
            waitForClick();
            move(ball, x_velocity, y_velocity);           
        }

        // ball bounces off top of window
        else if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
        // ball bounces off left side of window
        else if(getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        }
        //ball bounces off right side of window
        else if(getX(ball) + getWidth(ball) >=getWidth(window))
        {
            x_velocity = -x_velocity;
        }        
        // linger before moving again
        pause(10);
         
         
      //call detectCollision function
     GObject object = detectCollision(window, ball);
     
     if(object != NULL)
        {
      //ball hits paddle bounce back
      if (object == paddle)
        {
            y_velocity = -y_velocity;
        }
       // ball hits brick then removes it 
       else if (strcmp(getType(object), "GRect") == 0)
        { 
        y_velocity = -y_velocity;
        removeGWindow(window, object);
        bricks--;
        points++;
        updateScoreboard(window, label, points);
        }
        }      
        }       
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
    }    



/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    
    //CREATE A ROW OF BRICKS
    double x = 0;
    double y = 30;   
        //iterate through correct number of ROWS
        for(int num_of_rows = 1;  num_of_rows <= ROWS ; num_of_rows++)
           {
            //iterate through correct number of COLS
            for(int num_of_cols = 1; num_of_cols <= COLS; num_of_cols++)
                //print out bricks as GRect and add space between bricks
                {  
                GRect bricks = newGRect (x, y, 35, 10);
                 setColor(bricks, "RED");
                setFilled(bricks, true);
                add(window, bricks);
                x = x + 40;
                }
                // reset x coordinate to 0 and advance y coordinate for new row
                x = x-x;
                y = y +15;
            }  
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    //CREATE A BALL AND CENTER USING WIDTH AND HEIGHT OF WINDOW 
    
    GOval ball = newGOval(0,0,RADIUS * 2, RADIUS * 2);
    double x = (getWidth(window) -getWidth(ball)) / 2;
    double y = (getHeight(window) -getHeight(ball))/ 2;
    setLocation(ball,x,y);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
    
    
    
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    //set coordinates and color for paddle 
    GRect paddle = newGRect(0,0, PADDLEHEIGHT, PADDLEWIDTH);
    double x = (getWidth(window) - getWidth(paddle)) / 2;
    double y = (getHeight(window) - getHeight(paddle)) * 5/6;
    setLocation(paddle,x,y);
    setColor (paddle, "BLUE");
    setFilled (paddle, true);
    add(window, paddle);
    return paddle;
 
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    //
    
    GLabel label = newGLabel("0");
    double x = (getWidth(window)-getWidth(label)) / 2;
    double y = (getHeight(window)- getHeight(label)) / 3 ;
    setFont(label, "New Times Roman -40");
    setLocation(label,x,y);
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 3;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

