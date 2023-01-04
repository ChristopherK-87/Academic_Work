interface Address{
    static final String street = "9114 South Central Ave";
    static final String city = "Los Angeles";
    static final String state = "CA";
    static final int zip = 90003;

    public String getStreet();
    public String getCity();
    public String getState();
    public int getZip();
    public Address copy();
    public String toString();
}