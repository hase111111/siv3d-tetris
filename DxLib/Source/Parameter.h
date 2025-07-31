#pragma once

#include <map>
#include <string>

class Parameter {
 public:
  const static int Error = -1;

  Parameter() = default;
  virtual ~Parameter() = default;

  /// <summary>
  /// Parameter�N���X�Ƀf�[�^���Z�b�g����
  /// </summary>
  /// <param name="key">std::string�^�̃L�[</param>
  /// <param name="val">int�^�̃f�[�^</param>
  void setParam(std::string key, int val);

  /// <summary>
  /// Parameter�N���X�ɃZ�b�g���ꂽ�f�[�^���擾����
  /// </summary>
  /// <param name="key">std::string�^�̃L�[</param>
  /// <returns></returns>
  int getParam(std::string key) const;

 private:
  std::map<std::string, int> _map;
};
