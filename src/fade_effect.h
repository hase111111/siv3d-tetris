#pragma once

#include <functional>

namespace mytetris {

enum class FadeType {
  kFadeIn,
  kFadeOut,
};

class FadeEffect final {
 public:
  FadeEffect(int fade_time);
  ~FadeEffect() = default;

  //! @brief フェード演出を更新する.
  //! 必ず毎フレーム呼び出すこと.
  //! @return フェード中なら true、フェード完了なら false.
  bool Update();

  //! @brief フェード演出を開始する.
  //! @param fade_type フェードの種類.
  //! @param callback フェード完了時に呼び出されるコールバック関数.
  void Start(FadeType fade_type, const std::function<void()>& callback);

  //! @brief フェード演出を描画する.
  //! 描画順が最も手前になるように，必ず最後に呼び出すこと.
  void Draw() const;

 private:
  const int fade_time_;

  FadeType fade_type_{FadeType::kFadeIn};
  std::function<void()> callback_{[]() {}};
  int counter_{0};
};

}  // namespace mytetris
