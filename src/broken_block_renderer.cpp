
//! @file broken_block_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "broken_block_renderer.h"

#include <random>

#include "game_const.h"
#include "my_assert.h"
#include "tetromino_render_util.h"

namespace mytetris {

BrokenBlockRenderer::BrokenBlockRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : block_textures_(GetBlockTextureMap(resource_container_ptr)) {}

void BrokenBlockRenderer::SetBrokenBlocks(const float x, const float y,
                                          const TetrominoColor color,
                                          const bool left) {
  // 乱数で散らす.
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis_x(5.0f, 10.0f);
  std::uniform_real_distribution<float> dis_y(-5.f, 5.f);

  const float vx = left ? -1 * dis_x(gen) : dis_x(gen);
  const float vy = -20.f + dis_y(gen);
  broken_blocks_.emplace_back(x, y, vx, vy, 0.f, color);
}

void BrokenBlockRenderer::Update() {
  for (auto& [x, y, vx, vy, rot, color] : broken_blocks_) {
    x += vx;
    y += vy;
    vy += 1.5f;  // 重力加速度
    rot += vx < 0.f ? -0.3f : 0.3f;
  }

  // 画面外に出たブロックを削除.
  broken_blocks_.erase(
      std::remove_if(broken_blocks_.begin(), broken_blocks_.end(),
                     [](const auto& block) {
                       return std::get<1>(block) >
                              GameConst::kResolutionY * 2.f;
                     }),
      broken_blocks_.end());
}

void BrokenBlockRenderer::Draw(const float offset_x,
                               const float offset_y) const {
  for (const auto& [x, y, _vx, _vy, rot, color] : broken_blocks_) {
    if (color == TetrominoColor::kNone) {
      continue;
    }

    auto it = block_textures_.find(color);
    if (it == block_textures_.end()) {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      continue;
    }
    it->second.DrawRotated(x + offset_x, y + offset_y, RenderAnchor::Center,
                           2.f, rot);
  }
}

}  // namespace mytetris
