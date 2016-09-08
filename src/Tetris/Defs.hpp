#ifndef TETRIS_DEFS_HPP_
#define TETRIS_DEFS_HPP_

#include <memory>
#include <array>

namespace tetris {

template <typename T, std::size_t I, std::size_t J>
using Matrix = std::array< std::array<T, J>, I>;

template <typename T, std::size_t N>
using PtrArray = std::array<std::unique_ptr<T>, N>;

} /* namespace tetris */
#endif /* TETRIS_DEFS_HPP_ */
