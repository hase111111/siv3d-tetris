#include "fps_addon.h"

#include "my_assert.h"

#if defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

namespace mytetris {

FpsAddon::FpsAddon(const int32 target_fps)
    : one_frame_duration_(FpsToOneFrameDuration(target_fps)),
      sleep_until_(clock::now()) {
  DEBUG_ASSERT(target_fps > 0, "target_fps ÇÕê≥ÇÃílÇ≈Ç†ÇÈïKóvÇ™Ç†ÇËÇ‹Ç∑.");
}

#if defined(__EMSCRIPTEN__)
bool FpsAddon::update() {
  InternalUpdate();
  return true;
}

#else

void FpsAddon::postPresent() { InternalUpdate(); }

#endif  // defined(__EMSCRIPTEN__)

std::chrono::steady_clock::duration FpsAddon::FpsToOneFrameDuration(
    const int32 target_fps) {
  return std::chrono::duration_cast<clock::duration>(1s) / target_fps;
}
void FpsAddon::InternalUpdate() {
  sleep_until_ += one_frame_duration_;
  sleep_until_ =
      Max(sleep_until_, std::chrono::steady_clock::now() - max_drift_);

  std::this_thread::sleep_until(sleep_until_);
}

}  // namespace mytetris

#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)