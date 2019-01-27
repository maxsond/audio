
#include <math.h>

int compute_scale(int notes, double start, int midi_or_freq, double* scale){
  double frequency, ratio, c0, c5;
  ratio = pow(2.0, 1.0/12.0);
  c5 = 220.0 * pow(ratio, 3.0);
  c0 = c5 * pow(0.5, 5);
  if(midi_or_freq){
    frequency = start;
  }
  else{
    frequency = c0 * pow(ratio, start);
  }
  ratio = pow(2.0, 1.0/notes);
  for(int i = 0; i < notes; i++){
    scale[i] = frequency * pow(ratio, i);
  }
  return 0;
}
