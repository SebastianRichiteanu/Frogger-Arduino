#pragma once

class Matrix {
  public:
    static const byte rows = 8, columns = 8;

    void setRow(byte row, byte rowValue);
    void set(byte row, byte column, byte value);
    void setEffect(byte matr[]);

    void hammerEffect();
    void cupEffect();
    void heartEffect();
    void happyFace();
    void sadFace();

    void clear();
    void fill();
};

extern Matrix matrix;
