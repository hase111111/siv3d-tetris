#pragma once

class Define {
 public:
  const static int WIN_SIZEX;
  const static int WIN_SIZEY;

  const static int MINO_SIZE;
  const static int MINO_FALLING_COUNT;
  const static int MINO_ROCK_COUNT;

  enum { FIELD_SIZEX = 12, FIELD_SIZEY = 24 };

  const static int FIELD_LEFTX;
  const static int FIELD_UPPERY;

 private:
  Define() = delete;
};