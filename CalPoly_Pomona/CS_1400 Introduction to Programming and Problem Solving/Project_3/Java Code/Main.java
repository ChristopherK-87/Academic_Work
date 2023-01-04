public class Main {
    public static void main(String[] args) {
        count22NoOverlapTester();
        count22OverlapTester();
        factorsOf10Tester();
        balancedParensTester();
        reverseArrayTester();
    }// END main METHOD
    
    public static void count22NoOverlapTester(){
        Recursion testObject = new Recursion();
        String firstTestString = null;
        String secondTestString = "abc22x22x22";
        String thirdTestString = "222";
        String pass = "TEST PASSED";
        String fail = "TEST FAILED";

        System.out.println("\nTesting count22NoOverlap method in Recursion class.");
        System.out.println("\n** Testing for null string condition. **");
        if(testObject.count22NoOverlap(firstTestString) == -1)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing string 'abc22x22x22' **");
        if(testObject.count22NoOverlap(secondTestString) == 3)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing string '222' **");
        if(testObject.count22NoOverlap(thirdTestString) == 1)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("\nAll tests for count22NoOverlap method in Recursion class has been completed.");
        System.out.println("============================================================================\n");
    }// END count22NoOverlapTester METHOD

    public static void count22OverlapTester(){
        Recursion testObject = new Recursion();
        String firstTestString = null;
        String secondTestString = "abc22x22x22";
        String thirdTestString = "222";
        String fourthTestString = "abc222222";
        String pass = "TEST PASSED";
        String fail = "TEST FAILED";

        System.out.println("Testing count22Overlap method in Recursion class.");
        System.out.println("\n** Testing for null string condition. **");
        if(testObject.count22Overlap(firstTestString) == -1)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing string 'abc22x22x22' **");
        if(testObject.count22Overlap(secondTestString) == 3)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing string '222' **");
        if(testObject.count22Overlap(thirdTestString) == 2)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing string 'abc222222' **");
        if(testObject.count22Overlap(fourthTestString) == 5)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("\nAll tests for count22Overlap method in Recursion class has been completed.");
        System.out.println("============================================================================\n");
    }// END count22OverlapTester METHOD

    public static void factorsOf10Tester(){
        Recursion testObject = new Recursion();
        int[] firstTestArray = null;
        int[] secondTestArray = {1, 10, 20};
        int[] thirdTestArray = {100, 10, 20, 200};
        int[] fourthTestArray = {1000, 100, 10, 1, 10};
        int[] fifthTestArray = {10, 20, 33, 340};
        int value = 0;
        String pass = "TEST PASSED";
        String fail = "TEST FAILED";

        System.out.println("Testing factorsOf10 method in Recursion class.");
        System.out.println("\n** Testing for null array condition. **");
        if(testObject.factorsOf10(firstTestArray, value) == -1)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing array with elements [1, 10, 20] **");
        if(testObject.factorsOf10(secondTestArray, value) == 1)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing array with elements [100, 10, 20, 200] **");
        if(testObject.factorsOf10(thirdTestArray, value) == 2)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing array with elements [1000, 100, 10, 1, 10] **");
        if(testObject.factorsOf10(fourthTestArray, value) == 4)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing array with elements [10, 20, 33, 340] **");
        if(testObject.factorsOf10(fifthTestArray, value) == 0)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("\nAll tests for factorsOf10 method in Recursion class has been completed.");
        System.out.println("============================================================================\n");
    }// END factorsOf10Tester METHOD

    public static void balancedParensTester(){
        Recursion testObject = new Recursion();
        ArrayStack testStack = new ArrayStack();
        String firstTestString = null;
        String secondTestString = "((A+B) * C)";
        String thirdTestString = "C";
        String fourthTestString = "A+B)";
        String fifthTestString = "(A+B * C";
        String pass = "TEST PASSED";
        String fail = "TEST FAILED";

        System.out.println("Testing balancedParens method in Recursion class.");
        System.out.println("\n** Testing for null String condition. **");
        if(testObject.balancedParens(firstTestString, testStack) == false)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing with string '((A+B) * C)' **");
        if(testObject.balancedParens(secondTestString, testStack))
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing with string 'C' **");
        if(testObject.balancedParens(thirdTestString, testStack))
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing with string 'A+B)' **");
        if(testObject.balancedParens(fourthTestString, testStack) == false)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("** Testing with string '(A+B * C' **");
        if(testObject.balancedParens(fifthTestString, testStack) == false)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("\nAll tests for balancedParens method in Recursion class has been completed.");
        System.out.println("============================================================================\n");
    }// END balancedParensTester METHOD

    public static void reverseArrayTester(){
        Recursion testObject = new Recursion();
        Object[] testArray;
        Object[] originalArray;
        int index1 = 0;
        int index2 = 0;
        boolean isReversed = true;
        final int INTEGER_OBJECT_ARRAY_LENGTH = 10;
        String pass = "TEST PASSED";
        String fail = "TEST FAILED";

        System.out.println("Testing reverseArray method in Recursion class.");
        System.out.println("\n** Testing with 10 Integer objects in the testArray. **");
        testArray = new Object[INTEGER_OBJECT_ARRAY_LENGTH];
        originalArray = new Object[INTEGER_OBJECT_ARRAY_LENGTH];
        index2 = testArray.length - 1;

        for(int digit = 0; digit <= index2; digit++){
            Integer value = digit;
            testArray[digit] = value;
            originalArray[digit] = value;
        }
        testObject.reverseArray(testArray, index1, index2);

        for(int digit = index2; digit >= 0; digit--){
            if(testArray[index1++] != originalArray[digit]){
               isReversed = false;
               break; 
            }
        }
        if(isReversed)
            System.out.println("   " + pass);
        else
            System.out.println("   " + fail);

        System.out.println("\nAll tests for balancedParens method in Recursion class has been completed.");
        System.out.println("============================================================================\n");
    }// END reverseArrayTester METHOD
}// END Main CLASS
