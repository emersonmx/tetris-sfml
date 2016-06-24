#ifndef TETRIS_DEFS_HPP_
#define TETRIS_DEFS_HPP_

#include <array>

namespace tetris {

template <typename T, std::size_t I, std::size_t J>
using Matrix = std::array< std::array<T, J>, I>;

} /* namespace tetris */
#endif /* TETRIS_DEFS_HPP_ */
