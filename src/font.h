
//! @file font.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "render_anchor.h"

namespace mytetris {

// 循環参照を防ぐための前方宣言.
class FontView;

//! @brief 文字の描画を行うためのクラス.
//! @details
//! より正確には，int型のハンドルでフォントアセットを管理する DxLib と, Font
//! クラスで管理する Siv3D をラッパして共通のインターフェースを提供するクラス.
class Font final {
 public:
  Font() = delete;

#if defined DXLIB_COMPILE

  //! @brief フォントファイルをロードして Font クラスのインスタンスを生成する.
  //! @param file_name フォントファイルのパス. ロードに失敗するとアサート.
  Font(const std::string &file_name);

#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

  //! @brief フォントファイルをロードして Font クラスのインスタンスを生成する.
  //! @param file_name フォントファイルのパス.
  //! @param font_size フォントサイズ.
  Font(const std::string &file_name, int font_size);

#endif  // defined DXLIB_COMPILE

  // コピー禁止.
  // ハンドルをもらってくる場合は FontView 経由で行う.
  Font(const Font &) = delete;
  Font &operator=(const Font &) = delete;

  // ムーブは許可.
  Font(Font &&) = default;

  ~Font();

  void Draw(float x, float y, RenderAnchor anchor,
            const std::string &str) const;

  [[nodiscard]] inline static int GetCount() { return count_; }

  FontView GetView() const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor, int width,
                                    int height) const;

#if defined DXLIB_COMPILE
  inline int GetRawHandle() const { return handle_; }
  const int handle_;
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  inline const std::string &GetRawHandle() const { return handle_; }
  const std::string handle_;
#endif  // defined DXLIB_COMPILE

  const int font_size_;
  static int count_;

  friend class FontView;
};

}  // namespace mytetris
