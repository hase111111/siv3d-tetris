
#include "fps_addon.h"

#include "my_assert.h"

#if defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

namespace mytetris {

FpsAddon::FpsAddon(const std::shared_ptr<FpsController>& fps_controller_ptr)
    : fps_controller_ptr_(fps_controller_ptr) {
  // NULLチェック．
  DEBUG_ASSERT_NOT_NULL_PTR(fps_controller_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
}

void FpsAddon::postPresent() {
  // 処理が重い場合はここでコマ落ちさせる．
  fps_controller_ptr_->Wait();
}

}  // namespace mytetris

#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)