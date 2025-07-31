#pragma once

#include <map>
#include <string>

class Parameter {
 public:
  const static int Error = -1;

  Parameter() = default;
  virtual ~Parameter() = default;

  /// <summary>
  /// Parameterクラスにデータをセットする
  /// </summary>
  /// <param name="key">std::string型のキー</param>
  /// <param name="val">int型のデータ</param>
  void setParam(std::string key, int val);

  /// <summary>
  /// Parameterクラスにセットされたデータを取得する
  /// </summary>
  /// <param name="key">std::string型のキー</param>
  /// <returns></returns>
  int getParam(std::string key) const;

 private:
  std::map<std::string, int> _map;
};
