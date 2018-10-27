#Working Method
Copy all the instructions in the for inc and for body block in vectors except the br statements and
ret statements and place them in the begining of the for body block and for end block(used to implement
epilogue).Also modified the if condition statement.

#Known Errors
If there is an conditional statement in the for body(except ternary) it wont work as I am using br
statements as end points in case of conditional statements the br statement for "for body" going to cond block goes inside the if body.(which is shown in the test case Failing if)
In case of non unit increment(positive cases considered) statemenets in the epilogue will not be correct but should be fine for normal for body . 
#References
 1. LLVM Doxygen mannual
 2. LLVM prebuilt passes
 3. Class Slides
 4. Slides from various universities like Aalto, CMU and Cornel.
 5. The e books in the google drive.
 6. #llvm on server OFTC(for general info and interacting with the community, didn't ask any assignment related questions).
# Methods tried to implement the pass(these are written before oct 5)
**Method 1**
Iterate through the contents of the loop and store the instructions in a vector except the alloca statements and at the end of the block increment the induction variable the paste the copied content ; repeat this UF times. Problems faced : how to get the temp variable names(#Number kind of variable) , that needs to be changed in the copied statements, how to properly insert the statements most of the time it was giving seg faults; took some code snippets from the llvm programmers manual but they were giving error that those things doesn't exist in the given namespace eg: Type :: int32Ty doesn't exist in the Type namespace.
**Method 2** 
Similar to method 1 but instead of incrementing the induction variable make a copy of it, increment that and pass it to the copied statements  and changing the loop condition to i<N/UF . Faced similar problems in this as in method 1. Generalising this for SSA form would also be a problem.
**Method 3**
Go through the loopUnroll pass in the llvm library and study it to  get some basic idea for a proper implementation but it was some what complex to understand in a short time.
**Method 4**
Found something like loop Cloning, block cloning, instruction cloning  that might be used with  scalar evolution to implement the pass , tried playing around with that, due to lack of some sample code faced problems in implementing that. 
**Method 5**
Tried playing around with the canonical form but wasn't able to do much. 

# General problems faced

 1. How to even get started with the coding part.
 2. Didn't find complete small llvm transformation pass code which would be plug and play so that I can play around with it while knowing which part of the code is causing error.
 3. Interpreting and reading the llvm doxygen mannual properly and efficiently.
 4. When I was using insertBefore() it wasn't showing any updates in the ll file,(which it shouldn't without explicit flags) that made me think it wasn't working properly.
