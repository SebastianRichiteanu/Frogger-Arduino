#pragma once

// wrapper for integral types, adding bit-manipulation operations.
template <typename I>
struct Bitfield {
  I value;

  operator I() const { return value; }

  // gets the value of a bit.
  bool get(byte position) const { return value & (I(1) << position); }

  // sets the value of a bit to the `value` parameter.
  void set(byte position, bool value) {
    if (value) {
      set(position);
    } else {
      clear(position);
    }
  }

  // sets the value of a bit to `true`.
  void set(byte position) { value |= (I(1) << position); }

  // resets the value of a bit to `false`.
  void clear(byte position) { value &= ~(I(1) << position); }
};
