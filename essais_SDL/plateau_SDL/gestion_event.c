#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

const int XRES = 640;
const int YRES = 480;
const int BPP = 32;


int main(int argc, char** argv){

  SDL_Event event;
  SDL_Surface* ecran = NULL;
  int continuer = 1;

  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(XRES, YRES, BPP, SDL_HWSURFACE);
  SDL_WM_SetCaption("Gestion des événements en SDL", NULL);

  //la boucle principale : gestion des cas en fonction de la touche pressée
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
	 ecran = SDL_SetVideoMode(XRES, YRES, BPP, SDL_FULLSCREEN);
	 break;
       case 'g':
	 ecran = SDL_SetVideoMode(XRES, YRES, BPP, SDL_HWSURFACE);
	 //etc.
       }
       break;
  }

  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  //on efface l'écran (fond blanc)
  SDL_Flip(ecran);

 }

  SDL_Quit();
  return EXIT_SUCCESS;

}
