
//! @file resource_container.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <map>
#include <memory>
#include <string>

#include "font.h"
#include "font_view.h"
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
  void RegisterTexture(const std::string& name,
                       std::unique_ptr<const Texture>&& texture);

  //! @brief フォントを受け取り登録する.
  //! @param[in] name フォントのキー.
  //! この値が重複している場合Assertが発生する.
  //! @param[in] font フォントのデータ.
  void RegisterFont(const std::string& name,
                    std::unique_ptr<const Font>&& font);

  //! @brief 登録したテクスチャを取得する.
  //! テクスチャの実態はこのクラスのみで管理されるので，
  //! 取得できるのは参照の TextureView である.
  //! キーが存在しない場合は Assert が発生する.
  //! @param[in] name 取得するテクスチャのキー.
  //! @return 取得したテクスチャの参照.
  TextureView GetTexture(const std::string& name) const;

  //! @brief 登録したフォントを取得する.
  //! フォントの実態はこのクラスのみで管理されるので，
  //! 取得できるのは参照の FontView である.
  //! キーが存在しない場合は Assert が発生する.
  //! @param[in] name 取得するフォントのキー.
  //! @return 取得したフォントの参照.
  FontView GetFont(const std::string& name) const;

  //! @brief テクスチャが登録されているか確認する.
  //! @return true: 登録されている, false: 登録されていない
  inline bool HasTexture(const std::string& name) const {
    return textures.find(name) != textures.end();
  }

  //! @brief フォントが登録されているか確認する.
  //! @return true: 登録されている, false: 登録されていない
  inline bool HasFont(const std::string& name) const {
    return fonts.find(name) != fonts.end();
  }

  //! @brief 登録したテクスチャを削除する.
  //! 削除した後，GetTexture()で取得した TextureRef は無効になるので注意.
  //! キーが存在しない場合は何もしない.
  //! @param[in] name 削除するテクスチャのキー.
  void UnloadTexture(const std::string& name);

  //! @brief 登録したフォントを削除する.
  //! 削除した後，GetFont()で取得した FontRef は無効になるので注意.
  //! キーが存在しない場合は何もしない.
  void UnloadFont(const std::string& name);

 private:
  std::map<std::string, std::unique_ptr<const Texture>> textures;
  std::map<std::string, std::unique_ptr<const Font>> fonts;
};

}  // namespace mytetris