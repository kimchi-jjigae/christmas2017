# A template for initiating Spring and Dophax based games.

## Set up project dependencies

1. ```git submodule update --init --recursive```

## Rename the project

1. Change the `project_name` variable in the SConstruct file

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
