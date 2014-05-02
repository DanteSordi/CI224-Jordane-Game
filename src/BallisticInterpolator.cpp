#include "BallisticInterpolator.h"

BallisticInterpolator::BallisticInterpolator(Vector3 launch, int fps) {
  this->launch = new Vector3(launch);

  this->G = new Vector3(0.0f, 0.0f, 5.5f);   //back   up/down    straight   
  

this->fps = fps;
  this->count = 1;
}

Vector3 BallisticInterpolator::update() {
  count++;
  float time = ((float)count)/((float)fps);
  return ((*launch)*time) + ((*G) * ((1.0f/2.0f) * pow(time, 2.0f)));
}
