import java.util.Scanner;
public class Main{

	public static void main(String[] args){
        String message = "Please enter the item you with to find in an integer array. ";
        String found = "Item found at index ";
        int key = 0;
        int index = 0;
        Scanner input = new Scanner(System.in);
        try{
            
            System.out.print(message);
            key = input.nextInt();
            index = searchArray(key);
            System.out.println("\n" + found + index);
        } catch (Exception e){
            System.out.println(e);
        }
        finally{
            input.close();
        }
    }

    public static int searchArray(int searchItem)  throws Exception{
        int[] numericArray = {0,1,2,3,4,5,6,7,8,9};
        
        int index = 0;
        for(; index < 10; index++){
            if(searchItem == numericArray[index])
                break;
        }

        if(index == 10)
            throw new Exception("Element not found.");
        else
            return index;
        
    }
}