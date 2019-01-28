/*
    Calculate the frequencies
    in an Equal Temperament scale
    containing an arbitrary number of tones
*/
#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include "scale.h"

const char *argp_program_version = "nscale 1.0";
const char *argp_program_bug_address = "<vagus.eques@gmail.com>";

static char doc[] = "NScale calculates an octave in an equal temperament scale with the given start note and number of tones.\n\n"
"The start value is interpreted as a MIDI note value by default, but can optionally be interpreted as a frequency in Hz.";

static char args_doc[] = "tones start";

static struct argp_option options[] = {
  {"freqency",  'f',  0,  0,  "Interpret the start value as a frequency in Hz"},
  {"output", 'o', "FILE", 0, "Output to file instead of stdout"},
  {0}
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
  char* args[2];                /* arg1 & arg2 */
  int midifreq;
  char* output_file;
};

/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state){
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'f':
      arguments->midifreq = 1;
      break;
    case 'o':
      arguments->output_file = arg;
      break;

    case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
        /* Too many arguments. */
        argp_usage (state);

      arguments->args[state->arg_num] = arg;
      break;

    case ARGP_KEY_END:
      if (state->arg_num < 2)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char* argv[]){

  struct arguments arguments;

  /* Default values. */
  arguments.midifreq = 0;
  arguments.output_file = "-";

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  int notes;
  double start;

  notes = atoi(arguments.args[0]);

  start = atof(arguments.args[1]);

  if(arguments.midifreq == 0){
    if (start < 0){
      printf("Error: cannot have negative MIDI notes!\n");
      return 1;
    }
    else if(start > 127){
      printf("Error: maximum MIDI note is 127\n");
      return 1;
    }
  }
  else{
    if(start < 20 || start > 10000){
      printf("Error: please start at an audible frequency between 20 and 10,000\n");
      return 1;
    }
  }

  double scale[notes];
  compute_scale(notes, start, arguments.midifreq, (double*)&scale);
  if (!strcmp(arguments.output_file, "-")) {
    for(int i=0; i < notes; i++){
      printf("%f\n", scale[i]);
    }
  }
  else{
    FILE* f = fopen(arguments.output_file, "w+");
    for(int i=0; i < notes; i++){
      fprintf(f, "%f\n", scale[i]);
    }
    fclose(f);
    printf("Saved scale to %s\n", arguments.output_file);
  }
  return 0;
}
