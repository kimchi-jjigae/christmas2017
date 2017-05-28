# A template for initiating Spring and dophax based games.

## Set up project dependencies

1. ```git submodule update --init --recursive```


## Build dophax

1. ```cd dophax```
2. ```git submodule init```
3. ```git submodule update```
4. ```mkdir build```
5. ```cd build```
6. ```cmake ..```
7. ```make```

## Return to project folder

```cd ../..```

## Rename the project

1. Change `spring\_template` to the project name in CMakeLists.txt
3. Rename `spring\_template.dpx` to `project\_name.dpx`
4. Rename `spring\_template.hpp` to `project\_name.hpp`
5. Rename `spring\_template.cpp` to `project\_name.cpp`
6. :%s/SpringTemplate/ProjectName/g in both project_name.hpp and project_name.cpp
7. Change `#include "spring\_template.hpp"` to `#include "project\_name.hpp"` in project_name.cpp and main.cpp
8. Modify relevant variables in main.cpp
