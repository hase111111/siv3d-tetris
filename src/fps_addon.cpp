
#include "fps_addon.h"

#include "my_assert.h"

#if defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

namespace mytetris {

FpsAddon::FpsAddon(const std::shared_ptr<FpsController>& fps_controller_ptr)
    : fps_controller_ptr_(fps_controller_ptr) {
  // NULL�`�F�b�N�D
  DEBUG_ASSERT_NOT_NULL_PTR(fps_controller_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
}

void FpsAddon::postPresent() {
  // �������d���ꍇ�͂����ŃR�}����������D
  fps_controller_ptr_->Wait();
}

}  // namespace mytetris

#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)