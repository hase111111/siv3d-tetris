//! @file game_const.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris::game_const {

// 4:3 �̉𑜓x���`����D

static constexpr int kResolutionX = 640;
static constexpr int kResolutionY = 480;
static constexpr float kResolutionXF = static_cast<float>(kResolutionX);
static constexpr float kResolutionYF = static_cast<float>(kResolutionY);

//! @brief ���̃Q�[����1280x720����Ƀf�U�C������Ă��邽�߁C
//! ���̉𑜓x�ɑ΂���䗦���`����D
static constexpr float kResolutionEx = kResolutionXF / 1280.f;

static constexpr char kWindowTitle[] = "Tetris";

static_assert(kResolutionX % 16 == 0,
              "The resolution X must be a multiple of 16.");
static_assert(kResolutionY % 16 == 0,
              "The resolution Y must be a multiple of 16.");
static_assert(kResolutionX * 3 == kResolutionY * 4,
              "The resolution must be 4:3 aspect ratio.");

}  // namespace mytetris::game_const
