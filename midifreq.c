#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SEMITONE_RATIO 1.059463
#define C0 8.175799

int usage(){
  printf("Usage:\n"
  "midifreq midi <MIDI Note> : Displays approximate frequency of note\n"
  "midifreq freq <frequency in Hz> : Displays closest note to frequency\n");
  return 0;
}

int midi2freq(int midinote){
  double frequency;

  if(0<=midinote && midinote<=127){
    frequency = C0 * pow(SEMITONE_RATIO, midinote);
    printf("MIDI Note %d has a frequency of %.2f Hz\n", midinote, frequency);
  }
  else{
    printf("Please input a value from 0 to 127\n");
  }
  return 0;
}

int freq2midi(double freq){
  double fracmidi;
  int midinote;

  if(freq==0){
    printf("Please enter a decimal frequency value.\n");
    return 0;
  }
  if(freq < 16 || freq > 32768){
    printf("The audible range is approximately from 16 to 32,768 Hz. "
    "Try somewhere in there.\n");
    return 0;
  }

  fracmidi = log(freq / C0) / log(SEMITONE_RATIO);
  midinote = (int) (fracmidi + 0.5);
  printf("The nearest MIDI note to the frequency %.2f is %d\n", freq, midinote);
  return 0;
}

int main(int argc, char *argv[]){
  if(argc==3){
    if (!strcmp(argv[1], "midi")){
      return midi2freq(atoi(argv[2]));
    }
    else if (!strcmp(argv[1], "freq")){
      return freq2midi(atof(argv[2]));
    }
  }
  return usage();
}
