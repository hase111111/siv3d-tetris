#pragma once

#include <array>
#include <memory>
#include <optional>

#include "key_config_data.h"
#include "key_handle.h"

namespace mytetris {

//! @brief DxLibのキーボード入力を取得するクラス．
class KeyEventHandler final {
  static constexpr int kKeyNum = 256;  //!< DxLibにおけるキー総数．
 public:
  KeyEventHandler(const std::shared_ptr<KeyConfigData>& key_event_handler_ptr);

  //! @brief キー入力を更新する．
  //! これを毎フレーム実行しないと，キー入力を取得できない．
  void Update();

  //! @brief keyCodeのキーが押されているフレーム数を取得する．
  //! @param[in] keyCode どのキーを調べたいか，
  //! 例えばZキーだったら，KEY_INPUT_Z となる．
  //! @return 押されているフレーム数．異常な key_code が渡された場合は-1を返す．
  int GetPressingCount(KeyGroup group) const;

  //! @brief keyCodeのキーが離されているフレーム数を取得する．
  //! @param[in] keyCode どのキーを調べたいか，
  //! 例えばZキーだったら，KEY_INPUT_Z となる．
  //! @return 離されているフレーム数．異常な key_code が渡された場合は-1を返す．
  int GetReleasingCount(KeyGroup group) const;

  std::optional<KeyHandle> GetInputKeyHandle() const;

  KeyHandle GetKeyHandleFromKeyGroup(const KeyGroup group) const {
    return key_config_data_ptr_->Map(group);
  }

 private:
  //! @brief keyCodeが有効なキー番号か返す．
  //! @param[in] keyCode どのキーを調べたいか，
  //! 例えばZキーだったら，KEY_INPUT_Z となる．
  //! @retval true 有効なキー番号である．
  //! @retval false 無効なキー番号である．
  bool IsAvailableCode(const int key_code) const;

  const std::shared_ptr<const KeyConfigData> key_config_data_ptr_;

  std::array<int, kKeyNum> key_pressing_counter_;   //!< 押されカウンタ．
  std::array<int, kKeyNum> key_releasing_counter_;  //!< 離されカウンタ．
};

}  // namespace mytetris
