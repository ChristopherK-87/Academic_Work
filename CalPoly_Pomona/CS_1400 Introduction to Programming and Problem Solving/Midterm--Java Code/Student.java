public class Student extends Person{
    private long studentId;
    private String userName;

    public Student(Person person, long studentId, String userName){
        super();
        this.studentId = studentId;
        String tempUserName = super.getName();
        userName = tempUserName.charAt(0) + tempUserName.substring(' ');
    }

    public long getId(){
        long tempId = studentId;
        return tempId;
    }

    public String getUserName(){
        String tempUserName = userName;
        return tempUserName;
    }

    public setId(long id){
        studentId = id;
    }

    public setUserName(String userName){
        this.userName = userName;
    }

    public String toString(){
        String msg = String.format("%9d - %s - %s", getId(), this.getName(), getUserName());
        return msg; 
    }

    public Student copy(){
        Student tempStudent = new Student(this.person, this.getId(), this.getUserName());
        return tempPerson;
    }
}