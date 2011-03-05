$cd "J:\JastianSummer\modelsrc\jas_scientist"
$cdmaterials "models/jastiansummer/colonist"
$cdmaterials "models/jastiansummer/scientist"
$modelname "jas_scientist/chau.mdl"
$model "kleiner" "kleiner_reference.smd" {
	eyeball righteye ValveBiped.Bip01_Head1 -1.320 -2.950 67.580 eyeball_r 1.000  4.000 kleiner_sheet 0.630
	eyeball lefteye ValveBiped.Bip01_Head1 1.520 -2.950 67.580 eyeball_l 1.000  -4.000 kleiner_sheet 0.630
	eyelid  upper_right "mdldecompiler_expressions.vta" lowerer 1 -0.280000 neutral 1 0.170000 raiser 1 0.280000 split 0.1 eyeball righteye
	eyelid  lower_right "mdldecompiler_expressions.vta" lowerer 2 -0.360000 neutral 2 -0.270000 raiser 2 -0.100000  split 0.1 eyeball righteye
	eyelid  upper_left "mdldecompiler_expressions.vta" lowerer 3 -0.250000 neutral 3 0.180000 raiser 3 0.300000 split -0.1 eyeball lefteye
	eyelid  lower_left "mdldecompiler_expressions.vta" lowerer 4 -0.350000 neutral 4 -0.230000 raiser 4 -0.080000  split -0.1 eyeball lefteye
     mouth 0 "mouth"  ValveBiped.Bip01_Head1 0.000 1.000 0.000

// ../../../Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/male_sdk/male_06_expressions
	flexfile "mdldecompiler_expressions" {
		$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/standardflex_xsi.qci"
	}

	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/facerules_xsi.qci"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/bodyrules_xsi.qci"
}
$lod 7
 {
  replacemodel "kleiner_reference" "lod1_kleiner_reference"
}
$lod 15
 {
  replacemodel "kleiner_reference" "lod2_kleiner_reference"
}
$lod 30
 {
  replacemodel "kleiner_reference" "lod3_kleiner_reference"
}
$lod 45
 {
  replacemodel "kleiner_reference" "lod4_kleiner_reference"
}
$lod 70
 {
  replacemodel "kleiner_reference" "lod5_kleiner_reference"
}
$shadowlod
{
  replacemodel "kleiner_reference" "lod6_kleiner_reference"
}
$hboxset "default"
$hbox 1 "ValveBiped.Bip01_Head1" -1.250  -6.500  -3.190  8.250  3.500  3.310
$hbox 4 "ValveBiped.Bip01_L_UpperArm" 0.000  -2.750  -2.750  12.510  1.750  2.250
$hbox 4 "ValveBiped.Bip01_L_Forearm" 0.000  -2.190  -2.380  13.000  1.810  1.620
$hbox 4 "ValveBiped.Bip01_L_Hand" 0.060  -2.000  -1.500  4.060  1.000  2.500
$hbox 5 "ValveBiped.Bip01_R_UpperArm" 0.000  -3.000  -2.250  12.390  2.000  2.750
$hbox 5 "ValveBiped.Bip01_R_Forearm" -0.500  -2.200  -1.550  12.500  1.800  2.450
$hbox 5 "ValveBiped.Bip01_R_Hand" 0.060  -2.000  -2.500  4.060  1.000  1.500
$hbox 6 "ValveBiped.Bip01_L_Thigh" 0.000  -3.750  -3.250  17.850  3.750  3.250
$hbox 6 "ValveBiped.Bip01_L_Calf" 0.000  -3.510  -3.280  15.640  3.490  2.720
$hbox 6 "ValveBiped.Bip01_L_Foot" -1.070  -2.000  -2.840  5.040  5.000  2.160
$hbox 6 "ValveBiped.Bip01_L_Toe0" -0.500  -3.000  -2.190  2.500  0.000  2.460
$hbox 7 "ValveBiped.Bip01_R_Thigh" 0.000  -3.750  -3.250  17.850  3.750  3.250
$hbox 7 "ValveBiped.Bip01_R_Calf" 0.000  -3.510  -2.820  15.640  3.490  3.180
$hbox 7 "ValveBiped.Bip01_R_Foot" -1.060  -2.010  -2.280  5.050  4.990  2.720
$hbox 7 "ValveBiped.Bip01_R_Toe0" -0.500  -3.000  -2.600  2.500  0.000  2.100
$hbox 3 "ValveBiped.Bip01_Pelvis" -7.500  -5.500  -6.000  7.500  8.500  5.000
$hbox 2 "ValveBiped.Bip01_Spine2" -2.500  -2.500  -7.000  14.500  7.500  7.000
// Model uses material "kleiner_sheet.vmt"
// Model uses material "glass2.vmt"
// Model uses material "walter_face.vmt"
// Model uses material "mouth.vmt"
// Model uses material "eyeball_l.vmt"
// Model uses material "eyeball_r.vmt"
// Model uses material "glassesfront_walter.vmt"
// Model uses material "glassesside_walter.vmt"
$renamematerial walter_face chau_face
$attachment "eyes" "ValveBiped.Bip01_Head1" 3.56 -3.16 -0.10 rotate 0.00 -80.10 -90.00
$attachment "lefteye" "ValveBiped.Bip01_Head1" 3.58 -3.50 -1.55 rotate 0.00 -80.00 -90.00
$attachment "righteye" "ValveBiped.Bip01_Head1" 3.58 -3.50 1.30 rotate 0.00 -80.00 -90.00
$attachment "nose" "ValveBiped.Bip01_Head1" 2.70 -5.50 0.00 rotate 0.00 -80.00 -90.00
$attachment "mouth" "ValveBiped.Bip01_Head1" 1.00 -5.20 0.00 rotate 0.00 -80.00 -90.00
$attachment "tie" "ValveBiped.Bip01_Spine4" 1.50 6.20 0.00 rotate -0.00 90.00 90.00
$attachment "pen" "ValveBiped.Bip01_Spine4" -3.50 8.20 4.80 rotate -0.00 90.00 90.00
$attachment "chest" "ValveBiped.Bip01_Spine4" -4.00 4.00 0.00 rotate -0.00 83.00 90.00
$attachment "hips" "ValveBiped.Bip01_Pelvis" 0.00 -0.00 0.00 rotate -90.00 -90.00 0.00
$attachment "lefthand" "ValveBiped.Bip01_L_Hand" 3.50 -0.50 -0.00 rotate -0.00 0.00 -0.00
$attachment "righthand" "ValveBiped.Bip01_R_Hand" 3.50 -0.50 0.00 rotate 0.00 0.00 0.00
$attachment "attach_lShoulderAim" "ValveBiped.Bip01_Spine" 0.08 -5.11 2.72 rotate -90.00 -85.06 0.00
$attachment "attach_rShoulderAim" "ValveBiped.Bip01_Spine" 0.08 -5.11 -2.39 rotate -90.00 -85.06 0.00
$attachment "forward" "ValveBiped.forward" -0.00 -0.00 -0.00 rotate 0.00 0.00 -0.00
$attachment "anim_attachment_RH" "ValveBiped.Anim_Attachment_RH" -0.00 0.00 -0.00 rotate -90.00 -90.00 0.00
$attachment "anim_attachment_LH" "ValveBiped.Anim_Attachment_LH" 0.00 0.00 -0.00 rotate -90.00 -90.00 0.00
$attachment "anim_attachment_head" "ValveBiped.Bip01_Head1" -0.00 -0.00 0.00 rotate -90.00 -90.00 0.00
$includemodel "Kleiner_animations.mdl"
$includemodel "humans/male_shared.mdl"
$includemodel "Kleiner_postures.mdl"
$includemodel "Kleiner_gestures.mdl"
$surfaceprop "flesh"
$eyeposition 0.000 0.000 70.000
$illumposition 0.258 -1.113 35.329
$sequence ragdoll "ragdoll" ACT_DIERAGDOLL 1 fps 30.00
$ikchain rhand ValveBiped.Bip01_R_Hand knee  0.707 0.707 0.000
$ikchain lhand ValveBiped.Bip01_L_Hand knee  0.707 0.707 0.000
$ikchain rfoot ValveBiped.Bip01_R_Foot knee  0.707 -0.707 0.000
$ikchain lfoot ValveBiped.Bip01_L_Foot knee  0.707 -0.707 0.000
$collisionjoints "phymodel.smd" {

	$mass 90.0
	$inertia 10.00
	$damping 0.01
	$rotdamping 1.50
	$rootbone "valvebiped.bip01_pelvis"
	$jointmerge "ValveBiped.Bip01_Pelvis" "ValveBiped.Bip01_Spine1"

	$jointconstrain "valvebiped.bip01_spine2" x limit -48.00 48.00 0.00
	$jointconstrain "valvebiped.bip01_spine2" y limit -25.00 25.00 0.00
	$jointconstrain "valvebiped.bip01_spine2" z limit -25.00 50.00 0.00

	$jointconstrain "valvebiped.bip01_r_upperarm" x limit -39.00 39.00 0.00
	$jointconstrain "valvebiped.bip01_r_upperarm" y limit -79.00 95.00 0.00
	$jointconstrain "valvebiped.bip01_r_upperarm" z limit -93.00 23.00 0.00

	$jointconstrain "valvebiped.bip01_l_upperarm" x limit -30.00 30.00 0.00
	$jointconstrain "valvebiped.bip01_l_upperarm" y limit -95.00 84.00 0.00
	$jointconstrain "valvebiped.bip01_l_upperarm" z limit -86.00 26.00 0.00

	$jointconstrain "valvebiped.bip01_l_forearm" x limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_l_forearm" y limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_l_forearm" z limit -149.00 4.00 0.00

	$jointconstrain "valvebiped.bip01_l_hand" x limit -37.00 37.00 0.00
	$jointconstrain "valvebiped.bip01_l_hand" y limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_l_hand" z limit -57.00 59.00 0.00

	$jointconstrain "valvebiped.bip01_r_forearm" x limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_r_forearm" y limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_r_forearm" z limit -149.00 4.00 0.00

	$jointconstrain "valvebiped.bip01_r_hand" x limit -60.00 60.00 0.00
	$jointconstrain "valvebiped.bip01_r_hand" y limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_r_hand" z limit -57.00 70.00 0.00

	$jointconstrain "valvebiped.bip01_r_thigh" x limit -12.00 12.00 0.00
	$jointconstrain "valvebiped.bip01_r_thigh" y limit -8.00 75.00 0.00
	$jointconstrain "valvebiped.bip01_r_thigh" z limit -97.00 32.00 0.00

	$jointconstrain "valvebiped.bip01_r_calf" x limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_r_calf" y limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_r_calf" z limit -12.00 126.00 0.00

	$jointconstrain "valvebiped.bip01_head1" x limit -20.00 20.00 0.00
	$jointconstrain "valvebiped.bip01_head1" y limit -25.00 25.00 0.00
	$jointconstrain "valvebiped.bip01_head1" z limit -13.00 30.00 0.00

	$jointconstrain "valvebiped.bip01_l_thigh" x limit -12.00 12.00 0.00
	$jointconstrain "valvebiped.bip01_l_thigh" y limit -73.00 6.00 0.00
	$jointconstrain "valvebiped.bip01_l_thigh" z limit -93.00 30.00 0.00

	$jointconstrain "valvebiped.bip01_l_calf" x limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_l_calf" y limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_l_calf" z limit -8.00 126.00 0.00

	$jointconstrain "valvebiped.bip01_l_foot" x limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_l_foot" y limit -19.00 19.00 0.00
	$jointconstrain "valvebiped.bip01_l_foot" z limit -15.00 35.00 0.00

	$jointconstrain "valvebiped.bip01_r_foot" x limit 0.00 0.00 0.00
	$jointconstrain "valvebiped.bip01_r_foot" y limit -25.00 6.00 0.00
	$jointconstrain "valvebiped.bip01_r_foot" z limit -15.00 35.00 0.00
	$animatedfriction 1.000 400.000 0.500 0.300 0.000
}
