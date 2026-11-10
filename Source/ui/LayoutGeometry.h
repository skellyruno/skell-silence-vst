#pragma once
#include <array>
#include <algorithm>

namespace skell::ui::Layout {
// Pixel rectangles in the 1200 x 760 design coordinate system. Component
// transforms are applied once, uniformly, by PluginEditor::resized().
struct Rect {int x,y,w,h;
  constexpr int right() const noexcept {return x+w;}
  constexpr int bottom() const noexcept {return y+h;}
};
inline constexpr int designWidth=1200,designHeight=760;
inline constexpr std::array<Rect,6> panels{{
  {0,0,1200,70},     // header
  {24,86,805,300},  // timeline
  {24,402,805,145}, // detector
  {846,86,330,461}, // instrument rack
  {24,563,805,190}, // rules (room for all 7 rows at reduced sizes)
  {846,563,330,190} // dynamics
}};
constexpr bool intersects(Rect a,Rect b) noexcept {
  return a.x<b.right() && b.x<a.right() && a.y<b.bottom() && b.y<a.bottom();
}
constexpr bool valid() noexcept {
  for(size_t i=0;i<panels.size();++i){
    auto r=panels[i];
    if(r.x<0 || r.y<0 || r.w<=0 || r.h<=0 || r.right()>designWidth || r.bottom()>designHeight)
      return false;
    for(size_t j=0;j<i;++j)if(intersects(r,panels[j]))return false;
  }
  return true;
}
static_assert(valid(),"Skell Silence panels must fit without overlapping");
}
