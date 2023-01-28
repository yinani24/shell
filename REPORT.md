# Report

In this class, we are going to code all of our projects in C language. So, we 
decided to first brush up on our coding skills by reviewing online resources 
like GNU C library, geeksforgeeks. And then, we read the prompt and created a 
gameplan on how to go about the project. We set deadlines for each phase and 
tried our best to abide by it. We also watched the professor's lectures to 
get the idea of the key concepts used in the projects. 

## Phase 1:
We tried to convert the given code by Professor with the implementation of 
system using fork, exec and wait method. To implement this we used the 
assistance of the lecture slides that guided us in the process of 
understanding the 3 concepts and how they work in synchronization.

## Phase 2:
For this we tried to think about how in the prompt it was given that command 
may have white spaces.So we both thought about trying to remove the white 
spaces in the given command. So for this we approached by implementing strtok 
where we kept space as the delimiter. This way we were able to remove all the 
white spaces in the given command and separate all the components of the
command into seprate tokens. But now we started thinking about how all the 
arguments for the commands will be stored. So we thought of a 2D array of a 
char where the commands and all the arguments will be stored in the 2D array 
for easy execution of execvp. But we also started thinking about when 
piping phase will come we would have multiple arguments that will mean 
that we would need to have multiple 2D arrays for each command in the 
phase. So we used the prompt as the resource and started searching
for struct. We learned about structs from the W3School and then we implemented 
struct where we added the command and arguments as char arrays as part of the 
struct. This way a struct we will help us create instances of each command to
store its arguments and command. This we will be able to store each string of the
command in a seprate arugement and can easily pass to execvp for each command
when we reach piping. We also thought of using malloc for storing each argument
so we don't to worry about pointers and dereferncing at each point. This way we
can easily pass to the other functions as well. 

## Phase 3:
For this phase we thought of using chdir where we will be searching for cd in 
the command from the instance of our struct. We thought of using the slides to 
understand chdir and we looked throught eh documentation to understand 
the concept. Then we checked if the command had cd in it and then we 
moved around the cd with chdir. We also created one instance of directory 
in stuct so if we see cd in the command we store the directory name. 
This directory name we passed in chdir to check for our directory.

## Phase 4:
For this phase we started thinking of parsing the string based on the '>' 
symbol. We will use strtok for separating the command based on '>'. 
Then we thought of using the first string and parsing it with our 
already created parser. This way our parser will separate our command 
into different arguments which will be handled by execvp in the int 
main. Then the file name will be stored in another variable which will 
be part of struct. So for each instance of struct there will be 
a file when it comes to parsing. But we faced with lot of bugs with this where 
we were stuck with this for 2-3 days. When we strtoked the string based 
on the '>' symbol it continued on the strtok stream. This was happening 
because we copied the first argument of the token and passed it to our 
parser function. The function continued the strtok stream we created 
earlier and further parsed and messed with our original string. 
So to solve this error we decided to store each of the tokens. 
We then decided to send these saved tokens into the parser which will
then be saved on the instances. 
This way we were able to overcome the parsing error and were able to 
streamline our code. Then we changed the way our code where our 
whole command is checked for '>'. Then it is parsed into the struct 
instance. Then we used the slides to see how to operate the file 
operator and dup2 to open the file from the struct instance.

## Phase 5:
This phase was the hardest of all. We still arent sure if we were able to 
make it work completely till now. In this phase we first started 
thinking about counting the number of pipes. Then after counting the
number of pipes we allocated for each struct instance. 
Then we send the whole struct array to the parser function to parse 
each struct instance. Then we started looking into piping. This is 
where we started questioning the concepts. We left it for last 2 days 
and we got stuck with this. We tried to read the slides and watch the
lecture recordings available to understand how piping works in the 
class example. We were still stuck with it. Then we moved on to learning 
from the annoucement but both of us were having a hard time understanding 
what is going in the annoucement as well. After spending a day on this we 
were able to code something for the 2 pipes. We then tried clarifying our 
concepts again and again and understood somewhat of our code. We directly
started working with the for loop and didn't start with the 2 fork concept.
Then our code became extremely complicated with 2 pipes since we 
weren't able to connect the second command with first commands 
input and the third commands output. We tried several things 
but weren't able to solve it. Then we also faced the issue with 
waitpid which made it extremely complicated since we were 
trying to run it inside the child but then we tried to wait 
outside the for loop. This way some commands started working but 
some commands still have the error.

## Phase 6:
Then we started about appending where we started tweaking around 
in our caret_parser function which deals with parsing this symbol
 '>'. There we tried to search for double appending and update a 
variable in the instance of struct to make sure to append in the 
for loop. These small tweaking made everything work and then we 
started with the background working. For that we started by parsing
based on the end presence of '&' where we removed it from the 
commmand and processed all our previous processes. From there, 
we had to think about how the first process will run in the 
background while the promt shows up to accept the next process. 
We referred to the waitpid page in GNU C library and found out 
that WNOHANG will help execute this task because this makes waitpid
return immediately instead of waiting. From here, we made sure the 
prompt appears immediately whenever there is an '&' as the last 
token by incrementing and continuing to the next iteration of the 
loop. We make sure that we save the command so that we can print 
it whenever the termination occurs. In this way,we were able to
complete this task.  

## Programming Challenges Faced:
We had hard time finding the parsing errors since C implementation 
was confusing and tirseome for both of us. Then we had 
difficulty understanding the concept behind piping since forking 
and child-parent relation became  really confusing for both of 
us. We also had a problem with indedation since my vscode 
and my partner's vscode had different spacing. We were 
working on each other's laptop due to which the indendation
got messed up. We had to spend a considerable amount of time
at the end to fix that. But we were able to overcome all 
the challenges.

## Personal Challenges Faced:
We spent a lot of time working late at night to complete this assignment. 
Due to this, our health was not at its best. However, 
the topics covered in this project were very interesting 
which motivated us to push beyond our limits. Overall, 
we had a fun time coding this assignment and LEARNT A LOT. 

## Citations:
https://www.w3schools.com/c/c_structs.php
https://www.w3schools.in/c-programming/dynamic-memory-allocation
https://www.gnu.org/software/libc/manual/html_mono/libc.html#index-waitpid
https://www.geeksforgeeks.org/c-programming-language/
