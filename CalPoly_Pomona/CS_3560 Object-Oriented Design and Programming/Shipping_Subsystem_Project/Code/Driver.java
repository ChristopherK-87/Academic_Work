import javax.sql.rowset.CachedRowSet;
import BeegShipping.dbConnector;

public class Driver {
    public static void main(String[] args) throws Exception {
        dbConnector dbObject = new dbConnector(); 
        String dbPath = "E:\\_School\\CalPoly Pomona\\Classes\\1_CS 3560\\Group Project\\BeegShipping V2.accdb";
        if(dbObject.setConnection(dbPath) == 1){
            System.out.println("Connection established.");
        }
        else
            System.out.println("connection error.");

        String sql = "SELECT * FROM Client";
        
        try (CachedRowSet crs = dbObject.viewTables(sql)) {
            while(crs.next()){
                int id = crs.getInt("ClientID");
                String companyName = crs.getString("CompanyName");
                
                System.out.println(id + ", " + companyName);
            }
        }

        String sql_two = "INSERT INTO Client (CompanyName) VALUES (\"MagicMountain\")";
        if(dbObject.insertOrUpdate(sql_two) > 0 ){
            System.out.println("INSERT/UPDATE SUCCESS");
        }
        else
            System.out.println("INSERT/UPDATE FAIL");

        try (CachedRowSet crs_two = dbObject.viewTables(sql)) {
            while(crs_two.next()){
                int id_two = crs_two.getInt("ClientID");
                String companyName_two = crs_two.getString("CompanyName");
                    
                System.out.println(id_two + ", " + companyName_two);
            }
        }

        if(dbObject.disconnect() == 1)
            System.out.println("Connection Closed.");
        else
            System.out.println("Error in closing db connection or db connection is null.");
    }
}
