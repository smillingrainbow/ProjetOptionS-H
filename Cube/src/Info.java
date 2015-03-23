/***
 *
 * Récupération des informations de la table structure
 */
public class Info {
	private int idStructure;
	private String nom;
	private String description;
	
	public Info()
	{
		this.idStructure = 0;
		this.nom = "";
		this.description = "";
	}
	
	/***
	 * Constructeur
	 * @param var_idStructure : id du cube sélectionné
	 * 
	 * Création d'une connexion à la base de données 
	 * Récupération des données associé au cube
	 */
	public Info(int var_idStructure)
	{
		DB db = new DB();
		
		String sql = "select nom, description from structure where id_structure = "+var_idStructure;
		
		Object result[];
		
		result = db.getResultSelect(sql);
		
		if(result != null)
		{
			this.idStructure = var_idStructure;
			this.nom = (String)result[0];
			this.description = (String)result[1];
		}
		else
		{
			this.idStructure = var_idStructure;
			this.nom = "Not Found";
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
}
