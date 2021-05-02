#include "SDL/SDL.h"
//pour compiler : gcc -Wall hello.c -o hello -lSDL

int main (int argc, char *argv[]){
  //les images
  SDL_Surface* hello = NULL;
  SDL_Surface* screen = NULL;

  //initialise SDL
  SDL_Init(SDL_INIT_EVERYTHING);
  
  //initialise un écran de résolution 640*480 à 32 bpp
  screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
  hello = SDL_LoadBMP("hello.bmp"); 

  //Appliquer l'image à l'écran
  SDL_BlitSurface(hello, NULL, screen, NULL); 

  //Mettre l'écran à jour
  SDL_Flip(screen); 

  //Pause : l'image va apparaître pendant 3 secondes
  SDL_Delay(3000); 

  //supprimer l'image de la mémoire 
  SDL_FreeSurface(hello); 
  SDL_Quit(); //pour fermer la librairie

  return 0;
}
