
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
  // 明示的に move するために insert を使用.
  textures.insert(std::make_pair(name, std::move(texture)));
}

void ResourceContainer::RegisterFont(const std::string& name,
                                     std::unique_ptr<const Font>&& font) {
  DEBUG_ASSERT(fonts.find(name) == fonts.end(),
               std::format("Font with name {} already exists.", name));
  // 明示的に move するために insert を使用.
  fonts.insert(std::make_pair(name, std::move(font)));
}

TextureView ResourceContainer::GetTexture(const std::string& name) const {
  ASSERT(textures.find(name) != textures.end(),
         std::format("Texture with name {} does not exist.", name));
  return textures.at(name)->GetView();
}

FontView ResourceContainer::GetFont(const std::string& name) const {
  ASSERT(fonts.find(name) != fonts.end(),
         std::format("Font with name {} does not exist.", name));
  return fonts.at(name)->GetView();
}

void ResourceContainer::UnloadTexture(const std::string& name) {
  auto it = textures.find(name);
  if (it == textures.end()) {
    return;
  }
  textures.erase(it);
}

void ResourceContainer::UnloadFont(const std::string& name) {
  auto it = fonts.find(name);
  if (it == fonts.end()) {
    return;
  }
  fonts.erase(it);
}

}  // namespace mytetris
