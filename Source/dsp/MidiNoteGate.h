#pragma once
#include <array>
#include <cstdint>
#include <cstddef>

namespace skell::dsp {
// Tracks MIDI note gates across blocks and channels without allocations.
// The first pressed key opens a gap; the final released key closes it.
// Duplicate note-ons and unmatched note-offs cannot corrupt the count.
class MidiNoteGate final {
public:
  enum class Edge : std::uint8_t { none, opened, closed };
  void reset() noexcept { held.fill(0); count=0; }
  int activeCount() const noexcept { return count; }
  Edge processRaw(std::uint8_t status, std::uint8_t pitch,
                  std::uint8_t velocity) noexcept {
    const auto type=std::uint8_t(status & 0xf0);
    if (pitch >= 128 || (type != 0x80 && type != 0x90)) return Edge::none;
    const bool on=type==0x90 && velocity!=0;
    auto& active=held[std::size_t(status & 0x0f)*128u+pitch];
    if(on){
      if(active) return Edge::none;
      active=1;
      return ++count==1 ? Edge::opened : Edge::none;
    }
    if(!active) return Edge::none;
    active=0;
    return --count==0 ? Edge::closed : Edge::none;
  }
private:
  std::array<std::uint8_t,16*128> held{};
  int count=0;
};
} // namespace skell::dsp
