add_executable(braces
    braces.cpp
)

add_executable(umap
    umap.cpp
)

add_executable(blocks
    blocks.cpp
)
target_link_libraries(blocks ${EXTRA_LIBS})
