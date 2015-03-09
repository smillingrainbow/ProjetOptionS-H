import java.applet.Applet;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GraphicsConfiguration;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.media.j3d.Alpha;
import javax.media.j3d.BoundingBox;
import javax.media.j3d.BoundingPolytope;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.Canvas3D;
import javax.media.j3d.ModelClip;
import javax.media.j3d.RotationInterpolator;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.vecmath.AxisAngle4d;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3f;
import javax.vecmath.Vector4d;

import com.sun.j3d.utils.applet.MainFrame;
import com.sun.j3d.utils.behaviors.mouse.MouseRotate;
import com.sun.j3d.utils.geometry.ColorCube;
import com.sun.j3d.utils.universe.SimpleUniverse;


public class test1 extends Applet{
	
	private int numberLineCube = 4;
	
	//Xpre, Ypre, Zpre, NomPre sont pour enregistrer les informations du cube precedent
	private float Xpre = 0, Ypre = 0, Zpre = 0;
	private int NomPre = 0;
	
	//Apres bouger, la valeur de l'axe X : -ecart
	private float ecart = 3;
	
	//variable de Boucle pour la fonction createSceneGraph(). On l'utilise dans la fonction init() aussi
	float MoinsCenter = 1;
	
	//La taille de cube, quand on crée un ReColorCube, c'est le premier argument
	float tailleCube = 0.1f;
	
	//Si c'est la premiere fois pour choisir un cube
	private boolean first = true;
	
	//Le tableau de ReColorCube
	public ReColorCube rcc[] = new ReColorCube[numberLineCube*numberLineCube*numberLineCube];
	
	//Le tableau de TransformGroup
	public TransformGroup objRotate[] = new TransformGroup[numberLineCube*numberLineCube*numberLineCube];
	
	//private BranchGroup objRoot;
	
	public test1(){}
	
	
	public BranchGroup createSceneGraph()
	{
		
		int noRCC = 0;
		
		BranchGroup objRoot = new BranchGroup();
		
		//objRoot = new BranchGroup();
		
		
		
		
		for(float Z=(-MoinsCenter); Z<numberLineCube-MoinsCenter; Z=Z+1)
			for(float Y=(-MoinsCenter); Y<numberLineCube-MoinsCenter; Y=Y+1)
				for(float X=(-MoinsCenter); X<numberLineCube-MoinsCenter; X=X+1)
				{
					Transform3D rotate = new Transform3D();
					
					Vector3f v3f = new Vector3f(0.25f*X, 0.25f*Y, 0.25f*Z); 
					 
					rotate.setTranslation(v3f); //translation
					
					objRotate[noRCC] = new TransformGroup(rotate);
					objRotate[noRCC].setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
					objRotate[noRCC].setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
					
					
					//On peut utiliser le souris pour tourner le cube
					//Mais, au début, on ne peut pas les tourner. Car, on n'utilise pas encore la fonction setSchedulingBounds
					MouseRotate behavior = new MouseRotate();					
				    behavior.setTransformGroup(objRotate[noRCC]);
				    objRotate[noRCC].addChild(behavior);
				  
				    //
				    ModelClip mc = new ModelClip();
				    mc.setEnables(new boolean[]{false,false,false,false,false,false});
				    mc.setCapability(ModelClip.ALLOW_PLANE_READ);
				    mc.setCapability(ModelClip.ALLOW_PLANE_WRITE);
				    mc.setCapability(ModelClip.ALLOW_ENABLE_READ);
				    mc.setCapability(ModelClip.ALLOW_ENABLE_WRITE);
				    mc.setCapability(ModelClip.ALLOW_INFLUENCING_BOUNDS_READ);
				    mc.setCapability(ModelClip.ALLOW_INFLUENCING_BOUNDS_WRITE);
				    mc.setCapability(ModelClip.ALLOW_SCOPE_READ);
				    mc.setCapability(ModelClip.ALLOW_SCOPE_WRITE);
				    objRotate[noRCC].addChild(mc);
					
					rcc[noRCC] = new ReColorCube(tailleCube, (noRCC+1)+"", X, Y, Z);
					
					//ajoute ReColorCube au tableau TransformGroup
					objRotate[noRCC].addChild(rcc[noRCC]);
					
					//ajouter TransformGroup a BranchGroup
					objRoot.addChild(objRotate[noRCC]);
		
					noRCC++;
				}

		
		return objRoot;
	}
	
