#include "Parameter.h"

void Parameter::setParam(std::string key, int val) { _map[key] = val; }

int Parameter::getParam(std::string key) const {
  auto it = _map.find(key);  // 指定キーを取得
  if (_map.end() == it) {    // 無かったら
    return Error;            // エラー
  } else {
    return it->second;  // あったら値を返す
  }
}
