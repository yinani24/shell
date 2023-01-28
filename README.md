#Report

##Phase 1:
We tried to convert the given code by Professor with the implementtion of system using fork, exec and wait method. To implement this we used the assistance of the lecture slides that guided in the process of understanding the 3 concepts and how they work in synchronization.

##Phase 2:
For this we tried to think about how in the prompt it was given that command may have white spaces. So we both thought about trying to remove the white spaces in the given command. So for this we approached by implementing strtok where we kept space as the delimiter. This way we were able to remove all the white spaces in the given command and separate all the components of the command into seprate tokens. But now we started thinking about how all the arguments for the commands will be stored. So we thought of a 2D array of a char where the commands and all the arguments will be stored in the 2D array for easy execution of execvp. But we also started thinking about when piping phase will come we would have multiple arguments that will mean that we would need to have multiple 2D arrays for each command in the phase. So we used the prompt as the resource and started searching for struct. We learned about structs from the W3School and then we implemented struct where we added the command and arguments as part of the struct. This way we thought having struct we will help us create instances of struct for each command to store its arguments. This we will be able to store each string of the command in a seprate arugement and this way we can easily pass to execvp for each command when we reach piping. 

##Phase 3:
For this phase we were thought of using chdir where we will be able to read
