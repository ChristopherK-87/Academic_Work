public class Main {
    public static void main(String[] args) throws Exception {
      String str = "1,2,3,4,5,6,7,8,9";
      String[] tokens = str.split(",");
      for(String s : tokens)
        System.out.println(s);
    }
}
