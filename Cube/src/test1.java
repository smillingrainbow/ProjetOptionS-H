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
	private boolean first_cube = true;
	
	//Le tableau de ReColorCube
	public ReColorCube tab_color_cube[] = new ReColorCube[numberLineCube*numberLineCube*numberLineCube];
	
	//Le tableau de TransformGroup
	public TransformGroup objRotate[] = new TransformGroup[numberLineCube*numberLineCube*numberLineCube];
	
	//private BranchGroup objRoot;
	
	public test1(){}
	
	/***
	 * Création de la scène - Tous les cubes
	 * @return BranchGroup
	 */
	public BranchGroup createSceneGraph()
	{
		
		int notab_color_cube = 0;
		
		BranchGroup objRoot = new BranchGroup();
		
		for(float Z=(-MoinsCenter); Z<numberLineCube-MoinsCenter; Z++)
			for(float Y=(-MoinsCenter); Y<numberLineCube-MoinsCenter; Y++)
				for(float X=(-MoinsCenter); X<numberLineCube-MoinsCenter; X++)
				{
					Transform3D rotate = new Transform3D();
					
					Vector3f v3f = new Vector3f(0.25f*X, 0.25f*Y, 0.25f*Z); 
					 
					rotate.setTranslation(v3f); //translation
					
					objRotate[notab_color_cube] = new TransformGroup(rotate);
					objRotate[notab_color_cube].setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
					objRotate[notab_color_cube].setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
					
					
					//On peut utiliser le souris pour tourner le cube
					//Mais, au début, on ne peut pas les tourner. Car, on n'utilise pas encore la fonction setSchedulingBounds
					MouseRotate behavior = new MouseRotate();					
				    behavior.setTransformGroup(objRotate[notab_color_cube]);
				    objRotate[notab_color_cube].addChild(behavior);
				  
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
				    objRotate[notab_color_cube].addChild(mc);
					
					tab_color_cube[notab_color_cube] = new ReColorCube(tailleCube, Integer.toString((notab_color_cube+1)), X, Y, Z);
					
					//ajoute ReColorCube au tableau TransformGroup
					objRotate[notab_color_cube].addChild(tab_color_cube[notab_color_cube]);
					
					//ajouter TransformGroup a BranchGroup
					objRoot.addChild(objRotate[notab_color_cube]);
		
					notab_color_cube++;
				}

		
		return objRoot;
	}
	
	public void init()
	{
		setLayout(new BorderLayout());
		
		/** Panel droit **/
		
		JPanel panelEast = new JPanel();
		panelEast.setSize(100, 100);
		panelEast.setLayout(new GridLayout(8,1));
		
		String nom[] = new String[numberLineCube*numberLineCube*numberLineCube];
		
		for(int iBoucle=0; iBoucle<numberLineCube*numberLineCube*numberLineCube; iBoucle++)
		{
			nom[iBoucle] = Integer.toString(iBoucle+1);
		}
		
		//Creer un JComboBox pour que les utilisateurs puissent choisir un cube selon l'id
		final JComboBox cb_choix_cube = new JComboBox(nom);
		cb_choix_cube.insertItemAt("Sélectionner numéro de cube", 0);
		cb_choix_cube.setSelectedIndex(0);
		panelEast.add(cb_choix_cube);
		
		//Creer JRadioButton pour choisir le plan
		ButtonGroup jbg = new ButtonGroup();
		JRadioButton btn_x = new JRadioButton("X");
		JRadioButton btn_y = new JRadioButton("Y");
		JRadioButton btn_z = new JRadioButton("Z");
		
		jbg.add(btn_x);
		jbg.add(btn_y);
		jbg.add(btn_z);
		
		JPanel panelRadioButton = new JPanel();
		
		panelRadioButton.add(btn_x);
		panelRadioButton.add(btn_y);
		panelRadioButton.add(btn_z);
		
		panelEast.add(panelRadioButton);
		
		add("East", panelEast);
		
		/** Panel bas **/
		
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
		
		/** Canvas central **/
		
		final BoundingSphere bounds = new BoundingSphere(new Point3d(0.0,0.0,0.0), 10.0f);
		
		//Creer Universe de 3D
		GraphicsConfiguration config = SimpleUniverse.getPreferredConfiguration();
		Canvas3D canvas3D = new Canvas3D(config); //Creer un canvas
		canvas3D.setSize(800, 800);
		add("Center", canvas3D);
		
		BranchGroup scene = createSceneGraph();
		
		scene.compile();
		
		SimpleUniverse u = new SimpleUniverse(canvas3D); //creer un universe
		
		u.getViewingPlatform().setNominalViewingTransform();
		
		u.addBranchGraph(scene);
		
		
		/** Evènements JComboBox **/
		
		// Sélection d'un cube dans la liste
		cb_choix_cube.addItemListener(new ItemListener(){
			public void itemStateChanged(ItemEvent e)
			{
				//Si le choix de cube change
				if(e.getStateChange() == ItemEvent.SELECTED)
				{
					// Retirer de la liste l'item par défaut
					cb_choix_cube.removeItemAt(0);
					
					// Marche car le nom affiché est un numéro
					int IdNom = Integer.parseInt(e.getItem().toString());
					
					//Afficher les infos correspondant au cube
					Info info = tab_color_cube[IdNom-1].getInfo();
					textIdStructure.setText(Integer.toString(info.getIdStructure()));
					textNom.setText(info.getNom());
					textDescription.setText(info.getDescription());
					
					float coordonnee[] = tab_color_cube[IdNom-1].getXYZ();
										
					Transform3D rotate = new Transform3D();				
					
					Vector3f v3f;
					int timeChange = 50; //La periode pour changer le point centre (ms)
					//La premiere fois, il ne suffit pas de mettre le cube en position originale, parce qu'il n'y a aucun cube au debut
					if(first_cube == true)
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
						MouseRotate mr =  (MouseRotate)objRotate[IdNom-1].getChild(0);
						mr.setSchedulingBounds(bounds);												
						
						//Apres la premiere fois, on affect FALSE a la variable 'first_cube'
						first_cube = false;
					}
					else
					{ // Si ce n'est pas la première fois qu'un cube est sélectionné
						v3f = new Vector3f(0.25f*Xpre, 0.25f*Ypre, 0.25f*Zpre);
						rotate.setTranslation(v3f);
						objRotate[NomPre-1].setTransform(rotate);
						
						//Configurer le cube precedent pour qu'il ne tourne plus
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
						
						//Configurer le nouveau cube à faire tourner
						mr =  (MouseRotate)objRotate[IdNom-1].getChild(0);
						mr.setSchedulingBounds(bounds);
					}
				}
			}
		});
		
		// Choix de l'axe X
		btn_x.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e)
			{
				// Si ce un cube a déjà été choisi
				if(NomPre != 0)
				{
					float coordonnee[] = tab_color_cube[NomPre-1].getXYZ();
					
					Vector4d v4d = new Vector4d(-1.0, 0.0, 0.0, -0.25*coordonnee[1]);
					
					ModelClip mcTemp = (ModelClip)objRotate[NomPre-1].getChild(1);
					
					mcTemp.setPlane(0, v4d);
					mcTemp.setEnable(0, true);
					mcTemp.setInfluencingBounds(bounds);
				}
			}
		});
		
		// Choix de l'axe Y
		btn_y.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e)
			{
				if(NomPre != 0)
				{
					float coordonnee[] = tab_color_cube[NomPre-1].getXYZ();
					
					Vector4d v4d = new Vector4d(0.0, -1.0, 0.0, 0.25*coordonnee[1]);
					System.out.println("Choix de l'axe Y - 4e var v4d = "+0.25*coordonnee[1]);
					
					ModelClip mcTemp = (ModelClip)objRotate[NomPre-1].getChild(1);
					
					mcTemp.setPlane(1, v4d);
					mcTemp.setEnable(1, true);
					
					mcTemp.setInfluencingBounds(bounds);
				}
			}
		});
		
		// Choix de l'axe Z
		btn_z.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e)
			{
				if(NomPre != 0)
				{
					float coordonnee[] = tab_color_cube[NomPre-1].getXYZ();
					
					Vector4d v4d = new Vector4d(0.0, 0.0, -1.0, 0.25*coordonnee[1]);
					System.out.println("Choix de l'axe Z - 4e var v4d = "+0.25*coordonnee[1]);
					
					ModelClip mcTemp = (ModelClip)objRotate[NomPre-1].getChild(1);
					
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
		
		System.out.println("Lancement de l'application");
		new MainFrame(new test1(), 1024, 1024);
	}

}
