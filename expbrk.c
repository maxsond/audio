// Implement formula x[t] = a* exp(-k/T)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv){
  int i, npoints;
  double startval, endval;
  double dur, step, start, end, thisstep;
  double fac, valrange, offset;
  const double verysmall = 1.0e-4; // -80 dB

  if(argc != 5){
    printf("Usage: expbrk duration npoints startval endval\n");
    return 1;
  }

  dur = atof(argv[1]);
  if(dur <= 0.0){
    fprintf(stderr, "Error: duration must be positive.\n");
    return 1;
  }
  npoints = atoi(argv[2]);
  if(npoints <= 0){
    fprintf(stderr, "Error: npoints must be positive.\n");
    return 1;
  }

  step = dur/npoints;

  startval = atof(argv[3]);
  endval = atof(argv[4]);
  valrange = endval - startval;
  if(valrange == 0){
    fprintf(stderr, "Warning: start and end values are the same.\n");
  }
  if(startval > endval){
    start = 1.0;
    end = verysmall;
    valrange = -valrange;
    offset = endval;
  }
  else{
    start = verysmall;
    end = 1.0;
    offset = startval;
  }

  thisstep = 0.0;

  // Make normalized curve
  fac = pow(end/start, 1.0/npoints);
  for(i = 0; i < npoints; i++){
    fprintf(stdout, "%.4lf\t%.8lf\n", thisstep, offset + start * valrange);
    start *= fac;
    thisstep += step;
  }

  // Print final value
  fprintf(stdout, "%.4lf\t%.8lf\n", thisstep, offset + start * valrange);
  return 0;
}
