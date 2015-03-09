
public class Info {
	//On obtient les infos de la table structure
	private int idStructure;
	private String nom;
	private String description;
	
	public Info()
	{
		this.idStructure = 0;
		this.nom = "";
		this.description = "";
	}
	
	public Info(int var_idStructure)
	{
		//Creer une base de donnees pour obtenir les infos selon idStructure
		DB db = new DB();
		
		String sql = "select nom, description from structure where id_structure = "+var_idStructure;
		
		Object result[] = db.getResultSelect(sql);
		
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
	
	public int getIdStructure()
	{
		return this.idStructure;
	}
	
	public String getNom()
	{
		return this.nom;
	}
	
	public String getDescription()
	{
		return this.description;
	}
}
