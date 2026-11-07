#pragma once
#include <array>
#include <atomic>
#include <cstdint>
#include <algorithm>
namespace skell::dsp {
struct MappedGap { double from=0,to=0; };
// Single writer (audio thread), atomic consumers (UI + host state save).
class GapMap {
public:
  static constexpr int capacity=2048;
  void clear() noexcept { count.store(0,std::memory_order_release); }
  int size() const noexcept { return count.load(std::memory_order_acquire); }
  bool append(double from, double to) noexcept {
    if (!(to>from) || from<0) return false;
    const int n=count.load(std::memory_order_relaxed);
    if (n>=capacity) return false;
    begins[size_t(n)].store(from,std::memory_order_relaxed);
    ends[size_t(n)].store(to,std::memory_order_relaxed);
    count.store(n+1,std::memory_order_release);
    return true;
  }
  MappedGap get(int index) const noexcept {
    if(index<0 || index>=size()) return {};
    return {begins[size_t(index)].load(std::memory_order_relaxed),ends[size_t(index)].load(std::memory_order_relaxed)};
  }
  void replace(int index, MappedGap value) noexcept {
    if(index>=0 && index<size() && value.to>value.from) {
      begins[size_t(index)].store(value.from,std::memory_order_release);
      ends[size_t(index)].store(value.to,std::memory_order_release);
    }
  }
  void erase(int index) noexcept {
    int n=size(); if(index<0 || index>=n) return;
    for(int i=index;i<n-1;++i) { auto v=get(i+1); begins[size_t(i)].store(v.from); ends[size_t(i)].store(v.to); }
    count.store(n-1,std::memory_order_release);
  }
private:
  std::array<std::atomic<double>,capacity> begins{},ends{};
  std::atomic<int> count{0};
};
}
