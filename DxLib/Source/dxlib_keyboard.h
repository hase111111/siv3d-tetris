
#pragma once

#include <array>

namespace mytetris {

//! @brief DxLibのキーボード入力を取得するクラス．
class DxLibKeyboard final {
 public:
  DxLibKeyboard();

  //! @brief キー入力を更新する．
  //! これを毎フレーム実行しないと，キー入力を取得できない．
  void update();

  //! @brief keyCodeのキーが押されているフレーム数を取得する．
  //! @param[in] keyCode どのキーを調べたいか，
  //! 例えばZキーだったら，KEY_INPUT_Z となる．
  //! @return 押されているフレーム数．異常な key_code が渡された場合は-1を返す．
  int getPressingCount(const int key_code) const;

  //! @brief keyCodeのキーが離されているフレーム数を取得する．
  //! @param[in] keyCode どのキーを調べたいか，
  //! 例えばZキーだったら，KEY_INPUT_Z となる．
  //! @return 離されているフレーム数．異常な key_code が渡された場合は-1を返す．
  int getReleasingCount(const int key_code) const;

  //! @brief どれかのキーが押されているか返す．
  //! @retval true どれかのキーが押されている．
  //! @retval false どれも押されていない．
  bool isAnyKeyPressed() const;

 private:
  static const int kKeyNum = 256;  //!< DxLibにおけるキー総数．

  //! @brief keyCodeが有効なキー番号か返す．
  //! @param[in] keyCode どのキーを調べたいか，
  //! 例えばZキーだったら，KEY_INPUT_Z となる．
  //! @retval true 有効なキー番号である．
  //! @retval false 無効なキー番号である．
  bool isAvailableCode(const int key_code) const;

  std::array<int, kKeyNum> key_pressing_counter_;  //!< 押されカウンタ．
  std::array<int, kKeyNum> key_releasing_counter_;  //!< 離されカウンタ．
};

}  // namespace mytetris
