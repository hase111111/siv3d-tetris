//! @file game_const.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris::game_const {

// 4:3 の解像度を定義する．

static constexpr int kResolutionX = 960;
static constexpr int kResolutionY = 720;
static constexpr float kResolutionXF = static_cast<float>(kResolutionX);
static constexpr float kResolutionYF = static_cast<float>(kResolutionY);

//! @brief このゲームは1280x720を基準にデザインされているため，
//! その解像度に対する比率を定義する．
static constexpr float kResolutionEx = kResolutionXF / 1280.f;

static constexpr char kWindowTitle[] = "Tetris";

}  // namespace mytetris::game_const
