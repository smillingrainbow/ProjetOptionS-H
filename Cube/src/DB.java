import java.sql.*;

/*** 
 *
 * R�alise la connexion avec la base de donn�es
 * R�cup�re les informations des �l�ments de la table structure
 */
public class DB {
	private String driver;
	private String url;
	private String user;
	private String password;
	static public boolean db_connection; // Indique au fichier si la connexion � la db a bien �t� effectu�e
	
	private Connection conn;
	
	public DB()
	{
		this.driver = "com.mysql.jdbc.Driver";
		this.url = "jdbc:mysql://127.0.0.1/structurecerveaubrebis";
		this.user = "root";
		this.password = "root";
		
		this.conn = null;
	}
	
	public DB(String var_databaseName, String var_user, String var_password)
	{
		this.driver = "com.mysql.jdbc.Driver";
		this.url = "jdbc:mysql://127.0.0.1/"+var_databaseName;
		this.user = var_user;
		this.password = var_password;
		
		this.conn = null;
	}
	
	/***
	 * Fonction de connexion � la base de donn�es
	 */
	private void connection()
	{
		try{
			Class.forName(this.driver);
			this.conn = DriverManager.getConnection(this.url, this.user, this.password);
			if(this.conn.isClosed())
			{
				System.out.println("Sorry, can't connect to the database");
			}
			db_connection = true;
			System.out.println("Connexion � la base de donn�es �tablie.");
		}
		catch(ClassNotFoundException e)
		{
			db_connection = false;
			System.out.println("Sorry, can't find the Driver");
			e.printStackTrace();
		}
		catch(Exception e)
		{
			db_connection = false;
			System.out.println("> Exception < Erreur de connexion � la base de donn�es (v�rifier Wamp)");
			System.out.println("> Exception < D�commenter la ligne de catch de la fonction \"connection()\" dans le fichier \"DB.java\" pour plus d'informations");
			//e.printStackTrace();
		}
	}
	
	/***
	 * Fonction de d�connexion � la base de donn�es
	 */
	private void closeConnection()
	{
		try{
			if(this.conn != null && !this.conn.isClosed())
			{
				this.conn.close();
				System.out.println("Connexion � la base de donn�es ferm�e.");
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	/***
	 * 
	 * @param sql : requ�te sql de r�cup�ration des donn�es
	 * @return R�sultat de la requ�te
	 */
	public Object[] getResultSelect(String sql)
	{
		Object result[] = null;
		
		try{
			this.connection();
			Statement statement;
			ResultSet rs;
			
			if(db_connection == true) // Si la connexion � la base de donn�es a bien �t� effectu�e
			{
				statement = this.conn.createStatement();
				rs = statement.executeQuery(sql);
			
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
						result = new Object[numberColonnes];
						
						rs.first();
						
						for(int iBoucle=0; iBoucle<numberColonnes; iBoucle++)
						{
							result[iBoucle] = rs.getObject(iBoucle+1);
						}
						rs.close();
					}
				}
			}
		}
		catch(Exception e)
		{
			System.out.println("> Exception < Erreur de r�cup�ration des donn�es (informations non pr�sentes dans la db)");
			System.out.println("> Exception < D�commenter la ligne de catch de la fonction \"getResultSelect()\" dans le fichier \"DB.java\" pour plus d'informations");
			//e.printStackTrace();
		}
		//Fermeture de la connexion � la base de donn�es
		this.closeConnection();
		return result;
	}
	
}
