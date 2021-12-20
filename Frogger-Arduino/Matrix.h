#pragma once

class Matrix {
  public:
    static const byte rows = 8, columns = 8;

    void set(byte row, byte column, byte value);
    void setRow(byte row, byte rowValue);

    void clear();
    void fill();
    
    void setEffect(byte matr[]);
    void frogEffect();
    void cupEffect();
    void hammerEffect();
    void heartEffect();
    void happyFace();
    void sadFace();
};

extern Matrix matrix;
