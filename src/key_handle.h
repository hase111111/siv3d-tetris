#pragma once

#include <string>
#include <vector>

namespace mytetris {

enum class KeyHandle : int {
  kA = 0x1E,
  kB = 0x30,
  kC = 0x2E,
  kD = 0x20,
  kE = 0x12,
  kF = 0x21,
  kG = 0x22,
  kH = 0x23,
  kI = 0x17,
  kJ = 0x24,
  kK = 0x25,
  kL = 0x26,
  kM = 0x32,
  kN = 0x31,
  kO = 0x18,
  kP = 0x19,
  kQ = 0x10,
  kR = 0x13,
  kS = 0x1F,
  kT = 0x14,
  kU = 0x16,
  kV = 0x2F,
  kW = 0x11,
  kX = 0x2D,
  kY = 0x15,
  kZ = 0x2C,
  kLShift = 0x2A,
  kRShift = 0x36,
  kLControl = 0x1D,
  kRControl = 0x9D,
  kLAlt = 0x38,
  kRAlt = 0xB8,
  kEscape = 0x01,
  kSpace = 0x039,
  kLeft = 0xCB,
  kUp = 0xC8,
  kRight = 0xCD,
  kDown = 0xD0,
  kDelete = 0xD3,
  kMinus = 0x0C,      // -
  kPrevTrack = 0x90,  // ^
  kYen = 0x7D,        // ￥
  kAt = 0x91,         // ＠
  kLBracket = 0x1A,   // ［
  kRBracket = 0x1B,   // ］
  kSemicolon = 0x27,  // ；
  kColon = 0x92,      // ：
  kComma = 0x33,      // ,
  kPeriod = 0x34,     // .
  kSlash = 0x35,      // /
  kEnter = 0x1C,
  k0 = 0x0B,
  k1 = 0x02,
  k2 = 0x03,
  k3 = 0x04,
  k4 = 0x05,
  k5 = 0x06,
  k6 = 0x07,
  k7 = 0x08,
  k8 = 0x09,
  k9 = 0x0A,
  kTab = 0x0F,
  kBack = 0x0E,
};

inline const std::vector<KeyHandle> key_list{
    KeyHandle::kA,         KeyHandle::kB,         KeyHandle::kC,
    KeyHandle::kD,         KeyHandle::kE,         KeyHandle::kF,
    KeyHandle::kG,         KeyHandle::kH,         KeyHandle::kI,
    KeyHandle::kJ,         KeyHandle::kK,         KeyHandle::kL,
    KeyHandle::kM,         KeyHandle::kN,         KeyHandle::kO,
    KeyHandle::kP,         KeyHandle::kQ,         KeyHandle::kR,
    KeyHandle::kS,         KeyHandle::kT,         KeyHandle::kU,
    KeyHandle::kV,         KeyHandle::kW,         KeyHandle::kX,
    KeyHandle::kY,         KeyHandle::kZ,         KeyHandle::kLShift,
    KeyHandle::kRShift,    KeyHandle::kLControl,  KeyHandle::kRControl,
    KeyHandle::kLAlt,      KeyHandle::kRAlt,      KeyHandle::kEscape,
    KeyHandle::kSpace,     KeyHandle::kLeft,      KeyHandle::kUp,
    KeyHandle::kRight,     KeyHandle::kDown,      KeyHandle::kDelete,
    KeyHandle::kMinus,     KeyHandle::kPrevTrack, KeyHandle::kYen,
    KeyHandle::kAt,        KeyHandle::kLBracket,  KeyHandle::kRBracket,
    KeyHandle::kSemicolon, KeyHandle::kColon,     KeyHandle::kComma,
    KeyHandle::kPeriod,    KeyHandle::kSlash,     KeyHandle::kEnter,
    KeyHandle::k0,         KeyHandle::k1,         KeyHandle::k2,
    KeyHandle::k3,         KeyHandle::k4,         KeyHandle::k5,
    KeyHandle::k6,         KeyHandle::k7,         KeyHandle::k8,
    KeyHandle::k9,         KeyHandle::kTab,       KeyHandle::kBack,
};

inline std::string KeyHandleToString(const KeyHandle key_handle) {
  switch (key_handle) {
    case KeyHandle::kA:
      return "A";
    case KeyHandle::kB:
      return "B";
    case KeyHandle::kC:
      return "C";
    case KeyHandle::kD:
      return "D";
    case KeyHandle::kE:
      return "E";
    case KeyHandle::kF:
      return "F";
    case KeyHandle::kG:
      return "G";
    case KeyHandle::kH:
      return "H";
    case KeyHandle::kI:
      return "I";
    case KeyHandle::kJ:
      return "J";
    case KeyHandle::kK:
      return "K";
    case KeyHandle::kL:
      return "L";
    case KeyHandle::kM:
      return "M";
    case KeyHandle::kN:
      return "N";
    case KeyHandle::kO:
      return "O";
    case KeyHandle::kP:
      return "P";
    case KeyHandle::kQ:
      return "Q";
    case KeyHandle::kR:
      return "R";
    case KeyHandle::kS:
      return "S";
    case KeyHandle::kT:
      return "T";
    case KeyHandle::kU:
      return "U";
    case KeyHandle::kV:
      return "V";
    case KeyHandle::kW:
      return "W";
    case KeyHandle::kX:
      return "X";
    case KeyHandle::kY:
      return "Y";
    case KeyHandle::kZ:
      return "Z";
    case KeyHandle::kLShift:
      return "Left Shift";
    case KeyHandle::kRShift:
      return "Right Shift";
    case KeyHandle::kLControl:
      return "Left Control";
    case KeyHandle::kRControl:
      return "Right Control";
    case KeyHandle::kLAlt:
      return "Left Alt";
    case KeyHandle::kRAlt:
      return "Right Alt";
    case KeyHandle::kEscape:
      return "Escape";
    case KeyHandle::kSpace:
      return "Space";
    case KeyHandle::kLeft:
      return "Left Arrow";
    case KeyHandle::kUp:
      return "Up Arrow";
    case KeyHandle::kRight:
      return "Right Arrow";
    case KeyHandle::kDown:
      return "Down Arrow";
    case KeyHandle::kDelete:
      return "Delete";
    case KeyHandle::kMinus:
      return "-";
    case KeyHandle::kPrevTrack:
      return "^";
    case KeyHandle::kYen:
      return "\\";
    case KeyHandle::kAt:
      return "@";
    case KeyHandle::kLBracket:
      return "[";
    case KeyHandle::kRBracket:
      return "]";
    case KeyHandle::kSemicolon:
      return ";";
    case KeyHandle::kColon:
      return ":";
    case KeyHandle::kComma:
      return ",";
    case KeyHandle::kPeriod:
      return ".";
    case KeyHandle::kSlash:
      return "/";
    case KeyHandle::kEnter:
      return "Enter";
    case KeyHandle::k0:
      return "0";
    case KeyHandle::k1:
      return "1";
    case KeyHandle::k2:
      return "2";
    case KeyHandle::k3:
      return "3";
    case KeyHandle::k4:
      return "4";
    case KeyHandle::k5:
      return "5";
    case KeyHandle::k6:
      return "6";
    case KeyHandle::k7:
      return "7";
    case KeyHandle::k8:
      return "8";
    case KeyHandle::k9:
      return "9";
    case KeyHandle::kTab:
      return "Tab";
    case KeyHandle::kBack:
      return "Backspace";
  }

  return "Unknown";
}

}  // namespace mytetris
