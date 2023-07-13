#include "raylib.h"
#include <stdio.h>

struct window; // Rectangle, 4 components
// TODO: Create pointers only if it's necessary
struct Player
{
  Vector2 top;
  Vector2 almostTop;
  Vector2 halfTop;
  Vector2 center;
  Vector2 halfbottom;
  Vector2 almostBottom;
  Vector2 Bottom;
  Vector2 size;
  Vector2 position;
};

struct Motion
{
  bool left;
  bool right;
};

struct Status
{
  bool run;
  bool reset;
};

// Program main entry point
int main(void)
{
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  struct Player player1;
  player1.size.y = 30.00;
  player1.size.x = 10.00;
  player1.position.y = (screenHeight / 2) - (player1.size.y / 2);
  player1.position.x = 1.00;
  player1.center.y = player1.position.y;
  player1.center.x = player1.position.x;

  struct Player player2;
  player2.size.y = 30.00;
  player2.size.x = 10.00;
  player2.position.y = (screenHeight / 2) - (player2.size.y / 2);
  player2.position.x = screenWidth - player2.size.x;
  player2.center.y = player2.position.y;
  player2.center.x = player2.position.x;

  Vector2 ball;
  ball.y = screenHeight / 2;
  ball.x = screenWidth / 2;

  // TODO: When is the first time play it, define random motion.
  struct Motion motion;
  motion.left = false;
  motion.right = true;

  struct Status status;
  status.run = false;
  status.reset = false;

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Players movement
    if (IsKeyDown(KEY_W) && player1.center.y >= 0)
      player1.center.y -= 8.0f;
    if (IsKeyDown(KEY_S) && (player1.center.y + (screenHeight / 5)) <= screenHeight)
      player1.center.y += 8.0f;

    if (IsKeyDown(KEY_UP) && player2.center.y >= 0)
      player2.center.y -= 8.0f;
    if (IsKeyDown(KEY_DOWN) && (player2.center.y + (screenHeight / 5)) <= screenHeight)
      player2.center.y += 8.0f;

    // Run game
    if (IsKeyPressed(KEY_ENTER))
      status.run = !status.run;

    // Ball movement
    if (status.run && motion.right)
      ball.x += 5.0f;
    if (status.run && motion.left)
      ball.x -= 5.0f;

    if (ball.x >= screenWidth)
      status.reset = true;

    if (ball.x <= 0)
      status.reset = true;

    if (status.reset)
    {
      player1.center.y = screenHeight / 2;
      player1.center.x = 1.00;
      player2.center.y = screenHeight / 2;
      player2.center.x = screenWidth - 11;
      ball.y = screenHeight / 2;
      ball.x = screenWidth / 2;
      status.reset = false;
      status.run = false;
      motion.right = true;
      motion.left = false;
    }

    // Colition with player
    // TODO: Update algorithm
    if (ball.y >= player1.center.y && ball.y <= (player1.center.y + player1.size.y) && (ball.x <= player1.size.x))
    {
      motion.right = true;
      motion.left = false;
    }

    if (ball.y >= player2.center.y && ball.y <= (player2.center.y + player2.size.y) && ball.x >= (screenWidth - player2.size.x))
    {
      motion.right = false;
      motion.left = true;
    }

    //  Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("move player one with arrow keys", 10, 10, 20, DARKGRAY);

    DrawCircleV(ball, 10, RED);                          // Draw a circle (Vector version);
    DrawRectangleV(player1.center, player1.size, BLACK); // Draw a line (Vector version)
    DrawRectangleV(player2.center, player2.size, BLACK); // Draw a line (Vector version)

    EndDrawing();
  }

  // De-Initialization
  CloseWindow(); // Close window and OpenGL context

  return 0;
}