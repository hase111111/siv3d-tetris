
//! @file resource_container.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <map>
#include <string>

#include "texture.h"
#include "texture_view.h"

namespace mytetris {

class ResourceContainer final {
 public:
  ResourceContainer() = default;
  ~ResourceContainer() = default;

  //! @brief テクスチャを受け取り登録する.
  //! @param[in] name テクスチャのキー.
  //! この値が重複している場合Assertが発生する.
  //! @param[in] texture テクスチャのデータ.
  void RegisterTexture(const std::string& name, Texture&& texture);

  //! @brief 登録したテクスチャを取得する.
  //! テクスチャはの実態はこのクラスのみで管理されるので，
  //! 取得できるのは参照の TextureView である.
  //! キーが存在しない場合は Assert が発生する.
  //! @param[in] name 取得するテクスチャのキー.
  //! @return 取得したテクスチャの参照.
  TextureView GetTexture(const std::string& name) const;

  //! @brief テクスチャが登録されているか確認する.
  //! @return true: 登録されている, false: 登録されていない
  inline bool HasTexture(const std::string& name) const {
    return textures.find(name) != textures.end();
  }

  //! @brief 登録したテクスチャを削除する.
  //! 削除した後，GetTexture()で取得した TextureRef は無効になるので注意.
  //! キーが存在しない場合は何もしない.
  //! @param[in] name 削除するテクスチャのキー.
  void UnloadTexture(const std::string& name);

 private:
  std::map<std::string, Texture> textures;
};

}  // namespace mytetris