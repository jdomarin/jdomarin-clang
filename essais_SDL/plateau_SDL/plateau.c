#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

//pour compiler : gcc -Wall plateau.c -o plateau -lSDL -lSDL_image

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

  if(loadedImage != NULL) { 
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

  SDL_Event event;
  int continuer = 1;

  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE);

  //mettre l'entête de fichier au-dessus de l'écran
  SDL_WM_SetCaption("Plateau de jeu de dames anglaises", NULL);
  plateau = load_image("plateau.jpg");
  background = load_image("background.bmp"); 

  apply_surface(0, 0, plateau, screen);
  /*apply_surface(SCREEN_WIDTH / 2, 0, background, screen);
  apply_surface(0, SCREEN_HEIGHT / 2, background, screen);
  apply_surface(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, background, screen);
  
  apply_surface(170, 100, plateau, screen);
  */

  //issu de event2.c
       
  while(continuer){

    SDL_WaitEvent(&event); //attendre événement
  
    switch(event.type){
    case SDL_QUIT:
      continuer = 0;
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
      case SDLK_ESCAPE:
	continuer = 0;
	break;
      case 'f':
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN);
	break;
      case 'g':
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE);
	//etc.
      }
      break;
    }
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    //on efface l'écran (fond blanc)
    SDL_Flip(screen);
    
    
    return EXIT_SUCCESS;
  }
  

  //SDL_Delay(5000);
  SDL_FreeSurface(plateau);
  SDL_Quit();
 
  return 0;

}
