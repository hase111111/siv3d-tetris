#include "CalcUtils.h"

#include <DxLib.h>

#include <cmath>

/*
 *@brief val�̏����_��point�ʂ��l�̌ܓ����Ċۂ߂�
 */
float CalcUtils::roundPoint(float val, int point) {
  float ret;
  ret = (float)((double)val * pow(10.f, point - 1));
  ret = (float)(int)(ret + 0.5f);
  return (float)((double)ret * pow(10.f, -point + 1));
}
