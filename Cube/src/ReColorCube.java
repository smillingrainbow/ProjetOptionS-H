import com.sun.j3d.utils.geometry.ColorCube;

/***
 * Création et sélection d'un cube avec ses informations
 */
public class ReColorCube extends ColorCube{
	
	private String nomCube="";
	private float X;
	private float Y;
	private float Z;	
	private Info info;
	
	public ReColorCube(double scale, String var_nomCube, float var_X, float var_Y, float var_Z)
	{
		super(scale);
		
		this.nomCube = var_nomCube;
		this.X = var_X;
		this.Y = var_Y;
		this.Z = var_Z;
		
	}
	
	/***
	 * Getter des coordonnées du cube
	 * @return Tableau des variables x, y et z
	 */
	public float[] getXYZ()
	{
		float xyz[] =  new float[3];
		xyz[0] = this.X;
		xyz[1] = this.Y;
		xyz[2] = this.Z;
		
		return xyz;
	}
	
	/***
	 * Getter du nom du cube
	 * @return
	 */
	public String getNomCube()
	{
		return this.nomCube;
	}
	
	/***
	 * Getter des informations du cube
	 * @return
	 */
	public Info getInfo()
	{

		this.info = new Info(Integer.parseInt(nomCube));
		
		return this.info;
	}
}
