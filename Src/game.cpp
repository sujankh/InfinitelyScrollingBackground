#include "game.h"

Game::Game():FramePS(60)
{
 TICK_INTERVAL = 1000 / FramePS;
}

Game::~Game()
{
 SDL_Quit();
}

void Game::Init(char* title)
{
 SDL_WM_SetCaption(title, NULL);
 SDL_ShowCursor(SDL_DISABLE);
}

void Game::Process()
{
 SDL_Event event;
 SDLKey k;

 Uint8* keystate;
 bool running = true;
 Graphics bg;
 bg.LoadImage("bgpath.png");
 int w = 800, h = 640, xVel = 0, yVel = 0; //w and h are params of the bg image
 SDL_Rect camera = {0, h - 480, 640, 480}; //640 x 480 screen size
 bg.SetSource(camera);

 nextTime = SDL_GetTicks() + TICK_INTERVAL;
 while(running)
 {
     //if(xVel != 0)
        bg.SetSource(camera);

     bg.DrawClip();
     if(camera.x > 0)
     {
        bg.SetSource(0, camera.y);
        bg.DrawClip(w - camera.x, 0);
     }

    if(SDL_PollEvent(&event))
    {
       switch(event.type)
        {
         case SDL_KEYDOWN:
            k=event.key.keysym.sym;

            if(k == SDLK_RIGHT)
                xVel = 5;
            else if(k == SDLK_UP)
                yVel = -5;
            else if(k == SDLK_DOWN)
                yVel = 5;
         break;

         case SDL_KEYUP:
            k=event.key.keysym.sym;

            if(k == SDLK_RIGHT)
                xVel = 0;
            else if(k == SDLK_UP || k == SDLK_DOWN)
                yVel = 0;
         break;

         case SDL_QUIT:
          running = false;
          continue;
         break;
        }
     }

    camera.x += xVel;
    if(camera.x > w)
        camera.x = 0;

    camera.y += yVel;
    if(camera.y < 0)
        camera.y = 0;
    else if(camera.y + camera.h > h) //h is the height of bg
        camera.y = h - camera.h;

    SDL_PumpEvents();
    keystate = SDL_GetKeyState(NULL);
    if(keystate[SDLK_ESCAPE])
    {
       running = false;
       continue;
    }

    window.Flip();
    SDL_Delay(TimeLeft());
    nextTime += TICK_INTERVAL;
 }

}

Uint32 Game::TimeLeft()
{
  Uint32 now;

  now = SDL_GetTicks();
  if(nextTime <= now)
      return 0;
  else
      return nextTime - now;
}
