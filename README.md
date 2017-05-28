# A template for initiating Spring and dophax based games.

## Set up project dependencies

1. ```git submodule update --init --recursive```

## Build dophax - With script

1. ```./build_dophax.sh```

## Build dophax - Manual version

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

## Change origin

If you cloned this from spring_template you probably want to change origin to a new remote git repo.

1. git remote set-url origin <URL TO REPO>

## If you want to clear out the old history, then follow these steps

1. Make a new commit with the renaming changes above and name it "Initial commit" or what you want.
2. ```git checkout --orphan temp <ID OF OUR NEW COMMIT> # create a new branch without parent history```
3. ```git commit -m "Initial commit" # create a first commit on this branch```
4. ```git rebase --onto temp <ID OF OUR NEW COMMIT> master # now rebase the part of master branch that we want to keep onto this branch```
5. ```git branch -D temp # delete the temp branch```
6. Now whenever you make a new commit, the old history will be gone. You must now push it with git push -f.
