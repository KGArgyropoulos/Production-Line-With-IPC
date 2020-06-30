# Production Line Operation, using IPC (Inter-Process Communication)

The fitments move through 4 stages of a production line as shown below.
# Constructor -> Painter -> Controller -> Assembler
In each of these stages, every fitment stays for some time, which can be different, depending on the type of fitment. \
We have 3 types of fitments,hence 3 sections of production line and x(input) products created by each of them.\
The production line schema is shown above:
![alt text](https://github.com/KGArgyropoulos/Production-Line-With-IPC/blob/master/prodLine.png)

To achieve this, we use a model with **semaphores** and **shared memory**.\
More on the implementation techniques and the algorithm used later.

- Compilation: make
- Remove object files: make clean
- Execution: ./simulator x
	* where x is the number of the fitments in each section of the production
- Production line stages
	* Construction: This is the stage where the fitments get their form(type). This stage works as a general construction driver. Fitments are created at random time and section (type of fitment). When a fitment is made, it gets a random 4-digit id number.
	* Painting: This is the stage where the fitment get painted. There's only on paint shop, so the fitments take place one after another, depending on which came in first. Time needed for a fitment to complete its painting is same for fitments of the same type.
	* Control: This stage gets fitments ready for assemblement. Fitments get passed to the assembelement stage, when there is at least one of every type available. In other words, the final product is made from 1 fitment of typeA, 1 of typeB and 1 of typeC.When all 3 of them are in the controller's stage, then they can proceed to the assemblement. There's also a delay, similar to the paint shop's.
	* Assemblement: The product gets assigned a new id, resulting from the 3 ids of its components. The time spent there is also fixed.
- At the end of the program, the average delay for the paint shop and the average delay between the first fitment and the final product are calculated.