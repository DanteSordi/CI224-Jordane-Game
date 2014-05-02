#include "GameAsset.h"
#include "IInterpolator.h"

#ifndef CUBEASSET_H_
#define CUBEASSET_H_


class CubeAsset : public GameAsset {
 public:
  CubeAsset();
  CubeAsset(float x, float y, float z);
  ~CubeAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  shared_ptr<IInterpolator> li;
};

#endif // CUBEASSET_H_
