#ifndef _FRAMES_H___
#define _FRAMES_H___

#include <stdio.h>
#include <time.h>

#define UPDATE_RATE 30   //milisegundos

class Frames{
   clock_t t1, t2;
   long    cont_frames;
   float   fps, fps_old;
public:
   Frames()
   {
      t1 = clock();
	  cont_frames = 0;
      fps_old = 20; //valor inicial
   }

   float getFrames(){
      double tempo;

      t2 = clock();
      tempo  = (double)(t2 - t1);  //milisegundos
      cont_frames++;
      //apos UPDATE_RATE milisegundos, atualiza o framerate
      if( tempo > UPDATE_RATE )
      {
         t1 = t2;
         fps = cont_frames / (tempo/CLOCKS_PER_SEC);
         cont_frames = 0;
         fps_old = fps;

         if (fps > 60.0f) { //Trava o fps em 60
            Sleep(16);
         }

         return fps;
      }
      //se nao foi decorrido UPDATE_RATE milisegundos, retorna a taxa antiga
      return fps_old;
   }
};

#endif
