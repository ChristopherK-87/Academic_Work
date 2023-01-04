public class Main {
    public static void main(String[] args) {        
        arrayStackPushTester(); 
        arrayStackPopTester(); 
        arrayStackPeekTester();
        arrayStackisEmptyTester(); 
        arrayStackClearTester();         

        arrayQueueEnqueueTester();
        arrayQueueDequeueTester();
        arrayQueueGetFrontTester();
        arrayQueueIsEmptyTester();
        arrayQueueClearTester();
    }

    
    public static void arrayStackPushTester(){ 
        ArrayStack myStack = new ArrayStack(); 
        String pass = "TEST SUCCESSFUL\n"; String fail = "TEST FAIL\n";
        String message = "CLASS: ArrayStack \nMETHOD: push() \nDESCRIPTION: Passing an int value of 10 to the above method to test for"
                        + "correct functionality by using the peek() method of the class for verification."; 
        System.out.println(message);
      
      myStack.push(10); if(myStack.peek() == 10) System.out.println(pass); else
      System.out.println(fail);
      
      String message2 =
      "CLASS: ArrayStack \nMETHOD: push() \nDESCRIPTION: Passing sequential int values starting at zero using a loop"
      + " fifteen times to test if array is resized correctly.";
      System.out.println(message2);
      
      int input; for(input = 0; input < 15; input++){ myStack.push(input);
      if(myStack.peek() != input){ System.out.println(fail); break; } } if(input ==
      10) System.out.println(pass); 
    }
      
      public static void arrayStackPopTester(){ ArrayStack myStack = new
      ArrayStack(); String pass = "TEST SUCCESSFUL\n"; String fail = "TEST FAIL\n";
      String message =
      "CLASS: ArrayStack \nMETHOD: pop() \nDESCRIPTION: Testing for the correct removal and return of the top element of"
      +
      " the stack. Using the push() method to insert a value to the stack and checking for equality using pop()."
      ; System.out.println(message);
      
      myStack.push(15); if(myStack.pop() == 15) System.out.println(pass); else
      System.out.println(fail); 
    }
      
      public static void arrayStackPeekTester(){ ArrayStack myStack = new
      ArrayStack(); String pass = "TEST SUCCESSFUL\n"; String fail = "TEST FAIL\n";
      String message =
      "CLASS: ArrayStack \nMETHOD: peek() \nDESCRIPTION: Testing for the correct return of the top element of"
      +
      " the stack. Using the push() method to insert a value to the stack and checking for equality using peek()."
      ; System.out.println(message);
      
      myStack.push(10); if(myStack.peek() == 10) System.out.println(pass); else
      System.out.println(fail); 
    }
      
      public static void arrayStackisEmptyTester(){ ArrayStack myStack = new
      ArrayStack(); String pass = "TEST SUCCESSFUL\n"; String fail = "TEST FAIL\n";
      String message =
      "CLASS: ArrayStack \nMETHOD: isEmpty() \nDESCRIPTION: Testing for the correct empty state of a stack array by instantiation"
      +
      " of an ArrayStack object. Array should have default values of zero and is thus empty."
      ; System.out.println(message);
      
      if(myStack.isEmpty()) System.out.println(pass); else
      System.out.println(fail); 
    }
     
      public static void arrayStackClearTester(){ ArrayStack myStack = new
      ArrayStack(); String pass = "TEST SUCCESSFUL\n"; String fail = "TEST FAIL\n";
      String message =
      "CLASS: ArrayStack \nMETHOD: clear() \nDESCRIPTION: Testing for the correct functionality of clearning a stack array. using"
      + " the isEmpty() method to verify."; System.out.println(message);
      
      myStack.push(10); 
      if(myStack.isEmpty()) 
        System.out.println(fail); 
    else{
      myStack.clear(); 
      if(myStack.isEmpty()) 
      System.out.println(pass); 
      else
      System.out.println(fail);
    }
    }

    public static void arrayQueueEnqueueTester() {
        ArrayQueue myQueue = new ArrayQueue();
        String pass = "TEST SUCCESSFUL\n";
        String fail = "TEST FAIL\n";
        String message = "CLASS: ArrayQueue \nMETHOD: enqueue() \nDESCRIPTION: Passing an int value of 10 to the above method to test for"
                + "correct functionality by using the getFront() method of the class for verification.";
        System.out.println(message);

        myQueue.enqueue(10);
        if (myQueue.getFront() == 10)
            System.out.println(pass);
        else
            System.out.println(fail);

        myQueue.clear();
        String message2 = "CLASS: ArrayQueue \nMETHOD: Enqueue() \nDESCRIPTION: Passing sequential int values starting at zero using a loop"
                + " five times. Then dequeue twice and use another loop seven times starting at 5 to check for proper cyclindrical logic.\n"
                + "Once finished, use a loop to dequeue my queue object to check for correct functionality.";

        System.out.println(message2);
        int input = 0;
        while (input < 5)
            myQueue.enqueue(input++);
        
        myQueue.dequeue();
        myQueue.dequeue();        
        while (input < 12)
            myQueue.enqueue(input++);
        
        int index = 0;
        int frontValue = 0;
        while (index < 10) {
            frontValue = myQueue.dequeue();            
            if (frontValue != (index +2) )
                System.out.print(fail);
            
            index++;            
        }
        System.out.println();
        if (index == 10)
            System.out.println(pass);
        
        String message3 = "CLASS: ArrayQueue \nMETHOD: Enqueue() \nDESCRIPTION: Passing sequential int values starting at zero using a loop"
                + " fifteen times. Then use a second loop to dequeue to test if array is resized correctly.";
        System.out.println(message3);
        
        for (input = 0; input < 15; input++)
            myQueue.enqueue(input);

        frontValue = 0;        
        for (index = 0; index < 15; index++) {
            frontValue = myQueue.dequeue();
            if (frontValue != index) {
                System.out.println(fail);
                break;
            }
        }
        if (frontValue == 14)
            System.out.println(pass);
    }

    public static void arrayQueueDequeueTester() {
        ArrayQueue myQueue = new ArrayQueue();
        String pass = "TEST SUCCESSFUL\n";
        String fail = "TEST FAIL\n";
        String message = "CLASS: ArrayQueue \nMETHOD: dequeue() \nDESCRIPTION: Testing for the correct removal and return of the front element of"
                + " the queue. Using the enqueue() method to insert a value to the queue and checking for equality using dequeue().";
        System.out.println(message);

        myQueue.enqueue(15);
        if (myQueue.dequeue() == 15)
            System.out.println(pass);
        else
            System.out.println(fail);
    }

    public static void arrayQueueGetFrontTester() {
        ArrayQueue myQueue = new ArrayQueue();
        String pass = "TEST SUCCESSFUL\n";
        String fail = "TEST FAIL\n";
        String message = "CLASS: ArrayQueue \nMETHOD: getFront() \nDESCRIPTION: Testing for the correct return of the front element of"
                + " the queue. Using the enqueue() method to insert a value to the queue and checking for equality using getFront().";
        System.out.println(message);

        myQueue.enqueue(10);
        if (myQueue.getFront() == 10)
            System.out.println(pass);
        else
            System.out.println(fail);
    }

    public static void arrayQueueIsEmptyTester() {
        ArrayQueue myQueue = new ArrayQueue();
        String pass = "TEST SUCCESSFUL\n";
        String fail = "TEST FAIL\n";
        String message = "CLASS: ArrayQueue \nMETHOD: isEmpty() \nDESCRIPTION: Testing for the correct empty state of a queue array by instantiation"
                + " of an ArrayQueue object. Array should have default values of zero and is thus empty.";
        System.out.println(message);

        if (myQueue.isEmpty())
            System.out.println(pass);
        else
            System.out.println(fail);
    }

    public static void arrayQueueClearTester() {
        ArrayQueue myQueue = new ArrayQueue();
        String pass = "TEST SUCCESSFUL\n";
        String fail = "TEST FAIL\n";
        String message = "CLASS: ArrayQueue \nMETHOD: clear() \nDESCRIPTION: Testing for the correct functionality of clearning a queue array. using"
                + " the isEmpty() method to verify.";
        System.out.println(message);

        myQueue.enqueue(10);
        if (myQueue.isEmpty())
            System.out.println(fail);
        else {
            myQueue.clear();
            if (myQueue.isEmpty())
                System.out.println(pass);
            else
                System.out.println(fail);
        }
    }

}