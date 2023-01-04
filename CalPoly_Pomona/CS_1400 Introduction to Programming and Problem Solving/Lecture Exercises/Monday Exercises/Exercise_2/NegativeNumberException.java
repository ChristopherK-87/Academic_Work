public class NegativeNumberException extends NumberFormatException{
    public NegativeNumberException(){
        String message = "Error: Negative Number.";
        System.out.println(message);
    }
    public NegativeNumberException(String message){
        System.out.println(message);
    }
}