/*
    Calculate the frequencies
    in an Equal Temperament scale
    containing an arbitrary number of tones
*/
#include <stdio.h>
#include <stdlib.h>
#include "scale.h"

int main(int argc, char* argv[]){

  if(argc != 3){
    printf("Usage: nscale <notes> <midinote>\n");
    return 1;
  }

  int notes, midinote;

  notes = atoi(argv[1]);

  midinote = atoi(argv[2]);
  if(midinote < 0){
    printf("Error: cannot have negative MIDI notes!\n");
    return 1;
  }
  if(midinote > 127){
    printf("Error: maximum MIDI note is 127\n");
    return 1;
  }

  double scale[notes];
  compute_scale(notes, midinote, 0, (double*)&scale);
  for(int i=0; i < notes; i++){
    printf("%f\n", scale[i]);
  }
  return 0;
}
