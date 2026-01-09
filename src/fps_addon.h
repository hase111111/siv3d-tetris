#pragma once

#if defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

#include <Siv3D.hpp>

namespace mytetris {

class FpsAddon final : public IAddon {
  using clock = std::chrono::steady_clock;

 public:
  explicit FpsAddon(int32 target_fps);

#if defined(__EMSCRIPTEN__)
  bool update() override;
#else
  void postPresent() override;
#endif  // defined(__EMSCRIPTEN__)

  // フレームレートを変更.
  void SetTargetFPS(const int32 target_fps) {
    one_frame_duration_ = FpsToOneFrameDuration(target_fps);
  }

 private:
  // 1フレームあたりの時間を計算.
  static clock::duration FpsToOneFrameDuration(int32 target_fps);

  void InternalUpdate();

  static constexpr clock::duration max_drift_ = 10ms;
  clock::duration one_frame_duration_;
  std::chrono::time_point<clock> sleep_until_;
};

}  // namespace mytetris

#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
