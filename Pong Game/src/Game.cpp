#include "../include/Game.h"

double playerPos1 = 0.0, playerPos2 = 0.0, ballPosX = 50.0, ballPosY = 50.0, playerSpeed = 3e5, maxBallSpeedX = 3.5e5, ballSpeedX = maxBallSpeedX, ballSpeedY = 0.2, miniPlayerPos = -37, maxPlayerPos = 36, miniBallPos = 3.0, maxBallPos = 96.0, AISpeed = 3e5, ballRadius = 1.1;
bool startMove = false, turn = true, isRoundStarting = true, swapButton = true, AIPlayer = false;
int playerOneScore = 0, playerTwoScore = 0;

// Function to reset the game state
void resetGame()
{
    playerOneScore = 0;
    playerTwoScore = 0;
    ballPosX = 50.0;
    ballPosY = 50.0;
    ballSpeedY = 0.2;
    playerPos1 = 0.0;
    playerPos2 = 0.0;
    turn = true;
    startMove = false;
    isRoundStarting = true;
    swapButton = true;
    AIPlayer = false;
}

// Enum for game modes
enum currentGameMode
{
    MENU,
    GAME,
    PLAYERONEWIN,
    PLAYERTWOWIN,
};

currentGameMode GameMode;

double customClamp(double value, double minVal, double maxVal)
{
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

// Helper function to reset the round
void resetRound()
{
    ballSpeedY = 0.2;
    ballPosX = 50.0;
    ballPosY = 50.0;
    playerPos1 = 0.0;
    playerPos2 = 0.0;
    startMove = false;
    isRoundStarting = true;
}

// Input checking functions
bool isDown(Input* input, int button)
{
    return input->buttons[button].isDown;
}

bool pressed(Input* input, int button)
{
    return input->buttons[button].isDown && input->buttons[button].changeState;
}

bool released(Input* input, int button)
{
    return !(input->buttons[button].isDown) && input->buttons[button].changeState;
}

// Game simulation function
void Game::simulateGame(Input* input, Renderer graphicsRenderer, RenderWin32Platform render, double time)
{
    // Draw the arena
    graphicsRenderer.drawRectangle(render, 0, 100, 0, 2.5, 0x34495E);
    graphicsRenderer.drawRectangle(render, 0, 2.5, 0, 100, 0x34495E);
    graphicsRenderer.drawRectangle(render, 96.5, 100, 0, 100, 0x34495E);
    graphicsRenderer.drawRectangle(render, 0, 100, 96.5, 100, 0x34495E);
    graphicsRenderer.drawRectangle(render, 2.5, 96.5, 2.5, 96.5, 0x5D6D7E);
    graphicsRenderer.drawRectangle(render, 3, 96, 3, 96, 0x2C3E50);

    double performanceMultiplier = time / (1.0 / 60.0); // Assuming 60 FPS as target

    if (GameMode == GAME)
    {
        // Player one movement
        if (isDown(input, BUTTON_W)) playerPos1 += playerSpeed * performanceMultiplier;
        if (isDown(input, BUTTON_S)) playerPos1 -= playerSpeed * performanceMultiplier;

        // Clamp player positions to keep within bounds
        playerPos1 = customClamp(playerPos1, miniPlayerPos, maxPlayerPos);
        playerPos2 = customClamp(playerPos2, miniPlayerPos, maxPlayerPos);

        if (AIPlayer)
        {
            // AI movement logic
            if (playerPos2 + 55 < ballPosY) playerPos2 += AISpeed * performanceMultiplier;
            if (playerPos2 + 50 > ballPosY) playerPos2 -= AISpeed * performanceMultiplier;

            if (isRoundStarting && (isDown(input, BUTTON_W) || isDown(input, BUTTON_S)))
            {
                startMove = true;
                isRoundStarting = false;
            }
        }
        else
        {
            // Player two movement
            if (isDown(input, BUTTON_UP)) playerPos2 += playerSpeed * performanceMultiplier;
            if (isDown(input, BUTTON_DOWN)) playerPos2 -= playerSpeed * performanceMultiplier;

            if (isRoundStarting) {
                if ((!turn && (isDown(input, BUTTON_W) || isDown(input, BUTTON_S))) ||
                    (turn && (isDown(input, BUTTON_UP) || isDown(input, BUTTON_DOWN))))
                {
                    startMove = true;
                    isRoundStarting = false;
                }
            }
        }

        if (startMove)
        {
            // Move the ball
            ballPosX += ballSpeedX * performanceMultiplier;
            ballPosY += ballSpeedY * performanceMultiplier;
        }

        // Ball collision with bounds
        if (ballPosX < miniBallPos || ballPosX > maxBallPos)
        {
            ballSpeedX *= -1;
            ballPosX = ballPosX < miniBallPos ? miniBallPos : maxBallPos;
        }
        if (ballPosY < miniBallPos || ballPosY > maxBallPos)
        {
            ballSpeedY *= -1;
            ballPosY = ballPosY < miniBallPos ? miniBallPos : maxBallPos;
        }

        // Ball collision with player one
        if (ballPosY >= 41 + playerPos1 && ballPosY <= 61 + playerPos1 && ballPosX - ballRadius <= 5.5)
        {
            ballSpeedX *= -1;
            ballPosX = 5.501 + ballRadius;
            double relativeIntersectY = (41 + playerPos1 + 61 + playerPos1) / 2 - ballPosY;
            ballSpeedY = relativeIntersectY * 0.4e5;
        }

        // Ball collision with player two
        if (ballPosY >= 41 + playerPos2 && ballPosY <= 61 + playerPos2 && ballPosX + ballRadius >= 93.5)
        {
            ballSpeedX *= -1;
            ballPosX = 93.501 - ballRadius;
            double relativeIntersectY = (41 + playerPos2 + 61 + playerPos2) / 2 - ballPosY;
            ballSpeedY = relativeIntersectY * 0.4e5;
        }

        // Player two wins round
        if (ballPosX <= 3)
        {
            playerTwoScore++;
            resetRound();
        }

        // Player one wins round
        if (ballPosX >= 96) 
        {
            playerOneScore++;
            resetRound();
        }

        // Check for win condition
        if (playerOneScore == 10)
        {
            GameMode = PLAYERONEWIN;
            resetGame();
        }
        else if (playerTwoScore == 10)
        {
            GameMode = PLAYERTWOWIN;
            resetGame();
        }

        // Draw scores, players, and ball
        graphicsRenderer.drawNumber(render, playerTwoScore, 55, 56, 90, 91, 0x000000);
        graphicsRenderer.drawNumber(render, playerOneScore, 44, 45, 90, 91, 0x000000);
        graphicsRenderer.drawCircle(render, ballPosX, ballPosY, ballRadius, 0xbfb8b4);
        graphicsRenderer.drawRectangle(render, 3.5, 5.5, 40 + playerPos1, 60 + playerPos1, 0x89BCDD);
        graphicsRenderer.drawRectangle(render, 93.5, 95.5, 40 + playerPos2, 60 + playerPos2, 0x89BCDD);
    }
    else if (GameMode == MENU)
    {
        // Menu rendering logic
        graphicsRenderer.drawText(render, "PONG GAME", 37, 80, 0x000000);
        graphicsRenderer.drawText(render, "MADE BY: OMAR ABDELMONEM SAYED", 9, 20, 0x000000);

        if (pressed(input, BUTTON_LEFT)) swapButton = true;
        if (pressed(input, BUTTON_RIGHT)) swapButton = false;

        if (swapButton)
        {
            graphicsRenderer.drawRectangle(render, 52, 92, 40, 60, 0x95A5A6);
            graphicsRenderer.drawRectangle(render, 8, 48, 40, 60, 0x424949);
            AIPlayer = true;
        }
        else
        {
            graphicsRenderer.drawRectangle(render, 52, 92, 40, 60, 0x424949);
            graphicsRenderer.drawRectangle(render, 8, 48, 40, 60, 0x95A5A6);
            AIPlayer = false;
        }

        graphicsRenderer.drawText(render, "SINGLE PLAYER", 9.5, 48, 0xffffff);
        graphicsRenderer.drawText(render, "MULTIPLAYER", 56, 48, 0xffffff);

        if (pressed(input, BUTTON_ENTER)) 
        {
            GameMode = GAME;
            resetRound();
        }
    }
    else if (GameMode == PLAYERONEWIN)
    {
        graphicsRenderer.drawText(render, "PLAYER ONE WON", 30, 55, 0xffffff);
        graphicsRenderer.drawText(render, "PRESS ENTER TO PLAY AGAIN", 15, 30, 0xffffff);
        if (pressed(input, BUTTON_ENTER))
        {
            GameMode = MENU;
        }
    }
    else
    {
        graphicsRenderer.drawText(render, "PLAYER TWO WON", 30, 55, 0xffffff);
        graphicsRenderer.drawText(render, "PRESS ENTER TO PLAY AGAIN", 15, 30, 0xffffff);
        if (pressed(input, BUTTON_ENTER))
        {
            GameMode = MENU;
        }
    }
}
