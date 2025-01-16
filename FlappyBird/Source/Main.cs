using System;
using Raylib_cs;

class GameApp
{
    static void Main(string[] args)
    {
        Raylib.InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

        while(!Raylib.WindowShouldClose())
        {
            Raylib.BeginDrawing();
            Raylib.ClearBackground(Color.RayWhite);
            Raylib.EndDrawing();
        }

        Raylib.CloseWindow();
    }

    private static readonly int WINDOW_WIDTH = 600;
    private static readonly int WINDOW_HEIGHT = 800;
    private static readonly string WINDOW_TITLE = "FlappyBird";
}