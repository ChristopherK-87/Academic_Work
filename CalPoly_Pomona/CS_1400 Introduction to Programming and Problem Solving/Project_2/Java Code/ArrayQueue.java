public class ArrayQueue{

    private int arraySize;
    private int front;
    private int back;
    private int count;
    private int[] store;

    /**
     * Constructor with no parameters designed to initialize fields to default values, and instantiate a new int array of size ten.
     * 
     * @Param:  NONE
     * @Return: NONE
     */
    public ArrayQueue() {
        arraySize = 10;
        front = 0;
        back = 0;
        count = 0;
        store = new int[arraySize];
    }// END OF ArrayQueue()

    /**
     * Method designed to insert an integer value to the back of a queue array.
     * 
     * If the array is full, then a call to the resizeArray method will be performed and newEntry will then be assigned to the 
     *     back of the newly sized queue array. If the array is NOT full, then the newEntry will be assigned to the back of the array.
     * 
     * @Param:  newEntry  Integer value that is queue onto the back of the array.
     * @Return: NONE
     */
    public void enqueue(int newEntry){
        if(count == arraySize){
            resizeArray(arraySize, store);
            store[back % arraySize] = newEntry;
            back++;
            count++;
        }
        else{
            store[back % arraySize] = newEntry;
            back = (back + 1) % arraySize;
            count++;
        }
    }// END OF enqueue()

    /**
     * Method designed to remove and return the element of the front of the queue.
     * 
     If the queue is empty, then an exception will be thrown. Else the front element is assigned to a local variable and returned, and the
     *    index of the front of the array is incremented.
     * 
     * @exception: EmptyQueueException  If the queue is empty before attemping the dequeue operation, then the execption will be thrown.
     * @Param:     NONE
     * @Return:    firstElement         Local variable assigned the value of the first element of the queue.
     */
    public int dequeue(){
        if( isEmpty() )
            throw new EmptyQueueException();
        else{
            int firstElement;
            firstElement = store[front % arraySize];
            count--;
            front++;

            if(count == 0){
                front = 0;
                back = 0;
            }
            return firstElement;
        }
    }// END OF dequeue()

    /**
     * Method designed to view the first element of a queue array without removal from the queue.
     * 
     * If the queue is empty, then an exception will be thrown. Else the first element is returned using a local variable.
     * 
     * @exception: EmptyQueueException  If the queue is empty before attemping the getFront operation, then the execption will be thrown.
     * @Param:     NONE
     * @Return:    lastElement          Local variable assigned the value of the first element of the queue.
     */
    public int getFront(){
        if( isEmpty() )
            throw new EmptyQueueException();
        else{
            int firstElement;
            firstElement = store[front];       
            return firstElement;
        }
    }// END OF getFront()

    /**
     * Method designed to check if a queue array is empty. 
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
     * Method designed to loop through the queue array and assign a value of zero to each index of the queue array. The method 
     *     also assigns the value of zero to the fields front, back, and count.
     * 
     * @exception: EmptyQueueException  If the queue is empty before attemping the getFront operation, then the execption will be thrown.
     * @Param:     NONE
     * @Return:    N/A
     */
    public void clear(){
        if( isEmpty() )
            throw new EmptyQueueException();
        else{
            for (int index = 0; index < arraySize; index++)
                store[index] = 0;
            
            front = 0;
            back = 0;
            count = 0;
        }
    }// END OF clear()

    /**
     * Method designed to double the size of the queue array. The method will call the copyArray to copy the elements onto a larger
     *     queue array and assign the store reference to this new queue array.
     * 
     * @Param:  oldSize     The current size of the array that is to be doubled.
     * @Param:  oldStore[]  The reference to the current queue array.
     * @Return: N/A
     */
    private void resizeArray(int oldSize, int[] oldStore){
        int newSize = 2*oldSize;
        store = copyArray(oldStore, newSize, oldSize);
        arraySize = newSize; 

    }// END OF resizeArray()

    /**
     * Method designed to copy the elements of the incoming array into a larger array and return the reference to the larger array.
     * 
     * @Param:  oldSize[]   The passed array that is to be copied from.
     * @Param:  newSize     The size of the new array.
     * @Return: tempStore   The reference to the new larger array.
     */
    private int[] copyArray(int[] oldStore, int newSize, int oldSize){
        int[] tempStore = new int[newSize];
        int index = 0;

        while(index < oldSize){
            tempStore[index++] = oldStore[front % oldSize];
            front++;
        }

        while(index < newSize)
            tempStore[index++] = 0;
  
        front = 0;
        back = count;
        return tempStore;
    
    }// END OF copyArray()

}//END OF CLASS ArrayQueue