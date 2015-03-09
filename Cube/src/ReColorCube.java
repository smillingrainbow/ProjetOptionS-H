import com.sun.j3d.utils.geometry.ColorCube;


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
		
		this.info = new Info(Integer.parseInt(nomCube));
	}
	
	public float[] getXYZ()
	{
		float xyz[] =  new float[3];
		xyz[0] = this.X;
		xyz[1] = this.Y;
		xyz[2] = this.Z;
		
		return xyz;
	}
	
	public String getNomCube()
	{
		return this.nomCube;
	}
	
	public Info getInfo()
	{
		return this.info;
	}
}
