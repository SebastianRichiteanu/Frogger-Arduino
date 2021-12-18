#pragma once

// swap function created for highscores list sorting
template <typename T>
void swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
};
