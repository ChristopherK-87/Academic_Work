public class Main{
    public static void main(String[] args){
        String src = "I don't know how to use strings.";
        String target = "don't";
        String replacement = "now";
        int index = 0;

        index = src.indexOf(target);
        System.out.println("Index of target is: " + index);
        
        System.out.println("Substring of src is: " + src.substring(index, index + target.length()));
        System.out.println("Replacement of src is: " + src.replace(target, replacement));

    }
}