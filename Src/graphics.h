#ifndef GRAPHI_H
#define GRAPHI_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "screen.h"
extern Screen window;

class Graphics
{
 private:
   SDL_Surface *surface, *screen;
   SDL_Rect position, sourcePosition;
   Uint32 colorKey;
 public:
   Graphics();
   ~Graphics();
   void LoadImage(const char* path);
   void Free();
   void SetX(int x);
   void SetY(int y);
   void SetXY(int x, int y);

   void MakeTransparent(int r, int g, int b);

   void Draw();
   void Draw(int x, int y);
   void DrawClip();
   void DrawClip(int x, int y); //draw clip on the given coords

   void SetSource(int x, int y);
   void SetSource(SDL_Rect &source);

   void SetRectangle(int w, int h);
   void SetFillColor(int r, int g, int b);
   void Fill();

   int GetX();
   int GetY();
 };

#endif
