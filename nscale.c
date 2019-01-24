/*
    Calculate the frequencies in an octave
    in an Equal Temperament scale
    containing an arbitrary number of notes
    between 1 and 24
*/
#include <stdio.h>
#include <math.h>

double* calculate(int notes, int midinote){
  double frequency, ratio, c0, c5;

  ratio = pow(2.0, 1.0/12.0);
  c5 = 220.0 * pow(ratio, 3.0);
  c0 = c5 * pow(0.5, 5);
  ratio = pow(2.0, 1.0/notes);
  frequency = c0 * pow(ratio, midinote);
  double scale[notes];
  for(int i = 0; i < notes; i++){
    scale[i] = frequency * pow(ratio, i);
    printf("%f\n", scale[i]);
  }
  return scale;
}

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

  calculate(notes, midinote);
  return 0;
}
