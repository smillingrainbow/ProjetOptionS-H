import java.sql.*;

public class DB {
	private String driver;
	private String url;
	private String user;
	private String password;
	
	private Connection conn;
	
	public DB()
	{
		this.driver = "com.mysql.jdbc.Driver";
		this.url = "jdbc:mysql://127.0.0.1:3306/projetoption";
		this.user = "root";
		this.password = "";
		
		this.conn = null;
	}
	
	public DB(String var_databaseName, String var_user, String var_password)
	{
		this.driver = "com.mysql.jdbc.Driver";
		this.url = "jdbc:mysql://127.0.0.1:3306/"+var_databaseName;
		this.user = var_user;
		this.password = var_password;
		
		this.conn = null;
	}
	
	private void connection()
	{
		try{
			Class.forName(this.driver);
			this.conn = DriverManager.getConnection(this.url, this.user, this.password);
			if(this.conn.isClosed())
			{
				System.out.println("Sorry, can't connect to the database");
			}
		}
		catch(ClassNotFoundException e)
		{
			System.out.println("Sorry, can't find the Driver");
			e.printStackTrace();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	private void closeConnection()
	{
		try{
			if(this.conn != null && !this.conn.isClosed())
			{
				this.conn.close();
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public Object[] getResultSelect(String sql)
	{
		try{
			this.connection();
			Statement statement = this.conn.createStatement();
			ResultSet rs = statement.executeQuery(sql);
			
			if(rs != null)
			{
				//Obtenir le nombre de lignes
				rs.last();
				int numberRows = rs.getRow();
				
				if(numberRows != 0)
				{
					ResultSetMetaData rsmd = rs.getMetaData();
					
					//Obtenir le nombre de colonnes
					int numberColonnes = rsmd.getColumnCount();
					
					//S'il y a bp de ligne, on obtient la premiere ligne
					Object result[] = new Object[numberColonnes];
					
					rs.first();
					
					for(int iBoucle=0; iBoucle<numberColonnes; iBoucle++)
					{
						result[iBoucle] = rs.getObject(iBoucle+1);
					}
					rs.close();
					this.closeConnection();
					
					return result;
				}
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		return null;
	}
	
}
