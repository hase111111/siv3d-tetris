
//! @file fps_addon.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#if defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

#include <Siv3D.hpp>
#include <memory>

#include "fps_controller.h"

namespace mytetris {

class FpsAddon : public s3d::IAddon {
 public:
  FpsAddon() = delete;
  explicit FpsAddon(const std::shared_ptr<FpsController> &fps_controller_ptr);

  void postPresent();

 private:
  const std::shared_ptr<FpsController> fps_controller_ptr_;
};

}  // namespace mytetris

#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
