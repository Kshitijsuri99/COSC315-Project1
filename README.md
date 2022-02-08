# COSC315-Project1

Team Members:
Florencia Chomski, Ahmad Raza Jamal, Kshitij Suri
 
### Contributions
All team members contributed to the success of this project. 

**For Part 1 (Use of fork and exec)**
<br/>
Florencia contributed majorly on researching about the functions and how they work, whereas Kshitij worked on testing and checking if the code runs perfectly and the execution of the code is correct. Jamal worked on implementing the code. 
<br/><br/>
**For Part 2 (Parallel and Sequential Execution)**
<br/>
Jamal contributed majorly on researching about the functions and how they work, whereas Florencia worked on testing and checking if the code runs perfectly and the execution of the code is correct. Kshitij worked on implementing the code. 
<br/><br/>
**For Part 3 (Process Timeouts)**
Kshitij contributed majorly on researching about the functions and how they work, whereas Jamal worked on testing and checking if the code runs perfectly and the execution of the code is correct. Florencia worked on implementing the code.
<br/><br/>
**For Part 4 (Code Structure)**
Every team member mostly structured their own code but we all followed a strict coding standard which we developed ourselves which helped code maintainability, readability and integrity.
<br/><br/>
**For Part 5 (Code Comment)**
All the team members added comments in their code for better understanding of the code helping with readability and maintainability.
<br/><br/>
**For Part 6 (Design Document)** 
All the team members had a meeting and contributed to the design document by explaining and wording the logic behind the code.

**Design Choices**
<br/><br/>
For the sequential implementation, a child process is created “count” times using the fork() method. The program continues to call fork() until the program exits to the parent process (fork returns >0) or it fails (fork returns -1). Thus the process runs “count” times, sequentially.

For parallel, the pthread() function is used to create individual threads for the children system calls. This will create the number of threads as specified by the count. Each thread will have a unique id which makes each child identifiable. The threads are run for all the children and once they are all done running, the parent process is run using pthread_join() fn. The thread needs to be passed a struct, as data to the function parameter, which will provide the function parallelThreadsFn() all the necessary data it needs to execute the children. 

**Sample Output**

![parallel and sequential outputs](https://user-images.githubusercontent.com/33037741/152927177-dc2a88e1-82dd-4652-9108-e6f301e6934d.png)


