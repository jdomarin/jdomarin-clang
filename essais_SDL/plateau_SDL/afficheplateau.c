#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

//pour compiler : gcc -Wall afficheplateau.c -o afpl -lSDL -lSDL_image

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *plateau = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

SDL_Surface *load_image(char* filename) {
 
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL; 
  
  loadedImage = IMG_Load(filename); 

  if(loadedImage != NULL) 
{
  optimizedImage = SDL_DisplayFormat(loadedImage);
  SDL_FreeSurface(loadedImage);
 } 
  return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination) { 
  SDL_Rect offset; 
  offset.x = x; 
  offset.y = y; 
  SDL_BlitSurface(source, NULL, destination, &offset); 
} 


int main (int argc, char **argv) {

  SDL_Init(SDL_INIT_EVERYTHING);

   if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
     return 1;

   screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

   if (screen == NULL)
     return 1;

   //mettre l'entête de fichier au-dessus de l'écran
   SDL_WM_SetCaption("Plateau de jeu de dames anglaises", NULL);
   plateau = load_image("plateau.jpg" );
   background = load_image("background.bmp"); 

   apply_surface(0, 0, background, screen);
   apply_surface(320, 0, background, screen);
   apply_surface(0, 240, background, screen);
   apply_surface(320, 240, background, screen);

   apply_surface(170, 100, plateau, screen);

   if(SDL_Flip(screen) == -1)
     return 1;
   
   SDL_Delay(5000);
   SDL_FreeSurface(plateau);
   SDL_FreeSurface(background);
   SDL_Quit();

   return 0;
 }
