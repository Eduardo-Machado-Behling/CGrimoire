macro(test_component name)
  add_executable(test_${name}
    ${name}.c
  )

  target_link_libraries(test_${name}
    CGrimoire
    Unity
  )

  add_test(suite_${name} test_${name})  
endmacro(test_component)

test_component(array)
test_component(vector)
test_component(stack)
test_component(queue)
test_component(hashmap)
test_component(string)