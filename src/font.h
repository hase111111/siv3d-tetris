
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

// �z�Q�Ƃ�h�����߂̑O���錾.
class FontView;

//! @brief �����̕`����s�����߂̃N���X.
//! @details
//! ��萳�m�ɂ́Cint�^�̃n���h���Ńt�H���g�A�Z�b�g���Ǘ����� DxLib ��, Font
//! �N���X�ŊǗ����� Siv3D �����b�p���ċ��ʂ̃C���^�[�t�F�[�X��񋟂���N���X.
class Font final {
 public:
  Font() = delete;

#if defined DXLIB_COMPILE

  //! @brief �t�H���g�t�@�C�������[�h���� Font �N���X�̃C���X�^���X�𐶐�����.
  //! @param file_name �t�H���g�t�@�C���̃p�X. ���[�h�Ɏ��s����ƃA�T�[�g.
  Font(const std::string &file_name);

#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

  //! @brief �t�H���g�t�@�C�������[�h���� Font �N���X�̃C���X�^���X�𐶐�����.
  //! @param file_name �t�H���g�t�@�C���̃p�X.
  //! @param font_size �t�H���g�T�C�Y.
  Font(const std::string &file_name, int font_size);

#endif  // defined DXLIB_COMPILE

  // �R�s�[�֎~.
  // �n���h����������Ă���ꍇ�� FontView �o�R�ōs��.
  Font(const Font &) = delete;
  Font &operator=(const Font &) = delete;

  // ���[�u�͋���.
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
