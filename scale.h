#ifndef SCALE_H_   /* Include guard */
#define SCALE_H_

int compute_scale(int notes, double start, int midi_or_freq, double* scale);
  /*
  Calculate the notes in a scale from start
  Start may be a MIDI note (midi_or_freq = 0)
    Or a frequency in hertz (midi_or_freq = 1)
  Must pass in a pointer to a a double array
    This array must have length <notes>
    And will be populated with the notes in the scale in Hz
  */
  
#endif
