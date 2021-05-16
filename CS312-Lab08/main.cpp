#include <iostream>

const int SCR_WIDTH = 256;
const int SCR_HEIGHT = 256;

int main() {
  std::cout << "P3\n" << SCR_WIDTH << ' ' << SCR_HEIGHT << "\n255\n";
  for (int j = SCR_HEIGHT - 1; j >= 0; --j) {
    // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < SCR_WIDTH; ++i) {
      auto r = double(i) / (SCR_WIDTH - 1);
      auto g = double(j) / (SCR_HEIGHT - 1);
      auto b = 0.25;
      int ir = static_cast<int>(255.999 * r);
      int ig = static_cast<int>(255.999 * g);
      int ib = static_cast<int>(255.999 * b);
      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  // std::cerr << "\nDone.\n";
}
