import java.sql.*;

public class AccessDB_Connector_Test{
    public static void main(String []args){
        String databaseURL = "jdbc:ucanaccess://E:\\_School\\CalPoly Pomona\\Classes\\1_CS 3560\\Group Project\\BeegShipping V2.accdb";
        try (Connection connection = DriverManager.getConnection(databaseURL)) {
                
                
            String sql = "INSERT INTO Client (CompanyName) VALUES (?)";
            
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, "Disney");
            //preparedStatement.setString(1, "Disney");
            //preparedStatement.setString(3, "0919989998");
            
            int row = preparedStatement.executeUpdate();
            
            if (row > 0) {
                System.out.println("A row has been inserted successfully.");
            }
            
            sql = "SELECT * FROM Client";
            
            Statement statement = connection.createStatement();
            ResultSet result = statement.executeQuery(sql);
            
            while (result.next()) {
                int id = result.getInt("ClientID");
                String companyName = result.getString("CompanyName");
                
                System.out.println(id + ", " + companyName);
            }
            
        } catch (SQLException ex) {
            System.out.println("connection Error");
            ex.printStackTrace();
        }
    }
}
