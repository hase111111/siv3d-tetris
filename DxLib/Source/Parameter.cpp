#include "Parameter.h"

void Parameter::setParam(std::string key, int val) { _map[key] = val; }

int Parameter::getParam(std::string key) const {
  auto it = _map.find(key);  // �w��L�[���擾
  if (_map.end() == it) {    // ����������
    return Error;            // �G���[
  } else {
    return it->second;  // ��������l��Ԃ�
  }
}
