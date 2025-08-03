
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

  //! @brief �e�N�X�`�����󂯎��o�^����.
  //! @param[in] name �e�N�X�`���̃L�[.
  //! ���̒l���d�����Ă���ꍇAssert����������.
  //! @param[in] texture �e�N�X�`���̃f�[�^.
  void RegisterTexture(const std::string& name, Texture&& texture);

  //! @brief �o�^�����e�N�X�`�����擾����.
  //! �e�N�X�`���͂̎��Ԃ͂��̃N���X�݂̂ŊǗ������̂ŁC
  //! �擾�ł���͎̂Q�Ƃ� TextureView �ł���.
  //! �L�[�����݂��Ȃ��ꍇ�� Assert ����������.
  //! @param[in] name �擾����e�N�X�`���̃L�[.
  //! @return �擾�����e�N�X�`���̎Q��.
  TextureView GetTexture(const std::string& name) const;

  //! @brief �e�N�X�`�����o�^����Ă��邩�m�F����.
  //! @return true: �o�^����Ă���, false: �o�^����Ă��Ȃ�
  inline bool HasTexture(const std::string& name) const {
    return textures.find(name) != textures.end();
  }

  //! @brief �o�^�����e�N�X�`�����폜����.
  //! �폜������CGetTexture()�Ŏ擾���� TextureRef �͖����ɂȂ�̂Œ���.
  //! �L�[�����݂��Ȃ��ꍇ�͉������Ȃ�.
  //! @param[in] name �폜����e�N�X�`���̃L�[.
  void UnloadTexture(const std::string& name);

 private:
  std::map<std::string, Texture> textures;
};

}  // namespace mytetris