package BeegShipping;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import javax.sql.rowset.CachedRowSet;
import javax.sql.rowset.RowSetFactory;
import javax.sql.rowset.RowSetProvider;




public class dbConnector{
    private String dbDriver;
    private String dbDriverAndPath;    
    private Statement stmt;
    private ResultSet rs;
    private Connection conn;
    private int status;

    public int setConnection(String pathInput){
        status = 0;
        dbDriver = "jdbc:ucanaccess://";
        dbDriverAndPath = dbDriver+pathInput;       
        try{
            conn = DriverManager.getConnection(dbDriverAndPath);
            status = 1;
        }catch (SQLException e){
            e.printStackTrace();
        }
        return status;
    }

    public CachedRowSet viewTables(String sqlStatement) throws SQLException{
        stmt = conn.createStatement();
        rs = stmt.executeQuery(sqlStatement);	
        RowSetFactory factory = RowSetProvider.newFactory();
        CachedRowSet crs = factory.createCachedRowSet();        
        crs.populate(rs);
        return crs;
    }

    public int insertOrUpdate(String sqlStatement) throws SQLException{
        stmt = conn.createStatement();            
        status = stmt.executeUpdate(sqlStatement);
        return status;
    }

    public int disconnect(){
        status = 0;
        if (conn != null){
            try{
                conn.close();             
                conn = null;
                status = 1;                
            }
            catch (SQLException e){
                e.printStackTrace();
            }
        }
        return status;
    }


    


}
