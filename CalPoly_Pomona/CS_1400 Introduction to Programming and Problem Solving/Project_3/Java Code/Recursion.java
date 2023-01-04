public class Recursion {
    private int count;
    private int index;
    private boolean isBalanced;
    private Object temp;

     /**
     * Constructor with no parameters designed to initialize fields to default values and create a new temporary object.
     * 
     * @Param:  NONE
     * @Return: NONE
     */
    public Recursion() {
        count = 0;
        index = 0;
        isBalanced = true;
        temp = new Object();
    }// END OF CONSTRUCTOR

     /**
     * Method designed to pass a string to a recursive method to count the number of consecutive, non-overlaping 22's in the string.
     * 
     * if the string == null then return -1, else if string length <= 1 then return 0, else call the recursive method in a return statement.
     * 
     * @Param:  str                             String that is to be checked by the recursive method.
     * @Return: count22NoOverlapRecursion(str)  The number of consecutive, non-overlapping occurences of 22 in the string str, passed from the recursive method.
     */
    public int count22NoOverlap(String str) {
        count = 0;
        if (str == null)
            return -1;
        else {
            if (str.length() <= 1)
                return 0;
            else
                return count22NoOverlapRecursion(str);
        }
    }// END count22NoOverlap METHOD

     /**
     * Method designed to count the number of consecutive, non-overlaping 22's in a string using recursion.
     * 
     * if string length < 2, then return 0. if the first and second position of the string = 2 then count is incremented and recursive
     *      call on substring with its begining index incremented by 2, else recursive call on a substring its begining index incremented by 1
     *      for each instance of recursion, respectively. 
     * At the end of each recursive call, base case returns 0 and each subsequent call returns count.
     * 
     * @Param:  str     String that is to be checked, with each recursive call passing a smaller substring of str
     * @Return: count   The number of consecutive, non-overlapping occurences of 22 in the string str.
     */
    private int count22NoOverlapRecursion(String str) {
        if (str.length() < 2)
            return 0;

        if ((str.charAt(0) == '2') && (str.charAt(1) == '2')) {
            count++;
            count22NoOverlapRecursion(str.substring(2));
        } else
            count22NoOverlapRecursion(str.substring(1));

        return count;
    }// END count22NoOverlapRecursion METHOD

     /**
     * Method designed to pass a string to a recursive method to count the number of consecutive, with overlap, 22's in the string.
     * 
     * if the string == null then return -1, else if string length <= 1 then return 0, else call the recursive method in a return statement.
     * 
     * @Param:  str                             String that is to be checked by the recursive method.
     * @Return: count22OverlapRecursion(str)    The number of consecutive, with overlap, occurences of 22 in the string str, passed from the recursive method.
     */
    public int count22Overlap(String str) {
        count = 0;
        if (str == null)
            return -1;

        if (str.length() <= 1)
            return 0;

        return count22OverlapRecursion(str);
    }// END count22Overlap METHOD

     /**
     * Method designed to count the number of consecutive, with overlap, 22's in a string using recursion.
     * 
     * if string length < 2, then return 0. if the first and second position of the substring = 2 then count is incremented.
     * Recursive call on a substring with its begining index incremented by 1 on each instance of recursion.
     * At the end of each recursive call, base case returns 0, and each subsequent call returns count.
     * 
     * @Param:  str     String that is to be checked, with each recursive call passing a smaller substring of str
     * @Return: count   The number of consecutive, non-overlapping occurences of 22 in the string str.
     */
    private int count22OverlapRecursion(String str) {
        if (str.length() < 2)
            return 0;

        if ((str.charAt(0) == '2') && (str.charAt(1) == '2')) {
            count++;
        }
        count22OverlapRecursion(str.substring(1));
        return count;
    }// END count22OverlapRecursion METHOD

     /**
     * Method designed to pass an integer array to a recursive method to count the number of consecutive, increasing or decreasing, factors of ten.
     * 
     * if the array == null then return -1, if array length < 2 then return 0, else call the recursive method in a return statement.
     * 
     * @Param:  array                                   An integer array of variable length where its elements are chcek for factors of ten.
     *          value                                   an integer that will hold the count of consecutive factors of ten. Its initial passed value should be zero. 
     * @Return: factorsOf10Recursion(array, value)      call to the recursive method that should return the count of consecutive factors of ten.
     */
    public int factorsOf10(int[] array, int value) {
        count = 0;
        index = 0;
        if (array == null)
            return -1;
        if (array.length < 2)
            return 0;

        return factorsOf10Recursion(array, value);
    }//END factorsOf10 METHOD

     /**
     * Method designed to count the number of consecutive, increasing or decreasing, factors of ten.
     * 
     * if index >= array length, then return 0.
     * if index == 0, then value = array[index], then recrusive call to method.
     *      else if value < array[index] check for increasing factor of ten. 
     *           if true, increment count, value = array[index++], and recursive call to method.
     *           if false, value = array[index++] and recursive call to method.
     *      else if value is a decreasing factor of ten, increment count, value = array[index], and recursive call to method.
     *           else value = array[index++], and recursive call to method.
     * At the end of each recursive call, base case returns 0, and each subsequent call returns count.
     * 
     * @Param:  str     String that is to be checked, with each recursive call passing a smaller substring of str
     * @Return: count   The number of consecutive, non-overlapping occurences of 22 in the string str.
     */
    private int factorsOf10Recursion(int[] array, int value) {
        if (index >= array.length)
            return 0;

        if (index == 0) {
            value = array[index++];
            factorsOf10Recursion(array, value);
        } 
        else {
            if (value < array[index]) {
                if ((value * 10) == array[index]) {
                    count++;
                    value = array[index++];
                    factorsOf10Recursion(array, value);
                } 
                else {
                    value = array[index++];
                    factorsOf10Recursion(array, value);
                }
            } 
            else {
                if ((value / 10) == array[index]) {
                    count++;
                    value = array[index++];
                    factorsOf10Recursion(array, value);
                } 
                else {
                    value = array[index++];
                    factorsOf10Recursion(array, value);
                }
            }
        }
        return count;
    }// END factorsOf10Recursion METHOD

     /**
     * Method designed to pass a string and an ArrayStack to a recursive method to check if algebraic expression has balanced parentheses.
     * 
     * if string == null, return false. if string length < 2 the check if length = 1 and either '(' or ')' is in the string, if true then return false, else return true.
     * if string lenght > 2 then pass string and stack to recursive method to check for balanced parentheses.
     * 
     * @Param:  string                          string of an algebraic expression that is to be check for balanced parentheses, if present.
     *          stack                           an arraystack that is used to hold open parenthesis.  
     * @Return: balancedParens(string, stack)   call to the recursive method that should return a boolean value.
     */
    public boolean balancedParens(String string, ArrayStack stack) {
        isBalanced = true;
        index = 0;
        if (string == null)
            return false;
        
        int len = string.length();
        if (len < 2) {
            if (len == 1 && (string == "(" || string == ")"))
                return false;
            else
                return true;
        }
        return balancedParensRecursion(string, stack);
    }// END balancedParens METHOD

     /**
     * Method designed to test if an algebraic expression has balanced parentheses.
     * 
     * if index >= string length, check if stack is empty. if true isBalanced = false.
     *      else, using switch statment, if char at string position of index is '(' then push char to the stack, increment index, and recursively call the method.
     *            if char at string position of index is ')' then check if stack is empty. if true index = string length and isBalanced = false.
     *                  if false then increment index, pop the stack, and recursively call the method.
     *            else increment the index and recursively call the method. 
     * At the end of each recursive call, starting with the base case of index >= string lenght, return isBalanced.
     * 
     * @Param:  string       String that is to be checked for balanced algebraic expression.
     *          stack        arraystack that is used to hold open parentheses.
     * @Return: isBalanced   boolean used to return true or false.
     */  
    private boolean balancedParensRecursion(String string, ArrayStack stack) {
        if (index >= string.length()) {
            if (stack.isEmpty() == false)
                isBalanced = false;            
        } 
        else {
            switch (string.charAt(index)) {
                case '(':
                    stack.push(string.charAt(index++));
                    balancedParensRecursion(string, stack);
                    break;
                case ')':
                    if (stack.isEmpty()) {
                        index = string.length();
                        isBalanced = false;
                    } else {
                        index++;
                        try {
                            stack.pop();
                        } catch (Exception e) {
                        }
                        balancedParensRecursion(string, stack);
                    }
                    break;
                default:
                    index++;
                    balancedParensRecursion(string, stack);
                    break;
            }
        }
        return isBalanced;
    }// END balancedParensRecursion METHOD

     /**
     * Method designed to pass an Object array, and two indexes in order to revese the order of the array's elements.
     * 
     * if array != null and array length > 1, call the recursive method.
     * 
     * @Param:  array   An Object array whose order of its elements is to be reversed using a recursive method.
     *          index1  An integer that holds the first index of the array.
     *          index2  An integer that holds the last index of the array.  
     * @Return: N/A
     */
    public void reverseArray(Object[] array, int index1, int index2) {
        if(array != null && array.length > 1)
            reverseArrayRecursion(array, index1, index2);                        
    }// END reverseArray MEHTOD

     /**
     * Method designed to reverse the order of the elements of the passed object array using recursion.
     * 
     * assing the temp variable to the point to the element at index1.
     * if index1 < index2, then assign array position at index1 to index2, increment index1 then assign
     *      array at index2 to temp and decrement index2. Then recusively call the method.     * 
     * Once index1 >= index2, recursion will end and array should be reversed.
     * 
     * @Param:  array   An object array whose order of elements is to be reversed.
     *          index1  A starting index for the array that is incremented for each recursive call. 
     *          index2  An ending index for the array that is decremented for each recursive call.     
     * @Return: N/A
     */  
    private void reverseArrayRecursion(Object[] array, int index1, int index2) {
        temp = array[index1];
        if(index1 < index2){
            array[index1++] = array[index2];
            array[index2--] = temp;
            reverseArrayRecursion(array, index1, index2);
        }
    }// END reverseArrayRecursion METHOD
}// END Recursion CLASS
