$modelname jas_colonist/colonist.mdl
$cdmaterials models/jastiansummer/colonist

$pushd "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/Male_sdk"

//start eye/face data
$eyeposition 0 0 70

// head controllers
$attachment "eyes" "ValveBiped.Bip01_Head1" 0.043 -4.2197 67.5554 absolute
$attachment "mouth" "ValveBiped.Bip01_Head1" 1.00 -6.30 0.00 rotate 0 -80 -90
$attachment "chest" "ValveBiped.Bip01_Spine2" 5.00 4.00 -0.00 rotate 0.00 90.00 90.00
$attachment "forward" "ValveBiped.Bip01_Head1" 0.00 0.00 0.00 rotate 0.00 -80.00 -90.00
$attachment "anim_attachment_RH" "ValveBiped.Bip01_R_Hand" 0.00 0.00 0.00 rotate -90.00 -90.00 0.00
$attachment "anim_attachment_LH" "ValveBiped.Bip01_L_Hand" 0.00 0.00 0.00 rotate -90.00 -90.00 0.00
$attachment "anim_attachment_head" "ValveBiped.Bip01_Head1" 0.00 0.00 0.00 rotate -90.00 -90.00 0.00
$attachment "back" "ValveBiped.Bip01_Spine4" 0.00 -2.50 0.00 rotate 0.00 0.00 0.00
$includemodel "humans/male_shared.mdl"
$includemodel "humans/male_ss.mdl"
$includemodel "humans/male_gestures.mdl"
$includemodel "humans/male_postures.mdl"

$model male_06 "male_06_reference.smd"{
	eyeball righteye "ValveBiped.Bip01_Head1" -1.2711 -4.2197 67.5593 "eyeball_r" 1 4 "pupil_r" 0.63
	eyeball lefteye "ValveBiped.Bip01_Head1" 1.3572 -4.2197 67.5514 "eyeball_l" 1 -4 "pupil_l" 0.63

	eyelid  upper_right "male_06_expressions" lowerer 1 -0.2621 neutral 0 0.1287 raiser 2 0.2467 split 0.1 eyeball righteye
	eyelid  lower_right "male_06_expressions" lowerer 3 -0.3409 neutral 0 -0.2156 raiser 4 -0.0736 split 0.1 eyeball righteye
	eyelid  upper_left "male_06_expressions" lowerer 1 -0.2621 neutral 0 0.1287 raiser 2 0.2467 split -0.1 eyeball lefteye
	eyelid  lower_left "male_06_expressions" lowerer 3 -0.3409 neutral 0 -0.2156 raiser 4 -0.0736 split -0.1 eyeball lefteye

	mouth 0 "mouth" "ValveBiped.Bip01_Head1" 0 1 0     // mouth illumination

	flexfile "male_06_expressions" {
		$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/standardflex_xsi.qci"
	}

	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/facerules_xsi.qci"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/bodyrules_xsi.qci"
}

//end eye/face data	

$texturegroup skinfamilies
{
	{ citizen_sheet }
	{ citizen_sheet_worker }
	{ citizen_sheet_soldier }
}


$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/standardhierarchy.qci"
$alwayscollapse "male_06"
$alwayscollapse "XSISceneRoot"


$proceduralbones "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2mp/modelsrc/humans_sdk/male.vrd"


$pushd "../male_animations_sdk"
$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/male_animations_sdk/male_shared_XSI_sdk.qci"
$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/male_animations_sdk/body_poses_lean.qci"
//$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/male_animations_sdk/WeaponAnims_shared_sdk.qci"
$popd


$lod 10 
{
	replacemodel "Male_06_reference" "Male_06_LOD_1" 
}

$lod 20 
{
	replacemodel "Male_06_reference" "Male_06_LOD_2"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/removehands.qci"
	
}

$lod 35 
{
	replacemodel "Male_06_reference" "Male_06_LOD_3"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/lowesthumanskeleton.qci"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/lowesthumannohelpers.qci"
	nofacial
}

$lod 50 
{
	replacemodel "Male_06_reference" "Male_06_LOD_4"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/lowesthumanskeleton.qci"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/lowesthumannohelpers.qci"
	nofacial
}

$lod 90 
{
	replacemodel "Male_06_reference" "Male_06_LOD_5"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/lowesthumanskeleton.qci"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/lowesthumannohelpers.qci"
	nofacial
}

$shadowlod
{
	replacemodel "Male_06_reference" "Male_06_LOD_shadow" 
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/lowesthumanskeleton.qci"
	$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/lowesthumannohelpers.qci"
	nofacial
}

$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/Male_sdk/hitbox.qci"
$include "J:/Program Files/Steam/steamapps/nightgunner5/sourcesdk_content/hl2/modelsrc/humans_sdk/Male_sdk/ragdoll.qci"