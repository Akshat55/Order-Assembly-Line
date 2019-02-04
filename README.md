# Order-Assembly-Line


### Project Description
Assembly line simulation. Customer orders using processors that perform tasks of adding and removing specific items according to customer specifications and quality control inspections.

**Tasks** - handles each task of the assembly line  
**Customer Orders** - handles each customer order passing through the assembly line  
**Managers** - manages the tasks, customer orders and items passing through the assembly line  
**Assembly Line** - manages the processors that constitute the assembly line  
**Source** - executes the assembly line simulator for realistic data  


### Compilation & Exection:   
Navigate to the directory where the project resides using the CLI **(Using GCC - Everything has to be in the current file)** .    
  
**g++ \*.cpp -std=c++0x**  
  
This will create Order-Assembly-Line executable. Enter the following to run the executable:  
  
**Order-Assembly-Line "TaskList_Malformed.dat" "CustomerOrders_Malformed.dat" "ItemList_Malformed.dat" "|"**



### UML Diagram
![UML Diagram](/Images/UML.png)