	public void init()
	{
		setLayout(new BorderLayout());
		
		JPanel panelEast = new JPanel();
		panelEast.setSize(100, 100);
		panelEast.setLayout(new GridLayout(8,1));
		
		
		String nom[] = new String[numberLineCube*numberLineCube*numberLineCube];
		
		for(int iBoucle=0; iBoucle<numberLineCube*numberLineCube*numberLineCube; iBoucle++)
		{
			nom[iBoucle] = (iBoucle+1)+"";
		}
		
		//Creer un JComboBox pour que les utilisateurs peuvent choisir un cube selon le nom de cube
		JComboBox jcb = new JComboBox(nom);
		
		
		panelEast.add(jcb);
		
		//Creer JRadioButton pour choisir le plan
		ButtonGroup jbg = new ButtonGroup();
		JRadioButton jrbX = new JRadioButton("X");
		JRadioButton jrbY = new JRadioButton("Y");
		JRadioButton jrbZ = new JRadioButton("Z");
		
		jbg.add(jrbX);
		jbg.add(jrbY);
		jbg.add(jrbZ);
		
		JPanel panelRadioButton = new JPanel();
		
		panelRadioButton.add(jrbX);
		panelRadioButton.add(jrbY);
		panelRadioButton.add(jrbZ);
		
		panelEast.add(panelRadioButton);
		
		add("East", panelEast);
		
		//Creer un panel pour afficher les info correspondant à un cube
		JPanel panelSouth = new JPanel();
		panelSouth.setLayout(new GridLayout(2,3));
		
		JLabel labelIdStructure = new JLabel("Id Structure");
		JLabel labelNom = new JLabel("Nom");
		JLabel labelDescription = new JLabel("Description");
		
		//final type est pour les utiliser dans la fonction de ItemListener
		final JTextField textIdStructure = new JTextField();
		final JTextField textNom = new JTextField();
		final JTextField textDescription = new JTextField();
		
		panelSouth.add(labelIdStructure);
		panelSouth.add(labelNom);
		panelSouth.add(labelDescription);
		
		panelSouth.add(textIdStructure);
		panelSouth.add(textNom);
		panelSouth.add(textDescription);
		
		add("South", panelSouth);
		
		final BoundingSphere bounds = new BoundingSphere(new Point3d(0.0,0.0,0.0), 10.0f);
		
		//Creer Universe de 3D
		GraphicsConfiguration config = SimpleUniverse.getPreferredConfiguration();
		Canvas3D canvas3D = new Canvas3D(config); //Creer un canvas
		canvas3D.setSize(800, 800);
		add("Center", canvas3D);
		
		BranchGroup scene = createSceneGraph();
		
		scene.compile();
		
		SimpleUniverse u = new SimpleUniverse(canvas3D); //creer une universe
		
		u.getViewingPlatform().setNominalViewingTransform();
		
		u.addBranchGraph(scene);
		
		
		
		//evenement de JCOMBOBOX
		jcb.addItemListener(new ItemListener(){
			public void itemStateChanged(ItemEvent e)
			{
				//Quand le choix change
				if(e.getStateChange() == ItemEvent.SELECTED)
				{
					int IdNom = Integer.parseInt((String)e.getItem());
					
					//Afficher les infos correspondant au cube
					Info info = rcc[IdNom-1].getInfo();
					textIdStructure.setText(info.getIdStructure()+"");
					textNom.setText(info.getNom());
					textDescription.setText(info.getDescription());
					
					
					
					float coordonnee[] = rcc[IdNom-1].getXYZ();
										
					Transform3D rotate = new Transform3D();
					
					//float ecart = 3;					
					
					Vector3f v3f;
					int timeChange = 50; //La periode pour changer le point centre (ms)
					//La premiere fois, il ne suffit pas de mettre le cube en position originale, parce qu'il n'y a aucun cube au debut
					if(first == true)
					{   //Les coordonnees du cube precedent
						Xpre = coordonnee[0];
						Ypre = coordonnee[1];
						Zpre = coordonnee[2];
						//Le numero du cube precedent
						NomPre = IdNom;												
						
						float fBoucle = 0;
						//Tous les timeChange(ms), on change le point centre
						while(fBoucle < ecart+coordonnee[0])
						{
														
							//la valeur de l'axe X est -0.5f a la fin
							v3f = new Vector3f(0.25f*(coordonnee[0]-fBoucle), 0.25f*coordonnee[1], 0.25f*coordonnee[2]);
							rotate.setTranslation(v3f); //changer le point centre
							objRotate[IdNom-1].setTransform(rotate);
							fBoucle += 0.05f;
							
							try{ 
								//attendre timeChange(ms), apres qu'on change le point centre, c'est comme animation
								Thread.sleep(timeChange);
							}catch(Exception exc)
							{
								exc.printStackTrace();
							}
						}
						
						
						
						//Configurer ce cube pour le faire tourner
						//BoundingSphere bounds = new BoundingSphere(new Point3d(0.25f*coordonnee[0],0.25f*coordonnee[1],0.25f*coordonnee[2]), 10.0f);
						MouseRotate mr =  (MouseRotate)objRotate[IdNom-1].getChild(0);
						mr.setSchedulingBounds(bounds);												
						
						//Apres la premiere fois, on affect FALSE a la variable 'first'
						first = false;
					}
					else
					{
						v3f = new Vector3f(0.25f*Xpre, 0.25f*Ypre, 0.25f*Zpre);
						rotate.setTranslation(v3f);
						objRotate[NomPre-1].setTransform(rotate);
						
						//Configurer le cube precedent pour le faire ne pas tourner
						MouseRotate mr =  (MouseRotate)objRotate[NomPre-1].getChild(0);
						mr.setSchedulingBounds(null);
						
						ModelClip mcTemp = (ModelClip)objRotate[NomPre-1].getChild(1);
						mcTemp.setEnable(0, false);
						mcTemp.setEnable(1, false);
						mcTemp.setEnable(2, false);
						mcTemp.setEnable(3, false);
						mcTemp.setEnable(4, false);
						mcTemp.setEnable(5, false);
						
						Xpre = coordonnee[0];
						Ypre = coordonnee[1];
						Zpre = coordonnee[2];
						NomPre = IdNom;
						//behaviorPre = behavior;
						
						float fBoucle = 0;
						while(fBoucle < ecart+coordonnee[0])
						{
							v3f = new Vector3f(0.25f*(coordonnee[0]-fBoucle), 0.25f*coordonnee[1], 0.25f*coordonnee[2]);
							rotate.setTranslation(v3f);
							objRotate[IdNom-1].setTransform(rotate);
							fBoucle += 0.05f;
							
							try{
								Thread.sleep(timeChange);
							}catch(Exception exc)
							{
								exc.printStackTrace();
							}
						}
						
						//System.out.println(0.25f*(coordonnee[0]-fBoucle)+"");
						
						//Configurer ce cube pour le faire tourner
						//BoundingSphere bounds = new BoundingSphere(new Point3d(0.25f*coordonnee[0],0.25f*coordonnee[1],0.25f*coordonnee[2]), 10.0f);
						mr =  (MouseRotate)objRotate[IdNom-1].getChild(0);
						mr.setSchedulingBounds(bounds);
					}
				}
			}
		});
		
		//Click sur X
		jrbX.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e)
			{
				if(NomPre != 0)
				{
					float coordonnee[] = rcc[NomPre-1].getXYZ();
					
					Vector4d v4d = new Vector4d(-1.0, 0.0, 0.0, -0.25*ecart);
					//Vector4d v4d2 = new Vector4d(-1.0, 0.0, 0.0, -0.25*ecart-0.05);
					
					ModelClip mcTemp = (ModelClip)objRotate[NomPre-1].getChild(1);
					//BoundingSphere bounds = new BoundingSphere(new Point3d(-0.25f*ecart,0.25f*coordonnee[1],0.25f*coordonnee[2]), 10.0f);
					
					//BoundingBox bounds = new BoundingBox(new Point3d(-0.85,0.25f*coordonnee[1]-0.1f,0.25f*coordonnee[2]-0.1f), new Point3d(-0.65,0.25f*coordonnee[1]+0.1f,0.25f*coordonnee[2]+0.1f));	
					
					mcTemp.setPlane(0, v4d);
					//mcTemp.setPlane(1, v4d2);
					mcTemp.setEnable(0, true);
					//mcTemp.setEnable(1, true);
					mcTemp.setInfluencingBounds(bounds);
				}
			}
		});
		
		//CLick sur Y

		jrbY.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e)
			{
				if(NomPre != 0)
				{
					float coordonnee[] = rcc[NomPre-1].getXYZ();
					
					Vector4d v4d = new Vector4d(0.0, -1.0, 0.0, 0.25*coordonnee[1]);
					///Vector4d v4d = new Vector4d(0.0, 1.0, 0.0, -0.25*coordonnee[1]);
					System.out.println(0.25*coordonnee[1]);
					//Vector4d v4d2 = new Vector4d(1.0, 0.0, 0.0, 0.25*MoinsCenter+tailleCube);
					Vector4d v4d2 = new Vector4d(1.0, 0.0, 0.0, -0.15);
					
					ModelClip mcTemp = (ModelClip)objRotate[NomPre-1].getChild(1);
					//BoundingSphere bounds = new BoundingSphere(new Point3d(-0.25f*ecart,0.25f*coordonnee[1],0.25f*coordonnee[2]), 10.0f);
					
					//BoundingBox bounds = new BoundingBox(new Point3d(-0.85,0.25f*coordonnee[1]-0.1f,0.25f*coordonnee[2]-0.1f), new Point3d(-0.65,0.25f*coordonnee[1]+0.1f,0.25f*coordonnee[2]+0.1f));	
					
					mcTemp.setPlane(1, v4d);
					mcTemp.setEnable(1, true);
					//mcTemp.setPlane(0, v4d2);
					//mcTemp.setEnable(0, true);
					
					mcTemp.setInfluencingBounds(bounds);
				}
			}
		});
		
		//Click sur Z
		jrbZ.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e)
			{
				if(NomPre != 0)
				{
					float coordonnee[] = rcc[NomPre-1].getXYZ();
					
					Vector4d v4d = new Vector4d(0.0, 0.0, 1.0, 0.25*coordonnee[2]);
					
					ModelClip mcTemp = (ModelClip)objRotate[NomPre-1].getChild(1);
					//BoundingSphere bounds = new BoundingSphere(new Point3d(-0.25f*ecart,0.25f*coordonnee[1],0.25f*coordonnee[2]), 10.0f);
					
					//BoundingBox bounds = new BoundingBox(new Point3d(-0.85,0.25f*coordonnee[1]-0.1f,0.25f*coordonnee[2]-0.1f), new Point3d(-0.65,0.25f*coordonnee[1]+0.1f,0.25f*coordonnee[2]+0.1f));	
					
					mcTemp.setPlane(1, v4d);
					mcTemp.setEnable(1, true);
					mcTemp.setInfluencingBounds(bounds);
				}
			}
		});
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		new MainFrame(new test1(), 1024, 1024);
	}

}
