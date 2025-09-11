
//! @file my_assert.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <cassert>
#include <source_location>
#include <stdexcept>
#include <string>

namespace mytetris {

namespace assert_internal {

bool IsInitialized();

void ErrorAssert(const std::string& conditional_expression,
                 const std::string& error_mes, const std::string& file,
                 const std::string& func, const int line);

}  // namespace assert_internal

}  // namespace mytetris

//! @brief �G���[�����������Ƃ��ɃG���[���b�Z�[�W��\������D
//! @param expression �G���[�����������̎�(������)
//! @param error_mes �G���[���b�Z�[�W�D
#define MYTETRIS_INTERNAL_ERROR_MESSAGE(expression, error_mes)               \
  const std::source_location location = std::source_location::current();     \
  ::mytetris::assert_internal::ErrorAssert(                                  \
      expression, error_mes, location.file_name(), location.function_name(), \
      location.line());

#define ASSERT(expr, error_mes)                             \
  do {                                                      \
    if (!(!!(expr))) {                                      \
      if (!::mytetris::assert_internal::IsInitialized()) {  \
        assert(false && "DxLib is not initialized.");       \
      } else {                                              \
        const std::string expr_str = #expr;                 \
        const std::string message = error_mes;              \
        MYTETRIS_INTERNAL_ERROR_MESSAGE(expr_str, message); \
      }                                                     \
    }                                                       \
  } while (0)

#define ASSERT_NOT_NULL_PTR(ptr) ASSERT((ptr) != nullptr, "nullptr passed.")

#define ASSERT_MUST_NOT_REACH_HERE() \
  ASSERT(false, "This part is never reached.")

#ifdef _DEBUG

//! @brief �G���[�����������Ƃ��ɃG���[���b�Z�[�W��\������D
//! DxLib �̓�����~�߁C�Ǝ��̃G���[���b�Z�[�W��\������D
//! DxLib ������������Ă��Ȃ��ꍇ�́C��O�𓊂��邪�C���������Ăяo���Ȃ����ƁD
//! @param expr TRUE �ł��邱�Ƃ����҂�������
//! @param error_mes �G���[���b�Z�[�W
#define DEBUG_ASSERT(expr, error_mes) ASSERT(expr, error_mes)

#define DEBUG_ASSERT_NOT_NULL_PTR(ptr) \
  DEBUG_ASSERT((ptr) != nullptr, "nullptr passed.")

#define DEBUG_ASSERT_MUST_NOT_REACH_HERE() \
  DEBUG_ASSERT(false, "This part is never reached.")

#else

#define DEBUG_ASSERT(expr, error_mes) ((void)0)

#define DEBUG_ASSERT_NOT_NULL_PTR(ptr) ((void)0)

#define DEBUG_ASSERT_MUST_NOT_REACH_HERE() ((void)0)

#endif  // _DEBUG
