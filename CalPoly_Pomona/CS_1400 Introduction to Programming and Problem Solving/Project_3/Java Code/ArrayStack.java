public class ArrayStack{

    private int arraySize;
    private int currentPosition;
    private int count;
    private char[] store;

    /**
     * Constructor with no parameters designed to initialize fields to default values, and instantiate a new int array of size ten.
     * 
     * @Param:  NONE
     * @Return: NONE
     */
    public ArrayStack(){
        currentPosition = 0;
        count = 0;
        arraySize = 10;
        store = new char[arraySize];

    }// END OF ArrayStack()

    /**
     * Method designed to insert an integer value onto top of a stack array.
     * 
     * If the array is full, then a call to the resizeArray method will be performed and newEntry will then be assigned to the 
     *     top of the newly sized stack array. If the array is NOT full, then the newEntry will be assigned to the top of the array.
     * 
     * @Param:  newEntry  Integer value that is pushed onto the stack
     * @Return: N/A
     */
    public void push(char newEntry){
        if(count == arraySize){
            resizeArray(arraySize, store);
            store[currentPosition++] = newEntry;
            count++;
        }
        else{
            store[currentPosition++] = newEntry;
            count++;
        }
    }// END OF push()

    /**
     * Method designed to remove and return the top element of a stack array.
     * 
     * If the stack is empty, then an exception will be thrown. Else top element is
     * assigned to a local variable and returned, and the index of the stack array
     * is decremented.
     * 
     * @exception: Exception           If the stack is empty before attemping the
     *                                 pop operation, then the execption will be
     *                                 thrown.
     * @Param: NONE
     * @Return: topElement Local variable assigned the value of the top element of
     *          the stack.
     */
    public char pop() throws Exception {
        if( isEmpty() )
            throw new Exception("Empty Stack Array");
        else{
            char topElement;
            topElement = store[currentPosition - 1];
            store[--currentPosition] = 0;
            count--;
            return topElement; 
        }
    }// END OF pop()

    /**
     * Method designed to view the top element of a stack array without removal from
     * the stack.
     * 
     * If the stack is empty, then an exception will be thrown. Else top element is
     * returned using a local variable.
     * 
     * @exception: Exception           If the stack is empty before attemping the
     *                                 peek operation, then the execption will be
     *                                 thrown.
     * @Param: NONE
     * @Return: lastElement Local variable assigned the value of the top element of
     *          the stack.
     */
    public char peek() throws Exception {
        if( isEmpty() )
            throw new Exception("Empty Stack Array");
        else{
            char lastElement;
            lastElement = store[currentPosition - 1];
            return lastElement;
        }
    }// END OF peek()

    /**
     * Method designed to check if a stack array is empty. 
     * 
     * If count = 0 then return true, else return false.
     * 
     * @Param:  NONE
     * @Return: true/false  returns boolean value of true or false depending on condition of the count field.
     */
    public boolean isEmpty(){
        if (count == 0)
            return true;
        else
            return false;  

    }// END OF isEmpty()

    /**
     * Method designed to loop through the stack array and assign a value of zero to
     * each index of the stack array. The method also assigns the value of zero to
     * the fields currentPosition and count.
     *
     * @exception: Exception           If the stack is empty before attemping the
     *                                 clear operation, then the execption will be
     *                                 thrown.
     * @Param: NONE
     * @Return: N/A
     */
    public void clear() throws Exception {
        if( isEmpty() )
            throw new Exception("Empty Stack Array");
        else{
            for (int index = 0; index < currentPosition; index++)
                store[index] = 0;            
            
            currentPosition = 0;
            count = 0;
        }
    }// END OF clear()

    /**
     * Method designed to double the size of the stack array. The method will call the copyArray to copy the elements onto a larger
     *     stack array and assign the store reference to this new stack array.
     * 
     * @Param:  oldSize     The current size of the array that is to be doubled.
     * @Param:  oldStore[]  The reference to the current stack array.
     * @Return: N/A
     */
    private void resizeArray(int oldSize, char[] oldStore){
        int newSize = 2*oldSize;
        store = copyArray(oldStore, newSize);
        arraySize = newSize;   

    }// END OF resizeArray()

    /**
     * Method designed to copy the elements of the incoming array into a larger array and return the reference to the larger array.
     * 
     * @Param:  oldSize[]   The passed array that is to be copied from.
     * @Param:  newSize     The size of the new array.
     * @Return: tempStore   The reference to the new larger array.
     */
    private char[] copyArray(char[] oldStore, int newSize){
        char[] tempStore = new char[newSize];
        for(int index = 0; index < currentPosition; index++)
            tempStore[index] = oldStore[index];
        
        return tempStore;

    }// END OF copyArray()

} // END OF CLASS ArrayStack