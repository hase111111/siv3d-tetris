#include "tetris_field_effect.h"

#include <Siv3D.hpp>
#include <random>
#include <set>

#include "my_assert.h"
namespace mytetris {

TetrisFieldEffect::TetrisFieldEffect(
    const std::shared_ptr<const TetrisLevel>& tetris_level_ptr)
    : tetris_level_ptr_(tetris_level_ptr) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_level_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_level_ptr_);

  ResetFieldEffects();
}

void TetrisFieldEffect::Update() {
  if (!is_active_) {
    return;
  }

  // カウントを進める.
  ++cnt_;

  UpdateEffect();

  if (last_total_clear_lines_ / 10 <
      tetris_level_ptr_->GetTotalClearLines() / 10) {
    // 10ラインごとにエフェクトを変更.
    ChangeEffect();

    ResetFieldEffects();
  }

  last_total_clear_lines_ = tetris_level_ptr_->GetTotalClearLines();
}

void TetrisFieldEffect::Reset() {
  // カウントをリセット.
  cnt_ = 0;

  ResetFieldEffects();
}

float TetrisFieldEffect::GetAlpha(const int x, const int y) const {
  if (x == 0 || x == TetrisField::kWidth - 1 || y == 0 ||
      y == TetrisField::kHeight - 1) {
    // 壁は常に不透明.
    return 1.0f;
  }

  return static_cast<float>(alpha_[x][y]);
}

std::pair<int, int> TetrisFieldEffect::GetDiff(const int x, const int y) const {
  if (x == 0 || x == TetrisField::kWidth - 1 || y == 0 ||
      y == TetrisField::kHeight - 1) {
    // 壁は不動.
    return {0, 0};
  }

  return {static_cast<int>(diff_[x][y].first),
          static_cast<int>(diff_[x][y].second)};
}

void TetrisFieldEffect::UpdateEffect() {
  switch (effect_type_) {
    case EffectType::kBlind: {
      Blind();
      break;
    }
    case EffectType::kBlink: {
      Blink();
      break;
    }
    case EffectType::kRandomBlind: {
      RandomBlind();
      break;
    }
    case EffectType::kRandomMove: {
      RandomMove();
      break;
    }
    case EffectType::kRandomShake: {
      RandomShake();
      break;
    }
    case EffectType::kSinMove: {
      SinMove();
      break;
    }
    case EffectType::kBlinkAndSinMove: {
      Blink();
      SinMove();
      break;
    }
    case EffectType::kBlinkAndShake: {
      Blink();
      RandomShake();
      break;
    }
    case EffectType::kRandomBlinkAndShake: {
      RandomBlind();
      RandomShake();
      break;
    }
    case EffectType::kRandomBlinkAndSin: {
      RandomBlind();
      SinMove();
      break;
    }
    case EffectType::kBlindAndRandomMove: {
      Blind();
      RandomMove();
      break;
    }
    case EffectType::kNone:
    default:
      break;
  }
}

void TetrisFieldEffect::Blind() {
  const float time = 60;
  const float alpha = cnt_ < time ? (time - cnt_) / time : 0.0f;
  for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 1; y < TetrisField::kHeight - 1; ++y) {
      alpha_[x][y] = alpha;
    }
  }
}

void TetrisFieldEffect::Blink() {
  const float time = 240.f;
  const float alpha = abs(cosf(cnt_ / time * 3.14159f * 2.f));
  for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 1; y < TetrisField::kHeight - 1; ++y) {
      alpha_[x][y] = alpha;
    }
  }
}

void TetrisFieldEffect::RandomBlind() {
  if (cnt_ < 15) {
    return;
  }

  for (int i{0}; i < 3; ++i) {
    // 適当に選んだマスの透明度を0.fに変える.
    std::random_device seed_gen;
    std::uint32_t seed = seed_gen();
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> dist_x(1, TetrisField::kWidth - 2);
    std::uniform_int_distribution<int> dist_y(1, TetrisField::kHeight - 2);
    const int x = dist_x(engine);
    const int y = dist_y(engine);
    alpha_[x][y] = (std::max)(0., alpha_[x][y] - 0.3);
  }
}

void TetrisFieldEffect::RandomShake() {
  if (cnt_ % 3 != 0) {
    return;
  }

  // -10.0 ~ 10.0 の範囲でランダムにシェイクする.
  std::random_device seed_gen;
  std::uint32_t seed = seed_gen();
  std::mt19937 engine(seed);
  std::uniform_real_distribution<double> dist(-10.0, 10.0);

  for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 1; y < TetrisField::kHeight - 1; ++y) {
      diff_[x][y] = {dist(engine), dist(engine)};
    }
  }
}

void TetrisFieldEffect::RandomMove() {
  if (cnt_ % 60 == 20) {
    std::random_device seed_gen;
    std::uint32_t seed = seed_gen();
    std::mt19937 engine(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
      for (int y = 1; y < TetrisField::kHeight - 1; ++y) {
        speed_[x][y] = {dist(engine), dist(engine)};
      }
    }
  }

  for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 1; y < TetrisField::kHeight - 1; ++y) {
      diff_[x][y].first += speed_[x][y].first;
      diff_[x][y].second += speed_[x][y].second;
    }
  }
}

void TetrisFieldEffect::SinMove() {
  for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 1; y < TetrisField::kHeight - 1; ++y) {
      diff_[x][y].first = 20.0 * std::sinf((cnt_ + x * 5 + y * 3) / 15.f);
      diff_[x][y].second = 20.0 * std::cosf((cnt_ + x * 5 + y * 3) / 15.f);
    }
  }
}

void TetrisFieldEffect::ChangeEffect() {
  // エフェクトをランダムに変更.
  std::random_device seed_gen;
  std::uint32_t seed = seed_gen();
  std::mt19937 engine(seed);
  const auto past = effect_type_;

  std::vector<EffectType> banned_effects;
  banned_effects.push_back(EffectType::kNone);
  banned_effects.push_back(EffectType::kSinMove);
  banned_effects.push_back(EffectType::kBlinkAndSinMove);
  banned_effects.push_back(EffectType::kRandomBlinkAndSin);

  while (true) {
    std::uniform_int_distribution<int> dist(
        0, static_cast<int>(EffectType::kNone) - 1);
    effect_type_ = static_cast<EffectType>(dist(engine));

    if (std::find(banned_effects.begin(), banned_effects.end(), effect_type_) ==
            banned_effects.end() &&
        effect_type_ != past) {
      break;
    }
  }
}

void TetrisFieldEffect::ResetFieldEffects() {
  // diff_, speed_ をリセット.
  for (int x = 0; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 0; y < TetrisField::kHeight - 1; ++y) {
      diff_[x][y] = {0, 0};
      speed_[x][y] = {0, 0};
      alpha_[x][y] = 1.0;
    }
  }
}

}  // namespace mytetris
