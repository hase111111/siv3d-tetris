
//! @file tetromino_render_util.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <map>
#include <memory>

#include "resource_container.h"
#include "tetromino.h"
#include "tetromino_color.h"
#include "texture_view.h"

namespace mytetris {

std::map<TetrominoColor, TextureView> GetBlockTextureMap(
    const std::shared_ptr<const ResourceContainer> resource_container_ptr);

void DrawTetromino(const Tetromino& tetromino, const TextureView& texture,
                   float render_x, float render_y, float alpha,
                   float block_size);

void DrawTetrominoCenter(const Tetromino& tetromino, const TextureView& texture,
                         float render_x, float render_y, float alpha,
                         float block_size);

}  // namespace mytetris
