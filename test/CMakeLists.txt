add_executable(test1
  main.c
)

target_link_libraries(test1
  CGrimoire
  Unity
)

add_test(suite_1_test test1)