//! @file fps_controller.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "fps_controller.h"

#if defined(DXLIB_COMPILE)
#include <Dxlib.h>
#elif defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

#include <cmath>
#include <string>

#include "game_const.h"

namespace mytetris {

FpsController::FpsController(const int target_fps)
    : target_fps_value_(target_fps),
      one_frame_time_(static_cast<int>(1000.0 / target_fps)),
      list_max_(target_fps * 2),
      need_skip_draw_screen_(false) {}

void FpsController::Wait() {
  if (!TargetFpsIsValid()) {
    return;
  }

  // 待つべき時間を取得して待つ．
  int wait_time = 0;

  if (CheckNeedSkipDrawScreen(&wait_time)) {
#if defined(DXLIB_COMPILE)
    WaitTimer(wait_time);  // 取得した時間分待つ．

    RegisterTime(GetNowCount());  // 現在の時刻を記録する．

#elif defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

    s3d::System::Sleep(wait_time);
    RegisterTime(
        static_cast<int>(s3d::Time::GetMillisec()));  // 現在の時刻を記録する．

#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

  } else {
    // 時間オーバーしているので，コマ落ちの処理をする．

    // このフレームは理想的な処理をしたものとして，記録する．
    RegisterTime(time_list_.back() + one_frame_time_);

    need_skip_draw_screen_ = true;  // 描画を飛ばすフラグを立てる．
  }
}

bool FpsController::SkipDrawScene() {
  if (!TargetFpsIsValid()) {
    return false;
  }

  // スキップフラグが立っているならば，そのフラグを折り，シーンをスキップする．
  if (need_skip_draw_screen_) {
    need_skip_draw_screen_ = false;
    return true;
  }

  return false;
}

void FpsController::RegisterTime(const int now_time) {
  time_list_.push_back(now_time);  // 現在の時刻を記憶．

  if (time_list_.size() > list_max_) {
    // 器から漏れたら削除する．
    time_list_.pop_front();
  }
}

bool FpsController::CheckNeedSkipDrawScreen(int* time) const {
  // 時刻を初期化．
  (*time) = 0;

  // 時刻リストが空なら，Wait時間は0秒．
  if (time_list_.empty()) {
    (*time) = 0;
    return true;
  }

  // 実際にかかった時間を求める．
#if defined DXLIB_COMPILE
  int actually_took_time = GetNowCount() - time_list_.back();
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  int actually_took_time =
      static_cast<int>(s3d::Time::GetMillisec()) - time_list_.back();
#endif  // defined DXLIB_COMPILE

  // 計算上かかるべき時間 - 実際にかかった時間　はすなわち待つべき時間．
  int wait_time = one_frame_time_ - actually_took_time;

  if (wait_time >= 0) {
    // 待ち時間が正の値であるとき，
    // (つまり，かかるべき時間より実際にかかった時間が小さい時)はそのまま値を返す．

    (*time) = wait_time;
    return true;
  } else {
    // 待ち時間が負の値であるとき．

    if (static_cast<int>(abs(wait_time)) < one_frame_time_) {
      // １フレーム以上遅れていないならば，処理を行う．
      return false;
    }
  }

  // どれにも引っかからなかった場合０を返す．
  (*time) = 0;
  return true;
}

bool FpsController::TargetFpsIsValid() const {
  // マイナスの値は許容しない．
  if (target_fps_value_ <= 0) {
    return false;
  }

  // １秒間に１フレーム以上は許容しない．
  if (target_fps_value_ > 60) {
    return false;
  }

  return true;
}

}  // namespace mytetris
