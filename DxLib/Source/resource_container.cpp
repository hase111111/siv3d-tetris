
//! @file resource_container.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "resource_container.h"

#include <format>

#include "my_assert.h"

namespace mytetris {

void ResourceContainer::RegisterTexture(
    const std::string& name, std::unique_ptr<const Texture>&& texture) {
  DEBUG_ASSERT(textures.find(name) == textures.end(),
               std::format("Texture with name {} already exists.", name));
  // –¾Ž¦“I‚É move ‚·‚é‚½‚ß‚É insert ‚ðŽg—p.
  textures.insert(std::make_pair(name, std::move(texture)));
}

TextureView ResourceContainer::GetTexture(const std::string& name) const {
  DEBUG_ASSERT(textures.find(name) != textures.end(),
               std::format("Texture with name {} does not exist.", name));
  return textures.at(name)->GetView();
}

void ResourceContainer::UnloadTexture(const std::string& name) {
  auto it = textures.find(name);
  if (it == textures.end()) {
    return;
  }
  textures.erase(it);
}

}  // namespace mytetris
