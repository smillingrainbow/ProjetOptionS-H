/***
 *
 * R�cup�ration des informations de la table structure
 */
public class Info {
	private int idStructure;
	private String nom;
	private String description;
	private String nomTab[];
	
	public Info()
	{
		this.idStructure = 0;
		this.nom = "";
		this.description = "";
		
		DB db = new DB();
		String sql = "SELECT COUNT(id_structure) FROM structure";
		Object result[][];
		result = db.getResultSelect(sql);
		if(result != null){
			nomTab = new String[Integer.parseInt(result[0][0].toString())];
//			System.out.println(result[0].toString());
			sql = "SELECT nom FROM structure";
			result = db.getResultSelect(sql);
//			System.out.println(result.length);
			if(result!= null){
				for (int i=0; i<result.length; i++){
//					System.out.println(result[i][0].toString());
					nomTab[i] = result[i][0].toString();
				}
			}
		}
		
	}
	
	/***
	 * Constructeur
	 * @param var_idStructure : id du cube s�lectionn�
	 * 
	 * Cr�ation d'une connexion � la base de donn�es 
	 * R�cup�ration des donn�es associ� au cube
	 */
	public Info(int var_idStructure)
	{
		DB db = new DB();
		
		String sql = "select nom, description from structure where id_structure = "+var_idStructure;
		
		Object result[][];
		
		result = db.getResultSelect(sql);
		
		if(result != null)
		{
			this.idStructure = var_idStructure;
			this.nom = (String)result[0][0];
			this.description = (String)result[0][1];
		}
		else
		{
			this.idStructure = var_idStructure;
			this.nom = "Not Found";
			this.description = "Not Found";
		}		
	}
	
	public Info(String value)
	{
		DB db = new DB();
		
		String sql = "select id_structure,description from structure where nom = '"+ value +"'";
		
		Object result[][];
		
		result = db.getResultSelect(sql);
		
		if(result != null)
		{
			this.idStructure = Integer.parseInt(result[0][0].toString());
			this.nom = value;
			this.description = result[0][1].toString();
		}
		else
		{
			this.idStructure = 0;
			this.nom = value;
			this.description = "Not Found";
		}		
	}
	
	
	/***
	 * Getter de l'id
	 * @return id du cube
	 */
	public int getIdStructure()
	{
		return this.idStructure;
	}
	
	/***
	 * Getter du nom du cube
	 * @return nom du cube
	 */
	public String getNom()
	{
		return this.nom;
	}
	
	/***
	 * Getter de la description
	 * @return description du cube
	 */
	public String getDescription()
	{
		return this.description;
	}
	
	public String[] getNomTab(){
		return this.nomTab;
	}
}
