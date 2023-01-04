public class recursionExample{
    public static void main(String[] args){

        int[] numbers = {1,2,3,4,5,6,7,8,9,10};
        int sum = rangeSum(numbers, 0, 9);
        System.out.println("Sum of the numbers array is: " + sum);
    }

    public static int rangeSum(int[] num, int startIdx, int endIdx){
        if(num.length == 0)
            return 0;
        return rangeSumRecursion(num, startIdx, endIdx);
    }

    private static int rangeSumRecursion(int[] num, int startIdx, int endIdx){
        if (startIdx == endIdx)
            return num[i];

        return num[i] + rangeSumRecursion(num, startIdx++, endIdx);
    }
}