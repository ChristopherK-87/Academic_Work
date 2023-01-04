public class Person{
    private String ssn;
    private String name;
    private Address address;

    public Person(String ssn, String name, Address address){
        this.ssn = ssn;
        this.name = name;
        this.address = address;
    }
    public String getSsn() {
        String tempSsn = ssn;
        return tempSsn;
    }

    public String getName() {
        String tempName = name;
        return tempName;
    }

    public String getStreet() {
        String tempStreet = Address.street;
        return tempStreet;
    }

    public String getCity() {
        String tempCity = Address.city;
        return tempCity;
    }

    public String getState() {
        String tempState = Address.state;
        return tempState;
    }

    public int getZip() {
        int tempZip = Address.zip;
        return tempZip;
    }

    public String toString(){
        String msg = String.format("%s %s, %s, %s %d", getName(), getStreet(), getCity(), getState(), getZip());
        return msg; 
    }

    public Person copy(){
        Person tempPerson = new Person(this.getSsn(), this.getName(), this.address);
        return tempPerson;
    }
}