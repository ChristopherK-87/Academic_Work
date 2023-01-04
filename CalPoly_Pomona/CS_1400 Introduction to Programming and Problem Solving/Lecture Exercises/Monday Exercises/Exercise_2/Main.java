

public class Main{
    public static void main(String[] args){
       int num1 = 2;
       int num2 = -3;
       summation(num1, num2);
    }

   
    public static void summation(int number1, int number2){
        int sum = 0;
        if(number2 < 0 || number1 < 0){
            throw new NegativeNumberException();
        }
        else
            sum = number1 + number2;

        System.out.println(sum);
    }
}

