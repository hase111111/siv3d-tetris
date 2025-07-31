#include "CalcUtils.h"

#include <DxLib.h>

#include <cmath>

/*
 *@brief val‚Ì¬”“_‘æpointˆÊ‚ğlÌŒÜ“ü‚µ‚ÄŠÛ‚ß‚é
 */
float CalcUtils::roundPoint(float val, int point) {
  float ret;
  ret = (float)((double)val * pow(10.f, point - 1));
  ret = (float)(int)(ret + 0.5f);
  return (float)((double)ret * pow(10.f, -point + 1));
}
