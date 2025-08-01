#include "CalcUtils.h"

#include <DxLib.h>

#include <cmath>

/*
 *@brief valの小数点第point位を四捨五入して丸める
 */
float CalcUtils::roundPoint(float val, int point) {
  float ret;
  ret = (float)((double)val * pow(10.f, point - 1));
  ret = (float)(int)(ret + 0.5f);
  return (float)((double)ret * pow(10.f, -point + 1));
}
